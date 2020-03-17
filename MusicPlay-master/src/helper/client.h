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
    void receivePlaylist();
    void showString();
    void sendData(QString data);
    void displayError(QAbstractSocket::SocketError);

Q_SIGNALS:
    void signalShowImage(QImage image);
    void signalSendInfo(QString name,QString singer,QString album);
    void signalSendPinYin(QString name,QString pinyin);
    void signalMediaInfo(QString name,QString singer,QString album);
    void signalMediaPinYin(QString name,QString pinyin);
    void signalSendLrc(QTextEdit *&lrc);
    void signalSendList(QString);
    void signalShowMusicWidget();
    void signalMediaPinYins(QString,QString);

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

    QFile *localFile;
    qint32 totalBytes;
    qint32 fileNameSize;
    qint32 bytesReceived;
    QByteArray inBlock;
    QTextEdit *m_lrcText;
//    QPushButton *button;
};

#endif // CLIENT_H
