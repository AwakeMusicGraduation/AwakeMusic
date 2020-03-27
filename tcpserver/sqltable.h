#ifndef SQLTABLE_H
#define SQLTABLE_H
#include <QCoreApplication>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>
#include <QFile>
#include <QDebug>
#include <QVariantList>
#include "music.h"
#include "singer.h"
//static QString create_sql;
class Singer;
class Album;
class Sqltable{
private:
    QSqlDatabase db;
    QSqlQuery sql_query;
    QSqlQuery sql_querySinger;
    QSqlQuery sql_queryAlbum;
    QSqlQuery sql_querySpell;
    QSqlQuery sql_queryUser;
    QString user;//当前用户名

public:
    Sqltable();

public:
    void insertParmeter(int id, QString name, QString singer, QString lyric, QString album, QString audiopath);
    void query();
    void deletemusic(QString name);
    void updatamusic(int id,QString name);
    Music* querysingle(QString name);
    void insertParmeterSinger(int id, QString name,QString category);
    void insertParmeterAlbum(int id, QString name, QString startDate,QString  singerName);
    void insertParmeterTransform(QString name, QString spell);
    void insertParmeterUser(QString name,QString password);//用户注册

    std::vector<Singer*> querySinger();
    std::vector<Album*> queryAlbum();
    void queryTransform();
    void login(QString name,QString password);//登录
    Singer* querysingleSinger(QString name);
    Album* querysingleAlbum(QString name);
    QString querysingleTransform(QString name);
    std::vector<QString> querySingerAlbum(QString name);
    std::vector<QString> queryAlbumMusics(QString name);
    std::vector<QString> querySingerCategory(QString category);

    void createMusicList(QString name);//用户自己创建的音乐列表
    void searchMusicList();//用户登录后自动搜索属于自己的歌单并加载
    void insertMusicList(QString list,QString music,QString album,QString singer);//用户往特定歌单插入歌曲
    void deleteMusicFromList(QString list,QString music,QString album,QString singer);//用户删除特定歌单的歌曲
    void deleteMusicList(QString list);//用户删除特定歌单
    void search(QString content);//根据搜索内容搜索
};



#endif // SQLTABLE_H
