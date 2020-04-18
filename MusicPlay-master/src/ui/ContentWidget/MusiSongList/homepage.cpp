#include "homepage.h"
#include <QLabel>
#include <QFrame>
#include <QVBoxLayout>
#include <QRect>
#include "animatedwallwg.h"
#include "controlvalues.h"
#include <QHeaderView>
#include <QPushButton>
#include <QDebug>
#include <QPushButton>

HomePage::HomePage(QWidget *parent):QTableWidget (parent)
{
    initform();
    initconnect();
}

void HomePage::initform()
{
//    setFixedWidth(CENTERWIDGET_RIGHT);
    m_mainlayout = new QVBoxLayout(this);

    m_home = new QPushButton(this);
    m_home->setText("首页");
    //m_home->setFont(QFont(5));
    //m_home->setFixedSize(700,10);
    m_home->move(300,1);

    QFrame *line = new QFrame(this);
    line->setFrameShape(QFrame::HLine);
    line->move(0,33);
    line->setFixedSize(700,1);

    m_wall = new AnimatedWallWG(this);
    m_wall->move(0,50);
    //m_wall->setFixedSize(700,110);

    QFrame *line1 = new QFrame(this);
    line1->setFrameShape(QFrame::HLine);
    line1->move(0,185);
    line1->setFixedSize(700,1);

    m_tiplists = new QLabel("推荐歌单",this);
    m_tiplists->move(0,192);

    QFrame *line2 = new QFrame(this);
    line2->setFrameShape(QFrame::HLine);
    line2->move(0,220);
    line2->setFixedSize(80,1);

    table = new QTableWidget(this);
    table->setAlternatingRowColors(true);
    table->setStyleSheet("selection-background-color:lightblue;");
    table->setFixedWidth(700);
    table->setFocusPolicy(Qt::NoFocus);
    table->setColumnCount(4);
    table->setRowCount(2);
    table->setShowGrid(true);//display the grid
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);     //设置表格不能编辑
    table->setSelectionBehavior(QAbstractItemView::SelectItems);    //设置整行选中
    table->setSelectionMode(QAbstractItemView::SingleSelection);

    table->verticalHeader()->setDefaultSectionSize(45);

    QHeaderView *headerview = table->horizontalHeader();
    table->horizontalHeader()->hide();
    headerview->setVisible(false);

    table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    table->verticalHeader()->setVisible(false);
    table->setMidLineWidth(20);

    table->setColumnWidth(0,175);
    table->setColumnWidth(1,175);
    table->setColumnWidth(2,175);
    table->setColumnWidth(3,175);
    table->setRowHeight(0,140);
    table->setRowHeight(1,140);
    table->move(0,230);
    table->setFixedSize(700,280);

}

void HomePage::initconnect()
{
    //connect(this,SIGNAL(show()),this,SIGNAL(signalObtainAlbums()));
    connect(table,&QTableWidget::cellClicked,this,&HomePage::slotShowMusicsFromTip);
    connect(m_home,SIGNAL(clicked()),this,SIGNAL(signalObtainAlbums()));
    //对应点击切换图片后显示的歌曲
    connect(m_wall,&AnimatedWallWG::signalObtainSongs,this,&HomePage::slotShowSongs);
    connect(m_wall,&AnimatedWallWG::signalObtainSongs1,this,&HomePage::slotShowSongs1);
    connect(m_wall,&AnimatedWallWG::signalObtainSongs2,this,&HomePage::slotShowSongs2);
    connect(m_wall,&AnimatedWallWG::signalObtainSongs3,this,&HomePage::slotShowSongs3);
    connect(m_wall,&AnimatedWallWG::signalObtainSongs4,this,&HomePage::slotShowSongs4);
    connect(m_wall,&AnimatedWallWG::signalObtainSongs5,this,&HomePage::slotShowSongs5);

}

void HomePage::slotShowSongs()
{
    QString tip = "初学者";
    emit signalShowWidget();
    emit signalShowMusicsFromTip(tip);
}

void HomePage::slotShowSongs1()
{
    QString tip = "一半";
    emit signalShowWidget();
    emit signalShowMusicsFromTip(tip);
}

void HomePage::slotShowSongs2()
{
    QString tip = "怪咖";
    emit signalShowWidget();
    emit signalShowMusicsFromTip(tip);
}

void HomePage::slotShowSongs3()
{
    QString tip = "绅士";
    emit signalShowWidget();
    emit signalShowMusicsFromTip(tip);
}

void HomePage::slotShowSongs4()
{
    QString tip = "几个薛之谦";
    emit signalShowWidget();
    emit signalShowMusicsFromTip(tip);
}

void HomePage::slotShowSongs5()
{
    QString tip = "渡";
    emit signalShowWidget();
    emit signalShowMusicsFromTip(tip);
}

void HomePage::slotAddMusicTip(QString album,QImage image)
{
    if(row == 2 && column == 0)
    {
        row = 0;
        column = 0;
        m_albumsName.clear();
    }
    QWidget *widget = new QWidget;
    QLabel *label = new QLabel(album);
    label->setFont(QFont("Black",10,25));
    label->setAlignment(Qt::AlignCenter);
    label->setFixedSize(175,30);
    QPushButton *picture = new QPushButton;
    QPixmap pix = QPixmap::fromImage(image,Qt::AutoColor);
    QSize sz(195,110);
    pix.scaled(sz,Qt::KeepAspectRatio);
    QIcon icon;
    icon.addPixmap(pix);
    //picture->setPixmap(pix);
    picture->setIcon(icon);
    picture->setIconSize(sz);
    picture->setFixedSize(175,110);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(picture,Qt::AlignTop);
    layout->addWidget(label);
    widget->setFixedSize(175,150);
    widget->setLayout(layout);
    table->setCellWidget(row,column,widget);
    m_albumsName.push_back(album);

    if(column == 3)
    {
        column = 0;
        row++;
    }
    else if(row == 2)
    {
        row = 0;
        column = 0;
        m_albumsName.clear();
        table->clear();
    }
    else
        column++;
}

void HomePage::slotShowMusicsFromTip()
{
    int row1 = table->currentRow();
    int column1 = table->currentColumn();
    int sum = row1*4 + column1;
    qDebug() <<  row1 << column1 << sum << "应该查询的表";
    QString tip = m_albumsName.at(sum);
    //tip = "初学者";
    emit signalShowWidget();
    emit signalShowMusicsFromTip(tip);
}

void HomePage::slotShowMusics()
{

}
