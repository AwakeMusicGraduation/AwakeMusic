﻿//默认列表
#ifndef MUSICSONGSLISTWIDGET_H
#define MUSICSONGSLISTWIDGET_H

#include <QTableWidget>

class QMenu;

class MusicSongsListWidget : public QTableWidget
{
    Q_OBJECT
public:
    explicit MusicSongsListWidget(QWidget *parent);
    ~MusicSongsListWidget();

    //向tablewidget中添加一条记录
    void addItemContent(QString content /*,int row, int column = 0*/);
    //删除鼠标选中的行
    void removeItem();
    //删除某个列表中的所有歌曲
    void removeAllItem();
    //获取当前鼠标点击的行的内容
    QString getSelectContent();
    //添加文件中的mp3
    void addMusicFold(QString path);
    QList<QStringList> returnMusicInfo();
    //保存歌曲信息
    void saveMusicInfo(const QString &name,const QString &path);
    //获取歌曲路径
    QString getMusicPath(const QString& name);

    //返回tablewidget是否为空
    bool tableWidgetIsEmpty();
    void importMusicSongsName(const QStringList &file_name_list);
    void PlayMusic(const QString name);

Q_SIGNALS:
    void signalPlayMusic();
    void signalAddMusic();
    void signalAddMusicFolder();
    void signalDeleteMusic();
    void signalDeleteAllMusic();
    void signalShowLyric();
    void signalPlayMusicPath(QString path);

    void signalPlayMusic(const QString &musicName);

    //向下发送所要请求的歌曲信息
    void signalSendNextMusic(const QString &name);
    void signalSendPreviousMusic(const QString &name);

    //向bottombar发送开始要播放的歌曲
    void signalSendFirstPlayMusic(const QString &);

    //向下发送所请求的播放歌曲
    void signalSendPlayCmdMusicInfo(const QString &);

    //将列表中的所有歌曲显示到播放列表中
    void signalSendToPlayList(QList<QStringList> &);

    //QMenu的信号
    void signalQmenuPlayMusic();
    void signalQmenuDeleteAllMusic();

private Q_SLOTS:
    void slotCellDoubleClicked(int,int);

public Q_SLOTS:
    //获取上一首
    void slotGetNextMusic();
    void slotGetPreviouseMusic();
    void slotAddMusic();                            //添加歌曲
    void slotRemoveAllItem();
    void slotRemoveItem();
    void slotPlayMusic();


    /*程序启动后，若按下底部控制按钮，播放歌曲，则要先判断列表中是否有歌曲，
     * 若有，则从返回第一手歌曲,若没有则返回空
    */
    void slotGetFirstPlayMusic();

    //根据播放模式，发送不同的歌曲信息
    void slotSendPlayCmd(int);
private:
    void initForm();
    void initConnect();
    void initMenu();

    void setRadomPlayMusic();       //设置随机播放

protected:
    virtual void contextMenuEvent(QContextMenuEvent *event);

private:
    QMenu *m_menu;
    QMap<QString,QString> m_musicInfo;           //歌曲信息
    QList<QStringList> m_music;
};

#endif // MUSICSONGSLISTWIDGET_H
