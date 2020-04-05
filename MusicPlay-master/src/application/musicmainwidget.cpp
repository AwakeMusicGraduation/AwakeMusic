﻿#include "musicmainwidget.h"
#include "titlewidget.h"    //标题栏
#include "contentwidget.h"  //中央窗体
#include "bottomwidget.h"   //底部工具栏
#include "client.h"
#include <QVBoxLayout>
#include <QBitmap>
#include <QPainter>
#include <QDebug>
#include <QStackedWidget>
#include "controlvalues.h"
#include "playmusic.h"
#include "app.h"
#include "musicdesktoplrcmanage.h"
#include "loginform_test.h"
#include "MusiSongList/mymediaplaylist.h"

#include <QApplication>

MusicMainWidget::MusicMainWidget(QWidget *parent) :
    QFrame(parent)
{
    initForm();
    initWidget();
    initLayout();
    initPlayList();
    initConnect();

}

MusicMainWidget::~MusicMainWidget()
{
    delete m_titleWidget;
    delete m_bottomWidget;
}

//样式初始化
void MusicMainWidget::initForm()
{
    //设定窗体固定大小
    this->setFixedSize(WIDGET_WIDTH,WIDGET_HEIGHT);
    //设置标题
    this->setWindowTitle(SOFT_TITLE);
    //设置窗体标题栏隐藏--Qt::WindowStaysOnTopHint |
    this->setWindowFlags(Qt::FramelessWindowHint |
                         Qt::WindowSystemMenuHint |
                         Qt::WindowMinMaxButtonsHint);
    setMouseTracking(true);
    this->setObjectName("MainFrame");
    //初始化为未按下鼠标左键
    m_mouse_press = false;
    App::ReadConfig();
    m_curSkin = App::AppSkin;
    setStyleSheet(QString("#MainFrame {background-image:url(:/image/skin/%1);border:1px solid black;}").arg(m_curSkin));
}

//窗体初始化
void MusicMainWidget::initWidget()
{
    login = new loginform_test();
    m_titleWidget = new TitleWidget(this);
    //标题栏安装事件监听器
    installEventFilter(m_titleWidget);

    m_contentWidget = new Contentwidget(this);
    m_bottomWidget = new BottomWidget(this);
    m_playlist = new MyMediaPlayList(this);

    m_player = new PlayMusic(this);
    m_desktopLrc = new MusicDesktopLrcManage;
    m_client = new Client();
//    m_client->newConnect();
}

//布局初始化
void MusicMainWidget::initLayout()
{
    m_mainLayout = new QVBoxLayout(this);
    m_mainLayout->addWidget(m_titleWidget);
    m_mainLayout->addWidget(m_contentWidget);
    m_mainLayout->addWidget(m_bottomWidget);
    //设置布局边框距为0
    m_mainLayout->setContentsMargins(0,0,0,0);
    setLayout(m_mainLayout);
}

//信号和槽链接初始化（这里的信号传递主要是在顶部中间底部窗口之间的传递）
void MusicMainWidget::initConnect()
{
    //标题栏信号和槽关联
    connect(m_titleWidget,SIGNAL(signalSearchClicked()),
            m_contentWidget,SLOT(slotShowMediaSongs()));
    connect(m_titleWidget,SIGNAL(signalLogin()),
            this,SLOT(slotShowLoginWidget()));
    connect(m_titleWidget,SIGNAL(signalSkin()),
            this,SLOT(slotShowSkinWidget()));
    connect(m_titleWidget,SIGNAL(signalMin()),
            this,SLOT(slotShowMin()));
    connect(m_titleWidget,SIGNAL(signalClose()),
            this,SLOT(slotClose()));
    connect(m_titleWidget,SIGNAL(signalSearchContent(QString)),
            m_client,SLOT(sendData(QString)));

    //中央窗体信号和槽关联
    connect(m_contentWidget,SIGNAL(signalPlayMusic(QString)),
            m_player,SLOT(slotOpenMusic(QString)));
    connect(m_contentWidget,SIGNAL(signalPlayMediaMusic(QString)),
            m_player,SLOT(slotOpenMediaMusic(QString)));

    connect(m_player,SIGNAL(signalPlayStatue(int)),
            m_bottomWidget,SLOT(slotSetPlayOrPause(int)));
    //发送媒体长度
    connect(m_player,SIGNAL(signalSendPlayLength(qint64)),
            m_bottomWidget,SLOT(slotReceivePlayLength(qint64)));
    //发送播放声音
//    connect(m_player,SIGNAL(signalSendPlayVolume(int)),
//            m_bottomWidget,SLOT(slotSetPlayVolume(int)));
    //发送播放位置,将时间显示出来
    connect(m_player,SIGNAL(signalSendPlayPostion(qint64)),
            m_bottomWidget,SLOT(slotReceivePlayPostion(qint64)));
    //当声音滑块值变化时，发送声音值给播放音乐对象，改变对应值
    connect(m_bottomWidget,SIGNAL(signalSendPlayVolume(int)),
            m_player,SLOT(slotSetPlayVolume(int)));
    //当播放进度条值改变时，发送最新位置值该播放音乐对象，改变播放进度
    connect(m_bottomWidget,SIGNAL(signalSendPlayPostion(qint64)),
            m_player,SLOT(slotSetPlayPostion(qint64)));

    //底部菜单栏控制信号和槽关联
    connect(m_bottomWidget,SIGNAL(signalShowOrHide()),
            m_contentWidget,SLOT(slotShowOrHide()));
    connect(m_bottomWidget,SIGNAL(signalHidOrShowLyrc(int)),
            this,SLOT(slotShowOrHideDesktopLrc(int)));
    connect(m_bottomWidget,SIGNAL(signalHidOrShowPlayList()),this,SLOT(slotShowOrHideCornorList()));
    connect(m_bottomWidget,SIGNAL(signalPreviousMusic()),
            m_contentWidget,SIGNAL(signalSendPlayPreviouse()));

    connect(m_bottomWidget,SIGNAL(signalPlayOrPause(int)),
            this,SLOT(slotPlayOrPause(int)));

    connect(m_bottomWidget,SIGNAL(signalNextMusic()),
            m_contentWidget,SIGNAL(signalSendPlayNext()));
    connect(m_bottomWidget,SIGNAL(signalPlayProgressChange(int)),
            this,SLOT(slotPlayProgressChange(int)));
    /*****************请求第一次播放时的歌曲信息******************/

    //    connect(m_bottomWidget,SIGNAL(signalPlayOrPause(int)),
    //            m_contentWidget,SLOT(slotReceiveFirstPlayMusic(int)));

    //请求成功后传给播放器
    connect(m_contentWidget,SIGNAL(signalSendFirstPlayMusic(QString)),
            m_player,SLOT(slotOpenMusic(QString)));
    //关联请求回来的数据
    connect(m_contentWidget,SIGNAL(signalSendPlayNextMusic(QString)),
            this,SLOT(slotNextMusic(QString)));
    connect(m_contentWidget,SIGNAL(signalSendPlayPreviouseMusic(QString)),
            this,SLOT(slotPreviousMusic(QString)));
    //删除用户创建的音乐列表
    connect(m_contentWidget,SIGNAL(signalDeleteListFromServer(QString,QString,QString)),
            m_client,SLOT(sendDeleteListFromServer(QString,QString,QString)));

    /**********************解析歌词信号关联**************************/
    connect(m_player,SIGNAL(signalSendPlayingMusic(QString)),
            m_contentWidget,SIGNAL(signalRequestPlayingMusic(QString)));
    connect(m_player,SIGNAL(signalSendPlayingMedia(QString)),
            m_desktopLrc,SLOT(slotAnalyseLrc(QString)));
    connect(m_player,SIGNAL(signalSendPlayingMusic(QString)),
            m_desktopLrc,SLOT(slotReceiveMusicInfo(QString)));
    connect(m_player,SIGNAL(signalSendPlayPostion(qint64)),
            m_contentWidget,SIGNAL(signalRequestCurPlayTime(qint64)));
    connect(m_player,SIGNAL(signalSendPlayPostion(qint64)),
            m_desktopLrc,SLOT(slotReceiveCurrentPlayTime(qint64)));

    /******************根据播放模式，发送播放命令**********************/
//    connect(m_player,SIGNAL(signalSendPlayNextMusic(int)),
//            m_contentWidget,SIGNAL(signalRequestPlayCmd(int)));
    connect(m_bottomWidget,SIGNAL(signalPlayCmd(int)),
            m_contentWidget,SIGNAL(signalRequestPlayCmd(int)));
    connect(m_contentWidget,SIGNAL(signalSendPlayCmdMusic(QString)),
            m_player,SLOT(slotReceivePlayCmdMusic(QString)));//signalCategoryClicked;
    /******************获取从服务器发过来的消息**********************/
    connect(m_client,SIGNAL(signalShowImage(QImage)),
            m_bottomWidget,SLOT(slotShowImage(QImage)));
    connect(m_client,SIGNAL(signalSendInfo(QString,QString,QString)),
            m_contentWidget,SIGNAL(signalShowInfo(QString,QString,QString)));
    connect(m_client,SIGNAL(signalSendPinYin(QString,QString)),
            m_contentWidget,SIGNAL(signalSendPinYin(QString,QString)));
    connect(m_client,SIGNAL(signalMediaInfo(QString,QString,QString)),
            m_contentWidget,SIGNAL(signalMediaInfo(QString,QString,QString)));
    connect(m_client,SIGNAL(signalMediaPinYin(QString,QString)),
            m_contentWidget,SIGNAL(signalMediaPinYin(QString,QString)));

    //分类列表向客户端发送信息
    connect(m_contentWidget,SIGNAL(signalSendData(QString,QString)),
            m_client,SLOT(sendIdentity(QString,QString)));
    connect(m_client,SIGNAL(signalSendList(QString)),
            m_contentWidget,SIGNAL(signalSendList(QString)));
    connect(m_contentWidget,SIGNAL(signalCategoryClicked()),
            m_client,SLOT(newSingerConnect()));
    connect(m_client,SIGNAL(signalShowMusicWidget()),
            m_contentWidget,SLOT(slotShowMediaSongs()));
    connect(m_client,SIGNAL(signalMediaPinYins(QString,QString)),
            m_contentWidget,SIGNAL(signalShowMusics(QString,QString)));

    //刷新用户登录列表
    //connect(login,&loginform_test::signalUpdateList,
    //        m_contentWidget,&Contentwidget::signalUpdateList);
    //connect(this,&MusicMainWidget::slotUpdateList,m_contentWidget,&)
    connect(login,&loginform_test::signalUpdateList,
            m_contentWidget,&Contentwidget::signalUpdateList);
    qDebug() << "更新登录列表";
    connect(login,&loginform_test::signalUpdateName,m_titleWidget,&TitleWidget::slotUpdateName);
    qDebug() << "设置登录名";
    connect(login,&loginform_test::signalUpdateName,m_contentWidget,&Contentwidget::slotSetName);
    connect(m_contentWidget,&Contentwidget::signalCreateSongsList,
            m_client,&Client::sendSongsListData);//传输列表名

    //刷新播放列表
    connect(m_contentWidget,SIGNAL(signalSendSongsListWidget(QMap<int, QString> &)),this,SLOT(slotFlushPlayList(QMap<int, QString> &)));
}

void MusicMainWidget::initPlayList()
{
    qDebug()<<"显示播放列表";
    m_playlist->setGeometry(427,140,450,400);
}

void MusicMainWidget::mousePressEvent(QMouseEvent *event)
{
    //只能是鼠标左键移动和改变大小
    if(event->button() == Qt::LeftButton)
    {
        m_mouse_press = true;
    }

    //窗口移动距离
    m_move_point = event->globalPos() - pos();
}

void MusicMainWidget::mouseReleaseEvent(QMouseEvent *)
{
    m_mouse_press = false;
}

void MusicMainWidget::mouseMoveEvent(QMouseEvent *event)
{
    //移动窗口
    if(m_mouse_press)
    {
        QPoint move_pos = event->globalPos();
        move(move_pos - m_move_point);
    }
}

//显示登录界面
void MusicMainWidget::slotShowLoginWidget()
{
    qDebug() << "登录中";
    //loginform_test login;
    //login = new loginform_test();

    login->exec();
   // connect(login,&loginform_test::signalUpdateList,
   //         m_contentWidget,&Contentwidget::signalUpdateList);
   // qDebug() << "更新登录列表";
   // connect(login,&loginform_test::signalUpdateName,m_titleWidget,&TitleWidget::slotUpdateName);
   // qDebug() << "设置登录名";
    //connect(&login,loginform_test::login,this,MusicMainWidget::slotLogin);
}

//显示皮肤界面
void MusicMainWidget::slotShowSkinWidget()
{
    if (m_curSkin == "0.png")
    {
        m_curSkin = "1.png";
    }else if (m_curSkin == "1.png")
    {
        m_curSkin = "2.png";
    }else if (m_curSkin == "2.png")
    {
        m_curSkin = "3.png";
    }else if (m_curSkin == "3.png")
    {
        m_curSkin = "4.png";
    }else if (m_curSkin == "4.png")
    {
        m_curSkin = "5.png";
    }else if (m_curSkin == "5.png")
    {
        m_curSkin = "6.png";
    }else if (m_curSkin == "6.png")
    {
        m_curSkin = "7.png";
    }else if (m_curSkin == "7.png")
    {
        m_curSkin = "8.png";
    }else if (m_curSkin == "8.png")
    {
        m_curSkin = "9.png";
    }else if (m_curSkin == "9.png")
    {
        m_curSkin = "10.png";
    }else if (m_curSkin == "10.png")
    {
        m_curSkin = "11.png";
    }else if (m_curSkin == "11.png")
    {
        m_curSkin = "0.png";
    }

    setStyleSheet(QString("#MainFrame {background-image:url(:/image/skin/%1);border:1px solid black;}").arg(m_curSkin));
    App::AppSkin = m_curSkin;
    App::WriteConfig();
}

//最小化显示
void MusicMainWidget::slotShowMin()
{
    this->showMinimized();
}

//关闭程序
void MusicMainWidget::slotClose()
{
    //    this->close();
    qApp->exit(0);
}

void MusicMainWidget::slotPreviousMusic(const QString &name)
{
#if QDEBUG_OUT
    qDebug()<<"播放上一首音乐"<<name;
#endif
    m_player->slotOpenMusic(name);
}

void MusicMainWidget::slotPlayOrPause(int state)
{
    if (MUSIC_PLAY == state)
    {
        m_player->setPlayMusic();
        qDebug()<<"播放音乐";
    }else if (MUSIC_PAUSE == state)
    {
        m_player->setPauseMusic();
        qDebug()<<"暂停音乐";
    }
}

void MusicMainWidget::slotNextMusic(const QString &name)
{
#if QDEBUG_OUT
    qDebug()<<"播放下一首音乐"<<name;
#endif
    m_player->slotOpenMusic(name);
}

void MusicMainWidget::slotPlayProgressChange(int value)
{
    qDebug()<<"当前播放进度"<<value;
}

void MusicMainWidget::slotShowOrHideDesktopLrc(int value)
{
    if (SHOW_LYRC == value)
    {
        m_desktopLrc->show();
    }else if (HIDE_LYRC == value)
    {
        m_desktopLrc->hide();
    }
}

void MusicMainWidget::slotShowOrHideCornorList()
{
    if(m_playlist->isHidden()){
        //    显示播放列表
        m_playlist->show();
    }
    else{
        m_playlist->hide();
    }
}

void MusicMainWidget::slotTest(const QString &name)
{
    qDebug()<<"请求回来的歌曲为:"<<name;
}

void MusicMainWidget::slotFlushPlayList(QMap<int, QString> &m)
{
    m_playlist->slotReceiveList1(m);
}
