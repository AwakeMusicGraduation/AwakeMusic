#include "musiccenterwidget.h"
#include <QHeaderView>
#include <QDebug>

MusicCenterWidget::MusicCenterWidget()
{
    initForm();
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
    setSelectionBehavior(QAbstractItemView::SelectColumns);
    horizontalHeader()->setDefaultSectionSize(45);               //设置列宽
    horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);//禁止鼠标拖动缩放行列宽
    horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    setColumnWidth(0, 300);                                    //设置第一列宽度
    setColumnWidth(1,100);
    setColumnWidth(2,100);
}
