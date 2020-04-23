#include "contentwidget.h"
#include <QBitmap>
#include <QPainter>
#include "MusisLyrc/musiclyrcwidget.h"
#include "MusiSongList/musicsongslistwidget.h"
#include "MusiSongList/musicsongslists.h"
#include "MusiSongList/classifylist.h"
#include <QHBoxLayout>
//#include "MusiSongList/musicsongssummarizied.h"
#include <QDebug>
#include "app.h"
#include "MusiSongList/musicsongsmedia.h"
#include "MusiSongList/homepage.h"
#include "MusiSongList/searchlistwidget.h"

Contentwidget::Contentwidget(QWidget *parent) :
    QWidget(parent)
{
    initForm();
    initWidget();
    initLayout();
    initConnect();
    m_searchwidget->initWidget(m_musicSongsMedia);
}

Contentwidget::~Contentwidget()
{
    //    delete m_songsSummarizied;
    delete m_musicSongsLists;
    delete m_musicLyrcWidget;
    //    delete m_musicSongList;
    while (!m_musicSongList.isEmpty()) {
        MusicSongsListWidget *w = m_musicSongList.takeLast();
        delete w;
        w = NULL;
    }
    delete m_musicSongsMedia;
    delete m_musicSongsMedia2;
    delete m_classifyList;
    delete m_searchwidget;
}

void Contentwidget::initForm()
{
}

void Contentwidget::initWidget()
{
    //    m_songsSummarizied = new MusicSongsSummarizied(this);
    m_musicSongsLists = new MusicSongsLists(this);
    m_musicLyrcWidget = new MusicLyrcWidget(this);
    m_musicSongsMedia = new MusicSongsMedia(this);//搜素列表,分类列表
    m_musicSongsMedia2 = new MusicSongsMedia(this);//推荐列表
    m_searchwidget = new Searchlistwidget(this);
    m_classifyList = new classifyList(this);
    MusicSongsListWidget *widget = new MusicSongsListWidget(this);
    m_musicSongList.append(widget);
    m_home = new HomePage(this);
    //m_searchwidget->initWidget(m_musicSongsMedia);
    //    widget->addMusicFold("/root/CloudMusic/");
}

void Contentwidget::initLayout()
{
    m_mainLayout = new QHBoxLayout(this);
    //    m_mainLayout->addWidget(m_songsSummarizied,Qt::AlignLeft);
    m_mainLayout->addWidget(m_musicSongsLists,Qt::AlignLeft);       //右边列表栏
    m_mainLayout->addWidget(m_musicLyrcWidget,Qt::AlignRight);      //歌词栏
    m_mainLayout->addWidget(m_musicSongList.at(0),Qt::AlignRight);  //本地列表
    m_mainLayout->addWidget(m_musicSongsMedia,Qt::AlignRight);
    m_mainLayout->addWidget(m_musicSongsMedia2,Qt::AlignRight);    //推荐列表
    m_mainLayout->addWidget(m_classifyList,Qt::AlignRight);
    m_mainLayout->addWidget(m_home,Qt::AlignRight);
    m_mainLayout->addWidget(m_searchwidget,Qt::AlignRight);

    m_mainLayout->setSpacing(5);

    m_currentwidget = 0;
    this->connectMusicList(m_currentwidget);
    m_mainLayout->setContentsMargins(0,0,0,0);
    setLayout(m_mainLayout);
    m_musicLyrcWidget->hide();
    m_musicSongsMedia->hide();
    m_musicSongsMedia2->hide();
    m_classifyList->hide();
    m_musicSongList.at(m_currentwidget)->hide();
    m_home->show();
    m_searchwidget->hide();


    //m_searchContent->setVisible(true);
    m_showOrHide = false;
}

void Contentwidget::initConnect()
{
    /*****************接收当前播放的音乐，解析歌词****************/
    connect(this,SIGNAL(signalRequestPlayingMusic(QString)),
            m_musicLyrcWidget,SLOT(slotReceiveMusicInfo(QString)));
    connect(this,SIGNAL(signalRequestCurPlayTime(qint64)),
            m_musicLyrcWidget,SLOT(slotReceiveCurrentPlayTime(qint64)));
    connect(m_musicLyrcWidget,SIGNAL(signalHideLrc()),
            this,SLOT(slotHideLrc()));
    /***************根据点击的列表显示列表内容**********************/
    connect(m_musicSongsLists,SIGNAL(signalShowList(int,QString)),
            this,SLOT(slotShowList(int,QString)));
    connect(m_musicSongsLists,SIGNAL(signalAddNewList()),
            this,SLOT(slotAddNewList()));
    connect(m_musicSongsLists,SIGNAL(signalDeleteList(int)),
            this,SLOT(slotDeleteList(int)));
    connect(m_musicSongsLists,SIGNAL(signalDeleteListFromServer(QString,QString,QString)),
            this,SIGNAL(signalDeleteListFromServer(QString,QString,QString)));//发送删除列表的信息
    connect(m_musicSongsMedia,SIGNAL(signalPlayMediaMusic(QString)),
            this,SIGNAL(signalPlayMediaMusic(QString)));

    /***************显示客户端传输数据**********************/
    connect(this,SIGNAL(signalShowInfo(QString,QString,QString)),
            m_musicSongsMedia2,SLOT(slotAddItem(QString,QString,QString)));
    connect(this,SIGNAL(signalSendPinYin(QString,QString)),
            m_musicSongsMedia2,SLOT(slotSaveMusicInfo(QString,QString)));
    connect(this,SIGNAL(signalShowInfo(QString,QString,QString)),
            m_musicSongsMedia,SLOT(slotAddItem(QString,QString,QString)));
    connect(this,SIGNAL(signalSendPinYin(QString,QString)),
            m_musicSongsMedia,SLOT(slotSaveMusicInfo(QString,QString)));
    connect(m_musicSongsMedia2,SIGNAL(signalShowMediaLrc(QString)),
            m_musicLyrcWidget,SLOT(slotAnalyseMedia(QString)));
    connect(m_musicSongsMedia2,SIGNAL(signalShowPicture(QString)),
            this,SIGNAL(signalShowPicture(QString)));
    connect(m_musicSongsMedia,SIGNAL(signalShowMediaLrc(QString)),
            m_musicLyrcWidget,SLOT(slotAnalyseMedia(QString)));
    connect(m_musicSongsMedia,SIGNAL(signalShowPicture(QString)),
            this,SIGNAL(signalShowPicture(QString)));


    connect(m_musicSongsMedia2,SIGNAL(signalPlayMediaMusic(QString)),
            this,SIGNAL(signalPlayMediaMusic(QString)));
    connect(m_musicSongsMedia2,SIGNAL(signalShowMediaLrc(QString)),
            m_musicLyrcWidget,SLOT(slotAnalyseMedia(QString)));
    connect(this,SIGNAL(signalMediaInfo(QString,QString,QString)),
            m_musicSongsMedia2,SLOT(slotAddItem(QString,QString,QString)));
    connect(this,SIGNAL(signalMediaPinYin(QString,QString)),
            m_musicSongsMedia2,SLOT(slotSaveMusicInfo(QString,QString)));
    connect(this,SIGNAL(signalMediaInfo(QString,QString,QString)),
            m_musicSongsMedia2,SLOT(slotReceiveRecommend(QString,QString,QString)));
    connect(this,SIGNAL(signalMediaPinYin(QString,QString)),
            m_musicSongsMedia2,SLOT(slotReceiveRecommend(QString,QString)));
    connect(m_musicSongsMedia2,SIGNAL(signalShowPicture(QString)),
            this,SIGNAL(signalShowPicture(QString)));

    /***************分类列表向客户端发送数据**********************/
    connect(m_classifyList,SIGNAL(signalSendData(QString,QString)),
            this,SIGNAL(signalSendData(QString,QString)));
    connect(m_classifyList,SIGNAL(signalCategoryClicked()),
            this,SIGNAL(signalCategoryClicked()));
    connect(this,SIGNAL(signalSendList(QString)),
            m_classifyList,SLOT(addItemContent(QString)));
    connect(this,SIGNAL(signalShowMusics(QString,QString,QString,QString)),
            m_musicSongsMedia2,SLOT(slotShowMusics(QString,QString,QString,QString)));

    //更新用户列表
    connect(this,&Contentwidget::signalUpdateList,
            m_musicSongsLists,&MusicSongsLists::slotUpdateList);
    //传输创建的列表名
    connect(m_musicSongsLists,&MusicSongsLists::signalCreateSongsList,
            this,&Contentwidget::signalCreateSongsList);
    //修改列表名
    connect(m_musicSongsLists,&MusicSongsLists::signalModifySongsList,
            this,&Contentwidget::signalModifySongsList);

    //获取创建的列表名
    connect(m_musicSongsMedia,&MusicSongsMedia::signalObtainListName,
            m_musicSongsLists,&MusicSongsLists::slotObtainListName);
    connect(m_musicSongsMedia2,&MusicSongsMedia::signalObtainListName,
            m_musicSongsLists,&MusicSongsLists::slotObtainListName);
    connect(this, SIGNAL(signalObtainListName()), m_musicSongsLists,SLOT(slotObtainListName()));
    //接收列表名
    connect(m_musicSongsLists,&MusicSongsLists::signalSendListName,m_musicSongsMedia,&MusicSongsMedia::slotReceiveListName);
    connect(m_musicSongsLists,&MusicSongsLists::signalSendListName,m_musicSongsMedia2,&MusicSongsMedia::slotReceiveListName);
    connect(m_musicSongsLists,SIGNAL(signalSendListName(std::vector<QString>)),SIGNAL(signalSendListName(std::vector<QString>)));
    //将歌曲加入到对应列表并传到服务器
    connect(m_musicSongsMedia,&MusicSongsMedia::signalAddMusicToList,this,&Contentwidget::signalAddMusicToList);
    connect(m_musicSongsMedia2,&MusicSongsMedia::signalAddMusicToList,this,&Contentwidget::signalAddMusicToList);
    //添加下一首播放
    connect(m_musicSongsMedia, &MusicSongsMedia::signalSendNextMusicToList2, this, &Contentwidget::signalSendNextMusic2);
    connect(m_musicSongsMedia2, &MusicSongsMedia::signalSendNextMusicToList2, this, &Contentwidget::signalSendNextMusic2);

    //发送在线列表到播放列表
    connect(m_musicSongsMedia, &MusicSongsMedia::signalSendPlayList2,this, &Contentwidget::signalSendList2ToPlay);
    connect(m_musicSongsMedia2, &MusicSongsMedia::signalSendPlayList2,this, &Contentwidget::signalSendList2ToPlay);

    //获取首页的推荐歌单
    connect(m_home,&HomePage::signalObtainAlbums,this,&Contentwidget::signalObtainAlbums);
    //传回图片和专辑到首页
    connect(this,&Contentwidget::signalAlbumAndImage,m_home,&HomePage::slotAddMusicTip);
    //显示点击推荐的歌单后的界面
    connect(m_home,&HomePage::signalShowWidget,this,&Contentwidget::slotShowMediaSongs2);
    //获取推荐歌单里面的歌曲
    connect(m_home,&HomePage::signalShowMusicsFromTip,this,&Contentwidget::signalLoadTipMusics);
    //发送搜索内容
    connect(this,SIGNAL(signalSendSearch(QString)),m_searchwidget,SLOT(slotSaveSearchContent(QString)));
    connect(m_searchwidget,SIGNAL(signalSendData(QString,QString)),this,SIGNAL(signalSearchData(QString,QString)));
    connect(m_searchwidget,SIGNAL(signalBtnClicked()),this,SLOT(slotNewSearch()));
    //点击专辑时显示歌曲和窗口
    connect(m_musicSongsMedia,&MusicSongsMedia::signalShowMusicsForAlbum,this,&Contentwidget::slotShowMediaSongs);
    connect(m_musicSongsMedia,&MusicSongsMedia::signalShowMusicsForAlbum,this,&Contentwidget::signalLoadTipMusics);
    connect(m_musicSongsMedia2,&MusicSongsMedia::signalShowMusicsForAlbum,this,&Contentwidget::slotShowMediaSongs);
    connect(m_musicSongsMedia2,&MusicSongsMedia::signalShowMusicsForAlbum,this,&Contentwidget::signalLoadTipMusics);
    //点击歌手后显示表和专辑
    connect(m_musicSongsMedia,&MusicSongsMedia::signalShowTableWidget,this,&Contentwidget::slotShowTableWidget);
    connect(m_musicSongsMedia,&MusicSongsMedia::signalGetAlbums,this,&Contentwidget::signalGetAlbums);
    connect(m_musicSongsMedia2,&MusicSongsMedia::signalShowTableWidget,this,&Contentwidget::slotShowTableWidget);
    connect(m_musicSongsMedia2,&MusicSongsMedia::signalGetAlbums,this,&Contentwidget::signalGetAlbums);

    //列表删除音乐
    connect(m_musicSongsMedia2,SIGNAL(signalDeleteMusicFromList(QString,QString,QString,QString)),this,SLOT(slotDeleteMusicFromList(QString,QString,QString,QString)));

}

void Contentwidget::slotAddAlbum(QString album)
{
    m_classifyList->addItemContent(album);
}

void Contentwidget::slotDeleteMusicFromList(QString label, QString name, QString singer, QString album)
{
    emit signalDeleteMusicFromList(label,m_list,name,singer,album);
}

void Contentwidget::slotShowTableWidget()
{
    m_musicLyrcWidget->hide();
    m_showOrHide = false;
    m_musicSongList.at(m_currentwidget)->hide();
    this->disConnectMusicList(m_currentwidget);
    m_classifyList->removeAllItem();
    m_classifyList->m_currentCatagory = 2;
    m_classifyList->show();
    m_musicSongsMedia2->hide();
    m_musicSongsMedia->hide();
    m_home->hide();
}

void Contentwidget::connectMusicList(int index)
{
    connect(this,SIGNAL(signalRequestFirstPlayMusic()),
            m_musicSongList.at(index),SLOT(slotGetFirstPlayMusic()));
    connect(m_musicSongList.at(index),SIGNAL(signalSendFirstPlayMusic(QString)),
            this,SIGNAL(signalSendFirstPlayMusic(QString)));
    connect(m_musicSongList.at(index),SIGNAL(signalPlayMusicPath(QString)),
            this,SIGNAL(signalPlayMusic(QString)));
    connect(m_musicSongList.at(index),SIGNAL(signalSendPlayCmdMusicInfo(QString)),
            this,SIGNAL(signalSendPlayCmdMusic(QString)));
    connect(m_musicSongList.at(index), SIGNAL(signalSendToPlayList(QList<QString> &,int)),this,SIGNAL(signalSendSongsListWidget(QList<QString>  &,int)));
    //添加下一首播放
    connect(m_musicSongList.at(index), SIGNAL(signalSendNextMusicToList(QString&)),this,SIGNAL(signalSendNextMusic(QString&)));
    connect(m_musicSongList.at(index),&MusicSongsListWidget::signalAddMusicToList,this,&Contentwidget::signalAddMusicToList);
    //默认列表获取所创建的列表名
    connect(m_musicSongList.at(index),&MusicSongsListWidget::signalObtainListName,m_musicSongsLists,&MusicSongsLists::slotObtainListName);
    connect(m_musicSongsLists,&MusicSongsLists::signalSendListName,m_musicSongList.at(index),&MusicSongsListWidget::slotReceiveListName);

}

void Contentwidget::disConnectMusicList(int index)
{
    disconnect(this,SIGNAL(signalRequestFirstPlayMusic()),
               m_musicSongList.at(index),SLOT(slotGetFirstPlayMusic()));
    disconnect(m_musicSongList.at(index),SIGNAL(signalSendFirstPlayMusic(QString)),
               this,SIGNAL(signalSendFirstPlayMusic(QString)));

    disconnect(m_musicSongList.at(m_currentwidget),SIGNAL(signalPlayMusicPath(QString)),
               this,SIGNAL(signalPlayMusic(QString)));
    disconnect(m_musicSongList.at(m_currentwidget), SIGNAL(signalSendToPlayList(QList<QString> &,int)),this,SIGNAL(signalSendSongsListWidget(QList<QString>  &,int)));
    //添加下一首播放
    disconnect(m_musicSongList.at(m_currentwidget), SIGNAL(signalSendNextMusicToList(QString&)),this,SIGNAL(signalSendNextMusic(QString&)));
    disconnect(m_musicSongList.at(m_currentwidget),&MusicSongsListWidget::signalAddMusicToList,this,&Contentwidget::signalAddMusicToList);
    //默认列表获取所创建的列表名
    disconnect(m_musicSongList.at(m_currentwidget),&MusicSongsListWidget::signalObtainListName,m_musicSongsLists,&MusicSongsLists::slotObtainListName);
    disconnect(m_musicSongsLists,&MusicSongsLists::signalSendListName,m_musicSongList.at(m_currentwidget),&MusicSongsListWidget::slotReceiveListName);
}


void Contentwidget::slotReceiveFirstPlayMusic(int cmd)
{
    //发送之前先检测当前是否正在播放音乐
    App::ReadConfig();
    if (!App::IsPlaying)
    {
        if (MUSIC_PLAY == cmd)
        {
            emit signalRequestFirstPlayMusic();
        }
    }

}

void Contentwidget::slotShowLrc()
{
    m_musicLyrcWidget->show();
    m_searchwidget->hide();
    m_musicSongsMedia2->hide();
    m_classifyList->hide();
    m_home->hide();
    m_musicSongList.at(m_currentwidget)->hide();
    m_showOrHide = true;
}

void Contentwidget::slotHideLrc()
{
    m_musicLyrcWidget->hide();
    m_musicSongsMedia2->hide();
    m_classifyList->hide();
    m_home->hide();
    m_musicSongList.at(m_currentwidget)->show();
    m_showOrHide = false;
}

void Contentwidget::slotShowList(int row,QString list)
{
    qDebug() << row << "选择的行";
    m_musicLyrcWidget->hide();
    m_showOrHide = false;
    m_musicSongList.at(m_currentwidget)->hide();
    m_musicSongsMedia->hide();
    m_home->hide();
    this->disConnectMusicList(m_currentwidget);
    if(row == 1){
        m_classifyList->hide();
        m_searchwidget->hide();
        m_musicSongsMedia2->removeAllItem();
        m_musicSongsMedia2->showRecommendList();
        m_musicSongsMedia2->show();
    }else{
        m_musicSongsMedia2->hide();
        m_classifyList->hide();
        if(row == 0){
            m_musicSongList.at(row)->show();
            m_currentwidget = row;
            this->connectMusicList(m_currentwidget);
        }
        else if(row == 2){
            m_home->hide();
            m_classifyList->initCurrent();
            m_classifyList->show();

        }
        else{
            qDebug() << "执行";
            m_list = list;
            m_musicSongsMedia2->removeAllItem();
            m_musicSongsMedia2->show();
            QString label = "loadmusicfromlist";
            emit signalLoadMusicFromList(label,list);

            //m_musicSongList.at(row-2)->show();
            //m_currentwidget = row-2;
            //this->connectMusicList(m_currentwidget-2);
        }
    }
}

void Contentwidget::slotShowTip()
{
    m_musicLyrcWidget->hide();
    //m_showOrHide = false;
    m_musicSongList.at(m_currentwidget)->hide();
    this->disConnectMusicList(m_currentwidget);
    m_classifyList->hide();
    m_musicSongsMedia2->hide();
    m_home->close();
    m_musicSongsMedia->removeAllItem();
    m_musicSongsMedia->show();
    //m_searchwidget->show();
    //slotShowMediaSongs();
}

void Contentwidget::slotShowHomePage()
{
    m_musicLyrcWidget->hide();
    m_showOrHide = false;
    m_musicSongList.at(m_currentwidget)->hide();
    this->disConnectMusicList(m_currentwidget);
    m_classifyList->hide();
    m_musicSongsMedia2->hide();
    //m_musicSongsMedia->hide();
    m_searchwidget->hide();
    m_home->show();
}

void Contentwidget::slotAddNewList()
{
    MusicSongsListWidget *widget = new MusicSongsListWidget(this);
    m_musicSongList.append(widget);
    m_mainLayout->addWidget(widget,Qt::AlignRight);
    widget->hide();
    initConnect();
}

void Contentwidget::slotDeleteList(int row)
{
    m_musicSongList.removeAt(row);
}

void Contentwidget::slotShowOrHide()
{
    qDebug()<<"显示或隐藏歌词";
    if(m_showOrHide)
        slotHideLrc();
    else
        slotShowLrc();
}


//显示搜索结果
void Contentwidget::slotShowMediaSongs()
{
    m_musicSongsMedia->removeAllItem();
    if(m_musicSongsMedia->isHidden()){
        m_musicSongsMedia->show();
    }
    if(m_searchwidget->isHidden()){
        //m_searchwidget->initWidget(m_musicSongsMedia);
        m_searchwidget->show();
    }
    //m_musicSongsMedia->hide();
    m_musicSongList.at(m_currentwidget)->hide();
    m_musicLyrcWidget->hide();
    //m_musicSongsMedia2->removeAllItem();
    m_musicSongsMedia2->hide();
    m_classifyList->hide();
    m_home->hide();
    m_showOrHide = false;
}

void Contentwidget::slotShowMediaSongs2()
{
    m_searchwidget->hide();
    m_musicSongsMedia->hide();
    m_musicSongList.at(m_currentwidget)->hide();
    m_musicLyrcWidget->hide();
    m_musicSongsMedia2->removeAllItem();
    m_musicSongsMedia2->show();
    m_classifyList->hide();
    m_home->hide();
    m_showOrHide = false;
}

void Contentwidget::slotNewSearch()
{
    m_musicSongsMedia->removeAllItem();
}

void Contentwidget::slotSetName(QString name)
{
    m_musicSongsLists->user = name;
}
