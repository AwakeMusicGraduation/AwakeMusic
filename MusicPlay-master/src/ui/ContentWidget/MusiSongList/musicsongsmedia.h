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
    void initMenu();
    void saveMusicInfo();

Q_SIGNALS:
    void signalPlayMediaMusic(QString path);
    void signalShowMediaLrc(QString songPinYin);
    void signalShowPicture(QString name);
    void signalObtainListName();//获取列表名
    void signalAddMusicToList(QString label,QString list,QString name,QString singer,QString album);//将歌曲加入到对应的列表并传到服务器
    void signalSendNextMusicToList2(QStringList&);//下一首播放

    void signalSendPlayList2(QList<QStringList> &);//将该列表的内容传送到播放列表中

public Q_SLOTS:
    void slotAddItem(QString title,QString singer,QString album);
    void slotSaveMusicInfo(QString name,QString pinyin);
    void slotShowMusics(QString name,QString pinyin);
    void slotReceiveListName(std::vector<QString> listname);//接收列表名
    void slotResponse(QAction *);
    void slot();
private Q_SLOTS:
    void slotCellDoubleClicked(int row,int cloumn);
    void slotPlayMusic();
    void slotSendNextMusic();
private:
    QMap<QString,QString> m_musicInfo;
    QList<QStringList> m_music;//保存歌名，歌手，专辑，和播放路径
    QMenu *m_menu;
    QMenu *m_furtherMenu;
};

#endif // MUSICSONGSMEDIA_H
