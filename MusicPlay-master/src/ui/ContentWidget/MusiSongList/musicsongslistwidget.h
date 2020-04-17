//默认列表
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
    void addItemContent(QStringList );
    //删除鼠标选中的行
    void removeItem();
    //删除某个列表中的所有歌曲
    void removeAllItem();
    //获取当前鼠标点击的行的内容
    QString getSelectContent();
    //添加文件中的mp3
    void addMusicFold(QString path);
    //保存歌曲信息
    //    void saveMusicInfo(const QString &name,const QString &path);
    //获取歌曲路径
    //    QString getMusicPath(const QString& name);

    //返回tablewidget是否为空
    bool tableWidgetIsEmpty();
    void importMusicSongsName(const QStringList &file_name_list);
    void PlayMusics(const QString name);

Q_SIGNALS:
    void signalAddMusic();
    void signalAddMusicFolder();
    void signalDeleteMusic();
    void signalDeleteAllMusic();
    void signalShowLyric();
    void signalPlayMusicPath(QString path);
    void signalSendNextMusicToList(QString&);

    //向bottombar发送开始要播放的歌曲
    void signalSendFirstPlayMusic(const QString &);

    //向下发送所请求的播放歌曲
    void signalSendPlayCmdMusicInfo(const QString &);

    //将本地音乐的文件地址发送到播放列表中以便显示和播放,并发送当前播放歌曲的行数
    void signalSendToPlayList(QList<QString> &,int);

    void signalObtainListName();      //获取列表姓名
    void signalAddMusicToList(QString label,QString list,QString name,QString singer,QString album);//将歌曲加入到对应的列表并传到服务器

private Q_SLOTS:
    void slotCellDoubleClicked(int,int);


public Q_SLOTS:
    void slotAddMusic();                            //添加歌曲
    void slotRemoveAllItem();
    void slotRemoveItem();
    void slotPlayMusic();
    void slotSendNextMusic();                        //向播放列表发送下一首播放歌曲


    /*程序启动后，若按下底部控制按钮，播放歌曲，则要先判断列表中是否有歌曲，
     * 若有，则从返回第一手歌曲,若没有则返回空
    */
    void slotGetFirstPlayMusic();

    //接收列表名
    void slotReceiveListName(std::vector<QString> listname);
    //QAction槽
    void slotResponse(QAction*);
private:
    void initForm();
    void initConnect();
    void initMenu();

protected:
    virtual void contextMenuEvent(QContextMenuEvent *event);

private:
    QMenu *m_menu;
    QMenu *m_furthermenu;
    //保存本地歌曲播放路径
    QList<QString> m_musicpath;
};

#endif // MUSICSONGSLISTWIDGET_H
