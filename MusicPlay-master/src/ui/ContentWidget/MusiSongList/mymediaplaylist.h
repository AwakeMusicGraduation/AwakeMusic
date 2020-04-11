//播放列表
#ifndef MYMEDIAPLAYLIST_H
#define MYMEDIAPLAYLIST_H

#include <QDockWidget>

class QTabWidget;
class QTableWidget;
class QMenu;

namespace Ui {
class MyMediaPlayList;
}

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
    void removeAllItem();//在添加一个新列表前先删除播放列表的内容
    bool checkRepeatMusic(QString&);//查看是否有重复的歌曲


Q_SIGNALS:
     void signalShowLyric();
    void signalPlayMusic(QString path);
    void signalReatMusic();

private Q_SLOTS:
    void slotCellDoubleClicked(int,int);
    void slotPlayMusic();
    void slotAddNextPlayMusic(QString&);//添加本地歌曲

public slots:
    //将默认列表显示到播放列表中
    void slotReceiveList1(QList<QString> &);
    void slotShowQmenu(QPoint pos);

private:
    Ui::MyMediaPlayList *ui;
    QTabWidget *m_tab;
    QTableWidget *m_table1;
    QTableWidget *m_table2;
    QMenu *m_menu;
    QList<QString> m_musicpath;//用于保存播放的路径（包括在线的和本地的）便于播放---根据列表的行号来保存
//    QList<QStringList> m_musicinfo;//用于保存歌曲信息，便于显示---根据列表的行号来保存
};

#endif // MYMEDIAPLAYLIST_H
