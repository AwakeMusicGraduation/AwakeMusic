#ifndef MUSICSONGSLISTS_H
#define MUSICSONGSLISTS_H
#include <QTableWidget>
class MusicListMenu;
class SongMenu;

class MusicSongsLists : public QTableWidget
{
    Q_OBJECT
public:
    explicit MusicSongsLists(QWidget *parent);
    void addItemContent(QString content);
private:
    void initForm();
    void initWidget();
    void initConnect();
Q_SIGNALS:
    void signalShowList(int row);
    void signalDeleteList(int row);
    void signalAddNewList();
private Q_SLOTS:
    void slotCellClicked(int,int);
    void slotAddNewPlayList();
    void slotDeletePlayList();
protected:
    virtual void contextMenuEvent(QContextMenuEvent *event);
private:
    SongMenu *m_menu;
};

#endif // MUSICSONGSLISTS_H
