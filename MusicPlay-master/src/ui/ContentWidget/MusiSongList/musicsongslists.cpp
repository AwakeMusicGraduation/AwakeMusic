#include "musicsongslists.h"
#include "songmenu.h"
#include <QVBoxLayout>
#include <QHeaderView>
#include <QContextMenuEvent>
#include <QDebug>


MusicSongsLists::MusicSongsLists(QWidget *parent)
:QTableWidget(parent)
{
    initForm();
    initWidget();
    initConnect();
}

void MusicSongsLists::addItemContent(QString content)
{
    QTableWidgetItem *item = new QTableWidgetItem (content);
    item->setTextAlignment(Qt::AlignLeft |Qt::AlignVCenter);
    int rowIndex = rowCount();
    if (rowIndex >= 0)
    {
        //总函数加1
        setRowCount(rowIndex + 1);
        //添加一条记录到表格中来
        setItem(rowIndex,0,item);
    }
}

void MusicSongsLists::initForm()
{
    setFocusPolicy(Qt::NoFocus);
    setColumnCount(1);
    setRowCount(0);
    setShowGrid(true);//display the grid
    setEditTriggers(QAbstractItemView::NoEditTriggers);     //设置表格不能编辑
    setSelectionBehavior(QAbstractItemView::SelectRows);    //设置整行选中
    setSelectionMode(QAbstractItemView::SingleSelection);
//    horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    verticalHeader()->setDefaultSectionSize(45);

    QHeaderView *headerview = horizontalHeader();
    headerview->setVisible(false);
    headerview->resizeSection(0, 300);
    //    headerview->resizeSection(1, 20);
    //    headerview->resizeSection(2, 40);
    verticalHeader()->setVisible(false);
    QVBoxLayout *mainLayout = new QVBoxLayout;
    setLayout(mainLayout);

    m_menu = new SongMenu(this);
}

void MusicSongsLists::initWidget()
{
    this->addItemContent("默认列表");
    this->addItemContent("推荐列表");
    this->addItemContent("分类列表");
}

void MusicSongsLists::initConnect()
{
    connect(this,SIGNAL(cellClicked(int,int)),
            this,SLOT(slotCellClicked(int,int)));
    connect(m_menu,SIGNAL(signalAddNewList()),
            this,SLOT(slotAddNewPlayList()));
    connect(m_menu,SIGNAL(signalDeleteList()),
            this,SLOT(slotDeletePlayList()));
//    connect(m_menu,SIGNAL(signalRename()),
//            this,SLOT(slotRename()));
}

void MusicSongsLists::slotCellClicked(int row, int column)
{
    emit signalShowList(row);
}

void MusicSongsLists::slotAddNewPlayList()
{
    this->addItemContent("新建列表");
    emit signalAddNewList();
}

void MusicSongsLists::slotDeletePlayList()
{
    int rowIndex = currentRow();
    if (rowIndex != 0)
    {
        removeRow(rowIndex);
        emit signalDeleteList(rowIndex);
    }
}

void MusicSongsLists::contextMenuEvent(QContextMenuEvent *event)
{
    //右键显示菜单
    m_menu->exec(QCursor::pos());
    //窗口关闭
    event->accept();
}
