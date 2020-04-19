//播放列表
#ifndef MYMEDIAPLAYLIST_H
#define MYMEDIAPLAYLIST_H

#include <QDockWidget>
#include <QMap>
#include <deque>

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
    void addItemToHistoryList(QStringList);
    bool checkRepeatMusic(QString&);//查看是否有重复的歌曲
    void playMusicByOrder();//顺序循环播放音乐
    void playMusicByDisorder();//随机播放音乐
    void addMusicToHistoryList();//将播放了的歌曲放在历史记录里面，可以双击进行播放


Q_SIGNALS:
    void signalPlayMusic(QString path);//播放本地歌曲
    void signalPlayMediaMusic(QString);
    void signalReatMusic();
    void signalSendPlayNextMusic(QString,int);//播放下一首歌曲
    void signalSendPreviousMusic(QString,int);//播放上一首歌曲
    void signalSendPlayCmdMusicInfo(QString,int);//单曲循环
    void signalSendNameAndSinger(QString,QString);
    void signalObtainListName();   //获取列表名
    void signalAddMusicToList(QString,QString,QString,QString,QString);

private Q_SLOTS:
    void slotCellDoubleClicked(int,int);
    void slotPlayMusic();
    void slotAddNextLocalPlayMusic(QString&);//添加本地歌曲
    void slotRemoveAllItem();//在添加一个新列表前先删除播放列表的内容
    void slotDeleFromPlayList();

public slots:
    //将默认列表显示到播放列表中
    void slotReceiveList1(QList<QString> &,int);
    //将推荐列表显示到播放列表中
    void slotReceiveList2(QList<QStringList> &,int);
    void slotShowQmenu(QPoint pos);
    void slotAddNextOnlinePlayMusic(QStringList&);//添加在线音乐
    void slotGetNextMusic();
    void slotGetPreviouseMusic();

    /*程序启动后，若按下底部控制按钮，播放歌曲，则要先判断列表中是否有歌曲，
     * 若有，则从返回第一首歌曲,若没有则返回空
    */
    void slotGetFirstPlayMusic();
    //根据播放模式，发送不同的歌曲信息
    void slotSendPlayCmd(int);

    void slotReceiveListName(std::vector<QString> listname);
    void slotResponse(QAction*);

private:
    Ui::MyMediaPlayList *ui;
    QTabWidget *m_tab;
    QTableWidget *m_table1;
    QTableWidget *m_table2;
    QMenu *m_menu;
    QMenu *m_furthermenu;
    QList<playInfo> m_musicpath;//用于保存播放的路径（包括在线的和本地的）便于播放---根据列表的行号来保存
    std::deque<QString> m_historypath;//保存用户听过的歌曲，最多保存30首
    int m_currentplay;//用于保存现在正在播放的音乐的行数
};

#endif // MYMEDIAPLAYLIST_H
