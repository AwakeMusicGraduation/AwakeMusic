#ifndef MUSICSONGSMEDIA_H
#define MUSICSONGSMEDIA_H

#include <QTableWidget>
class MusicListMenu;

class MusicSongsMedia : public QTableWidget
{
    Q_OBJECT
public:
    explicit MusicSongsMedia(QWidget *parent);
    QString getMusicPinYin(QString name);
    void removeAllItem();
private:
    void initForm();
    void initConnect();
Q_SIGNALS:
    void signalPlayMediaMusic(QString path);
    void signalShowMediaLrc(QString songPinYin);
public Q_SLOTS:
    void slotAddItem(QString title,QString singer,QString album);
    void slotSaveMusicInfo(QString name,QString pinyin);
    void slotShowMusics(QString name,QString pinyin);
private Q_SLOTS:
    void slotCellDoubleClicked(int row,int cloumn);
private:
    QMap<QString,QString>m_musicInfo;
};

#endif // MUSICSONGSMEDIA_H
