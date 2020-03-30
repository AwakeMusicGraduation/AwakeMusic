#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include "sqltable.h"
#include "singertable.h"
#include "musictable.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initUI();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

public slots:
    void receiveServer();

public:
        QLabel *label;

private:
    Ui::MainWindow *ui;

    Sqltable *m_pCreateDb;
//    QTableView *m_pTableView;
    MusicTable *m_ptab;
    SingerTable *m_psingerTab;
    QSqlTableModel *modelM;
    QSqlTableModel *modelS;
};

#endif // MAINWINDOW_H
