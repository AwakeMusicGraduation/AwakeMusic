#include "musiccenterwidget.h"
#include <QHeaderView>
#include <QDebug>
#include "musicsongslistwidget.h"

MusicCenterWidget::MusicCenterWidget()
{
    initForm();
    initMusic();
}

void MusicCenterWidget::initForm()
{
    qDebug()<<"初始化中心界面";
    setColumnCount(3);
    setRowCount(0);
    QStringList sListHeader;
    sListHeader << "音乐标题" << "歌手" << "专辑";
    setHorizontalHeaderLabels(sListHeader);
    setShowGrid(false);
    setEditTriggers(QAbstractItemView::NoEditTriggers);     //设置表格不能编辑
    setSelectionBehavior(QAbstractItemView::SelectRows);
    horizontalHeader()->setDefaultSectionSize(45);               //设置列宽
    horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);//禁止鼠标拖动缩放行列宽
    horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    setColumnWidth(0, 300);                                    //设置第一列宽度
    setColumnWidth(1,100);
    setColumnWidth(2,100);
}

void MusicCenterWidget::addContenItem(QStringList m)
{
//    qDebug()<<"在中心界面添加音乐信息2";
//    qDebug()<<m.name();
    int rowIndex = rowCount();
    //总函数加1
    setRowCount(rowIndex + 1);
    //添加一条记录到表格中来
    setItem(rowIndex,0,new QTableWidgetItem(m.at(0)));
    setItem(rowIndex,1,new QTableWidgetItem(m.at(1)));
    setItem(rowIndex,2,new QTableWidgetItem(m.at(2)));
}

void MusicCenterWidget::slotFlushWidget(QList<QStringList> &m)
{
    for(int i=0; i<m.size(); i++)
        addContenItem(m.at(i));
}


void MusicCenterWidget::initMusic()
{
    qDebug()<<"在中心界面添加音乐信息1";
    MusicSongsListWidget *m = new MusicSongsListWidget(this);
    m->hide();
    QList<QStringList> music = m->returnMusicInfo();
    qDebug()<<music.size();
    for(int i=0; i<music.size(); i++){

        addContenItem(music.at(i));
    }
}



