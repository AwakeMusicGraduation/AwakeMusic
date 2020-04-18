#include "sqltable.h"
#include "singer.h"
#include "album.h"
#include <random>

Sqltable::Sqltable()
{  
    user = "";
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("MusicPlayer.db");
    if(db.open()){
        qDebug() << "Database Opened";



        QString create_sql = "create table music (id int primary key, name varchar(30), singer varchar(30), lyric varchar(100), audiopath varchar(30), album varchar(30))"; //创建数据表music

        //QString select_all_sql = "select * from music";
        QString create_sql1 = "create table singer (id int primary key, name varchar(30),category varchar(30))"; //创建数据表singer

        QString create_sql2 = "create table album (id int primary key, name varchar(30), startDate varchar(30),singername varchar(30))"; //创建数据表album

        QString create_sql3 = "create table transform (name varchar(30), spell varchar(30))"; //创建数据表

        QString create_sql4 = "create table user (name varchar(30), password varchar(30))"; //创建用户注册数据表
        QString create_sql5 = "create table user_list (user varchar(30), list varchar(30))";//创建用户歌单关联表

        QSqlQuery sql_query1,sql_query2,sql_query3,sql_query4,sql_query5;
        sql_query1.prepare(create_sql);
        sql_query2.prepare(create_sql1);
        sql_query3.prepare(create_sql2);
        sql_query4.prepare(create_sql3);
        sql_query5.prepare(create_sql4);
        sql_query = sql_query1;
        sql_querySinger = sql_query2;
        sql_queryAlbum = sql_query3;
        sql_querySpell = sql_query4;
        sql_queryUser = sql_query5;
        if(!sql_query.exec()) //查看创建表是否成功
        {
            qDebug()<<QObject::tr("Table music Create failed");
            qDebug()<<sql_query.lastError();
        }
        if(!sql_querySinger.exec()) //查看创建表是否成功
        {
            qDebug()<<QObject::tr("Table singer Create failed");
            qDebug()<<sql_querySinger.lastError();
        }
        if(!sql_queryAlbum.exec()) //查看创建表是否成功
        {
            qDebug()<<QObject::tr("Table album Create failed");
            qDebug()<<sql_queryAlbum.lastError();
        }
        if(!sql_querySpell.exec()) //查看创建表是否成功
        {
            qDebug()<<QObject::tr("Table spell Create failed");
            qDebug()<<sql_querySpell.lastError();
        }
        if(!sql_queryUser.exec()) //查看创建表是否成功
        {
            qDebug()<<QObject::tr("Table User Create failed");
            qDebug()<<sql_querySpell.lastError();
        }
        else
        {
            qDebug()<< "Tables Created" ;
        }
        sql_query.prepare(create_sql5);
        if(!sql_query.exec()) //查看创建表是否成功
        {
            qDebug()<<QObject::tr("Table user_list Create failed");
            qDebug()<<sql_query.lastError();
        }
    }
}

Sqltable::~Sqltable()
{
    db.close();
}

void Sqltable::insertParmeterTransform(QString name,QString spell)
{
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

}

QString Sqltable::insertParmeterUser(QString name, QString password)//查询用户名，用户名存在则不能注册
{
    QString select_all_user = "select * from user where name = ?";
    sql_queryUser.prepare(select_all_user);
    sql_queryUser.addBindValue(name);
    if(!sql_queryUser.exec())
    {
        qDebug()<<sql_queryUser.lastError();
    }

    QString m;
    if(!sql_queryUser.next())
    {
        QString insert_sql = "insert into user values(?,?)";    //插入数据


        //插入数据
        sql_queryUser.prepare(insert_sql);


        sql_queryUser.addBindValue(name);
        sql_queryUser.addBindValue(password);



        if(!sql_queryUser.execBatch())
        {
            qDebug()<<sql_queryUser.lastError();
        }
        else
        {
            m = "插入记录成功";
            qDebug()<<"插入记录成功";
        }
        if(!sql_queryUser.exec())
        {
            qDebug()<<sql_queryUser.lastError();
        }
    }
    else
    {
        qDebug()<<"用户名已存在.";
        m ="用户名已存在";
    }

    return m;
}


void Sqltable::insertParmeter(int id, QString name, QString singer, QString lyric, QString album, QString audiopath)
{
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

}


//插入歌手信息
void Sqltable::insertParmeterSinger(int id, QString name,QString category)
{
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

}

//插入专辑信息
void Sqltable::insertParmeterAlbum(int id, QString name, QString startDate,QString  singerName)
{
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

}

//查询spell
void Sqltable::queryTransform()
{
    QString select_all_sql = "select * from transform";
    //QSqlQuery sql_query1;
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
}

std::vector<QString> Sqltable::login(QString name,QString password)//先查询用户名，如果用户名存在，再比较密码，然后登录
{
    std::vector<QString> m;
    QString select_all_user = "select * from user where name = ?";
    sql_queryUser.prepare(select_all_user);
    sql_queryUser.addBindValue(name);

    if(!sql_queryUser.exec())
    {
        QString s = "error";
        m.push_back(s);
        qDebug()<< sql_queryUser.lastError();
    }
    if(!sql_queryUser.next()){
        QString s = "Don't have this user";
        m.push_back(s);
        qDebug() << "Don't have this user.";
    }
    else
    {
        QString password1 = sql_queryUser.value(1).toString();
        if(password == password1){
            QString s = "Sign in success";
            m.push_back(s);
            qDebug()<<"Sign in success.";
            user = name;
            searchMusicList(&m);
            //return m;
        }
        else
        {
            QString s = "password is wrong";
            m.push_back(s);
            qDebug()<<"password is wrong.";
        }
    }
    qDebug() << "返回查询到的列表";
    return m;
}

std::vector<Singer*> Sqltable::querySinger()
{
    Singer* singer;
    std::vector<Singer*> singers;
    QString select_all_sql = "select * from singer";
    //QSqlQuery sql_query1;
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
    return singers;
}

std::vector<Album*> Sqltable::queryAlbum()
{
    std::vector<Album*> albums;
    Album *album;
    QString select_all_sql = "select * from album";
    //QSqlQuery sql_query1;
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
    return albums;
}

void Sqltable::query()
{
    QString select_all_sql = "select * from music";
    //QSqlQuery sql_query1;
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
}


void Sqltable::deletemusic(QString name)
{
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
}


void Sqltable::updatamusic(int id,QString name)
{
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
}


Music* Sqltable::querysingle(QString name)
{
    Music *music;
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

    return music;
}

Singer* Sqltable::querysingleSinger(QString name)
{
    Singer *singer;
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

    return singer;
}

Album* Sqltable::querysingleAlbum(QString name)
{
    Album *album;
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

    return album;
}

QString Sqltable::querysingleTransform(QString name)
{
    QString sspell;
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

    return sspell;
}

//返回歌手的所有专辑名字
std::vector<QString> Sqltable::querySingerAlbum(QString name)
{
    std::vector<QString> albums;
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
    return albums;
}

//输入专辑名返回专辑里的所有歌曲
std::vector<QString> Sqltable::queryAlbumMusics(QString name)
{
    std::vector<QString> musics;
    QString select_sql = "select * from music where album = '" + name +"'";
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
    return musics;

}

std::vector<QString> Sqltable::querySingerCategory(QString category)
{
    std::vector<QString> singers;
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
    return singers;

}

QString Sqltable::createMusicList(QString name)//用户自己创建的音乐列表
{
    QString create_sql = "create table '" + name +"'(music varchar(30), singer varchar(30),album varchar(30))";
    QString insert_user_list = "insert into user_list values(?,?)";
    QSqlQuery sql_query1;
    sql_query1.prepare(create_sql);
    QString message;
    if(!sql_query1.exec()) //查看创建表是否成功
    {
        message = "Table MusicList Create failed";
        qDebug()<<QObject::tr("Table MusicList Create failed");
        qDebug()<<sql_query1.lastError();
    }
    else{
        message = "Table MusicList Create Succeed";
        qDebug()<<QObject::tr("Table MusicList Create Succeed");
        sql_query1.prepare(insert_user_list);
        sql_query1.addBindValue(user);
        sql_query1.addBindValue(name);
        if(!sql_query1.exec())
        {
            qDebug()<<sql_query1.lastError();
        }
    }
    return message;
}

void Sqltable::searchMusicList(std::vector<QString> *m)//用户登录后自动搜索属于自己的歌单并加载
{
    qDebug() << "查询用户创建的列表";
    QString select_sql = "select * from user_list where user = '" + user +"'";
    QSqlQuery sql_query1;
    sql_query1.prepare(select_sql);
    if(!sql_query1.exec())
    {
        qDebug() << sql_query1.lastError();
    }
    while(sql_query1.next())
    {
        QString s = sql_query1.value(1).toString();
        m->push_back(s);
        qDebug() << sql_query1.value(1).toString();
    }
    //    QString search_table = "SELECT name FROM sqlite_master WHERE type='table' ORDER BY name";
    //    QSqlQuery sql_query1;
    //    sql_query1.prepare(search_table);
    //    if(!sql_query1.exec()) //查看创建表是否成功
    //    {
    //        qDebug()<<sql_query1.lastError();
    //    }
    //    while(sql_query1.next())
    //    {
    //        QString name = sql_query1.value(0).toString();
    //        qDebug() << name;
    //    }
}

QString Sqltable::insertMusicList(QString list, QString music, QString album, QString singer)
{
    QString select_sql = "select * from user_list where list = '" + list +"'";
    QString insert_sql = "insert into " + list+ " values(?,?,?)";
    QString select_music = "select * from '" + list + "'where music = '" + music+"'";
    QSqlQuery sql_query1;
    QString message;
    sql_query1.prepare(select_sql);
    if(!sql_query1.exec())
    {
        qDebug() << sql_query1.lastError();
    }
    if(sql_query1.next()){
        //if(sql_query1.value(0).toString() == user)
        //{
            sql_query1.prepare(select_music);
            if(!sql_query1.exec())
            {
                qDebug() << sql_query1.lastError();
            }
            if(sql_query1.next())
            {
                message = "存在同名歌曲";
                qDebug() << "存在同名歌曲";
            }
            else{
                sql_query1.prepare(insert_sql);
                sql_query1.addBindValue(music);
                sql_query1.addBindValue(singer);
                sql_query1.addBindValue(album);
                if(!sql_query1.exec())
                {
                    qDebug() << sql_query1.lastError();
                }
                else
                    message = "插入歌曲成功";
                    qDebug() << "插入歌曲成功";
            }
       // }
       // else
       //     qDebug() << "不是此用户的歌单";
    }
    return message;
}

void Sqltable::deletemusicFromList(QString list, QString music, QString album, QString singer)
{
    QString delete_sql = "delete from '" +list+ "' where music = ? and album = ? and singer = ?";
    QString select_sql = "select * from user_list where list = '" + list +"'";
    QSqlQuery sql_query1;
    sql_query1.prepare(select_sql);
    if(!sql_query1.exec())
    {
        qDebug() << sql_query1.lastError();
    }
    if(sql_query1.next()){
        if(sql_query1.value(0).toString() == user)
        {
            sql_query1.prepare(delete_sql);
            sql_query1.addBindValue(music);
            sql_query1.addBindValue(album);
            sql_query1.addBindValue(singer);
            if(!sql_query1.exec())
            {
                qDebug()<<sql_query1.lastError();
            }
            else
                qDebug() << "删除歌曲成功";
        }
        else
            qDebug() << "不是此用户的歌单";
    }
}

QString Sqltable::deleteMusicList(QString list)
{
    QString select_sql = "select * from user_list where list = '" + list +"'";
    QString delete_sql = "drop table '" + list +"'";
    QString delete_user_list = "delete from user_list where list = '" + list + "'";
    QSqlQuery sql_query1;
    QString message;
    sql_query1.prepare(select_sql);
    if(!sql_query1.exec())
    {
        qDebug() << sql_query1.lastError();
    }
    if(sql_query1.next()){
        if(sql_query1.value(0).toString() == user)
        {
            sql_query1.prepare(delete_sql);
            if(!sql_query1.exec())
            {
                message = "删除表失败";
                qDebug() << "删除表失败";
                qDebug() << sql_query1.lastError();
            }
            else{
                sql_query1.prepare(delete_user_list);
                message = "删除成功";
                if(!sql_query1.exec())
                {
                    qDebug() << sql_query1.lastError();
                }
            }
        }
        else
            message = "不是此用户的歌单";
            qDebug() << "不是此用户的歌单";
    }
    return message;
}


std::vector<QString> Sqltable::loadMusicFromList(QString list)
{
    std::vector<QString> allmusics;
    qDebug() << "正在查" << list;
    QString select_all_sql = "select * from " + list;
    qDebug() << select_all_sql;

    QSqlQuery sql_query;

    sql_query.prepare(select_all_sql);


    if(!sql_query.exec())
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        qDebug()<<"查询成功" ;
        while(sql_query.next())
        {
            QString name = sql_query.value(0).toString();
            QString singer = sql_query.value(1).toString();
            QString album = sql_query.value(2).toString();
            allmusics.push_back(name);
            allmusics.push_back(singer);
            allmusics.push_back(album);
            QString spell = querysingleTransform(name);
            allmusics.push_back(spell);
            qDebug()<<"checked";
            qDebug()<< QString("music:%1  singer:%2  album:%3").arg(name).arg(singer).arg(album);
        }
    }
    return allmusics;
}

std::vector<QString> Sqltable::randomSelectAlbum()
{

    QString select_album_sql = "select name from album order by random() limit 8";
    QSqlQuery sql_query;
    std::vector<QString> albums;

    sql_query.prepare(select_album_sql);

    if(!sql_query.exec())
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        while(sql_query.next())
        {
            QString name = sql_query.value(0).toString();
            albums.push_back(name);
            qDebug()<<"checked";
            qDebug()<< QString("album:%1").arg(name);
        }
    }
    return albums;
}
std::vector<Music *> Sqltable::searchMusicBySinger(QString content)
{
    std::vector<Music *> musics;
    QString select_singer = "select * from music where singer = '" + content + "'";
    QSqlQuery sql_query1;
    QString name1,singer,lyric,album,audiopath;
    //搜索歌手
    sql_query1.prepare(select_singer);
    if(!sql_query1.exec())
    {
        qDebug() << sql_query1.lastError();
    }
    else{
        while(sql_query1.next())
        {
            name1 = sql_query1.value(1).toString();
            //qDebug() << QString("%1").arg(name1);
            singer = sql_query1.value(2).toString();
            lyric = sql_query1.value(3).toString();
            album = sql_query1.value(4).toString();
            audiopath = sql_query1.value(5).toString();

            Music *music = new Music(name1,singer,lyric,audiopath,album);
            musics.push_back(music);
            qDebug() << "singer " << sql_query1.value(1).toString() << " " << sql_query1.value(2).toString() << " "<<sql_query1.value(5).toString();
        }
        return musics;
    }
}

std::vector<Music *> Sqltable::searchMusicByAlbum(QString content)
{
    std::vector<Music *> musics;
    Music *music;
    QString select_album = "select * from music where album = '" + content + "'";
    QSqlQuery sql_query1;
    //搜索专辑
    sql_query1.prepare(select_album);
    if(!sql_query1.exec())
    {
        qDebug() << sql_query1.lastError();
    }
    else{
        while(sql_query1.next())
        {
            QString name1 = sql_query1.value(1).toString();
            //qDebug() << QString("%1").arg(name1);
            QString singer = sql_query1.value(2).toString();
            QString lyric = sql_query1.value(3).toString();
            QString album = sql_query1.value(4).toString();
            QString audiopath = sql_query1.value(5).toString();
            music = new Music(name1,singer,lyric,audiopath,album);
            musics.push_back(music);
            qDebug() << name1 << singer << album;
            qDebug() << "album " << sql_query1.value(1).toString() << " " << sql_query1.value(2).toString() << " "<<sql_query1.value(5).toString();
        }
    }
    return musics;
}

std::vector<Music *> Sqltable::searchMusicByList(QString content)
{
    std::vector<Music *> musics;
    QString select_list = "select * from user_list where list = '" + content + "'";
    QSqlQuery sql_query1;
    //搜索歌单
    sql_query1.prepare(select_list);
    if(!sql_query1.exec())
    {
        qDebug() << sql_query1.lastError();
    }
    else{
        while(sql_query1.next())
        {
            QString name1 = sql_query1.value(1).toString();
            //qDebug() << QString("%1").arg(name1);
            QString singer = sql_query1.value(2).toString();
            QString lyric = sql_query1.value(3).toString();
            QString album = sql_query1.value(4).toString();
            QString audiopath = sql_query1.value(5).toString();
            Music *music = new Music(name1,singer,lyric,audiopath,album);
            musics.push_back(music);
            qDebug() << "list " << sql_query1.value(1).toString();
        }
    }
    return musics;
}

std::vector<QString> Sqltable::albumsToPictures(std::vector<QString> albums)
{
    QString album;
    std::vector<QString> picturepaths;
    QSqlQuery sql_query;
    for(auto l:albums)
    {
        album = l;
        QString select_picture_sql = "select audiopath from music where album = '" + album +"'";
        sql_query.prepare(select_picture_sql);

        if(!sql_query.exec())
        {

            qDebug()<<sql_query.lastError();
        }
        else
        {
           if(sql_query.next())
           {
               QString path = sql_query.value(0).toString();
               picturepaths.push_back(path);
               qDebug()<<"checked";
               qDebug()<< QString("path:%1").arg(path);
           }
           else
               picturepaths.push_back("root/薛之谦/yiwai");
        }
    }
    return picturepaths;
}

std::vector<QString> Sqltable::searchMusicsForTip(QString tip)
{
    db.open();
    std::vector<QString> musics;
    QString select_sql = "select * from music where album = '" + tip +"'";
    sql_query.prepare(select_sql);

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
            QString singer = sql_query.value(2).toString();
            musics.push_back(name);
            musics.push_back(singer);
            musics.push_back(tip);
            QString spell = querysingleTransform(name);
            musics.push_back(spell);
            qDebug() << name << spell;
            qDebug()<<"checked";
        }
    }
    return musics;
}

std::vector<QString> Sqltable::queryAlbumsForSinger(QString singer)
{
    db.open();
    QString select_sql = "select * from album where singername = '" + singer +"'";
    QSqlQuery albums_query;
    albums_query.prepare(select_sql);
    std::vector<QString> albums;
    if(!albums_query.exec())
    {
        qDebug()<<albums_query.lastError();
    }
    else
    {
        qDebug()<<"查询成功" ;
        while(albums_query.next())
        {
            QString name = albums_query.value(1).toString();
            albums.push_back(name);
        }
   }
    db.close();
    return albums;
}
