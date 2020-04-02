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
    void receiveData();
    void acceptConnection();
    void acceptFileConnection();
    void acceptSingerConnection();
    void receiveCategoryData();
    void sendPlaylist();
    void sendSinger();
    void sendAlbum();
    void sendMusic();
    void sendLoginMessage();//验证登录信息
    void sendRegisterMessage();//验证注册信息
    void sendCreateSongsList();//创建歌曲列表
    void sendDeleteSongsList();//删除列表

    void displayError(QAbstractSocket::SocketError socketError);
signals:
    void sendToMaiWindow();

private:
    QTcpServer *tcpServer;
    QTcpSocket *clientConnection;
    QTcpServer *fileServer;
    QTcpSocket *fileConnection;
    QTcpServer *singerServer;
    QTcpSocket *singerConnection;


    Music *m;
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
