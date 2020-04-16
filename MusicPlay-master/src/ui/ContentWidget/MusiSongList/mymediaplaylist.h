//播放列表
#ifndef MYMEDIAPLAYLIST_H
#define MYMEDIAPLAYLIST_H

#include <QDockWidget>
#include <QMap>

class QTabWidget;
class QTableWidget;
class QMenu;

namespace Ui {
class MyMediaPlayList;
}

struct playInfo{
    bool i;//0表示本地音乐，1表示在线音乐
    QString path;//播放的地址
};

class MyMediaPlayList : public QDockWidget
{
    Q_OBJECT

public:
    explicit MyMediaPlayList(QWidget *parent = nullptr);
    ~MyMediaPlayList();

private:
    void initWidget();
    void initForm();
    void initMenu();
    void initConnect();
    void addContenItem(QStringList,int);
    bool checkRepeatMusic(QString&);//查看是否有重复的歌曲


Q_SIGNALS:
    void signalShowLyric();
    void signalPlayMusic(QString path);//播放本地歌曲
    void signalPlayMediaMusic(QString);
    void signalReatMusic();

private Q_SLOTS:
    void slotCellDoubleClicked(int,int);
    void slotPlayMusic();
    void slotAddNextLocalPlayMusic(QString&);//添加本地歌曲
    void slotRemoveAllItem();//在添加一个新列表前先删除播放列表的内容
    void slotDeleFromPlayList();

public slots:
    //将默认列表显示到播放列表中
    void slotReceiveList1(QList<QString> &);
    //将推荐列表显示到播放列表中
    void slotReceiveList2(QList<QStringList> &);
    void slotShowQmenu(QPoint pos);
    void slotAddNextOnlinePlayMusic(QStringList&);//添加在线音乐

private:
    Ui::MyMediaPlayList *ui;
    QTabWidget *m_tab;
    QTableWidget *m_table1;
    QTableWidget *m_table2;
    QMenu *m_menu;
    QList<playInfo> m_musicpath;//用于保存播放的路径（包括在线的和本地的）便于播放---根据列表的行号来保存
    int m_currentplay;//用于保存现在正在播放的音乐的行数
};

#endif // MYMEDIAPLAYLIST_H
