#ifndef MUSICBROKER_H
#define MUSICBROKER_H

#include <vector>
#include "sqltable.h"
#include "music.h"

class MusicBroker
{
public:
    MusicBroker();
    Music* findByName(QString name);
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
    //Music findBySinger(QString singer);

private:
    Sqltable *sqltable;
    std::vector<Music*> m_musics;
    std::vector<Singer*> m_singers;
};

#endif // MUSICBROKER_H
