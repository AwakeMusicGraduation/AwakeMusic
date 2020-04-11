#include "mymediaplaylist.h"
#include "ui_mymediaplaylist.h"
#include "musicsongslistwidget.h"
#include <QTabWidget>
#include <QTableWidget>
#include <QDebug>
#include <QMap>
#include <QMenu>
#include <QVBoxLayout>
#include <QHeaderView>
#include "playmusic.h"

MyMediaPlayList::MyMediaPlayList(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::MyMediaPlayList)
{
    ui->setupUi(this);

    initWidget();
    initForm();
    initMenu();
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
    this->setStyleSheet("selection-background-color:lightblue;");
    m_table1->setAlternatingRowColors(true);
    m_table2->setAlternatingRowColors(true);
    //设置没有焦点，这样就可以避免删除时，不选中行也能删除的问题!
    setFocusPolicy(Qt::NoFocus);
    m_table1->setColumnCount(3);
    m_table1->setRowCount(0);
    m_table1->setShowGrid(false);//display the grid
    m_table1->setEditTriggers(QAbstractItemView::NoEditTriggers);     //设置表格不能编辑
    m_table1->setSelectionBehavior(QAbstractItemView::SelectRows);    //进整行选择
    m_table1->setSelectionMode(QAbstractItemView::SingleSelection);
    m_table1->verticalHeader()->setDefaultSectionSize(25);
    m_table1->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);    //设置不可滑动
    m_table1->setContextMenuPolicy(Qt::CustomContextMenu);//允许m_table1接收QWidget::customContextMenuRequested()信号。


    //进行“列设置”
//    m_table1->setSelectionBehavior(QAbstractItemView::SelectColumns);
    m_table1->setColumnWidth(0,250);

    QHeaderView *headerview = m_table1->horizontalHeader();
    headerview->setVisible(false);
    m_table1->verticalHeader()->setVisible(false);

    //鼠标右键初始化
    //    m_menu = new MusicListMenu(this);
}

void MyMediaPlayList::initMenu()
{
    qDebug()<<"初始化菜单";
    m_menu = new QMenu(m_table1);

    QAction *actionpPlayMusic = new QAction("播放",this);
    QAction *actionAddMusicToList = new QAction("收藏到歌单",this);
    QAction *actionDeleteFromPlayList = new QAction("从列表中删除",this);

    m_menu->addAction(actionpPlayMusic);
    m_menu->addSeparator();
    m_menu->addAction(actionAddMusicToList);
    m_menu->addSeparator();
    m_menu->addAction(actionDeleteFromPlayList);

    connect(m_table1, SIGNAL(customContextMenuRequested(QPoint)),this, SLOT(slotShowQmenu(QPoint)));
}

void MyMediaPlayList::addContenItem(QStringList m)
{
    qDebug()<<m.at(0);
    int rowIndex = m_table1->rowCount();
    //总函数加1
    m_table1->setRowCount(rowIndex + 1);
    //添加一条记录到表格中来
    m_table1->setItem(rowIndex,0,new QTableWidgetItem(m.at(0)));
    m_table1->setItem(rowIndex,1,new QTableWidgetItem(m.at(1)));
    m_table1->setItem(rowIndex,2,new QTableWidgetItem(m.at(2)));
}

void MyMediaPlayList::removeAllItem()
{
    m_table1->setRowCount(0);
    m_table1->clearContents();
}

void MyMediaPlayList::slotReceiveList1(QList<QString>  &musicname)
{
    PlayMusic playmusic;
    qDebug()<<"接收到默认播放列表";
    removeAllItem();
    for(int i=0; i<musicname.size(); i++){
        QStringList s;
        s=playmusic.ResolutionMusicPath(musicname.at(i));
        addContenItem(s);
    }
    //        addContenItem(musicname.at(i));
}

void MyMediaPlayList::slotShowQmenu(QPoint pos)
{
    qDebug() << "接收到菜单信号";
QModelIndex index = m_table1->indexAt(pos);
if(index.row()>=0){
    m_menu->exec(QCursor::pos());
}
}



