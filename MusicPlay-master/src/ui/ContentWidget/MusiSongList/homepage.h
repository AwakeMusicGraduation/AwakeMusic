#ifndef HOMEPAGE_H
#define HOMEPAGE_H
#include <QTableWidget>
#include <QLabel>
#include <QWidget>
#include <QVariant>
#include <QPushButton>

class QLabel;
class QVBoxLayout;
class AnimatedWallWG;

class QTableWidget;

class HomePage:public QTableWidget
{
public:
    Q_OBJECT
public:
    explicit HomePage(QWidget *parent);
private:
    void initform();
    void initconnect();
signals:
    void signalObtainAlbums();//获取推荐歌单
public slots:
    void slotAddMusicTip(QString album,QImage image);//推荐歌单接收图片和专辑名
private:
    QVBoxLayout *m_mainlayout;
    QLabel *m_home;
    QLabel *m_tiplists;
    AnimatedWallWG *m_wall;
    QTableWidget *table;
    //QPushButton *m_albums[8];
    std::vector<QString> m_albumsName;
    int row = 0,column = 0;
public Q_SLOTS:
    void slotShowMusics();//点击歌单显示歌曲
};

#endif // HOMEPAGE_H
