#ifndef MUSICSONGSLISTS_H
#define MUSICSONGSLISTS_H
#include <QTableWidget>
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
Q_SIGNALS:
    void signalShowList(int row);
    void signalDeleteList(int row);
    void signalAddNewList();
    void signalCreateSongsList(QString label,QString name,QString list);//创建歌曲列表
    void signalDeleteListFromServer(QString label,QString user,QString name);//从服务端删除用户创建的列表

private Q_SLOTS:
    void slotCellClicked(int,int);
    void slotAddNewPlayList();
    void slotDeletePlayList();
    void slotCreateList();
public Q_SLOTS:
    void slotUpdateList(std::vector<QString> userMessage);
protected:
    virtual void contextMenuEvent(QContextMenuEvent *event);
private:
    SongMenu *m_menu;
    QDialog *d;
    QLineEdit *m;
    QPushButton *push;
public:
    QString user;
};

#endif // MUSICSONGSLISTS_H
