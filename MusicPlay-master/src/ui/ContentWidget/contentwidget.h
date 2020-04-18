#ifndef CONTENTWIDGET_H
#define CONTENTWIDGET_H

#include <QWidget>
#include "controlvalues.h"


class MusicLyrcWidget;
class QHBoxLayout;
class MusicSongsLists;
class MusicSongsListWidget;
class MusicSongsMedia;
class classifyList;
class DisplaySearchContent;
class HomePage;
class Searchlistwidget;

class Contentwidget : public QWidget
{
    Q_OBJECT
public:
    explicit Contentwidget(QWidget *parent = 0);
    ~Contentwidget();
private:
    void initForm();
    void initWidget();
    void initLayout();
    void initConnect();
    void connectMusicList(int);
    void disConnectMusicList(int);
    
Q_SIGNALS:
    //发送要播放的音乐(包括音乐具体信息)
    void signalPlayMusic(QString music);
    void signalPlayMediaMusic(QString path);
    void signalShowPicture(QString songName);

    /*************向上请求第一次要播放的歌曲信息***************/
    void signalRequestFirstPlayMusic();
    //请求成功，向下层发送
    void signalSendFirstPlayMusic(const QString &);

    //获取当前播放的音乐--解析歌词
    void signalRequestPlayingMusic(const QString &);
    void signalRequestCurPlayTime(qint64);

    //根据播放模式，请求歌曲
    void signalRequestPlayCmd(int);
    void signalSendPlayCmdMusic(const QString &);

    //显示客户端传输信息
    void signalShowInfo(QString,QString,QString);
    void signalSendPinYin(QString,QString);
    void signalMediaInfo(QString,QString,QString);
    void signalMediaPinYin(QString,QString);

    //分类列表向客户端发送信息
    void signalSendData(QString,QString data);
    void signalSendList(QString);
    void signalCategoryClicked();
    void signalShowMusics(QString,QString);

    void signalUpdateList(std::vector<QString> userMessage);//更新用户列表
    void signalCreateSongsList(QString label,QString name,QString list);//传输创建的列表名
    void signalDeleteListFromServer(QString label,QString user,QString name);//删除列表名

    void signalAddMusicToList(QString label,QString list,QString name,QString singer,QString album);//将歌曲加入到对应的列表并传到服务器
    void signalLoadMusicFromList(QString label,QString list);//加载用户创建的列表里面的内容

    void signalSendSongsListWidget(QList<QString>&, int);

    void signalSendNextMusic(QString&);

    void signalSendNextMusic2(QStringList&);

    void signalSendList2ToPlay(QList<QStringList>&,int);

    void signalObtainAlbums();//获取首页的推荐歌单
    void signalAlbumAndImage(QString album,QImage image);//传回图片和专辑到首页
    void signalLoadTipMusics(QString tip);//获取推荐歌单的歌曲

    //发送搜索内容
    void signalSendSearch(QString);//发给searchlistwidget
    void signalSearchData(QString name,QString data);//发给服务器
    
public slots:
    //接收bottombar发送过来的播放命令
    void slotReceiveFirstPlayMusic(int);
    void slotShowLrc();
    void slotHideLrc();
    void slotShowList(int row,QString list);
    void slotAddNewList();
    void slotDeleteList(int row);
    void slotShowOrHide();
    void slotShowMediaSongs();
    void slotNewSearch();
    void slotSetName(QString name);
    void slotShowTip();//显示推荐歌单的列表
    void slotShowHomePage();//显示首页

private:
//    MusicSongsSummarizied *m_songsSummarizied;
    QList<MusicSongsListWidget *> m_musicSongList;
    MusicLyrcWidget *m_musicLyrcWidget;
    MusicSongsLists *m_musicSongsLists;
    MusicSongsMedia *m_musicSongsMedia;
    MusicSongsMedia *m_musicSongsMedia2;
    classifyList *m_classifyList;
    DisplaySearchContent *m_searchContent;
    Searchlistwidget *m_searchwidget;
    int m_currentwidget;
    bool m_showOrHide;

    HomePage *m_home;

    QHBoxLayout *m_mainLayout;
    
};

#endif // CONTENTWIDGET_H
