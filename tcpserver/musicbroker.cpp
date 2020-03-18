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


