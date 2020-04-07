//推荐列表
#ifndef MUSICSONGSMEDIA_H
#define MUSICSONGSMEDIA_H

#include <QTableWidget>
class MusicListMenu;
class QMenu;
class QAction;
class QActionGroup;

class MusicSongsMedia : public QTableWidget
{
    Q_OBJECT
public:
    explicit MusicSongsMedia(QWidget *parent);
    QString getMusicPinYin(QString name);
    void removeAllItem();
protected:
    virtual void contextMenuEvent(QContextMenuEvent *event);
private:
    void initForm();
    void initConnect();
Q_SIGNALS:
    void signalPlayMediaMusic(QString path);
    void signalShowMediaLrc(QString songPinYin);
    void signalObtainListName();//获取列表名
    void signalAddMusicToList(QString label,QString list,QString name,QString singer,QString album);//将歌曲加入到对应的列表并传到服务器
public Q_SLOTS:
    void slotAddItem(QString title,QString singer,QString album);
    void slotSaveMusicInfo(QString name,QString pinyin);
    void slotShowMusics(QString name,QString pinyin);
    void slotReceiveListName(std::vector<QString> listname);//接收列表名
    void slotResponse(QAction *action);
    void slot();
private Q_SLOTS:
    void slotCellDoubleClicked(int row,int cloumn);
private:
    QMap<QString,QString>m_musicInfo;
    QAction *action;
    //QAction *action1;
    QMenu *menu;
    QMenu *furtherMenu;
    QActionGroup *group;
};

#endif // MUSICSONGSMEDIA_H
