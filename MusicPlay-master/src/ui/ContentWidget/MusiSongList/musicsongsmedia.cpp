#include "musicsongsmedia.h"
#include <QVBoxLayout>
#include <QHeaderView>
#include <QDebug>
//#define MusicPath "rtsp://10.253.241.175/mp3/"
#define MusicPath "rtsp://192.168.43.46/"


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
    headerview->resizeSection(1, 20);
    headerview->resizeSection(2, 40);
    verticalHeader()->setVisible(false);
    QVBoxLayout *mainLayout = new QVBoxLayout;
    setLayout(mainLayout);
}

void MusicSongsMedia::initConnect()
{
    connect(this,SIGNAL(cellDoubleClicked(int,int)),
            this,SLOT(slotCellDoubleClicked(int,int)));
}

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
}
