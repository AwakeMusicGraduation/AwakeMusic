﻿#ifndef CONTENTWIDGET_H
#define CONTENTWIDGET_H

#include <QWidget>
#include "controlvalues.h"

class MusicLyrcWidget;
class QHBoxLayout;
class MusicSongsLists;
class MusicSongsListWidget;
class MusicSongsMedia;
class classifyList;

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

    //向上发送播放上一首、下一首请求，歌曲列表收到该信号后会向下返回要播放的歌曲信息
    void signalSendPlayNext();
    void signalSendPlayPreviouse();

    //向下发送请求回来的歌曲信息
    void signalSendPlayNextMusic(const QString&);
    void signalSendPlayPreviouseMusic(const QString &);

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
    
public slots:
    //接收bottombar发送过来的播放命令
    void slotReceiveFirstPlayMusic(int);
    void slotShowLrc();
    void slotHideLrc();
    void slotShowList(int row);
    void slotAddNewList();
    void slotDeleteList(int row);
    void slotShowOrHide();
    void slotShowMediaSongs();

private:
//    MusicSongsSummarizied *m_songsSummarizied;
    QList<MusicSongsListWidget *> m_musicSongList;
    MusicLyrcWidget *m_musicLyrcWidget;
    MusicSongsLists *m_musicSongsLists;
    MusicSongsMedia *m_musicSongsMedia;
    MusicSongsMedia *m_musicSongsMedia2;
    classifyList *m_classifyList;
    int m_currentwidget;
    bool m_showOrHide;

    QHBoxLayout *m_mainLayout;
    
};

#endif // CONTENTWIDGET_H
