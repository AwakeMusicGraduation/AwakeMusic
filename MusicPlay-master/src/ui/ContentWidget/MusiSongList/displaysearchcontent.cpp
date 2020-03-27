#include "displaysearchcontent.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "classifylist.h"
#include <QHeaderView>
#include <QFrame>

DisplaySearchContent::DisplaySearchContent(QWidget *parent):
    QTableWidget (parent)
{
    currentClicked = 0;
    initform();
    initconnect();
}

void DisplaySearchContent::initform()
{
   m_singer = new QPushButton(this);
    m_singer->setText("歌手");
    m_singer->setFixedSize(50,30);

    m_album = new QPushButton(this);
    m_album->setText("专辑");
    m_album->setFixedSize(50,30);

    m_music = new QPushButton(this);
    m_music->setText("单曲");
    m_music->setFixedSize(50,30);

    m_songSheet = new QPushButton(this);
    m_songSheet->setText("歌单");
    m_songSheet->setFixedSize(50,30);

    setFocusPolicy(Qt::NoFocus);
    setShowGrid(true);//display the grid
    setEditTriggers(QAbstractItemView::NoEditTriggers);     //设置表格不能编辑
    setSelectionBehavior(QAbstractItemView::SelectRows);    //设置整行选中
    setSelectionMode(QAbstractItemView::SingleSelection);

    m_hlayout = new QHBoxLayout;
    m_hlayout->addWidget(m_singer);
    m_hlayout->addWidget(m_album);
    m_hlayout->addWidget(m_music);
    m_hlayout->addWidget(m_songSheet);

    m_mainLayout = new QVBoxLayout(this);
    m_mainLayout->addStretch(0);
    m_mainLayout->addSpacing(20);
    m_mainLayout->addLayout(m_hlayout,Qt::AlignTop);

    QFrame *line = new QFrame(this);
    line->setFrameShape(QFrame::HLine);
    m_mainLayout->addWidget(line);

    m_list = new classifyList(this);
    m_list->removeAllItem();
    m_mainLayout->addSpacing(20);
    m_mainLayout->addWidget(m_list,Qt::AlignBottom);

    setLayout(m_mainLayout);
}

void DisplaySearchContent::initconnect()
{
    connect(m_singer,&QPushButton::clicked,this,&DisplaySearchContent::slotShowSinger);
    connect(m_album,&QPushButton::clicked,this,&DisplaySearchContent::slotShowAlbum);
    connect(m_music,&QPushButton::clicked,this,&DisplaySearchContent::slotShowMusic);
    connect(m_songSheet,&QPushButton::clicked,this,&DisplaySearchContent::slotShowSongsheet);
}

void DisplaySearchContent::slotShowSinger()
{

}

void DisplaySearchContent::slotShowAlbum()
{

}

void DisplaySearchContent::slotShowMusic()
{

}

void DisplaySearchContent::slotShowSongsheet()
{

}
