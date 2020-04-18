#ifndef MUSICBROKER_H
#define MUSICBROKER_H

#include <vector>
#include "sqltable.h"
#include "music.h"

class MusicBroker
{
public:
    MusicBroker();
    std::vector<Music *> findByName(QString name);
    std::vector<Music *> findBySinger(QString singer);
    std::vector<Music *> findByAlbum(QString album);
    std::vector<Music *> findByList(QString list);
    QString findSpell(QString name);
    std::vector<Singer*> findSinger();
    std::vector<Music*> findPlayList(std::vector<QString> musics);
    std::vector<QString> findAlbums(QString name);
    std::vector<QString> findMusics(QString name);
    std::vector<QString> findSingers(QString category);
    std::vector<QString> findSpells(std::vector<QString> info);
    std::vector<QString> findUser(QString name,QString password);//查找用户和密码是否正确
    QString findRegisterInfo(QString name,QString password);//插入注册数据是否存在
    QString createSongsList(QString user,QString list);//创建音乐列表
    QString deleteSongsList(QString user,QString list);//删除音乐列表
    QString addMusicToList(QString list, QString name, QString singer,QString album);//添加歌曲到列表
    std::vector<QString> findMusicFromList(QString list);//从列表查询音乐
    //Music findBySinger(QString singer);
    std::vector<QString> findAlbums2();//找到随机选取的专辑
    std::vector<QString> findPicturesForAlbum(std::vector<QString> albums);//根据选取的album找到对应的图片
    std::vector<QString> findMusicsForTip(QString tip);//根据歌单查询音乐
    std::vector<QString> findAlbumsForSinger(QString name);//根据歌手查专辑

private:
    Sqltable *sqltable;
    std::vector<Music*> m_musics;
    std::vector<Singer*> m_singers;
};

#endif // MUSICBROKER_H
