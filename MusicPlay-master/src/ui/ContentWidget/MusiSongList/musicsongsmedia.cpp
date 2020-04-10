#include "musicsongsmedia.h"
#include "controlvalues.h"
#include <QVBoxLayout>
#include <QHeaderView>
#include <QDebug>
#include <QMenu>
#include <QAction>
#include <QContextMenuEvent>
#include <QActionGroup>
//#define MusicPath "rtsp://10.253.241.175/mp3/"
#define MusicPath "rtsp://192.168.0.14/mp3/"


MusicSongsMedia::MusicSongsMedia(QWidget *parent)
:QTableWidget(parent)
{
    initForm();
    initConnect();
//    slotAddItem("消愁","毛不易","消愁");
//    slotAddItem("song","","");
//    slotSaveMusicInfo("消愁","xiaochou");
//    slotSaveMusicInfo("song","song");
}

void MusicSongsMedia::slotSaveMusicInfo(QString name, QString pinyin)
{
    m_musicInfo[name] = pinyin;
}

void MusicSongsMedia::slotShowMusics(QString name, QString pinyin)
{
    slotAddItem(name,"","");
    slotSaveMusicInfo(name,pinyin);
}

QString MusicSongsMedia::getMusicPinYin(QString name)
{
    return m_musicInfo.value(name);
}

void MusicSongsMedia::removeAllItem()
{
    setRowCount(0);
    clearContents();
}

void MusicSongsMedia::initForm()
{
    this->setStyleSheet("selection-background-color:lightblue;");
    setAlternatingRowColors(true);
    setFixedWidth(CENTERWIDGET_RIGHT);
    setFocusPolicy(Qt::NoFocus);
    setColumnCount(3);
    setRowCount(0);
    setShowGrid(false);
    setEditTriggers(QAbstractItemView::NoEditTriggers);     //设置表格不能编辑
    setSelectionBehavior(QAbstractItemView::SelectRows);    //设置整行选中
    setSelectionMode(QAbstractItemView::SingleSelection);
//    horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    verticalHeader()->setDefaultSectionSize(45);

    QHeaderView *headerview = horizontalHeader();
    QStringList header;
    header << "歌曲名" << "歌手" << "专辑" ;
    setHorizontalHeaderLabels(header);
    headerview->setStretchLastSection(true);
    headerview->setVisible(true);
    headerview->resizeSection(0, 300);
    headerview->resizeSection(1, 150);
    headerview->resizeSection(2, 150);
    verticalHeader()->setVisible(false);
    QVBoxLayout *mainLayout = new QVBoxLayout;
    setLayout(mainLayout);

    menu = new QMenu();
    action = new QAction("加入列表",this);
    menu->addAction(action);
    group = new QActionGroup(this);
}

void MusicSongsMedia::initConnect()
{
    connect(this,SIGNAL(cellDoubleClicked(int,int)),
            this,SLOT(slotCellDoubleClicked(int,int)));

    connect(action,&QAction::triggered,this,&MusicSongsMedia::slot);
    //connect(action,SIGNAL(triggered()),this,SIGNAL(signalObtainListName()));
    connect(group,&QActionGroup::triggered,this,&MusicSongsMedia::slotResponse);

}

void MusicSongsMedia::slot()
{
    qDebug() << "begin";
    emit signalObtainListName();
}

//显示搜索结果
void MusicSongsMedia::slotAddItem(QString title, QString singer, QString album)
{
    QTableWidgetItem *item1 = new QTableWidgetItem (title);
    QTableWidgetItem *item2 = new QTableWidgetItem (singer);
    QTableWidgetItem *item3 = new QTableWidgetItem (album);
    item1->setTextAlignment(Qt::AlignLeft |Qt::AlignVCenter);
    item2->setTextAlignment(Qt::AlignLeft |Qt::AlignVCenter);
    item3->setTextAlignment(Qt::AlignCenter |Qt::AlignVCenter);
    int rowIndex = rowCount();
    if (rowIndex >= 0)
    {
        //总函数加1
        setRowCount(rowIndex + 1);
        //添加一条记录到表格中来
        setItem(rowIndex,0,item1);
        setItem(rowIndex,1,item2);
        setItem(rowIndex,2,item3);
    }
}

void MusicSongsMedia::slotCellDoubleClicked(int row, int cloumn)
{
    QString songName = item(row,0)->text();
    QString songPinYin = getMusicPinYin(songName);
    emit signalShowMediaLrc(songPinYin);
    emit signalPlayMediaMusic(MusicPath + songPinYin + ".mp3");
    emit signalShowPicture(songName);
}

void MusicSongsMedia::contextMenuEvent(QContextMenuEvent *event)
{
    //menu = new QMenu();
    //furtherMenu = new QMenu();
    //右键显示菜单
    //action = new QAction("加入列表",this);
    //QAction *action_1 = new QAction("我喜欢",this);
    //menu->addAction(action);
    //furtherMenu->addAction(action_1);
    menu->exec(QCursor::pos());
    furtherMenu->exec(QCursor::pos());
    //furtherMenu->exec(QCursor::pos());
    //connect(action,SIGNAL(triggered()),this,SIGNAL(signalObtainListName()));
    //窗口关闭
    event->accept();
}


void MusicSongsMedia::slotReceiveListName(std::vector<QString> listname)
{
    qDebug() << "accept";
    furtherMenu = new QMenu();
    //QActionGroup *group = new QActionGroup(this);
    QAction *action1;
    qDebug() << "hello";
    //action1 = new QAction("hhh",this);
    for(auto l:listname)
    {
        qDebug() << l << "listnamename";
        //group->addAction(action1);
        action1 = new QAction(l,this);
        //action1->setText(l);
        furtherMenu->addAction(action1);
        group->addAction(action1);
        furtherMenu->addSeparator();
        //connect(action1,&QAction::triggered,furtherMenu,&QMenu::clear);
        //action1 = NULL;
    }
    //action->destroyed();
   // furtherMenu->exec(QCursor::pos());
}

void MusicSongsMedia::slotResponse(QAction *action)
{
    QString list = action->text();
    //furtherMenu->
    qDebug() << "like the name" << list;
    int row = currentRow();
    QString label = "addmusictolist";
    QString name = this->item(row,0)->text();
    QString singer = this->item(row,1)->text();
    QString album = this->item(row,2)->text();
    qDebug() << name << singer << album;
    emit signalAddMusicToList(label,list,name,singer,album);
}
