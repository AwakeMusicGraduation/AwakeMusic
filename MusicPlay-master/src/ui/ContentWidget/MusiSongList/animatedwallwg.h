#ifndef ANIMATEWALLWG_H
#define ANIMATEWALLWG_H

#include <QLabel>
#include <QWidget>
#include <QVariant>
#include <QPushButton>
#include <QTableWidget>
#include "TitleBar/clickablelabel.h"

#define LRWIDTH     35     //左右两个点击按钮的宽度
#define SCALE       0.86   //旁边两个小Label占中间大Label的比例
#define COVER       50     //中间大Label挡住两边小Label的部分
#define DURATION    400    //动画持续时间
#define EASINGTIME  0.5    //中间缓冲时间
#define EASINGCURVE QEasingCurve::InOutCubic  //缓和曲线  InOutSine InOutQuart InOutCubic

class AnimatedWallWG : public QWidget
{
    Q_OBJECT
    enum { COUNT = 6 };
public:
    explicit AnimatedWallWG(QWidget *parent = 0);

    //初始化
    void initVar();
    void initWallpaper();
    void initLRButton();
    void setWallRect();
    void setLRButtonRect();
    void setWallpaper(QLabel *pWall, int i);
    void wallIndex(bool b, int n, int &i, int &j, int &k, int &l);

    //本类实例
    static AnimatedWallWG* Instance(QWidget *parent = 0)
    {
        if (m_pInstance == NULL)
        {
            m_pInstance = new AnimatedWallWG(parent);
        }
        return m_pInstance;
    }
signals:
    void signalObtainSongs();//获取图片对应的歌曲
    void signalObtainSongs1();//获取图片对应的歌曲
    void signalObtainSongs2();//获取图片对应的歌曲
    void signalObtainSongs3();//获取图片对应的歌曲
    void signalObtainSongs4();//获取图片对应的歌曲
    void signalObtainSongs5();//获取图片对应的歌曲

protected slots:
    void moveToLeft();
    void moveToRight();
    void onValueChanged(QVariant variant);

    void finished() { m_bAnimation = true; }

protected:
    bool eventFilter(QObject *watched, QEvent *event);
    void timerEvent(QTimerEvent *event);
    void paintEvent(QPaintEvent *event);

private:
    static AnimatedWallWG *m_pInstance;

    //正中间图片在链表中的索引
    int m_iWall;            //控件的索引
    int m_iRaise;           //置顶控件索引
    int m_idTimer;

    bool m_bAnimation;      //是否可以轮换

    //QLabel
    ClickableLabel *m_pWall[COUNT];
    QRect m_rtWall[3];      //没变化前的状态
    QRect m_rtLChange[5];   //从左到右变化过程中的状态
    QRect m_rtRChange[6];   //从右到左变化过程中的状态

    //QPushButton
    QPushButton *m_pLRButton[2];  //左右移动的两个点击按钮
};


#endif // ANIMATEWALLWG_H
