﻿#include "musicmainwidget.h"
#include "titlewidget.h"    //标题栏
#include "contentwidget.h"  //中央窗体
#include "bottomwidget.h"   //底部工具栏
#include "client.h"
#include <QVBoxLayout>
#include <QBitmap>
#include <QPainter>
#include <QTimer>
#include <QPalette>
#include <QDebug>
#include <QStackedWidget>
#include "controlvalues.h"
#include "playmusic.h"
#include "app.h"
#include "musicdesktoplrcmanage.h"
#include "loginform_test.h"
#include "MusiSongList/mymediaplaylist.h"
#include "miniplaylayout.h"

#include <QApplication>

MusicMainWidget::MusicMainWidget(QWidget *parent) :
    QFrame(parent)
{
    initForm();
    initWidget();
    initLayout();
    initPlayList();
    initConnect();
    emit signalSendLogin("user",App::user,App::password);

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

    m_miniplay = new MiniPlayLayout(this);
    m_miniplay ->setGeometry(0,470,180,50);
    m_miniplay->hide();


    m_player = new PlayMusic(this);
    m_desktopLrc = new MusicDesktopLrcManage;
    m_client = new Client();

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
            m_contentWidget,SLOT(slotShowMediaSongs()));//显示搜索框
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
    //标题栏发送搜索内容
    connect(m_titleWidget,SIGNAL(signalFirstSearch(QString,QString)),
            m_client,SLOT(sendData(QString,QString)));
    connect(m_titleWidget,SIGNAL(signalSearchContent(QString)),m_contentWidget,SIGNAL(signalSendSearch(QString)));
    connect(m_contentWidget,SIGNAL(signalSearchData(QString,QString)),m_client,SLOT(sendData(QString,QString)));

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
//    connect(m_bottomWidget,SIGNAL(signalShowOrHide()),
//            m_contentWidget,SLOT(slotShowOrHide()));
    connect(m_miniplay,&MiniPlayLayout::signalShowOrHide,
            m_contentWidget,&Contentwidget::slotShowOrHide);
    connect(m_bottomWidget,SIGNAL(signalHidOrShowLyrc(int)),
            this,SLOT(slotShowOrHideDesktopLrc(int)));
    connect(m_bottomWidget,SIGNAL(signalHidOrShowPlayList()),this,SLOT(slotShowOrHideCornorList()));
    connect(m_bottomWidget,SIGNAL(signalPreviousMusic()),
            m_playlist,SLOT(slotGetPreviouseMusic()));

    connect(m_bottomWidget,SIGNAL(signalPlayOrPause(int)),
            this,SLOT(slotPlayOrPause(int)));

    connect(m_bottomWidget,SIGNAL(signalNextMusic()),
            m_playlist,SLOT(slotGetNextMusic()));
    connect(m_bottomWidget,SIGNAL(signalPlayProgressChange(int)),
            this,SLOT(slotPlayProgressChange(int)));
    /*****************请求第一次播放时的歌曲信息******************/

    //    connect(m_bottomWidget,SIGNAL(signalPlayOrPause(int)),
    //            m_contentWidget,SLOT(slotReceiveFirstPlayMusic(int)));

    //请求成功后传给播放器
    connect(m_contentWidget,SIGNAL(signalSendFirstPlayMusic(QString)),
            m_player,SLOT(slotOpenMusic(QString)));
    //关联请求回来的数据
    connect(m_playlist,SIGNAL(signalSendPlayNextMusic(QString,int)),
            this,SLOT(slotNextMusic(QString,int)));
    connect(m_playlist,SIGNAL(signalSendPreviousMusic(QString,int)),
            this,SLOT(slotPreviousMusic(QString,int)));
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
    connect(m_player,SIGNAL(signalSendPlayNextMusic(int)),
            m_playlist,SLOT(slotSendPlayCmd(int)));
    connect(m_bottomWidget,SIGNAL(signalPlayCmd(int)),
            m_playlist,SLOT(slotSendPlayCmd(int)));
//    connect(m_playlist,SIGNAL(signalSendPlayCmdMusic(QString)),
//            m_player,SLOT(slotReceivePlayCmdMusic(QString)));//signalCategoryClicked;
    /******************获取从服务器发过来的消息**********************/
//    connect(m_client,SIGNAL(signalShowImage(QImage)),
//            m_bottomWidget,SLOT(slotShowImage(QImage)));
     connect(m_client,SIGNAL(signalShowImage(QImage)),m_miniplay,SLOT(slotReceiveImage(QImage)));
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
            m_contentWidget,SLOT(slotShowMediaSongs2()));
    connect(m_client,SIGNAL(signalMediaPinYins(QString,QString,QString,QString)),
            m_contentWidget,SIGNAL(signalShowMusics(QString,QString,QString,QString)));
    //播放列表向客户端发送消息
//    connect(m_playlist,SIGNAL(showPictureandLrc()),m_client,SLOT)

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
    connect(m_contentWidget,&Contentwidget::signalModifySongsList,
            m_client,&Client::sendModifyListName);//更改列表名

    //将歌曲加入到对应的列表并传到服务器
    connect(m_contentWidget,&Contentwidget::signalAddMusicToList,m_client,&Client::slotAddMusicToList);
    connect(m_playlist,&MyMediaPlayList::signalAddMusicToList,m_client,&Client::slotAddMusicToList);

    //加载列表里面的歌曲
    connect(m_contentWidget,&Contentwidget::signalLoadMusicFromList,
            m_client,&Client::slotLoadMusicFromList);
    //刷新播放列表
    connect(m_contentWidget,SIGNAL(signalSendSongsListWidget(QList<QString> &,int)),m_playlist,SLOT(slotReceiveList1(QList<QString>&,int)));
//    connect(m_contentWidget,SIGNAL(signalShowPicture(QString)),m_client,SLOT(sendSongName(QString)));
    //播放列表播放歌曲时请求显示专辑照片和歌词文件
    connect(m_playlist,SIGNAL(signalshowPictureandLrc(QString)),m_client,SLOT(sendSongName(QString)));
    //在播放列表中添加下一首播放
    connect(m_contentWidget,SIGNAL(signalSendNextMusic(QString&)),m_playlist, SLOT(slotAddNextLocalPlayMusic(QString&)));
    connect(m_contentWidget,SIGNAL(signalSendNextMusic2(QStringList&)), m_playlist,SLOT(slotAddNextOnlinePlayMusic(QStringList&)));
    //将推荐列表发送到播放列表
    connect(m_contentWidget, SIGNAL(signalSendList2ToPlay(QList<QStringList>&,int)),m_playlist,SLOT(slotReceiveList2(QList<QStringList>&, int)));
    //播放“播放列表”里面的歌曲
    connect(m_playlist,SIGNAL(signalPlayMusic(QString)),
            m_player,SLOT(slotOpenMusic(QString)));
    connect(m_playlist,SIGNAL(signalPlayMediaMusic(QString)),m_player,SLOT(slotOpenMediaMusic(QString)));
    //为播放列表获取列表名
    connect(m_playlist,SIGNAL(signalObtainListName()),m_contentWidget,SIGNAL(signalObtainListName()));
    connect(m_contentWidget,SIGNAL(signalSendListName(std::vector<QString>)),m_playlist,SLOT(slotReceiveListName(std::vector<QString>)));
    //发送该歌曲重复信号
    connect(m_playlist,SIGNAL(signalReatMusic()), this, SLOT(slotShowRepeatMessage()));

    //获取首页的推荐歌单
    connect(m_contentWidget,&Contentwidget::signalObtainAlbums,m_client,&Client::slotObtainAlbums);
    //传回专辑和图片到首页的推荐歌单
    connect(m_client,&Client::signalAlbumAndImage,m_contentWidget,&Contentwidget::signalAlbumAndImage);
    //获取推荐歌单的歌曲
    connect(m_contentWidget,&Contentwidget::signalLoadTipMusics,m_client,&Client::slotLoadTipMusics);
    //显示首页
    connect(m_titleWidget,&TitleWidget::signalShowHomePage,m_contentWidget,&Contentwidget::slotShowHomePage);
    //传送歌手的专辑
    connect(m_contentWidget,&Contentwidget::signalGetAlbums,m_client,&Client::slotGetAlbums);
    //接收歌手的专辑
    connect(m_client,&Client::signalAddAlbum,m_contentWidget,&Contentwidget::slotAddAlbum);

    //连接到小窗口的播放
    connect(m_playlist,SIGNAL(signalSendNameAndSinger(QString,QString)),m_miniplay,SLOT(slotReceiveNameAndSinger(QString,QString)));
    connect(m_playlist,SIGNAL(signalSendNameAndSinger(QString,QString)),this,SLOT(slotShowMiniPlay(QString,QString)));
    //删除列表中的歌曲
    connect(m_contentWidget,SIGNAL(signalDeleteMusicFromList(QString,QString,QString,QString,QString)),m_client,SLOT(sendDeleteMusicFromList(QString,QString,QString,QString,QString)));

    //用户登录
    connect(login,SIGNAL(signalLoginClicked(QString,QString,QString)),m_client,SLOT(sendLoginData(QString,QString,QString)));
    connect(m_client,SIGNAL(signalAcceptUserMessage(std::vector<QString>,std::vector<QImage>)),login,SLOT(slotAcceptUserMessage(std::vector<QString>,std::vector<QImage>)));
    connect(login,SIGNAL(signalRegisterClicked(QString,QString,QString)),m_client,SLOT(sendRegisterData(QString,QString,QString)));
    connect(m_client,SIGNAL(signalAcceptRegisterMessage(QString)),login,SLOT(slotAcceptRegisterMessage(QString)));
    connect(this,SIGNAL(signalSendLogin(QString,QString,QString)),m_client,SLOT(sendLoginData(QString,QString,QString)));
    connect(this,SIGNAL(signalSendLogin(QString,QString,QString)),login,SLOT(slotSetName(QString,QString,QString)));
    //传输歌单图片到服务器保存
    connect(m_contentWidget,&Contentwidget::signalAddTipPictureToServer,m_client,&Client::slotAddTipPictureToServer);

}

void MusicMainWidget::initPlayList()
{
    qDebug()<<"显示播放列表";
    m_playlist->setGeometry(427,160,450,400);
    m_playlist->hide();
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

void MusicMainWidget::slotShowRepeatMessage()
{
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(137, 190, 178));
    QLabel *msg = new QLabel(this);
    msg->setAutoFillBackground(true);
    msg->setGeometry(350,200,200,50);
    msg->setAlignment(Qt::AlignCenter);
    msg->setPalette(palette);
    msg->setText("列表已存在相同歌曲");
    QTimer::singleShot(1500,msg,SLOT(close()));
    msg->show();
}

void MusicMainWidget::slotPreviousMusic(const QString &name,int i)
{
#if QDEBUG_OUT
    qDebug()<<"播放上一首音乐"<<name;
#endif
    if(i==0){
        m_player->slotOpenMusic(name);
    }
    else {
        m_player->slotOpenMediaMusic(name);
    }
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

void MusicMainWidget::slotNextMusic(const QString &name,int i)
{
#if QDEBUG_OUT
    qDebug()<<"播放下一首音乐"<<name;
#endif
    if(i==0){
        m_player->slotOpenMusic(name);
    }
    else {
        m_player->slotOpenMediaMusic(name);
    }
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

void MusicMainWidget::slotShowMiniPlay(QString s,QString d)
{
    qDebug() <<s<<d;
    m_miniplay->show();
}
