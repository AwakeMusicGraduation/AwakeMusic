#ifndef MUSIC_H
#define MUSIC_H

#include <QString>

class Music{
public:
    Music();
    Music(QString n, QString s, QString a){
        m_name = n; m_singer = s; m_album = a;
    }
    Music(QString n){
        m_name = n;
        m_singer = "";
        m_album = "";
    }
    QString name(){return m_name;}
    QString singer(){return m_singer;}
    QString album(){return m_album;}

private:
    QString m_name;
    QString m_singer;
    QString m_album;
};

#endif // MUSIC_H
