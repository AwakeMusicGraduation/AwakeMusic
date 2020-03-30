#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "server.h"
#include <QWidget>
#include <QHBoxLayout>
#include <QSqlTableModel>
#include <QSettings>
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Server *server = new Server;
//    server->show();
    connect(server,SIGNAL(sendToMainWindow()),this, SLOT(receiveServer()));
    initUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initUI()
{
    m_ptab = new MusicTable;
    ui->tabWidget->addTab(m_ptab,tr("歌曲"));
    m_psingerTab = new SingerTable;
    ui->tabWidget->addTab(m_psingerTab, tr("歌手"));
}

void MainWindow::on_pushButton_clicked()
{
    int i=ui->tabWidget->currentIndex();
    switch (i) {
    case 0:
        m_ptab->updateDB();
        break;
    case 1:
        m_psingerTab->updateDB();
    }

}

void MainWindow::on_pushButton_2_clicked()
{
    int i=ui->tabWidget->currentIndex();
    switch (i) {
    case 0:
        m_ptab->revertDB();
        break;
    case 1:
        m_psingerTab->revertDB();
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    int i=ui->tabWidget->currentIndex();
    switch (i) {
    case 0:
        m_ptab->appendDB();
        break;
    case 1:
        m_psingerTab->appendDB();
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    int i=ui->tabWidget->currentIndex();
    switch (i) {
    case 0:
        m_ptab->deleteDB();
        break;
    case 1:
        m_psingerTab->deleteDB();
    }
}

void MainWindow::on_pushButton_5_clicked()
{
    int i=ui->tabWidget->currentIndex();
    switch (i) {
    case 0:
        m_ptab->ascendDB();
        break;
    case 1:
        m_psingerTab->ascendDB();
    }
}

void MainWindow::on_pushButton_6_clicked()
{
    int i=ui->tabWidget->currentIndex();
    switch (i) {
    case 0:
        m_ptab->descendDB();
        break;
    case 1:
        m_psingerTab->descendDB();
    }
}

void MainWindow::receiveServer()
{
    qDebug()<<"发送成功";
    ui->label->setText("发送成功");
}
