#ifndef CLIENT_H
#define CLIENT_H

#include <QAbstractSocket>
#include <QDialog>
#include <QBuffer>
#include <QFile>
#include <QTextEdit>

QT_BEGIN_NAMESPACE
class QTcpSocket;
class QPushButton;
QT_END_NAMESPACE

class Client : public QDialog
{
   Q_OBJECT
public:
    Client();
    void connectServer();

public slots:
    void newConnect();
    void newFileConnect();
    void newSingerConnect();
    void receiveCategory();
    void sendIdentity(QString identity, QString name);
    void receivePlaylist();//推荐列表json文件
    void showData();
    void showString();
    void sendSongName(QString name);//发送歌曲名,接收专辑图片和歌词
    void showPictureandLrc();
    void sendData(QString name,QString data);
    void sendLoginData(QString user,QString name,QString password);//发送登录信息
    void sendRegisterData(QString user,QString name,QString password);//发送注册信息
    void sendSongsListData(QString label,QString name,QString list);//发送创建的列表名
    void sendDeleteListFromServer(QString label,QString name,QString list);//发送删除用户创建的列表名
    void displayError(QAbstractSocket::SocketError);
    void acceptUserMessage();//接收登录信息
    void acceptRegisterMessage();//接收注册信息
    void acceptCreateList();//创建列表成功
    void acceptDeleteList();//删除列表
    void slotAddMusicToList(QString label,QString list,QString name,QString singer,QString album);//将歌曲加入到对应的列表并传到服务器
    void slotLoadMusicFromList(QString label,QString list);//从服务端加载音乐列表里面的歌曲到客户端
    void acceptMusicFromList();//接收服务端传回的列表中的音乐
    void acceptMusicInsertList();//是否插入成功
    void slotObtainAlbums();//获取首页的推荐歌单
    void acceptMusicTips();//接收首页的推荐歌单
    void slotLoadTipMusics(QString tip);//获取推荐歌单的音乐
    void acceptTipMusics();//接收推荐歌单的歌曲
    void slotGetAlbums(QString singer);//获取歌手的专辑
    void acceptAlbums();//接收专辑
    void sendDeleteMusicFromList(QString label,QString list, QString name, QString singer, QString album);


Q_SIGNALS:
    void signalShowImage(QImage image);
    void signalSendInfo(QString name,QString singer,QString album);
    void signalSendPinYin(QString name,QString pinyin);
    void signalMediaInfo(QString name,QString singer,QString album);
    void signalMediaPinYin(QString name,QString pinyin);
    void signalSendLrc(QTextEdit *&lrc);
    void signalSendList(QString);
    void signalShowMusicWidget();
    void signalMediaPinYins(QString,QString,QString,QString);
    void signalAcceptUserMessage(std::vector<QString> userMessage);//接收点击登录后传回的相关信息
    void signalAcceptRegisterMessage(QString message);//接收是否注册成功
    void signalAlbumAndImage(QString album,QImage image);//将传回的专辑和图片传到首页
    void signalAddAlbum(QString album);//将专辑加入列表

private:
    QTcpSocket *tcpSocket;
    QTcpSocket *fileSocket;
    QTcpSocket *singerSocket;

    QString data;
    //用来存放数据的大小信息
    QBuffer buffer;
    quint32 blockSize;
    QString fileName;
    QImage image;
    qint32 total;

    QFile *localFile;
    qint32 totalBytes;
    qint32 fileNameSize;
    qint32 bytesReceived;
    QByteArray inBlock;
    QTextEdit *m_lrcText;
//    QPushButton *button;
};

#endif // CLIENT_H
