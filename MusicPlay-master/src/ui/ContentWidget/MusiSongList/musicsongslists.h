#ifndef MUSICSONGSLISTS_H
#define MUSICSONGSLISTS_H
#include <QTableWidget>
#include <QColor>
class MusicListMenu;
class SongMenu;
class QDialog;
class QPushButton;

class MusicSongsLists : public QTableWidget
{
    Q_OBJECT
public:
    explicit MusicSongsLists(QWidget *parent);
    void addItemContent(QString content);

private:
    void initForm();
    void initWidget();
    void initConnect();
//    void setRowColor(int ,QColor);
Q_SIGNALS:
    void signalShowList(int row,QString list);      //发送信号，显示哪个界面
    void signalDeleteList(int row);
    void signalAddNewList();
    void signalCreateSongsList(QString label,QString name,QString list);//创建歌曲列表
    void signalDeleteListFromServer(QString label,QString user,QString name);//从服务端删除用户创建的列表
    void signalSendListName(std::vector<QString> listname);//将用户创建的列表传过来

private Q_SLOTS:
    void slotCellClicked(int,int);
    void slotAddNewPlayList();
    void slotDeletePlayList();
    void slotCreateList();

public Q_SLOTS:
    void slotUpdateList(std::vector<QString> userMessage);
    void slotObtainListName();//获取列表名
public slots:
//    void cellEntered(int,int);//鼠标移动时间，返回item的行和列
protected:
    virtual void contextMenuEvent(QContextMenuEvent *event);
//    void leaveEvent(QEvent *event); //鼠标移出事件


private:
    SongMenu *m_menu;
    QDialog *d;
    QLineEdit *m;
    QPushButton *push;
    std::vector<QString> listName;   //用于保存列表的名字
//    QColor lastRowBkColor;//存储item之前的颜色，默认设置为透明
//    int previousColorRow;//鼠标移动过的上一行行号

public:
    QString user;
};

#endif // MUSICSONGSLISTS_H
