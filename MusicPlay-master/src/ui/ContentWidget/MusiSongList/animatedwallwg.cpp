#include "animatedwallwg.h"

#include <QEvent>
#include <QPainter>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>

AnimatedWallWG *AnimatedWallWG::m_pInstance = NULL;

/***************************************************
 * 函数名称: AnimatedWallWG
 * 功   能: 构造函数 初始化UI、变量
 * 输入参数: parent 父类指针
 * 输出参数:
 * *************************************************/
AnimatedWallWG::AnimatedWallWG(QWidget *parent) :
    QWidget(parent)
{
    this->setFixedSize(700,130);
    //1. 初始化
    initVar();
    initWallpaper();
    initLRButton();

    //2. 开启定时器8秒轮换一次
    m_idTimer = startTimer(8000);

    //3. 安装事件过滤器捕获窗口大小改变事件
    this->installEventFilter(this);
}

/***************************************************
 * 函数名称: initVar
 * 功   能: 初始化变量
 * 输入参数:
 * 输出参数:
 * *************************************************/
void AnimatedWallWG::initVar()
{
    m_iWall = 0;
    m_iRaise = 0;
    m_idTimer = 0;
    m_bAnimation = true;
}

/***************************************************
 * 函数名称: initWallpaper
 * 功   能: 初始化背景墙
 * 输入参数:
 * 输出参数:
 * *************************************************/
void AnimatedWallWG::initWallpaper()
{
    //创建COUNT个Wall并且设置背景图
    for (int i = 0; i < COUNT; i++)
    {
        m_pWall[i] = new QLabel(this);
        setWallpaper(m_pWall[i], i);
    }

    //默认索引为1的Wall置顶
    m_pWall[1]->raise();

    //为了好看暂时把没用的Wall先移走
    m_pWall[3]->move(1920, 0);
    m_pWall[4]->move(1920, 0);
    m_pWall[5]->move(1920, 0);
}

/***************************************************
 * 函数名称: initLRButton
 * 功   能: 初始化左右两个点击按钮
 * 输入参数:
 * 输出参数:
 * *************************************************/
void AnimatedWallWG::initLRButton()
{
    //创建两个移动按钮
    m_pLRButton[0] = new QPushButton(this);
    m_pLRButton[1] = new QPushButton(this);

    m_pLRButton[0]->hide();
    m_pLRButton[1]->hide();

    connect(m_pLRButton[0], SIGNAL(clicked()), this, SLOT(moveToRight()));
    connect(m_pLRButton[1], SIGNAL(clicked()), this, SLOT(moveToLeft()));

    //设置按钮的图标
    QString style1 = QString("QPushButton{border: 0px; background: url(:/image/slidebuton/left.jpg) center no-repeat;}"
                             "QPushButton:hover{background-color: rgba(0, 0, 0, 30%);}"
                             "QPushButton:pressed{background-color: rgba(0, 0, 0, 50%);}");
    m_pLRButton[0]->setStyleSheet(style1);

    QString style2 = QString("QPushButton{border: 0px; background: url(:/image/slidebutton/right.jpg) center no-repeat;}"
                             "QPushButton:hover{background-color: rgba(0, 0, 0, 30%);}"
                             "QPushButton:pressed{background-color: rgba(0, 0, 0, 50%);}");
    m_pLRButton[1]->setStyleSheet(style2);
}

/***************************************************
 * 函数名称: setWallRect
 * 功   能: 设置动画移动的几个范围
 * 输入参数:
 * 输出参数:
 * *************************************************/
void AnimatedWallWG::setWallRect()
{
    int w, h;

    //中间的矩形geometry
    h = height();
    w = width() / 2.0;
    m_rtWall[1] = QRect(w / 2, 0, w, h);

    //左边矩形的geometry、右边矩形的geometry
    h = height() * SCALE;
    w = width() / 2.0 * SCALE;
    m_rtWall[0] = QRect(m_rtWall[1].left() - w + COVER, height() - h, w, h);
    m_rtWall[2] = QRect(m_rtWall[1].right() - COVER,    height() - h, w, h);

    //从左到右变化过程中的五个geometry
    m_rtLChange[0] = QRect(0 - w,                          height() - h, w, h);
    m_rtLChange[1] = QRect(m_rtLChange[0].x() + w,         height() - h, w, h);
    m_rtLChange[2] = QRect(m_rtLChange[1].x() + w - COVER, height() - h, w, h);
    m_rtLChange[3] = QRect(m_rtLChange[2].x() + w - COVER, height() - h, w, h);
    m_rtLChange[4] = QRect(m_rtWall[2].x() + w - COVER,    height() - h, w, h);

    //从右到左变化过程中的五个geometry
    m_rtRChange[0] = QRect(width(),                        height() - h, w, h);
    m_rtRChange[1] = QRect(m_rtRChange[0].x() - w,         height() - h, w, h);
    m_rtRChange[2] = QRect(m_rtRChange[1].x() - w + COVER, height() - h, w, h);
    m_rtRChange[3] = QRect(m_rtRChange[2].x() - w + COVER, height() - h, w, h);
    m_rtRChange[4] = QRect(m_rtWall[0].x() - w + COVER,    height() - h, w, h);

    //根据索引得到当前活动的三个Wall的下标
    int i, j, k, l;
    wallIndex(true, m_iWall, i, j, k, l);

    m_pWall[i]->setGeometry(m_rtWall[0]);
    m_pWall[j]->setGeometry(m_rtWall[1]);
    m_pWall[k]->setGeometry(m_rtWall[2]);
}

/***************************************************
 * 函数名称: setLRButtonRect
 * 功   能: 设置左右移动两个按钮的大小及位置
 * 输入参数:
 * 输出参数:
 * *************************************************/
void AnimatedWallWG::setLRButtonRect()
{
    //设置按钮的大小
    int w = LRWIDTH;
    int h = height() * SCALE;
    m_pLRButton[0]->setGeometry(0,           height() - h, w, h);
    m_pLRButton[1]->setGeometry(width() - w, height() - h, w, h);
}

/***************************************************
 * 函数名称: setWallpaper
 * 功   能: 设置墙纸
 * 输入参数:
 * 输出参数:
 * *************************************************/
void AnimatedWallWG::setWallpaper(QLabel *pWall, int i)
{
    if (pWall == NULL) return;
    QString style = QString("QLabel{border: 0px; border-image: url(:/image/wall/%1.jpg);}"
                            "QLabel:hover{background-color: rgba(255, 255, 255, 30%);}").arg(i);

    pWall->setStyleSheet(style);
}

/***************************************************
 * 函数名称: wallIndex
 * 功   能: 通过索引得到相对应的控件的下标
 * 输入参数: b   正反向
 *          n  当前索引
 *
 * 输出参数: i  左边控件的下标
 *          j  中间控件的下标
 *          k  右边控件的下标
 *          l  待出来控件的下标
 * *************************************************/
void AnimatedWallWG::wallIndex(bool b, int n, int &i, int &j, int &k, int &l)
{
    switch (n)
    {
    case 0: i = 0; j = 1; k = 2; l = b ? 3 : 5; break;
    case 1: i = 1; j = 2; k = 3; l = b ? 4 : 0; break;
    case 2: i = 2; j = 3; k = 4; l = b ? 5 : 1; break;
    case 3: i = 3; j = 4; k = 5; l = b ? 0 : 2; break;
    case 4: i = 4; j = 5; k = 0; l = b ? 1 : 3; break;
    case 5: i = 5; j = 0; k = 1; l = b ? 2 : 4; break;
    }
}

/***************************************************
 * 函数名称: moveToRight
 * 功   能: 从右往左移动
 * 输入参数:
 * 输出参数:
 * *************************************************/
void AnimatedWallWG::moveToLeft()
{
    //判图片断当前是否可以轮换图片
    if (!m_bAnimation) return;
    m_bAnimation = false;

    //根据当前索引获取左、中、右、待出现的控件
    int i, j, k, l;
    wallIndex(true, m_iWall, i, j, k, l);
    m_iRaise = k;

    //创建动画
    QPropertyAnimation *pAnimation[4];

    //左
    pAnimation[0] = new QPropertyAnimation(m_pWall[i], "geometry");
    connect(pAnimation[0], SIGNAL(finished()), pAnimation[0], SLOT(deleteLater()));
    pAnimation[0]->setDuration(DURATION);
    pAnimation[0]->setEasingCurve(EASINGCURVE);
    pAnimation[0]->setKeyValueAt(0, m_rtWall[0]);
    pAnimation[0]->setKeyValueAt(EASINGTIME, m_rtRChange[3]);
    pAnimation[0]->setKeyValueAt(1, m_rtRChange[4]);

    //中
    pAnimation[1] = new QPropertyAnimation(m_pWall[j], "geometry");
    connect(pAnimation[1], SIGNAL(finished()), pAnimation[1], SLOT(deleteLater()));
    pAnimation[1]->setDuration(DURATION);
    pAnimation[1]->setEasingCurve(EASINGCURVE);
    pAnimation[1]->setKeyValueAt(0, m_rtWall[1]);
    pAnimation[1]->setKeyValueAt(EASINGTIME, m_rtRChange[2]);
    pAnimation[1]->setKeyValueAt(1, m_rtWall[0]);

    //右
    pAnimation[2] = new QPropertyAnimation(m_pWall[k], "geometry");
    connect(pAnimation[2], SIGNAL(finished()), pAnimation[2], SLOT(deleteLater()));
    connect(pAnimation[2], SIGNAL(valueChanged(QVariant)), this, SLOT(onValueChanged(QVariant)));
    pAnimation[2]->setDuration(DURATION);
    pAnimation[2]->setEasingCurve(EASINGCURVE);
    pAnimation[2]->setKeyValueAt(0, m_rtWall[2]);
    pAnimation[2]->setKeyValueAt(EASINGTIME, m_rtRChange[1]);
    pAnimation[2]->setKeyValueAt(1, m_rtWall[1]);

    //待出现
    pAnimation[3] = new QPropertyAnimation(m_pWall[l], "geometry");
    connect(pAnimation[3], SIGNAL(finished()), pAnimation[3], SLOT(deleteLater()));
    pAnimation[3]->setDuration(DURATION);
    pAnimation[3]->setEasingCurve(EASINGCURVE);
    pAnimation[3]->setKeyValueAt(0, m_rtRChange[0]);
    pAnimation[3]->setKeyValueAt(EASINGTIME, m_rtRChange[0]);
    pAnimation[3]->setKeyValueAt(1, m_rtWall[2]);

    //组
    QParallelAnimationGroup *pGroup = new QParallelAnimationGroup(this);
    connect(pGroup, SIGNAL(finished()), pGroup, SLOT(deleteLater()));
    connect(pGroup, SIGNAL(finished()), this, SLOT(finished()));
    pGroup->addAnimation(pAnimation[0]);
    pGroup->addAnimation(pAnimation[1]);
    pGroup->addAnimation(pAnimation[2]);
    pGroup->addAnimation(pAnimation[3]);
    pGroup->start();

    //序号++
    if (++m_iWall >= COUNT) m_iWall = 0;
}

/***************************************************
 * 函数名称: moveToRight
 * 功   能: 从左往右移动
 * 输入参数:
 * 输出参数:
 * *************************************************/
void AnimatedWallWG::moveToRight()
{
    //判图片断当前是否可以轮换图片
    if (!m_bAnimation) return;
    m_bAnimation = false;

    //根据当前索引获取左、中、右、待出现的控件
    int i, j, k, l;
    wallIndex(false, m_iWall, i, j, k, l);
    m_iRaise = i;

    //创建动画
    QPropertyAnimation *pAnimation[4];

    //左
    pAnimation[0] = new QPropertyAnimation(m_pWall[i], "geometry");
    connect(pAnimation[0], SIGNAL(finished()), pAnimation[0], SLOT(deleteLater()));
    connect(pAnimation[0], SIGNAL(valueChanged(QVariant)), this, SLOT(onValueChanged(QVariant)));
    pAnimation[0]->setDuration(DURATION);
    pAnimation[0]->setEasingCurve(EASINGCURVE);
    pAnimation[0]->setKeyValueAt(0, m_rtWall[0]);
    pAnimation[0]->setKeyValueAt(EASINGTIME, m_rtLChange[1]);
    pAnimation[0]->setKeyValueAt(1, m_rtWall[1]);

    //中
    pAnimation[1] = new QPropertyAnimation(m_pWall[j], "geometry");
    connect(pAnimation[1], SIGNAL(finished()), pAnimation[1], SLOT(deleteLater()));
    pAnimation[1]->setDuration(DURATION);
    pAnimation[1]->setEasingCurve(EASINGCURVE);
    pAnimation[1]->setKeyValueAt(0, m_rtWall[1]);
    pAnimation[1]->setKeyValueAt(EASINGTIME, m_rtLChange[2]);
    pAnimation[1]->setKeyValueAt(1, m_rtWall[2]);

    //右
    pAnimation[2] = new QPropertyAnimation(m_pWall[k], "geometry");
    connect(pAnimation[2], SIGNAL(finished()), pAnimation[2], SLOT(deleteLater()));
    pAnimation[2]->setDuration(DURATION);
    pAnimation[2]->setEasingCurve(EASINGCURVE);
    pAnimation[2]->setKeyValueAt(0, m_rtWall[2]);
    pAnimation[2]->setKeyValueAt(EASINGTIME, m_rtLChange[3]);
    pAnimation[2]->setKeyValueAt(1, m_rtLChange[4]);

    //待出现
    pAnimation[3] = new QPropertyAnimation(m_pWall[l], "geometry");
    connect(pAnimation[3], SIGNAL(finished()), pAnimation[3], SLOT(deleteLater()));
    pAnimation[3]->setDuration(DURATION);
    pAnimation[3]->setEasingCurve(EASINGCURVE);
    pAnimation[3]->setKeyValueAt(0, m_rtLChange[0]);
    pAnimation[3]->setKeyValueAt(EASINGTIME, m_rtLChange[0]);
    pAnimation[3]->setKeyValueAt(1, m_rtWall[0]);

    //组
    QParallelAnimationGroup *pGroup = new QParallelAnimationGroup(this);
    connect(pGroup, SIGNAL(finished()), pGroup, SLOT(deleteLater()));
    connect(pGroup, SIGNAL(finished()), this, SLOT(finished()));
    pGroup->addAnimation(pAnimation[0]);
    pGroup->addAnimation(pAnimation[1]);
    pGroup->addAnimation(pAnimation[2]);
    pGroup->addAnimation(pAnimation[3]);
    pGroup->start();

    //序号--
    if (--m_iWall < 0) m_iWall = COUNT - 1;
}

/***************************************************
 * 函数名称: onValueChanged
 * 功   能: 根据时间设置中间控件Raise
 * 输入参数:
 * 输出参数:
 * *************************************************/
void AnimatedWallWG::onValueChanged(QVariant variant)
{
    Q_UNUSED(variant);
    QPropertyAnimation *pAnimation = qobject_cast<QPropertyAnimation *>(sender());
    if (pAnimation == NULL) return;

    if (pAnimation->currentTime() > DURATION * EASINGTIME)
    {
        m_pLRButton[0]->raise();
        m_pLRButton[1]->raise();
        m_pWall[m_iRaise]->raise();
    }
}

/***************************************************
 * 函数名称: eventFilter
 * 功   能: 事件过滤器
 * 输入参数:
 * 输出参数:
 * *************************************************/
bool AnimatedWallWG::eventFilter(QObject *watched, QEvent *event)
{
    switch ((int)event->type())
    {
    case QEvent::Resize:
        setWallRect();
        setLRButtonRect();
        break;

    case QEvent::Enter:
        m_pLRButton[0]->show();
        m_pLRButton[1]->show();
        break;

    case QEvent::Leave:
        m_pLRButton[0]->hide();
        m_pLRButton[1]->hide();
        break;
    }

    return QWidget::eventFilter(watched, event);
}

/***************************************************
 * 函数名称: timerEvent
 * 功   能: 计时器
 * 输入参数:
 * 输出参数:
 * *************************************************/
void AnimatedWallWG::timerEvent(QTimerEvent *event)
{
    if (event->timerId() != m_idTimer) return;

    //默认从右到左
    moveToLeft();
}

/***************************************************
 * 函数名称: paintEvent
 * 功   能: 画背景色
 * 输入参数:
 * 输出参数:
 * *************************************************/
void AnimatedWallWG::paintEvent(QPaintEvent *event)
{
    QPainter paint(this);
    paint.setPen(Qt::NoPen);
    paint.setBrush(QBrush(QColor(250, 250, 252)));
    paint.drawRect(rect());

    QWidget::paintEvent(event);
}

