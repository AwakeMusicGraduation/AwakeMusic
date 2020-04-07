#include "mymediaplaylist.h"
#include "ui_mymediaplaylist.h"
#include "musicsongslistwidget.h"
#include <QTabWidget>
#include <QTableWidget>
#include <QDebug>
#include <QMap>
#include <QVBoxLayout>
#include <QHeaderView>
#include "musiclistmenu.h"
#include "music.h"

MyMediaPlayList::MyMediaPlayList(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::MyMediaPlayList)
{
    ui->setupUi(this);

    initWidget();
    initForm();
    //    slotReceiveList1(m);
    //    QTableWidgetItem *item = new QTableWidgetItem("i.value()");
    //    item->setTextAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    //    int rowIndex=m_table1->rowCount();
    //    if(rowIndex>=0){
    //        m_table1->setRowCount(rowIndex+1);
    //        m_table1->setItem(rowIndex,0,item);
    //    }
}

MyMediaPlayList::~MyMediaPlayList()
{
    delete ui;
}

void MyMediaPlayList::initWidget()
{
    m_tab = new QTabWidget(this);
    m_table1 = new QTableWidget;
    m_tab->addTab(m_table1, tr("播放列表"));
    m_table2 = new QTableWidget(this);
    m_tab->addTab(m_table2, tr("历史记录"));

    this->setWidget(m_tab);
}

void MyMediaPlayList::initForm()
{
    //设置没有焦点，这样就可以避免删除时，不选中行也能删除的问题!
    setFocusPolicy(Qt::NoFocus);
    m_table1->setColumnCount(3);
    m_table1->setRowCount(0);
    m_table1->setShowGrid(false);//display the grid
    m_table1->setEditTriggers(QAbstractItemView::NoEditTriggers);     //设置表格不能编辑
    m_table1->setSelectionBehavior(QAbstractItemView::SelectRows);    //进整行选择
    m_table1->setSelectionMode(QAbstractItemView::SingleSelection);
    m_table1->verticalHeader()->setDefaultSectionSize(25);

    //进行“列设置”
//    m_table1->setSelectionBehavior(QAbstractItemView::SelectColumns);
    m_table1->setColumnWidth(0,300);

    QHeaderView *headerview = m_table1->horizontalHeader();
    headerview->setVisible(false);
    m_table1->verticalHeader()->setVisible(false);

    //鼠标右键初始化
    //    m_menu = new MusicListMenu(this);
}

void MyMediaPlayList::addContenItem(Music m)
{
    qDebug()<<m.name();
    int rowIndex = m_table1->rowCount();
    //总函数加1
    m_table1->setRowCount(rowIndex + 1);
    //添加一条记录到表格中来
    m_table1->setItem(rowIndex,0,new QTableWidgetItem(m.name()));
    m_table1->setItem(rowIndex,1,new QTableWidgetItem(m.singer()));
    m_table1->setItem(rowIndex,2,new QTableWidgetItem(m.album()));
}

void MyMediaPlayList::removeAllItem()
{
    m_table1->setRowCount(0);
    m_table1->clearContents();
}

void MyMediaPlayList::slotReceiveList1(QList<Music>  &musicname)
{
    qDebug()<<"接收到默认播放列表";
    removeAllItem();
    for(int i=0; i<musicname.size(); i++)
        addContenItem(musicname.at(i));
}



