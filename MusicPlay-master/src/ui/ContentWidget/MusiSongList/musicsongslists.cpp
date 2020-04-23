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
#include <QFileDialog>
#include "myhelper.h"
#include <QDebug>
#include <QBuffer>
#include <QImageReader>
#include <QImage>
#include <QPainter>

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
    label1->setObjectName("label1");
    QLabel *label2 = new QLabel(content);
    label2->setObjectName("label2");
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

}

void MusicSongsLists::addItemContentImage(QString content,QImage image)
{
    QWidget *widget = new QWidget;
    QLabel *label1 = new QLabel;
    label1->setObjectName("label1");
    label1->setFixedSize(35,25);
    QLabel *label2 = new QLabel(content);
    label2->setObjectName("label2");
    QLabel *label3 = new QLabel;
    QImage image1 = image.scaled(label1->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
    label1->setPixmap(QPixmap::fromImage(image1));
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(label1);
    layout->addWidget(label2);
    layout->addWidget(label3);
    widget->setFixedWidth(180);
    widget->setLayout(layout);

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

    //m_menu = new SongMenu(this);
}

void MusicSongsLists::initWidget()
{
    this->addItemContent("本地音乐");
    this->addItemContent("推荐列表");
    this->addItemContent("分类列表");
    listName.clear();
    //this->addItemContent("我喜欢");
}

void MusicSongsLists::insertItemContent(QString content, int row)
{
    QWidget *widget = new QWidget;
    QWidget *widget1 = this->cellWidget(row,0);
    QLabel *label1 = widget1->findChild<QLabel*>("label1");
    QLabel *label2 = new QLabel(content);
    label2->setObjectName("label2");
    QLabel *label3 = new QLabel;
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(label1);
    layout->addWidget(label2);
    layout->addWidget(label3);
    widget->setFixedWidth(180);
    widget->setLayout(layout);

    int rowIndex = rowCount();
    if (rowIndex >= 0)
    {
        //总函数加1
        //        listName.erase(listName.begin()+row);
        //        listName.insert(listName.begin()+row,content);
        //slotDeletePlayList();
        //insertRow(row);
        //添加一条记录到表格中来
        //        setItem(rowIndex,1,item);
        setCellWidget(row,0,widget);
    }
}

void MusicSongsLists::initConnect()
{
    connect(this,SIGNAL(cellClicked(int,int)),
            this,SLOT(slotCellClicked(int,int)));
   /* connect(m_menu,SIGNAL(signalAddNewList()),
            this,SLOT(slotAddNewPlayList()));
    connect(m_menu,SIGNAL(signalDeleteList()),
            this,SLOT(slotDeletePlayList()));
    connect(m_menu,SIGNAL(signalAddTipPicture()),
            this,SLOT(slotAddTipPicture()));*/
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

void MusicSongsLists::slotModifyPlayListNameWidget()
{
    d = new QDialog(this);
    d->setFixedSize(200,80);
    d->setObjectName("add");
    d->setStyleSheet("#add {background-image:url(:/image/skin/11.png)}");
    m = new QLineEdit(d);
    push = new QPushButton(d);
    push->move(50,50);
    push->setText("确定");
    currentrow = currentRow();
    d->show();
    connect(push,&QPushButton::clicked,
            this,&MusicSongsLists::slotModifyPlayListName);
}

void MusicSongsLists::slotModifyPlayListName()
{
    qDebug() << "修改列表槽";
    QString name =listName.at(currentrow-3);
    qDebug()<<"this is a bug" << name;
    QString label = "modifylist";
    QString s = m->text().trimmed();
    listName.at(currentrow-3) = s;
    insertItemContent(s,currentrow);
    emit signalModifySongsList(name,label,user,s);
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

void MusicSongsLists::slotUpdateList(std::vector<QString> userMessage,std::vector<QImage> images)
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
    int i = 0;
    for(auto l:userMessage)
    {
        if(images.at(i).isNull())
        {
            this->addItemContent(l);
        }
        else
        {
            this->addItemContentImage(l,images.at(i));
        }
        i++;
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
        //emit signalDeleteList(rowIndex);
        emit signalDeleteListFromServer(label,user,name);
    }
    else
    {
        qDebug() << "无法删除";
    }
}

void MusicSongsLists::slotAddTipPicture()
{
    qDebug() << "正在添加歌单图片";
    if(currentRow() > 2)
    {
    qDebug() << "正在添加歌单图片";
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFiles);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setNameFilters(myHelper::supportFormatsPicture());

    if(dialog.exec())
    {
        QStringList list = dialog.selectedFiles();
        QFileInfo finfo;
        QString filePath;

        if (list.isEmpty())
        {
            return;
        }
        //提取出图片名称
        foreach (QString str, list) {
            finfo = QFileInfo(str);
            filePath = finfo.filePath();
            qDebug() << filePath << "路径";
            QImage image;
            image.load(filePath);
            int row = currentRow();
            int column = currentColumn();
            QLabel *label1 = new QLabel;
            label1->setObjectName("label1");
            label1->setFixedSize(35,25);
            QImage image1 = image.scaled(label1->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
            label1->setPixmap(QPixmap::fromImage(image1));
            QWidget *item = this->cellWidget(row,column);
            QLabel* label2 = item->findChild<QLabel*>("label2");
            QString list = label2->text();
            qDebug() << list;
            QLabel *laber3 = new QLabel;
            QWidget *widget = new QWidget;
            QHBoxLayout *layout = new QHBoxLayout;
            layout->addWidget(label1);
            layout->addWidget(label2);
            layout->addWidget(laber3);
            widget->setFixedWidth(180);
            widget->setLayout(layout);
            setCellWidget(row,column,widget);
            emit signalAddTipPictureToServer(list,filePath);
       }
    }
    }
}

void MusicSongsLists::contextMenuEvent(QContextMenuEvent *event)
{
    SongMenu *m_menu = new SongMenu(this);
    connect(m_menu,SIGNAL(signalAddNewList()),
            this,SLOT(slotAddNewPlayList()));
    connect(m_menu,SIGNAL(signalDeleteList()),
            this,SLOT(slotDeletePlayList()));
    connect(m_menu,SIGNAL(signalAddTipPicture()),
            this,SLOT(slotAddTipPicture()));
    connect(m_menu,SIGNAL(signalModifyList()),this,SLOT(slotModifyPlayListNameWidget()));
    QAction *action = new QAction("修改列表名");
    QPoint p = event->pos();
    QModelIndex index = this->indexAt(p);
    qDebug() << index.row();
    if(index.row()>2){
            m_menu->addModifyAction(action);
    }
    //右键显示菜单
    m_menu->exec(QCursor::pos());
    //窗口关闭
    event->accept();
}
