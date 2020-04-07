//播放列表
#ifndef MYMEDIAPLAYLIST_H
#define MYMEDIAPLAYLIST_H

#include <QDockWidget>

class QTabWidget;
class QTableWidget;
class Music;

namespace Ui {
class MyMediaPlayList;
}

class MyMediaPlayList : public QDockWidget
{
    Q_OBJECT

public:
    explicit MyMediaPlayList(QWidget *parent = nullptr);
    ~MyMediaPlayList();

private:
    void initWidget();
    void initForm();
    void addContenItem(Music);
    void removeAllItem();//在添加一个新列表前先删除播放列表的内容

public slots:
    //将默认列表显示到播放列表中
    void slotReceiveList1(QList<Music> &);

private:
    Ui::MyMediaPlayList *ui;
    QTabWidget *m_tab;
    QTableWidget *m_table1;
    QTableWidget *m_table2;
};

#endif // MYMEDIAPLAYLIST_H
