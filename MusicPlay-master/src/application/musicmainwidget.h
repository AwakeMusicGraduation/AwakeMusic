#ifndef MUSICMAINWIDGET_H
#define MUSICMAINWIDGET_H


#include <QFrame>
#include <QMouseEvent>

class QVBoxLayout;
class TitleWidget;
class Contentwidget;
class BottomWidget;
class QStackedWidget;
class PlayMusic;
class MusicDesktopLrcManage;
class Client;
class loginform_test;
class MyMediaPlayList;

class MusicMainWidget : public QFrame
{
    Q_OBJECT
public:
    explicit MusicMainWidget(QWidget *parent = 0);
    ~MusicMainWidget();
    
Q_SIGNALS:

private:
    void initForm();
    void initWidget();
    void initLayout();
    void initConnect();
    void initPlayList();
    //自定义槽函数
private Q_SLOTS:
    void slotShowLoginWidget();                 //显示登录界面
    void slotShowSkinWidget();                  //显示皮肤界面
    void slotShowMin();                         //最小化
    void slotClose();                           //关闭

    void slotPreviousMusic(const QString &);    //上一首
    void slotPlayOrPause(int);                  //音乐播放或者暂停状态控制
    void slotNextMusic(const QString &);        //下一首
    void slotPlayProgressChange(int);           //播放进度改变
    void slotShowOrHideDesktopLrc(int);         //显示或者隐藏桌面歌词
    void slotShowOrHideCornorList();         //显示或隐藏播放列表

    void slotTest(const QString &);

    void slotFlushPlayList(QList<QString> &m);   //刷新播放列表

protected :
    virtual void mousePressEvent(QMouseEvent *);
    virtual void mouseReleaseEvent(QMouseEvent *);
    virtual void mouseMoveEvent(QMouseEvent *);
    //virtual bool eventFilter(QObject *, QEvent *);

private:
    TitleWidget *m_titleWidget;         //标题栏
    Contentwidget *m_contentWidget;     //中央窗体
    BottomWidget *m_bottomWidget;       //工具栏
    //QStackedWidget *m_stackedWidget;
    MusicDesktopLrcManage *m_desktopLrc;//桌面歌词
    QVBoxLayout *m_mainLayout;          //主布局
    MyMediaPlayList *m_playlist;


    QPoint m_move_point;                //移动的距离
    bool m_mouse_press;                 //按下鼠标左键

    QString m_curSkin;
    Client *m_client;

    PlayMusic *m_player;                //控制音乐播放
    loginform_test *login;
};

#endif // MUSICMAINWIDGET_H
