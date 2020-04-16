#include "musicbroker.h"

MusicBroker::MusicBroker()
{
    sqltable = new Sqltable();
}

Music* MusicBroker::findByName(QString name)
{
    return sqltable->querysingle(name);
}

QString MusicBroker::findSpell(QString name)
{
    return sqltable->querysingleTransform(name);
}

std::vector<Singer*> MusicBroker::findSinger()
{
    return sqltable->querySinger();
}

std::vector<Music*> MusicBroker::findPlayList(std::vector<QString> musics)
{
    std::vector<Music*> ms;
    for(auto l:musics)
    {
        ms.push_back(sqltable->querysingle(l));
    }
    return ms;
}

//查找歌手里面的所有专辑
std::vector<QString> MusicBroker::findAlbums(QString name)
{
    return sqltable->querySingerAlbum(name);
}

//查找专辑里所有的歌曲
std::vector<QString> MusicBroker::findMusics(QString name)
{
    return sqltable->queryAlbumMusics(name);
}

std::vector<QString> MusicBroker::findSingers(QString category)
{
    return sqltable->querySingerCategory(category);
}

std::vector<QString> MusicBroker::findSpells(std::vector<QString> info)
{
    std::vector<QString> infos;
    for(auto l:info){
        infos.push_back(l);
        infos.push_back(sqltable->querysingleTransform(l));
    }
    return infos;
}

//查找用户和密码是否匹配
std::vector<QString> MusicBroker::findUser(QString name, QString password)
{
    return sqltable->login(name,password);
}

QString MusicBroker::findRegisterInfo(QString name,QString password)
{
    return sqltable->insertParmeterUser(name,password);
}

QString MusicBroker::createSongsList(QString user,QString list)
{
    sqltable->user = user;
    return sqltable->createMusicList(list);
}

QString MusicBroker::deleteSongsList(QString user, QString list)
{
    sqltable->user = user;
    return sqltable->deleteMusicList(list);
}

QString MusicBroker::addMusicToList(QString list, QString name, QString singer,QString album)
{
    return sqltable->insertMusicList(list,name,singer,album);
}

std::vector<QString> MusicBroker::findMusicFromList(QString list)
{
    qDebug() << "musicBroker";
    return sqltable->loadMusicFromList(list);
}

std::vector<QString> MusicBroker::findAlbums2()
{
    return sqltable->randomSelectAlbum();
}

std::vector<QString> MusicBroker::findPicturesForAlbum(std::vector<QString> albums)
{
    return sqltable->albumsToPictures(albums);
}

