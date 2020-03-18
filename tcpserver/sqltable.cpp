#include "sqltable.h"
#include "singer.h"
#include "album.h"
#include <random>

Sqltable::Sqltable()
{  

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("MusicPlayer.db");
    if(db.open()){
        qDebug() << "Database Opened";

        QString create_sql = "create table music (id int primary key, name varchar(30), singer varchar(30), lyric varchar(100), album varchar(30), audiopath varchar(30))"; //创建数据表

        //QString select_all_sql = "select * from music";
        QString create_sql1 = "create table singer (id int primary key, name varchar(30),category varchar(30))"; //创建数据表

        QString create_sql2 = "create table album (id int primary key, name varchar(30), startDate varchar(30),singername varchar(30))"; //创建数据表

        QString create_sql3 = "create table transform (name varchar(30), spell varchar(30))"; //创建数据表

        QSqlQuery sql_query1,sql_query2,sql_query3,sql_query4;
        sql_query1.prepare(create_sql);
        sql_query2.prepare(create_sql1);
        sql_query3.prepare(create_sql2);
        sql_query4.prepare(create_sql3);
        sql_query = sql_query1;
        sql_querySinger = sql_query2;
        sql_queryAlbum = sql_query3;
        sql_querySpell = sql_query4;
        if(!sql_query.exec()) //查看创建表是否成功
        {
            qDebug()<<QObject::tr("Table Create failed");
            qDebug()<<sql_query.lastError();
        }
        if(!sql_querySinger.exec()) //查看创建表是否成功
        {
            qDebug()<<QObject::tr("Table Create failed");
            qDebug()<<sql_querySinger.lastError();
        }
        if(!sql_queryAlbum.exec()) //查看创建表是否成功
        {
            qDebug()<<QObject::tr("Table Create failed");
            qDebug()<<sql_queryAlbum.lastError();
        }
        if(!sql_querySpell.exec()) //查看创建表是否成功
        {
            qDebug()<<QObject::tr("Table Create failed");
            qDebug()<<sql_querySpell.lastError();
        }
        else
        {
            qDebug()<< "Tables Created" ;
        }
    }


}

void Sqltable::insertParmeterTransform(QString name,QString spell)
{
    db.open();
    //QSqlQuery sql_query;
    QString insert_sql = "insert into transform values(?,?)";    //插入数据


    //插入数据
    sql_querySpell.prepare(insert_sql);


    sql_querySpell.addBindValue(name);
    sql_querySpell.addBindValue(spell);



    if(!sql_querySinger.execBatch())
    {
        qDebug()<<sql_querySpell.lastError();
    }
    else
    {
        qDebug()<<"插入记录成功";
    }
    if(!sql_querySpell.exec())
    {
        qDebug()<<sql_querySpell.lastError();
    }

    db.close();
}


void Sqltable::insertParmeter(int id, QString name, QString singer, QString lyric, QString album, QString audiopath)
{
    db.open();
    //QSqlQuery sql_query;
    QString insert_sql = "insert into music values(?,?,?,?,?,?)";    //插入数据


    //插入数据
    sql_query.prepare(insert_sql);


    sql_query.addBindValue(id);
    sql_query.addBindValue(name);
    sql_query.addBindValue(singer);
    sql_query.addBindValue(lyric);
    sql_query.addBindValue(album);
    sql_query.addBindValue(audiopath);
    if(!sql_query.execBatch())
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        qDebug()<<"插入记录成功";
    }
    if(!sql_query.exec())
    {
        qDebug()<<sql_query.lastError();
    }

    db.close();
}


//插入歌手信息
void Sqltable::insertParmeterSinger(int id, QString name,QString category)
{
    db.open();
    //QSqlQuery sql_query;
    QString insert_sql = "insert into singer values(?,?,?)";    //插入数据


    //插入数据
    sql_querySinger.prepare(insert_sql);


    sql_querySinger.addBindValue(id);
    sql_querySinger.addBindValue(name);
    sql_querySinger.addBindValue(category);


    if(!sql_querySinger.execBatch())
    {
        qDebug()<<sql_querySinger.lastError();
    }
    else
    {
        qDebug()<<"插入记录成功";
    }
    if(!sql_querySinger.exec())
    {
        qDebug()<<sql_querySinger.lastError();
    }

    db.close();
}

//插入专辑信息
void Sqltable::insertParmeterAlbum(int id, QString name, QString startDate,QString  singerName)
{
    db.open();
    //QSqlQuery sql_query;
    QString insert_sql = "insert into album values(?,?,?,?)";    //插入数据


    //插入数据
    sql_queryAlbum.prepare(insert_sql);


    sql_queryAlbum.addBindValue(id);
    sql_queryAlbum.addBindValue(name);
    sql_queryAlbum.addBindValue(startDate);
    sql_queryAlbum.addBindValue(singerName);

    if(!sql_queryAlbum.execBatch())
    {
        qDebug()<<sql_queryAlbum.lastError();
    }
    else
    {
        qDebug()<<"插入记录成功";
    }
    if(!sql_queryAlbum.exec())
    {
        qDebug()<<sql_queryAlbum.lastError();
    }

    db.close();
}

//查询spell
void Sqltable::queryTransform()
{
    QString select_all_sql = "select * from transform";
    //QSqlQuery sql_query1;
    db.open();
    //QSqlQuery sql_query;
    sql_querySpell.prepare(select_all_sql);
    //sql_query = sql_query1;

    if(!sql_querySpell.exec())
    {
        qDebug()<<sql_querySpell.lastError();
    }
    else
    {
        qDebug()<<"查询成功" ;
        while(sql_querySpell.next())
        {
            QString name = sql_querySpell.value(0).toString();
            QString spell = sql_querySpell.value(1).toString();



            qDebug()<<"checked";
            qDebug()<<QString("Name:%1  Spell:%2 " ).arg(name).arg(spell);
        }
    }
    db.close();
}

std::vector<Singer*> Sqltable::querySinger()
{
    Singer* singer;
    std::vector<Singer*> singers;
    QString select_all_sql = "select * from singer";
    //QSqlQuery sql_query1;
    db.open();
    //QSqlQuery sql_query;
    sql_querySinger.prepare(select_all_sql);
    //sql_query = sql_query1;

    if(!sql_querySinger.exec())
    {
        qDebug()<<sql_querySinger.lastError();
    }
    else
    {
        qDebug()<<"查询成功" ;
        while(sql_querySinger.next())
        {
            int id = sql_querySinger.value(0).toInt();
            QString name = sql_querySinger.value(1).toString();
            QString category = sql_querySinger.value(2).toString();
            singer = new Singer(name, category);
            singers.push_back(singer);
            qDebug()<<"checked";
            qDebug()<<QString("ID:%1  Name:%2 Category:%3 " ).arg(id).arg(name).arg(category);
        }
    }
    db.close();
    return singers;
}

std::vector<Album*> Sqltable::queryAlbum()
{
    std::vector<Album*> albums;
    Album *album;
    QString select_all_sql = "select * from album";
    //QSqlQuery sql_query1;
    db.open();
    //QSqlQuery sql_query;
    sql_queryAlbum.prepare(select_all_sql);
    //sql_query = sql_query1;

    if(!sql_queryAlbum.exec())
    {
        qDebug()<<sql_queryAlbum.lastError();
    }
    else
    {
        qDebug()<<"查询成功" ;
        while(sql_queryAlbum.next())
        {
            int id = sql_queryAlbum.value(0).toInt();
            QString name = sql_queryAlbum.value(1).toString();
            QString startTime = sql_queryAlbum.value(2).toString();
            QString singerName = sql_queryAlbum.value(3).toString();
            qDebug()<<"checked";
            qDebug()<<QString("ID:%1  Name:%2  starDate:%3  singerName:%4" ).arg(id).arg(name).arg(startTime).arg(singerName);
            album = new Album(name,startTime,singerName);
            albums.push_back(album);
            delete album;
            album = nullptr;
        }
    }
    db.close();
    return albums;
}

void Sqltable::query()
{
    QString select_all_sql = "select * from music";
    //QSqlQuery sql_query1;
    db.open();
    //QSqlQuery sql_query;
    sql_query.prepare(select_all_sql);
    //sql_query = sql_query1;

    if(!sql_query.exec())
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        qDebug()<<"查询成功" ;
        while(sql_query.next())
        {
            int id = sql_query.value(0).toInt();
            QString name = sql_query.value(1).toString();
            QString singer = sql_query.value(2).toString();
            QString lyric = sql_query.value(3).toString();
            QString album = sql_query.value(4).toString();
            QString audiopath = sql_query.value(5).toString();
            qDebug()<<"checked";
            qDebug()<<QString("ID:%1  Name:%2  singer:%3 lyric:%4 album:%5 audiopath:%6" ).arg(id).arg(name).arg(singer).arg(lyric).arg(album).arg(audiopath);
        }
    }
    db.close();
}


void Sqltable::deletemusic(QString name)
{
    db.open();
    QString delete_sql = "delete from music where name = ?";
    sql_query.prepare(delete_sql);
    sql_query.addBindValue(name);
    if(!sql_query.exec())
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        qDebug()<<"删除成功" ;

    }
    db.close();
}


void Sqltable::updatamusic(int id,QString name)
{
    db.open();
    QString update_sql = "update music set name = :name where id = :id";
    sql_query.prepare(update_sql);
    sql_query.bindValue(":name",name);
    sql_query.bindValue(":id",id);
    if(!sql_query.exec())
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        qDebug()<<"更新成功" ;

    }
    db.close();
}


Music* Sqltable::querysingle(QString name)
{
    Music *music;
    db.open();
    QString select_sql = "select * from music where name = '" + name +"'";
    sql_query.prepare(select_sql);
    //sql_query.addBindValue(name);
    if(!sql_query.exec())
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        qDebug()<<"查询成功" ;
        if(!sql_query.first())
        {
            db.close();
            return nullptr;
        }
        sql_query.previous();
        while(sql_query.next())
        {
            int id = sql_query.value(0).toInt();
            QString name1 = sql_query.value(1).toString();
            //qDebug() << QString("%1").arg(name1);
            QString singer = sql_query.value(2).toString();
            QString lyric = sql_query.value(3).toString();
            QString album = sql_query.value(4).toString();
            QString audiopath = sql_query.value(5).toString();
            music = new Music(name1,singer,lyric,album,audiopath);

            qDebug()<<"checked";
            qDebug()<<QString("ID:%1  Name:%2  singer:%3 lyric:%4 album:%5 audiopath:%6" ).arg(id).arg(name1).arg(singer).arg(lyric).arg(album).arg(audiopath);
        }
    }
    db.close();

    return music;
}

Singer* Sqltable::querysingleSinger(QString name)
{
    Singer *singer;
    db.open();
    QString select_sql = "select * from singer where name = '" + name +"'";
    sql_querySinger.prepare(select_sql);
    //sql_query.addBindValue(name);
    if(!sql_querySinger.exec())
    {
        qDebug()<<sql_querySinger.lastError();
    }
    else
    {
        qDebug()<<"查询成功" ;
        while(sql_querySinger.next())
        {

            int id = sql_querySinger.value(0).toInt();
            QString name1 = sql_querySinger.value(1).toString();
            QString category = sql_querySinger.value(2).toString();

            singer = new Singer(name1,category);

            qDebug()<<"checked";
            qDebug()<<QString("ID:%1  Name:%2 category:%3 " ).arg(id).arg(name1).arg(category);
        }
    }
    db.close();

    return singer;
}

Album* Sqltable::querysingleAlbum(QString name)
{
    Album *album;
    db.open();
    QString select_sql = "select * from album where name = '" + name +"'";
    sql_queryAlbum.prepare(select_sql);
    //sql_query.addBindValue(name);
    if(!sql_queryAlbum.exec())
    {
        qDebug()<<sql_queryAlbum.lastError();
    }
    else
    {
        qDebug()<<"查询成功" ;
        while(sql_queryAlbum.next())
        {

            int id = sql_queryAlbum.value(0).toInt();
            QString name1 = sql_queryAlbum.value(1).toString();
            QString startDate = sql_queryAlbum.value(2).toString();
            QString singerName = sql_queryAlbum.value(3).toString();

            album = new Album(name1,startDate,singerName);

            qDebug()<<"checked";
            qDebug()<<QString("ID:%1  Name:%2 startDate:%3 singerName:%4" ).arg(id).arg(name1).arg(startDate).arg(singerName);
        }
    }
    db.close();

    return album;
}

QString Sqltable::querysingleTransform(QString name)
{
    QString sspell;
    db.open();
    QString select_sql = "select * from transform where name = '" + name +"'";
    sql_querySpell.prepare(select_sql);
    //sql_query.addBindValue(name);
    if(!sql_querySpell.exec())
    {
        qDebug()<<sql_querySpell.lastError();
    }
    else
    {
        qDebug()<<"查询成功" ;
        while(sql_querySpell.next())
        {


            QString name = sql_querySpell.value(0).toString();
            QString spell = sql_querySpell.value(1).toString();
            sspell = spell;




            qDebug()<<"checked";
            qDebug()<<QString("Name:%1  Spell:%2 " ).arg(name).arg(spell);
        }
    }
    db.close();

    return sspell;
}

//返回歌手的所有专辑名字
std::vector<QString> Sqltable::querySingerAlbum(QString name)
{
    std::vector<QString> albums;
    db.open();
    QString select_sql = "select * from album where singername = '" + name +"'";
    sql_queryAlbum.prepare(select_sql);
    //sql_query.addBindValue(name);
    if(!sql_queryAlbum.exec())
    {
        qDebug()<<sql_queryAlbum.lastError();
    }
    else
    {
        qDebug()<<"查询成功" ;
        while(sql_queryAlbum.next())
        {


            QString name = sql_queryAlbum.value(1).toString();
            albums.push_back(name);

            qDebug()<<"checked";
            qDebug()<<QString("Name:%1 ").arg(name);
        }
    }
    db.close();
    return albums;
}

//输入专辑名返回专辑里的所有歌曲
std::vector<QString> Sqltable::queryAlbumMusics(QString name)
{
    std::vector<QString> musics;
    db.open();
    QString select_sql = "select * from music where audiopath = '" + name +"'";
    sql_query.prepare(select_sql);
    //sql_query.addBindValue(name);
    if(!sql_query.exec())
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        qDebug()<<"查询成功" ;
        while(sql_query.next())
        {
            QString name = sql_query.value(1).toString();
            musics.push_back(name);

            qDebug()<<"checked";
            qDebug()<<QString("Name:%1 ").arg(name);
        }
    }
    db.close();
    return musics;

}

std::vector<QString> Sqltable::querySingerCategory(QString category)
{
    std::vector<QString> singers;
    db.open();
    QString select_sql = "select * from singer where category = '" + category +"'";
    sql_querySinger.prepare(select_sql);
    //sql_query.addBindValue(name);
    if(!sql_querySinger.exec())
    {
        qDebug()<<sql_querySinger.lastError();
    }
    else
    {
        qDebug()<<"查询成功" ;
        while(sql_querySinger.next())
        {
            QString name = sql_querySinger.value(1).toString();
            singers.push_back(name);

            qDebug()<<"checked";
            qDebug()<<QString("Name:%1 ").arg(name);
        }
    }
    db.close();
    return singers;

}




