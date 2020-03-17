#ifndef DATABASE_H
#define DATABASE_H

#include <QTextCodec>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTime>
#include <QSqlError>
#include <QtDebug>
#include <QSqlDriver>
#include <QSqlRecord>

class DataBase
{
public:
    bool createConnection();  //创建一个连接
    bool createTable();       //创建数据库表
    bool insert(QString name,QString password);            //插入数据
    bool queryAll(QString name,QString password);          //查询所有信息
    bool updateById(int id);  //更新
    bool deleteById(int id);  //删除
    bool sortById();          //排序
private:
    QSqlDatabase db;
};

#endif // DATABASE_H
