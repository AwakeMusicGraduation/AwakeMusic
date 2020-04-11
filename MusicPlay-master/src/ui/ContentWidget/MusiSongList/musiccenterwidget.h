//显示列表界面
#ifndef MUSICCENTERWIDGET_H
#define MUSICCENTERWIDGET_H

#include <QTableWidget>

class MusicCenterWidget : public QTableWidget
{
public:
    MusicCenterWidget();

private:
    void initForm();
//    void initMusic();    //界面初始化内容
    void addContenItem(QStringList);

public slots:
    void slotFlushWidget(QList<QStringList>&);

};

#endif // MUSICCENTERWIDGET_H
