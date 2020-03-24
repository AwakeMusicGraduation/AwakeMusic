#ifndef SINGERTABLE_H
#define SINGERTABLE_H

#include <QWidget>
#include <QSqlTableModel>

namespace Ui {
class SingerTable;
}

class SingerTable : public QWidget
{
    Q_OBJECT

public:
    explicit SingerTable(QWidget *parent = nullptr);
    ~SingerTable();
    void updateDB();
    void revertDB();
    void appendDB();
    void deleteDB();
    void ascendDB();
    void descendDB();
    void queryDB(QString);
    void showDB();

private:
    void initUI();

private:
    Ui::SingerTable *ui;
    QSqlTableModel *model;
};

#endif // SINGERTABLE_H
