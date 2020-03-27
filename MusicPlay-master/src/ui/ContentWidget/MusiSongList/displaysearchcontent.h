#ifndef DISPLAYSEARCHCONTENT_H
#define DISPLAYSEARCHCONTENT_H

#include <QTableWidget>
#include "controlvalues.h"

class QPushButton;
class QHBoxLayout;
class QVBoxLayout;
class QTableWidget;
class classifyList;
class DisplaySearchContent : public QTableWidget
{
    Q_OBJECT
public:
    explicit DisplaySearchContent(QWidget *parent);
    //~DisplaySearchContent();
private:
    void initform();
    void initconnect();
private:
    QPushButton *m_singer;
    QPushButton *m_album;
    QPushButton *m_music;
    QPushButton *m_songSheet;
    QHBoxLayout *m_hlayout;
    QVBoxLayout *m_mainLayout;
    classifyList *m_list;
    int currentClicked;
public Q_SLOTS:
    void slotShowSinger();
    void slotShowAlbum();
    void slotShowMusic();
    void slotShowSongsheet();

};

#endif // DISPLAYSEARCHCONTENT_H
