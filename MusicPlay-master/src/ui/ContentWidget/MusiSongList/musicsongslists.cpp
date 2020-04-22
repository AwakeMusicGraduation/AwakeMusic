#include "musicsongslists.h"
#include "songmenu.h"
#include "controlvalues.h"
#include <QVBoxLayout>
#include <QHeaderView>
#include <QContextMenuEvent>
#include <QDebug>
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QPixmap>
#include <QPalette>
#include <QMouseEvent>
#include <QHBoxLayout>


MusicSongsLists::MusicSongsLists(QWidget *parent)
    :QTableWidget(parent)
{

    initForm();
    initWidget();
    initConnect();
}

void MusicSongsLists::addItemContent(QString content)
{
    //    QTableWidgetItem *item = new QTableWidgetItem (content);//列表名
    QWidget *widget = new QWidget;
    QLabel *label1 = new QLabel;
    QLabel *label2 = new QLabel(content);
    QLabel *label3 = new QLabel;
    QPixmap *pic = new QPixmap(":/image/contextMenu/indicator_menu (1).png");
    QSize sz(5, 5);
    pic->scaled(sz,Qt::KeepAspectRatio);
    label1->setPixmap(*pic);
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(label1);
    layout->addWidget(label2);
    layout->addWidget(label3);
    widget->setFixedWidth(180);
    widget->setLayout(layout);
    //QLayoutItem *item = layout->layout()->takeAt(1);
    //QLabel *l = qobject_cast<QLabel*>(item->widget());
    //qDebug() << l->text() << "test";
    //    item->setTextAlignment(Qt::AlignLeft |Qt::AlignVCenter);
    //    label->setAlignment(Qt::AlignCenter);
    int rowIndex = rowCount();
    if (rowIndex >= 0)
    {
        //总函数加1
        listName.push_back(content);
        setRowCount(rowIndex + 1);
        //添加一条记录到表格中来
        //        setItem(rowIndex,1,item);
        setCellWidget(rowIndex,0,widget);
    }
    //QLayoutItem *item = layout->layout()->takeAt(1);
    //QLabel *l = (QLabel *)item->widget();
    //qDebug() << l->text() << "test";
}

void MusicSongsLists::initForm()
{
    setAlternatingRowColors(true);
    this->setStyleSheet("selection-background-color:lightblue;");
    setFixedWidth(CENTERWIDGET_LEFT);
    //    setFocusPolicy(Qt::NoFocus);
    setColumnCount(1);
    setRowCount(0);
    setShowGrid(false);//display the grid
    setEditTriggers(QAbstractItemView::NoEditTriggers);     //设置表格不能编辑
    setSelectionBehavior(QAbstractItemView::SelectRows);    //设置整行选中
    setSelectionMode(QAbstractItemView::SingleSelection);
    //    horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    verticalHeader()->setDefaultSectionSize(45);

    QHeaderView *headerview = horizontalHeader();
    headerview->setVisible(false);
    setColumnWidth(0,180);
    //    setColumnWidth(1,80);
    //    setColumnWidth(2,10);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    verticalHeader()->setVisible(false);
    //    QVBoxLayout *mainLayout = new QVBoxLayout;
    //    setLayout(mainLayout);

    m_menu = new SongMenu(this);
}

void MusicSongsLists::initWidget()
{
    this->addItemContent("本地音乐");
    this->addItemContent("推荐列表");
    this->addItemContent("分类列表");
    listName.clear();
    //this->addItemContent("我喜欢");
}

void MusicSongsLists::initConnect()
{
    connect(this,SIGNAL(cellClicked(int,int)),
            this,SLOT(slotCellClicked(int,int)));
    connect(m_menu,SIGNAL(signalAddNewList()),
            this,SLOT(slotAddNewPlayList()));
    connect(m_menu,SIGNAL(signalDeleteList()),
            this,SLOT(slotDeletePlayList()));
    //    connect(this,SIGNAL(cellEntered(int,int)),this,SLOT(cellEntered(int,int)));
}

void MusicSongsLists::slotCellClicked(int row, int column)
{
    QString list;
    if(row > 2)
    {
         list = listName[row-3];
    }
    else
    {
         list = "";
    }
    emit signalShowList(row,list);
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
    qDebug()<<label<<user<<s;
    d->hide();

}

void MusicSongsLists::slotObtainListName()
{
    qDebug() << "获取列名";
    int total = rowCount();
    qDebug() << total;
    std::vector<QString> listname;
    if(total <= 3)
    {
        emit signalSendListName(listName);
    }
    else{
       /* for(int i = 3; i < total; i++)
        {
            QString m = this->item(i,1)->text();
            qDebug() << m;
            listname.push_back(m);
        }*/
        emit signalSendListName(listName);
    }

}

void MusicSongsLists::slotUpdateList(std::vector<QString> userMessage)
{
    int total = rowCount();
    qDebug() << total;
    for(int i = 3; i <= total;i++)
    {
        removeRow(i);
        total--;
        i--;
    }
    listName.clear();
    for(auto l:userMessage)
    {
        this->addItemContent(l);
    }
}

void MusicSongsLists::slotDeletePlayList()
{
    QString name;
    int rowIndex = currentRow();
    QString label = "deletelist";
    if (rowIndex != 0 && rowIndex >2)
    {
        name = listName.at(rowIndex-3);
        std::vector<QString>::iterator m = listName.begin();
        while(m != listName.end())
        {
            if(*m == name)
                m = listName.erase(m);
            else
                m++;
        }
        //listName.at(rowIndex-3).clear();
        removeRow(rowIndex);
        emit signalDeleteList(rowIndex);
        emit signalDeleteListFromServer(label,user,name);
    }
    else
    {
        qDebug() << "无法删除";
    }
}

void MusicSongsLists::contextMenuEvent(QContextMenuEvent *event)
{
    //右键显示菜单
    m_menu->exec(QCursor::pos());
    //窗口关闭
    event->accept();
}
