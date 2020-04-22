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
    QSqlQuery sql_queryList;
public:
    QString user;//当前用户名

public:
    Sqltable();
    ~Sqltable();

public:
    void insertParmeter(int id, QString name, QString singer, QString lyric, QString album, QString audiopath);
    void query();
    void deletemusic(QString name);
    void updatamusic(int id,QString name);
    Music* querysingle(QString name);
    std::vector<Music*> queryMusicsByName(QString name);
    void insertParmeterSinger(int id, QString name,QString category);
    void insertParmeterAlbum(int id, QString name, QString startDate,QString  singerName);
    void insertParmeterTransform(QString name, QString spell);
    QString insertParmeterUser(QString name,QString password);//用户注册

    std::vector<Singer*> querySinger();
    std::vector<Album*> queryAlbum();
    void queryTransform();
    std::vector<QString> login(QString name,QString password);//登录
    Singer* querysingleSinger(QString name);
    Album* querysingleAlbum(QString name);
    QString querysingleTransform(QString name);
    std::vector<QString> querySingerAlbum(QString name);
    std::vector<QString> queryAlbumMusics(QString name);
    std::vector<QString> querySingerCategory(QString category);

    QString createMusicList(QString user,QString name);//用户自己创建的音乐列表
    void searchMusicList(QString user,std::vector<QString> *m);//用户登录后自动搜索属于自己的歌单并加载
    QString insertMusicList(QString list,QString music,QString album,QString singer);//用户往特定歌单插入歌曲
    QString deletemusicFromList(QString list,QString music,QString album,QString singer);//用户删除特定歌单的歌曲
    QString deleteMusicList(QString user,QString list);//用户删除特定歌单
    std::vector<QString> loadMusicFromList(QString list);//根据列表搜素对应的音乐
    std::vector<QString> randomSelectAlbum();//随机从专辑中选出8个专辑作为推荐歌单
    std::vector<QString> albumsToPictures(std::vector<QString> albums);//根据专辑得出图片的路径
    std::vector<QString> searchMusicsForTip(QString tip);//根据推荐歌单搜素歌曲
    std::vector<Music *> searchMusicBySinger(QString content);
    std::vector<Music *> searchMusicByAlbum(QString content);
    std::vector<Music *> searchMusicByList(QString content);
    std::vector<QString> queryAlbumsForSinger(QString singer);//根据歌手查询专辑
    //std::vector<QString> loadMusicFromList(QString list);//根据列表搜素对应的音乐
};



#endif // SQLTABLE_H
