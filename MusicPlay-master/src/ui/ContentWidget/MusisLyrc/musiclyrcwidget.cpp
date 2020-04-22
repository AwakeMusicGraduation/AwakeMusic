#include "musiclyrcwidget.h"
#include <QLabel>
#include <QVBoxLayout>
#include "app.h"
#include "controlvalues.h"
#include <QtDebug>
#include <QFile>
#include <QTextEdit>
#include <QTime>
#include <QTextBlock>
#include <QTextCodec>
#include <QScrollArea>

MusicLyrcWidget::MusicLyrcWidget(QWidget *parent)
    :QFrame(parent)
{
    initForm();
    initConnect();
}

MusicLyrcWidget::~MusicLyrcWidget()
{
}

void MusicLyrcWidget::mouseMoveEvent(QMouseEvent *event)
{
    //
}

void MusicLyrcWidget::initForm()
{
    m_lrcText = new QTextEdit;
    m_lrcText1 = new QTextEdit;
    //    setAttribute(Qt::WA_TranslucentBackground);
    //    setWindowFlags(Qt::FramelessWindowHint);
    installEventFilter(this);

    m_labelLyrc = new QLabel;
    m_labelLyrc->setObjectName("labelLyrc");
    m_lrcText->setText("本歌曲暂无歌词");
    m_lrcText->setFont(QFont(App::AppFontName, 20, QFont::Bold));
    m_lrcText->setCursor(Qt::PointingHandCursor);
    m_lrcText->setAlignment(Qt::AlignHCenter);
    //设置歌词颜色
    m_lrcText->setStyleSheet("color:#ED9464");

    //设置label自动换行(有些歌词太长，显示不完整)
    m_lrcText->adjustSize();
    //m_labelLyrc->setWordWrap(true);

    m_hideLrc = new QPushButton;
    m_hideLrc->setIcon(QIcon(":/image/hide"));
    m_hideLrc->setFlat(true);
    m_hideLrc->setCursor(Qt::PointingHandCursor);
    m_hideLrc->setIconSize(QSize(30,30));
    m_hideLrc->setFixedWidth(40);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *top = new QHBoxLayout;
    top->addStretch();
    top->addWidget(m_hideLrc,Qt::AlignLeft);
    mainLayout->addLayout(top);
    mainLayout->addWidget(m_lrcText);
    mainLayout->setContentsMargins(10,10,10,10);
    setLayout(mainLayout);
}

void MusicLyrcWidget::initConnect()
{
    connect(m_hideLrc,SIGNAL(clicked()),this,SIGNAL(signalHideLrc()));
}

void MusicLyrcWidget::analysisLyrc(const QString &name)
{
    QString fileName = name;
    QString lrcName = fileName.remove(fileName.right(3)) + "lrc";
    QFile file(lrcName);

    if (!file.open(QFile::ReadOnly | QIODevice::Text))
    {
        m_labelLyrc->setText("没有找到对应歌词!");
    }else
    {
        m_labelLyrc->setText("正在加载歌词");
        QTextStream in(&file);
        in.setCodec("UTF-8");
        m_lrcText->setText(in.readAll());
    }
}

void MusicLyrcWidget::slotReceiveMusicInfo(const QString &name)
{
#if QDEBUG_OUT
    qDebug()<<"当前歌曲名称:"<<name;
#endif
    this->analysisLyrc(name);
}

//接收当前播放的时间
void MusicLyrcWidget::slotReceiveCurrentPlayTime(qint64 time)
{
#if QDEBUG_OUT
    //    qDebug()<<"当前播放时间:"<<time;
#endif

    QTime curTime (0,(time/60000) % 60,(time / 1000) %60,time %1000);

    if (m_lrcText1->find(curTime.toString("mm:ss").left(7)))
    {
        QString str = curTime.toString("mm:ss").left(7);
        QString str1 = m_lrcText1->textCursor().block().text().replace(
                                        QRegExp("\\[\\d{2}:\\d{2}\\.\\d{2}\\]"),"");
        if(!str1.isEmpty())
            m_lrcText->scrollToAnchor(str);
    }


}

void MusicLyrcWidget::slotAnalyseMedia(QString name)
{
    QString lrcName = "/root/AwakeMusic/MusicPlay-master/Lrc/" + name + ".lrc";
    //QString lrcName = "/root/AwakeMusic/MusicPlay-master/Lrc/" + name;
    QFile file(lrcName);

    if (!file.open(QFile::ReadOnly | QIODevice::Text))
    {
        m_lrcText->setText("没有找到对应歌词!");
    }else
    {
        m_lrcText->clear();
        //m_labelLyrc->setText("正在加载歌词");
        while(!file.atEnd()){
            QString line = file.readLine();
            QString name = line.mid(1,5);
            line.replace(QRegExp("\\[\\d{2}:\\d{2}\\.\\d{2}\\]"),"");
            m_lrcText->append("<a name=\"" + name + "\" href=\"#word\">" + line +"</a>");
            m_lrcText->setFont(QFont("black",15,20));
            m_lrcText->setAlignment(Qt::AlignCenter);

        }
        file.close();
    }
    QFile file1(lrcName);
    if (file1.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file1);
        in.setCodec("UTF-8");
        m_lrcText1->setText(in.readAll());
    }
    file1.close();
}
