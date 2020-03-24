#include "singertable.h"
#include "ui_singertable.h"
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>

SingerTable::SingerTable(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SingerTable)
{
    ui->setupUi(this);
    model = new QSqlTableModel;
    model->setTable("singer");
    initUI();
}

SingerTable::~SingerTable()
{
    delete ui;
}

void SingerTable::initUI()
{
    qDebug()<<"开始初始化singertable!";
    model->select();
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tableView->setModel(model);
    model->setHeaderData(1, Qt::Orientation::Horizontal, "歌手");
    model->setHeaderData(2, Qt::Orientation::Horizontal, "类别");
}

//提交修改
void SingerTable::updateDB()
{
    qDebug()<<"提交";
    model->database().transaction();
    if(model->submitAll()){
        model->database().commit();
        QMessageBox::information(this ,tr("提示") , tr("修改成功!"));
    }
    else{
        model->database().rollback();
        QMessageBox::warning(this, tr("tableModel"),
                             tr("数据库错误: %1").arg(model->lastError().text()));
        QMessageBox::information(this ,tr("提示") , tr("修改失败!"));
    }
}

//撤销修改
void SingerTable::revertDB()
{
    model->revertAll();
}

//添加记录
void SingerTable::appendDB()
{
    //获得表的行数
    int rowNum=model->rowCount();
    int id=rowNum+1;

    //添加一行
    model->insertRow(rowNum);
    model->setData(model->index(rowNum,0), id);
}

//删除该行
void SingerTable::deleteDB()
{
    int curRow=ui->tableView->currentIndex().row();
    //删除该行
    model->removeRow(curRow);
    int ok=QMessageBox::warning(this,tr("删除当前行"),tr("你确定删除当前行吗？"),QMessageBox::Yes, QMessageBox::No);
    if(ok==QMessageBox::No){
        model->revert();
    }
    else {
        model->submitAll();
    }
}

void SingerTable::ascendDB()
{
    model->setSort(0,Qt::AscendingOrder);
    model->select();
}

void SingerTable::descendDB()
{
    model->setSort(0,Qt::DescendingOrder);
    model->select();
}

void SingerTable::queryDB(QString name)
{
    model->setFilter(QString("name='%1'").arg(name));
    model->select();
}

void SingerTable::showDB()
{
    model->setTable("student");
    model->select();
}
