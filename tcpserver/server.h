#ifndef SERVER_H
#define SERVER_H

#include <QDialog>
#include "ui_mainwindow.h"
#include <QTcpServer>
#include <QBuffer>
#include"music.h"
#include "musicbroker.h"
//#include <QObject>
class QTcpServer;

namespace Ui{
class Ui_MainWindow;
}

class Server: public QMainWindow
{
    Q_OBJECT
public:
    explicit Server(QWidget *parent = nullptr);
    ~Server();

private slots:
    void sendMessage();
    void sendPicture();//双击歌曲时发送音乐
    void receiveData();
    void acceptConnection();
    void acceptFileConnection();
    void acceptSingerConnection();
    void receiveCategoryData();
    void sendPlaylist();//发送推荐列表
    void sendSinger();
    void sendAlbum();
    void sendMusic();
    void sendLoginMessage();//验证登录信息
    void sendRegisterMessage();//验证注册信息
    void sendCreateSongsList();//创建歌曲列表
    void sendDeleteSongsList();//删除列表
    void sendAddMusicToList(QString list,QString name,QString singer,QString album);//音乐插入到对应列表
    void sendMusicFromList(QString list);//向客服端传输查询列表的音乐
    void sendMusicTips();//接收推荐歌单
    void sendTipMusics(QString tip);//根据推荐歌单搜素歌曲

    void displayError(QAbstractSocket::SocketError socketError);

Q_SIGNALS:
    void signalSendToMaiWindow();

private:
    QTcpServer *tcpServer;
    QTcpSocket *clientConnection;
    QTcpServer *fileServer;
    QTcpSocket *fileConnection;
    QTcpServer *singerServer;
    QTcpSocket *singerConnection;


    Music *m;
    std::vector<Music *> musics;
    MusicBroker *musicBroker;

    Ui::MainWindow *ui;
    QPixmap pix;

    quint32 blockSize;
    QString data;
    QString data1;
    QString data2;
    QString identity;
    QString name;
    QString password;

    QString message1;//歌名
    QString message2;//歌手
    QString message3;//
    QString message4;
    QString albumFilePath;
    std::vector<QString> a;

    QString fileName;
    QFile *localFile;
    QFile *lyricFile;
    qint32 bytesToWrite;
    qint32 payloadSize;
    qint32 totalBytes;
    QString user;//用户
    QString list;//列表
};

#endif // SERVER_H
