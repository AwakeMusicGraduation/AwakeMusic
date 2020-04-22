#include "database.h"

bool DataBase::createConnection()
{
    db = QSqlDatabase::addDatabase("QSQLITE","sqlite1");
    db.setDatabaseName("myQtDb.db");
    if(!db.open()){
        qDebug() << "无法建立连接";
        return false;
    }
    else {
        qDebug()<< "链接成功";
        return true;
    }
}

bool DataBase::createTable()
{
    db = QSqlDatabase::database("sqlite1");
    db.open();
    QSqlQuery query(db);
    bool success = query.exec("create table myUser(name varchar(20),passWord varchar(20))");

    if(success){
        qDebug() << QObject::tr("数据库表创建成功!\n");
        return true;
    }
    else {
        qDebug() <<QObject::tr("数据库表创建失败！\n");
        return false;
    }
}

bool DataBase::insert(QString name, QString password)
{
    QString _name;
    db.open();
    db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    query.exec("select * from myUser where name = '"+ name + "'");
    if(!query.exec()){
        qDebug() << query.lastError();
    }
    else {
        qDebug() << "注册查询成功";
    }
    while (query.next()) {
        _name = query.value(0).toString();
        qDebug() << _name;
        if(name == _name){
            return false;
        }
    }

    qDebug() << _name +" + " + name;
    query.prepare("insert into myUser values(?,?)");
    query.addBindValue(name);
    query.addBindValue(password);
    if(!query.execBatch())
    {
        QSqlError lastError = query.lastError();
        qDebug() << QString(QObject::tr("插入失败"));
        return false;
    }
    else{
        qDebug() << "插入成功";
    }

    if(!query.exec()){
        qDebug() << query.lastError();
    }
    db.close();
    return true;
}

//TODO 怎么查询
bool DataBase::queryAll(QString name, QString password)
{
    db.open();
    QString _name;
    QString _password;
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
        QSqlQuery query(db);
        query.exec("select * from myUser where name = '"+ name + "'");
        if(!query.exec()){
            qDebug() << query.lastError();
        }
        else {
            qDebug() << "查询成功";
        }
        while (query.next()) {
            _name = query.value(0).toString();
            _password = query.value(1).toString();
            if(_name == name && _password == password){
                qDebug() << "登录成功";
                return true;
            }
        }
        QSqlRecord rec = query.record();
        qDebug() << QObject::tr("automobil表字段数：" ) << rec.count();
        db.close();
        return false;
}





