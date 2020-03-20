#ifndef MUSICSONGSLISTS_H
#define MUSICSONGSLISTS_H
#include <QTableWidget>
class MusicListMenu;
class SongMenu;
class QDialog;
class QPushButton;

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
    void slotCreateList();
protected:
    virtual void contextMenuEvent(QContextMenuEvent *event);
private:
    SongMenu *m_menu;
    QDialog *d;
    QLineEdit *m;
    QPushButton *push;
};

#endif // MUSICSONGSLISTS_H
