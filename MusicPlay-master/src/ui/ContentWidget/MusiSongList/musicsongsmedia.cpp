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
#define MusicPath "rtsp://192.168.0.14/mp3"


MusicSongsMedia::MusicSongsMedia(QWidget *parent)
:QTableWidget(parent)
{
    initMenu();
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
}

void MusicSongsMedia::initConnect()
{
    connect(this,SIGNAL(cellDoubleClicked(int,int)),
            this,SLOT(slotCellDoubleClicked(int,int)));

    //connect(action,SIGNAL(triggered()),this,SIGNAL(signalObtainListName()));

}

void MusicSongsMedia::initMenu()
{
    m_menu = new QMenu();
    //        slot();
    QAction *actionPlayMusic = new QAction("播放", this);
    QAction *actionNextPlay = new QAction("下一首播放", this);
    m_menu->addAction(actionPlayMusic);
    m_menu->addAction(actionNextPlay);
    m_menu->addSeparator();

    m_furtherMenu = new QMenu("加入播放列表");

    m_menu->addMenu(m_furtherMenu);

    connect(actionPlayMusic, &QAction::triggered,this,&MusicSongsMedia::slotPlayMusic);
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

void MusicSongsMedia::slotPlayMusic()
{
    qDebug()<<"播放音乐";
    int row = currentRow();
    QString songName = item(row,0)->text();
    QString songPinYin = getMusicPinYin(songName);
    qDebug() << row << songName << songPinYin;
    emit signalShowMediaLrc(songPinYin);
    emit signalPlayMediaMusic(MusicPath + songPinYin + ".mp3");
    emit signalShowPicture(songName);
}

void MusicSongsMedia::contextMenuEvent(QContextMenuEvent *event)
{
    emit signalObtainListName();
    QPoint p = event->pos();
    QModelIndex index = this->indexAt(p);
    qDebug() << index.row();
    if(index.row()>=0){
    m_menu->exec(QCursor::pos());
    }
    event->accept();
}


void MusicSongsMedia::slotReceiveListName(std::vector<QString> listname)
{
    qDebug() << "初始化二级菜单";
    QAction *action1;
    if(!listname.empty()){
        m_furtherMenu->clear();
        for(auto l:listname)
        {
            qDebug() <<"接收到列表名" << l << "listnamename";
            action1 = new QAction(l,this);
            m_furtherMenu->addAction(action1);
            m_furtherMenu->addSeparator();
        }
    }
    else {
        m_furtherMenu->clear();
        action1 = new QAction("无列表，请新增列表");
        m_furtherMenu->addAction(action1);
    }
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
