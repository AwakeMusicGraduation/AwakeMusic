#include "server.h"
#include <QtNetwork>
#include <QTcpServer>
#include <QPushButton>
#include <QGridLayout>

Server::Server(QWidget *parent)
    : ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tcpServer = new QTcpServer();

    blockSize = 0;
    bytesToWrite = 0;
    payloadSize = 32 * 1024;
    totalBytes = 0;
    //发送推荐列表
    //sendPlaylist();

    qDebug() << "构造函数赋值成功！";

    tcpServer->listen(QHostAddress::Any,6668);
    // tcpServer->listen( QHostAddress::LocalHost, 6667);
    connect(tcpServer,&QTcpServer::newConnection,this,&Server::acceptConnection);
    //调用了qtcpserver类的listen（）函数来监听到来的连接，这里监听了本地主机的6666端口，这样可以实现客户端和服务端在同一台计算机上运行并通信，也可以换成其他地址。
    //一旦有客户端连接到服务器就会发射newConnection（）信号。

    //开始监听文件传送套接字
    fileServer = new QTcpServer();
    fileConnection = new QTcpSocket();
    fileServer->listen(QHostAddress::Any, 8888);
    connect(fileServer, &QTcpServer::newConnection,this, &Server::acceptFileConnection);

    //开始监听传输分类套接字
    singerServer = new QTcpServer();
    singerConnection = new QTcpSocket();
    singerServer->listen(QHostAddress::Any, 2222);
    connect(singerServer, &QTcpServer::newConnection, this, &Server::acceptSingerConnection);
}


Server::~Server()
{}


void Server::acceptConnection()
{
    ui->label->setText("连接成功");
    qDebug() << "connect success";
    emit sendToMaiWindow();
    clientConnection = tcpServer->nextPendingConnection();
    //sendPlaylist();
    connect(clientConnection, &QIODevice::readyRead,this,&Server::receiveData);
    connect(clientConnection,QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),this,&Server::displayError);
}

void Server::acceptFileConnection()
{
    ui->label->setText("发送推荐列表");
    fileConnection = fileServer->nextPendingConnection();
    sendPlaylist();
}

void Server::acceptSingerConnection()
{
    ui->label->setText("发送歌手分类");
    singerConnection = singerServer->nextPendingConnection();
    connect(singerConnection, &QIODevice::readyRead,this,&Server::receiveCategoryData);
}

void Server::receiveCategoryData()
{
    QDataStream in(singerConnection);
    //设置数据流版本，这里要和服务器端相同。
    in.setVersion(QDataStream::Qt_5_10);

    blockSize = 0;
    if(blockSize==0){
        //判断接收数据是否大于两字节，也就是文件的大小信息所占的空间
        //如果时则保存到blockSize变量中，否则直接返回，继续接受数据
        if(singerConnection->bytesAvailable() < 2*(int)sizeof(quint32)) return;
        in >> blockSize;
    }
    //如果没有得到全部的数据，则返回，继续接收数据
    if(singerConnection->bytesAvailable()<blockSize) return;
    //将接收到的数据存放到变量中
    in >> data1 >> data2;
    qDebug()<< data1 << data2;
    if(data1 == "singer"){
        sendSinger();
    }
    if(data1 == "album"){
        sendAlbum();
    }
    if(data1 == "music"){
        sendMusic();
    }

    blockSize = 0;
}

void Server::sendSinger()
{
    musicBroker = new MusicBroker();
    std::vector<QString> singers;
    singers = musicBroker->findSingers(data2);
    identity = "singer";
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);

    out.setVersion(QDataStream::Qt_5_10);
    qint32 total = 0;
    total += identity.size();
    for(auto l:singers)
    {
        total += l.size();

    }
    qDebug() << total;

    out << total;
    out << identity;
    qDebug() << block.size();

    for(auto l:singers){
        out << l;
        qDebug() << l;
    }
    qDebug() << block.size();
    singerConnection->write(block);
    block.resize(0);
    singerConnection->disconnectFromHost();
    ui->label->setText("歌手传输成功");

}

void Server::sendAlbum()
{
    musicBroker = new MusicBroker();
    std::vector<QString> albums;
    albums = musicBroker->findAlbums(data2);
    identity = "album";
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);

    out.setVersion(QDataStream::Qt_5_10);
    qint32 total = 0;
    total += identity.size();
    for(auto l:albums)
    {
        total += l.size();
    }
    out << total;
    out << identity;
    for(auto l:albums){
        out << l;
    }
    singerConnection->write(block);
    block.resize(0);
    singerConnection->disconnectFromHost();
    ui->label->setText("专辑传输成功");
}

void Server::sendMusic()
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);

    out.setVersion(QDataStream::Qt_5_10);
    std::vector<QString> m, musics;
    qint32 total = 0;
    identity = "music";
    total += identity.size();
    //m = new Music();
    musicBroker = new MusicBroker();
    m = musicBroker->findMusics(data2);
    musics = musicBroker->findSpells(m);
    for(auto l:musics){
        total += l.size();
    }
    out << total << identity;

    for(auto l:musics){
        out << l;
    }
    singerConnection->write(block);
    block.resize(0);
    singerConnection->disconnectFromHost();
    ui->label->setText("发送歌曲成功");
}

void Server::receiveData()
{
    QDataStream in(clientConnection);
    //设置数据流版本，这里要和服务器端相同。
    in.setVersion(QDataStream::Qt_5_10);

    if(blockSize==0){
        //判断接收数据是否大于两字节，也就是文件的大小信息所占的空间
        //如果时则保存到blockSize变量中，否则直接返回，继续接受数据
        if(clientConnection->bytesAvailable() < (int)sizeof(quint32)) return;
        in >> blockSize;
    }
    //如果没有得到全部的数据，则返回，继续接收数据
    if(clientConnection->bytesAvailable()<blockSize) return;
    //将接收到的数据存放到变量中
    in >> data;
    qDebug()<< data << "what";

    if(data == "user")
    {
        in >> name;
        in >> password;
        sendLoginMessage();
        qDebug() << "登录";
        ui->label->setText("用户登录");
    }
    else if(data == "register")
    {
        in >> name;
        in >> password;
        sendRegisterMessage();
        qDebug() << "注册";
        ui->label->setText("注册用户");
    }
    else if(data == "creatlist")
    {
        in >> user;
        in >> list;
        sendCreateSongsList();
        ui->label->setText("创建歌曲列表");
    }
    else if(data == "deletelist")
    {
        in >> user;
        in >> list;
        sendDeleteSongsList();
        ui->label->setText("删除列表");
    }
    else if(data == "addmusictolist")
    {
        QString list,name,singer,album;
        in >> list >> name >> singer >> album;
        sendAddMusicToList(list,name,singer,album);
    }

    else if(data == "loadmusicfromlist")
    {
        QString list;
        in >> list;
        qDebug() << list;
        sendMusicFromList(list);
    }
    else if(data == "picture")
    {
        in >> name;
        sendPicture();
    }
    else if(data == "musictips")
    {
        sendMusicTips();
    }
    else if(data == "tip")
    {
        QString tip;
        in >> tip;
        sendTipMusics(tip);
    }
    else{

        if(!data.isNull())
        {
            sendMessage();
        }
    }

    blockSize = 0;
    //显示接收到的数据
}


//登陆时验证信息是否正确
void Server::sendLoginMessage()
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_10);
    musicBroker = new MusicBroker();
    std::vector<QString> m = musicBroker->findUser(name,password);
    qint32 total = 0;
    for(auto l:m)
    {
        total += l.size();
    }
    out << qint32(total);
    for(auto l:m)
    {
        out << l;
        qDebug() << l << "音乐列表名";
    }
    clientConnection->write(block);
    qDebug() << "传输登录信息";
    clientConnection->disconnectFromHost();
    //connect(clientConnection, &QAbstractSocket::disconnected,
    //        clientConnection, &QObject::deleteLater);
}

void Server::sendRegisterMessage()
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_10);
    musicBroker = new MusicBroker();
    QString m = musicBroker->findRegisterInfo(name,password);
    out << qint32(m.size());
    out << m;
    clientConnection->write(block);
    clientConnection->disconnectFromHost();
    //connect(clientConnection, &QAbstractSocket::disconnected,
    //        clientConnection, &QObject::deleteLater);
}

void Server::sendCreateSongsList()
{
    musicBroker = new MusicBroker();
    QString message = musicBroker->createSongsList(user,list);
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_10);
    //QString message = "创建列表成功";
    out << qint32(message.size());
    out << message;
    clientConnection->write(block);
    clientConnection->disconnectFromHost();
}

void Server::sendDeleteSongsList()
{
    musicBroker = new MusicBroker();
    QString message = musicBroker->deleteSongsList(user,list);
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_10);
    //QString message = "删除列表成功";
    out << qint32(message.size());
    out << message;
    clientConnection->write(block);
    clientConnection->disconnectFromHost();
}

void Server::sendAddMusicToList(QString list,QString name,QString singer,QString album)
{
    musicBroker = new MusicBroker();
    QString message = musicBroker->addMusicToList(list,name,singer,album);
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_10);
    out << qint32(message.size());
    out << message;
    clientConnection->write(block);
    clientConnection->disconnectFromHost();
}

void Server::sendMusicFromList(QString list)
{
    qDebug() << "准备从数据库查找音乐";
    musicBroker = new MusicBroker();
    std::vector<QString> allmusics = musicBroker->findMusicFromList(list);
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_10);
    int total = 0;
    for(auto l:allmusics)
    {
        total += l.size();
    }
    out << qint32(total);
    for(auto l:allmusics)
    {
        out << l;
        qDebug() << l << "musicfromlist";
    }
    clientConnection->write(block);
    clientConnection->close();
}

void Server::sendMessage()
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    QBuffer buffer;

    out.setVersion(QDataStream::Qt_5_10);
    //m = new Music();
    musicBroker = new MusicBroker();
    m = musicBroker->findByName(data);
    if(m == nullptr){
        QString error = "亲，我们暂时没有权限哟！";
        qDebug() << error;
        out << qint32(error.size());
        out << error;
        clientConnection->write(block);
        ui->label->setText("歌曲不存在！");
    }
    else{
        a = m->getInformation(a);
        delete m;
        m = nullptr;
        message4 = musicBroker->findSpell(data);//拼音
        qDebug() << "徐露";
        qDebug() << a[0] << a[1] << a[2] << a[3];
        qDebug() << message4;
        message1 = a.at(0);//歌名
        message2 = a.at(1);//歌手
        message3 = a.at(2);//专辑


        out << quint32(message1.size() +message2.size()+message3.size() +message4.size());
        out << message1 << message4 << message2 << message3;


        connect(clientConnection, &QAbstractSocket::disconnected,
                clientConnection, &QObject::deleteLater);

        clientConnection->write(block);

        block.resize(0);
    }
    clientConnection->disconnectFromHost();
    ui->label->setText("发送歌曲成功");
    a.clear();
}

void Server::sendPicture()
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    QBuffer buffer;

    out.setVersion(QDataStream::Qt_5_10);
    musicBroker = new MusicBroker();
    m = musicBroker->findByName(name);
    if(m == nullptr){
        QString error = "亲，我们暂时没有权限哟！";
        qDebug() << error;
        out << qint32(error.size());
        out << error;
        clientConnection->write(block);
        ui->label->setText("歌曲不存在！");
    }
    else{
        a = m->getInformation(a);
        delete m;
        m = nullptr;
        albumFilePath = a.at(3) + ".JPG";
        qDebug() << albumFilePath;
        QPixmap(albumFilePath).save(&buffer,"JPG");

        out << quint32(buffer.data().size());
        block.append(buffer.data());


        connect(clientConnection, &QAbstractSocket::disconnected,
                clientConnection, &QObject::deleteLater);

        clientConnection->write(block);

        block.resize(0);

        clientConnection->reset();
        out.device()->seek(0);

        fileName = a[4];
        localFile = new QFile(fileName);

        qDebug() << localFile->exists();
        if(!localFile->open(QFile::ReadOnly)){
            qDebug() << "client:open file error";
        }
        else{
            qDebug() << "start to write";
            totalBytes = localFile->size();
            QString currenFileName = fileName.right(fileName.size()-fileName.lastIndexOf('/')-1);
            //        out << qint32(0) << qint32(0) << currenFileName;
            qDebug() << currenFileName.size();
            totalBytes += block.size();
            qDebug() << totalBytes;

            //        out.device()->seek(0);
            out << totalBytes << qint32((block.size()-sizeof(qint32)*2)) << currenFileName;
            bytesToWrite = totalBytes-clientConnection->write(block);
            qDebug() << bytesToWrite;
            block.resize(0);

            while(bytesToWrite){
                block = localFile->read(qMin(bytesToWrite,payloadSize));
                qDebug() << "read";
                bytesToWrite -= (int)clientConnection->write(block);
                block.resize(0);
                qDebug() << "传输歌词成功";
            }
            localFile->close();
        }
    }
    a.clear();
    clientConnection->disconnectFromHost();
}


void Server::sendMusicTips()
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_10);
    std::vector<QString> albums;
    std::vector<QString> picturepaths;
    QString album;
    QString path;

    musicBroker = new MusicBroker();
    albums = musicBroker->findAlbums2();
    picturepaths = musicBroker->findPicturesForAlbum(albums);
    qint32 total = 0;
    for(int i = 0; i < albums.size() ; i++)
    {   QByteArray block2;
        qDebug() << "正首页";
        QBuffer buffer;
        album = albums.at(i);
        qint32 m = album.size();
        total += album.size();
        total += m;
        qDebug() << total;
        path = picturepaths.at(i) + ".JPG";
        QPixmap(path).save(&buffer,"JPG");
        total += buffer.data().size();
        block2.append(buffer.data());
        total += block.size();
        //block2.clear();
        qDebug() << total;
        qDebug() << album << path <<"this is tips";

    }
    //total += sizeof(qint32)*16;
    out << total;
    //clientConnection->write(block);
    for(int i = 0; i < albums.size() ; i++)
    {
        qDebug() << albums.size() << picturepaths.size() << "总数";
        qDebug() << "正在传输专辑和图片到首页";
        QBuffer buffer;
        //qDebug() << buffer.data().size() << "this is size";
        album = albums.at(i);
        path = picturepaths.at(i) + ".JPG";
        //path = "/root/薛之谦/yiwai.JPG";
        QPixmap(path).save(&buffer,"JPG");
        qDebug() << album << path <<"this is tips";
        out << qint32(buffer.data().size()) << qint32(album.size()) << album;
        block.append(buffer.data());
        //buffer.seek(0);
        clientConnection->write(block);
        block.resize(0);
        clientConnection->reset();
        out.device()->seek(0);

     }
    //clientConnection->write(block);
    albums.clear();
    picturepaths.clear();
    clientConnection->disconnectFromHost();

}

void Server::sendTipMusics(QString tip)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_10);
    musicBroker = new MusicBroker();
    std::vector<QString> musics = musicBroker->findMusicsForTip(tip);
    qint32 total = 0;
    for(auto l:musics)
    {
        total += l.size();
    }
    out << total;
    for(auto l : musics)
    {
        out << l;
    }
    //musics.clear();
    clientConnection->write(block);
    clientConnection->disconnectFromHost();

}

void Server::sendPlaylist()
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);

    out.setVersion(QDataStream::Qt_5_10);
    lyricFile = new QFile("/root/music.json");
    if(!lyricFile->open(QIODevice::ReadOnly)){
        qDebug() << "could't open projects json";
        return;
    }

    qDebug() << "start to write";
    totalBytes = lyricFile->size();
    qDebug() << totalBytes;
    //QDataStream sendOut(&outBlock,QIODevice::WriteOnly);
    // sendOut.setVersion(QDataStream::Qt_5_10);
    fileName = "music.json";
    QString currenFileName = fileName.right(fileName.size()-fileName.lastIndexOf('/')-1);
    out << qint32(0) << qint32(0) << currenFileName;
    qDebug() << currenFileName << "当前文件名的大小" << currenFileName.size();
    totalBytes += block.size();
    qDebug() << totalBytes;

    //sendOut << qint64(0) << qint64(0) << currenFileName;
    out.device()->seek(0);
    out << totalBytes << qint32((block.size()-sizeof(qint32)*2));
    //totalBytes += outBlock.size();
    //outBlock.resize(0);
    bytesToWrite = totalBytes-fileConnection->write(block);
    qDebug() << bytesToWrite;
    block.resize(0);

    //connect(clientConnection,&QIODevice::readyRead,this,&Server::update);
    while(bytesToWrite){
        block = lyricFile->read(qMin(bytesToWrite,payloadSize));
        //qDebug() << s;
        qDebug() << "read";
        //tcpSocket->write(outBlock);
        //qDebug() << outBlock;
        bytesToWrite -= (int)fileConnection->write(block);
        block.resize(0);
    }

    lyricFile->close();
    fileConnection->disconnectFromHost();
    ui->label->setText("发送推荐列表成功");
}



void Server::displayError(QAbstractSocket::SocketError socketError)
{
    Q_UNUSED(socketError)
    qDebug()<<clientConnection->errorString();
    clientConnection->close();
}
