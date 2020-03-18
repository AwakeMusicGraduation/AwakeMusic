#ifndef ALBUM_H
#define ALBUM_H

#include <QString>
#include <vector>
class Music;

class Album
{
public:
    Album();
    Album(QString name, QString startDate,QString singerName);
    void addMusic(Music *music);
    std::vector<QString> getAlbumInfo(std::vector<QString> info);

private:
    QString m_name;
    QString m_startDate;
    QString m_singerName;
    std::vector<Music*> _musics;
};

#endif // ALBUM_H
