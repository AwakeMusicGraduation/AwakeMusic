#include "playmusic.h"
#include "vlc/vlc.h"
#include "qvlcplayer.h"
#include <QDebug>
#include <QTimer>
#include "myhelper.h"
#include "app.h"

PlayMusic::PlayMusic(QObject *parent) : QObject(parent)
{
    initForm();
    initConnect();
}

PlayMusic::~PlayMusic()
{
    delete m_player;
    m_player = NULL;
}

//打开音乐
void PlayMusic::slotOpenMusic(QString name)
{
    if (name.isEmpty())
    {
        emit signalPlayStatue(MUSIC_PAUSE);
        qDebug()<<"当前返回为空";
        return;
    }else
    {
        m_player->Play(name);
        setPlayMusic();

        myHelper::Sleep(100);
        qint64 length = m_player->GetLength();

        //打开媒体后，发送媒体信息，包括：媒体长度、当前声音、当前位置
        emit signalSendPlayLength(length);
        //    emit signalSendPlayVolume(m_player->getVolume());
        //    emit signalSendPlayPostion(m_player->GetPos());
        emit signalPlayStatue(MUSIC_PLAY);
        myHelper::Sleep(100);
        emit signalSendPlayingMusic(name);
    }
}

void PlayMusic::slotOpenMediaMusic(QString path)
{
    if (path.isEmpty())
    {
        emit signalPlayStatue(MUSIC_PAUSE);
        qDebug()<<"当前返回为空";
        return;
    }else
    {
        m_player->PlayMeida(path);
        setPlayMusic();

        myHelper::Sleep(100);
        qint64 length = m_player->GetLength();

        //打开媒体后，发送媒体信息，包括：媒体长度、当前声音、当前位置
        emit signalSendPlayLength(length);
        //    emit signalSendPlayVolume(m_player->getVolume());
        //    emit signalSendPlayPostion(m_player->GetPos());
        emit signalPlayStatue(MUSIC_PLAY);
        myHelper::Sleep(100);
        QString name = path.remove(path.left(26));
        path = name.remove(name.right(4));
        emit signalSendPlayingMedia(path);
    }
}

//改变当前播放媒体音量
void PlayMusic::slotSetPlayVolume(int value)
{
    m_player->Volume(value);
}

void PlayMusic::slotSetPlayPostion(qint64 pos)
{
    m_player->SetPlayTime(pos);
}

void PlayMusic::slotReceivePlayCmdMusic(const QString & name)
{
    if (!name.isEmpty()){

        m_player->Play(name);
        this->setPlayMusic();
    }
    else
    {
        m_player->Pause();
    }
}

void PlayMusic::slotUpdateInterface()
{
    if (libvlc_NothingSpecial == m_player->GetPlayStatue())
    {
        return;
    }
    if (libvlc_Ended == m_player->GetPlayStatue())
    {
        emit signalPlayStatue(MUSIC_PLAY_END);
        return;
    }

    qint64 pos = m_player->GetTime();

    emit signalSendPlayPostion(pos);
}

void PlayMusic::setPlayMusic()
{
    if (!m_player->IsPlaying())
        m_player->Play();
    App::IsPlaying = true;
    App::WriteConfig();
    emit signalPlayStatue(MUSIC_PLAY);
}

//用于接收bottomWidget发送过来的控制信号
void PlayMusic::setPauseMusic()
{
    m_player->Pause();

    emit signalPlayStatue(MUSIC_PAUSE);
}

void PlayMusic::initForm()
{
    m_player = new QVlcPlayer(this);

    //定时更新播放接口信息
    m_pollerTimer = new QTimer(this);
    //start timer to trigger every 300 ms the updateInterface slot
    m_pollerTimer->start(300);
}


void PlayMusic::initConnect()
{
    connect(m_pollerTimer,SIGNAL(timeout()),
            this,SLOT(slotUpdateInterface()));
}

void PlayMusic::sendPlayMusicCmd()
{
    //读取配置文件中播放模式信息，发送不同的命令
    App::ReadConfig();
    int mode = App::AppPlayMode;
    emit signalSendPlayNextMusic(mode);
}

