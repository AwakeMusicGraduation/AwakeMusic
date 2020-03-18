#include "album.h"

Album::Album()
{

}

Album::Album(QString name, QString startDate,QString singerName):m_name{name},m_startDate{startDate},m_singerName{singerName}
{

}

void Album::addMusic(Music *music)
{
    _musics.push_back(music);
}


std::vector<QString> Album::getAlbumInfo(std::vector<QString> info)
{
    info.push_back(m_name);
    info.push_back(m_startDate);
    info.push_back(m_singerName);
    return info;
}
