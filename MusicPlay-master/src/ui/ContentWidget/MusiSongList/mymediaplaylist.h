#ifndef MYMEDIAPLAYLIST_H
#define MYMEDIAPLAYLIST_H

#include <QDockWidget>

class QTabWidget;
class QTableWidget;

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
    void addContenItem(QString);
    void removeAllItem();

public slots:
    //将默认列表显示到播放列表中
    void slotReceiveList1(QMap<int,QString> &);

private:
    Ui::MyMediaPlayList *ui;
    QTabWidget *m_tab;
    QTableWidget *m_table1;
    QTableWidget *m_table2;
};

#endif // MYMEDIAPLAYLIST_H
