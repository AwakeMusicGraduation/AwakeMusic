#include "musicdesktoplrcmanage.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QMouseEvent>
#include "lyrctoolbarwidget.h"      //工具栏
#include <QLinearGradient>
#include <QTimer>
#include <QTime>
#include <QPainter>
#include <QTextStream>
#include <QTextBlock>
#include <QTextCodec>

MusicDesktopLrcManage::MusicDesktopLrcManage(QWidget *parent)
    :QWidget(parent)
{
    initForm();
    initWidget();
    initConnect();
}

MusicDesktopLrcManage::~MusicDesktopLrcManage()
{
    delete m_toolBarWidget;
    delete m_labelLrc;
}

void MusicDesktopLrcManage::initForm()
{
    //设置窗体标题栏隐藏--Qt::WindowStaysOnTopHint |
    this->setWindowFlags(Qt::FramelessWindowHint |
                         Qt::WindowSystemMenuHint |
                         Qt::WindowMinMaxButtonsHint |
                         Qt::WindowStaysOnTopHint);    //设置窗口在最前端
    //设置背景透明
    this->setAttribute(Qt::WA_TranslucentBackground);
    setMouseTracking(true);
    setFixedSize(700,200);
    setGeometry(350,460,this->width(),this->height());
    this->setObjectName("desktopWiget");
    m_lrcText = new QTextEdit;
}

void MusicDesktopLrcManage::initWidget()
{
    m_toolBarWidget = new LyrcToolBarWidget(this);

    m_labelLrc = new QLabel(this);
    m_labelLrc->setAlignment(Qt::AlignHCenter |Qt::AlignVCenter);
    m_labelLrc->setText("欢迎使用AwakeMusic播放器");
    m_labelLrc->setFont(QFont("Times New Roman", 30, QFont::Bold));
    m_labelLrc->setStyleSheet("color:#9AD66A");

    m_mainLayout = new QVBoxLayout(this);
    m_mainLayout->addWidget(m_toolBarWidget);
    m_mainLayout->addWidget(m_labelLrc);
    m_mainLayout->setContentsMargins(0,0,0,0);

}

void MusicDesktopLrcManage::initConnect()
{
    connect(m_toolBarWidget,SIGNAL(signalClose()),
            this,SLOT(slotClose()));
    connect(m_toolBarWidget,SIGNAL(signalLock()),
            this,SLOT(slotLock()));
}

void MusicDesktopLrcManage::slotLock()
{
    m_toolBarWidget->hide();
}

void MusicDesktopLrcManage::slotClose()
{
    this->hide();
}

void MusicDesktopLrcManage::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_offset = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
    QWidget::mousePressEvent(event);
}

void MusicDesktopLrcManage::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        setCursor(Qt::PointingHandCursor);
        move(event->globalPos() - m_offset);
        event->accept();
    }
    QWidget::mousePressEvent(event);
}

void MusicDesktopLrcManage::enterEvent(QEvent *event)
{
    if (m_widgetLock){
        return;
    }

    QWidget::enterEvent(event);
    setStyleSheet("QWidget#desktopWiget{border: 1px solid #555555;"
                  "background-color:rgba(0,0,0,40)}");

}

void MusicDesktopLrcManage::leaveEvent(QEvent *event)
{
    if (m_widgetLock){
        return;
    }
    QWidget::leaveEvent(event);
    m_toolBarWidget->hide();
    setStyleSheet("QWidget#desktopWiget{background-color:transparent;}");
}

void MusicDesktopLrcManage::closeEvent(QCloseEvent *event)
{
    QWidget::closeEvent(event);
}
void MusicDesktopLrcManage::analysisLyrc(const QString &name)
{
    QString fileName = name;
    QString lrcName = fileName.remove(fileName.right(3)) + "lrc";
    QFile file(lrcName);

    if (!file.open(QFile::ReadOnly | QIODevice::Text))
    {
        m_labelLrc->setText("没有找到对应歌词!");
    }else
    {
        m_labelLrc->setText("正在加载歌词");
        QTextStream in(&file);
        in.setCodec("UTF-8");
        m_lrcText->setText(in.readAll());
    }
}

void MusicDesktopLrcManage::slotAnalyseLrc(QString name)
{
    QString lrcName = "/root/MusicPlay-master/Lrc/" + name + ".lrc";
    QFile file(lrcName);

    if (!file.open(QFile::ReadOnly | QIODevice::Text))
    {
        m_labelLrc->setText("没有找到对应歌词!");
    }else
    {
        m_labelLrc->setText("正在加载歌词");
        QTextStream in(&file);
        in.setCodec("UTF-8");
        m_lrcText->setText(in.readAll());
    }
}

void MusicDesktopLrcManage::slotReceiveMusicInfo(QString name)
{
    this->analysisLyrc(name);
}

//接收当前播放的时间
void MusicDesktopLrcManage::slotReceiveCurrentPlayTime(qint64 time)
{
#if QDEBUG_OUT
//    qDebug()<<"当前播放时间:"<<time;
#endif
    QTime curTime(0,(time/60000) % 60,(time / 1000) %60,time %1000);
    if (m_lrcText->find(curTime.toString("mm:ss").left(7)))
    {
        QString str = m_lrcText->textCursor().block().text().replace(
                    QRegExp("\\[\\d{2}:\\d{2}\\.\\d{2}\\]"),"");

        m_labelLrc->setText(str);
//        qDebug()<<QString(str);
    }
}


