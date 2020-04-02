#include "musicsongslists.h"
#include "songmenu.h"
#include <QVBoxLayout>
#include <QHeaderView>
#include <QContextMenuEvent>
#include <QDebug>
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>


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
    this->addItemContent("我喜欢");
}

void MusicSongsLists::initConnect()
{
    connect(this,SIGNAL(cellClicked(int,int)),
            this,SLOT(slotCellClicked(int,int)));
    connect(m_menu,SIGNAL(signalAddNewList()),
            this,SLOT(slotAddNewPlayList()));
    connect(m_menu,SIGNAL(signalDeleteList()),
            this,SLOT(slotDeletePlayList()));
//    connect(push,&QPushButton::clicked,
//            this,&MusicSongsLists::slotCreateList);
//    connect(m_menu,SIGNAL(signalRename()),
//            this,SLOT(slotRename()));
}

void MusicSongsLists::slotCellClicked(int row, int column)
{
    emit signalShowList(row);
}

//创建列表时弹出对话框
void MusicSongsLists::slotAddNewPlayList()
{
    d = new QDialog(this);
    d->setFixedSize(200,100);
    d->setObjectName("add");
    d->setStyleSheet("#add {background-image:url(:/image/skin/11.png)}");
    m = new QLineEdit(d);
    push = new QPushButton(d);
    push->move(50,50);
    push->setText("确定");
    d->show();
    connect(push,&QPushButton::clicked,
            this,&MusicSongsLists::slotCreateList);//创建一个新的列表

   // this->addItemContent(m->text().trimmed());
   // emit signalAddNewList();

}

void MusicSongsLists::slotCreateList()
{
    QString label = "creatlist";
    QString s = m->text().trimmed();
    this->addItemContent(m->text().trimmed());
    emit signalCreateSongsList(label,user,s);
    d->hide();

}

void MusicSongsLists::slotUpdateList(std::vector<QString> userMessage)
{
    int total = this->rowCount();
    qDebug() << total;
    for(int i = 4; i <= total;i++)
    {
        removeRow(i);
        total--;
        i--;
    }
    for(auto l:userMessage)
    {
        this->addItemContent(l);
    }
}

void MusicSongsLists::slotDeletePlayList()
{

    int rowIndex = currentRow();
    QString name = this->item(rowIndex,0)->text();
    QString label = "deletelist";
    if (rowIndex != 0)
    {
        removeRow(rowIndex);
        emit signalDeleteList(rowIndex);
        emit signalDeleteListFromServer(label,user,name);
    }
}

void MusicSongsLists::contextMenuEvent(QContextMenuEvent *event)
{
    //右键显示菜单
    m_menu->exec(QCursor::pos());
    //窗口关闭
    event->accept();
}
