#ifndef SINGER_H
#define SINGER_H
#include<QString>
#include<vector>

class Album;

class Singer
{
public:
    Singer();
    Singer(QString name,QString category);
    void addAlbum(Album *album);
    std::vector<QString> getInformation(std::vector<QString> a);

private:
    QString m_name;
    QString m_category;
    std::vector<Album*> _albums;
};

#endif // SINGER_H
