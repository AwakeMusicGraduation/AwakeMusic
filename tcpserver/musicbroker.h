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
    //Music findBySinger(QString singer);

private:
    Sqltable *sqltable;
    std::vector<Music*> m_musics;
    std::vector<Singer*> m_singers;
};

#endif // MUSICBROKER_H
