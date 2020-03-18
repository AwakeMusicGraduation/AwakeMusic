#ifndef MUSIC_H
#define MUSIC_H
#include <QString>
#include <vector>

class Music{
public:
    Music();
    ~Music();
    Music(QString name, QString singer, QString lyric, QString album, QString audiopath);

    std::vector<QString> getInformation(std::vector<QString> &a);

private:

    QString m_name;
    QString m_singer;
    QString m_lyric;
    QString m_album;
    QString m_audiopath;
};

#endif // MUSIC_H
