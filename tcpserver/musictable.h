#ifndef MUSICTABLE_H
#define MUSICTABLE_H

#include <QWidget>
#include <QTableView>
#include <QStandardItemModel>
#include <QSqlTableModel>
#include "sqltable.h"

namespace Ui {
class MusicTable;
}

class MusicTable : public QWidget
{
    Q_OBJECT

public:
    explicit MusicTable(QWidget *parent = nullptr);
    ~MusicTable();
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
    Ui::MusicTable *ui;
    QSqlTableModel *model;
};

#endif // MUSICTABLE_H
