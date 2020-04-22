#include "miniplaylayout.h"
#include "ui_miniplaylayout.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QFrame>
#include <QDebug>
#include "TitleBar/clickablelabel.h"

MiniPlayLayout::MiniPlayLayout(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::MiniPlayLayout)
{

    ui->setupUi(this);
    initWidget();
    qDebug() <<"连接！！！！！";
    connect(m_label1,&ClickableLabel::clicked,this,&MiniPlayLayout::signalShowOrHide);

}

MiniPlayLayout::~MiniPlayLayout()
{
    delete ui;
}

void MiniPlayLayout::slotReceiveImage(QImage image)
{
    m_label1->setScaledContents(true);
    QSize qs = m_label1->rect().size();
    //    image.scaled(m_label1->width(),m_label1->height());
    m_label1->setPixmap(QPixmap::fromImage(image).scaled(qs));
}

void MiniPlayLayout::slotReceiveNameAndSinger(QString name, QString singer)
{
    qDebug()<<"接收到歌曲信息   mini";
    m_label2->text().clear();
    m_label2->setText(name+"\n"+singer);
}

void MiniPlayLayout::slotShowOrHidedddd()
{
    if(showorhide==false){
        m_label1->setToolTip("显示歌词");
    }
    else {
        m_label1->setToolTip("隐藏歌词");
    }
    showorhide = !showorhide;
    qDebug()<<"接收槽";
    emit signalShowOrHide();
}

void MiniPlayLayout::initWidget()
{
    QFrame *wid = new QFrame();
    setTitleBarWidget(NULL);
    m_label1 = new ClickableLabel();
    m_label1->setCursor(Qt::PointingHandCursor);
    m_label1->setFixedSize(50,50);
    m_label1->setToolTip("显示歌词");
    //    m_label1->setStyleSheet("border:0.01px solid gray;");
    m_label2 = new ClickableLabel();
    //    m_label2->setStyleSheet("border:0.01px solid gray;");
    m_label1->setFrameShape(QFrame::NoFrame);
    m_label2->setFrameShape(QFrame::NoFrame);
    m_label1->setFixedSize(50,50);
    m_label1->move(0,0);
    m_label2->setFixedSize(105,50);

    //    wid->setFrameShape(QFrame::Box);
    wid->setFrameShape(QFrame::Box);
    //    wid->setFrameShape(QFrame::Sunken);
    QPalette pal;
    pal.setColor(QPalette::Background,Qt::white);
    wid->setAutoFillBackground(true);
    wid->setPalette(pal);
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(m_label1);
    layout->addWidget(m_label2);
    layout->addSpacing(0);

    wid->setLayout(layout);
    this->setWidget(wid);

    showorhide = false;
}
