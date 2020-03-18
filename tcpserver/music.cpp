#include "music.h"

Music::Music()
{
}

Music::~Music()
{

}

Music::Music(QString name, QString singer, QString lyric, QString album, QString audiopath):m_name{name}, m_singer{singer}, m_lyric{lyric}, m_album{album}, m_audiopath{audiopath}
{
}

std::vector<QString> Music::getInformation(std::vector<QString> &a)
{
    a.push_back(m_name);
   // a.push_back(m_spell);
    a.push_back(m_singer);
    a.push_back(m_audiopath);//专辑
    a.push_back(m_album);
    a.push_back(m_lyric);
    return a;
}

