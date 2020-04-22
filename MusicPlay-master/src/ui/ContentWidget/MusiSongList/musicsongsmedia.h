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
    void showRecommendList();

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
    void signalDeleteMusicFromList(QString label,QString name,QString singer,QString album);//将歌曲从列表删除
    void signalSendNextMusicToList2(QStringList&);
    //将该列表的内容传送到播放列表中
    void signalSendPlayList2(QList<QStringList> &,int);
    void signalShowMusicsForAlbum(QString album);//点击专辑时显示歌曲
    void signalShowTableWidget();//显示专辑的表
    void signalGetAlbums(QString singer);//根据歌手获取专辑


public Q_SLOTS:
    void slotAddItem(QString title,QString singer,QString album);
    void slotSaveMusicInfo(QString name,QString pinyin);
    void slotShowMusics(QString name,QString singer,QString album,QString pinyin);//保存推荐列表的歌曲
    void slotReceiveListName(std::vector<QString> listname);//接收列表名
    void slotResponse(QAction *);
    void slot();
    void slotReceiveRecommend(QString,QString,QString);
    void slotReceiveRecommend(QString,QString);

private Q_SLOTS:
    void slotCellDoubleClicked(int row,int cloumn);
    void slotPlayMusic();
    void slotSendNextMusic();
    void slotDeleteMusic();
private:
    QMap<QString,QString> m_musicInfo;
    QList<QStringList> m_music;//保存歌名，歌手，专辑，和播放路径
    QList<QStringList> m_recommendinfo;//保存推荐列表的音乐信息
    QList<QString> m_recommendpinyin;//保存推荐列表的音乐拼音
    QMenu *m_menu;
    QMenu *m_furtherMenu;
};

#endif // MUSICSONGSMEDIA_H
