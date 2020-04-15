#include "homepage.h"
#include <QLabel>
#include <QFrame>
#include <QVBoxLayout>
#include <QRect>
#include "animatedwallwg.h"
#include <QHeaderView>
#include <QPushButton>

HomePage::HomePage(QWidget *parent):QTableWidget (parent)
{
    initform();
    initconnect();
}

void HomePage::initform()
{
    m_mainlayout = new QVBoxLayout(this);

    m_home = new QLabel("首页",this);
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

    QTableWidgetItem *l = new QTableWidgetItem("hello");
    QTableWidgetItem *m = new QTableWidgetItem("Micheal");

    table->setItem(0,0,l);
    table->setItem(0,1,m);
    table->show();


}

void HomePage::initconnect()
{

}

void HomePage::slotAddMusicTip(QString album,QImage image)
{
    QWidget *widget = new QWidget;
    QLabel *label = new QLabel(album);
    QPushButton *picture = new QPushButton;
    QPixmap pix = QPixmap::fromImage(image,Qt::AutoColor);
    QIcon icon;
    icon.addPixmap(pix);
    picture->setIcon(icon);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(picture);
    layout->addWidget(label);
    widget->setFixedSize(175,140);
    widget->setLayout(layout);
    table->setCellWidget(row,column,widget);
    m_albumsName.push_back(album);
    if(column == 3)
    {
        column = 0;
        row++;
    }
    else
        column++;
}

void HomePage::slotShowMusics()
{

}
