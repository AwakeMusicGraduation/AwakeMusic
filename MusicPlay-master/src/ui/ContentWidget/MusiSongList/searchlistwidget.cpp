#include "searchlistwidget.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QDebug>

Searchlistwidget::Searchlistwidget(QWidget *parent)
    :QWidget(parent)
{
    //this->setGeometry(0,0,700,600); //设置窗体部件大小
    //this->resize(230,600);
    //this->setStyleSheet("selection-background-color:lightblue;");
}

void Searchlistwidget::initWidget(QWidget *w)
{
    QHBoxLayout *header = new QHBoxLayout;
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    m_btn1 = new QPushButton("歌曲");
    m_btn2 = new QPushButton("歌手");
    m_btn3 = new QPushButton("专辑");
    m_btn4 = new QPushButton("歌单");

    header->addWidget(m_btn1);
    header->addWidget(m_btn2);
    header->addWidget(m_btn3);
    header->addWidget(m_btn4);

    mainLayout->addLayout(header,Qt::AlignTop);
    mainLayout->addWidget(w);
   // w->show();
    setLayout(mainLayout);
    initConnect();
}

void Searchlistwidget::initConnect()
{
    connect(m_btn1,SIGNAL(clicked(bool)),this,SLOT(slotbtn1Clicked()));
    connect(m_btn2,SIGNAL(clicked(bool)),this,SLOT(slotbtn2Clicked()));
    connect(m_btn3,SIGNAL(clicked(bool)),this,SLOT(slotbtn3Clicked()));
    connect(m_btn4,SIGNAL(clicked(bool)),this,SLOT(slotbtn4Clicked()));
}

void Searchlistwidget::slotbtn1Clicked()
{
    emit signalSendData("music",m_data);
    emit signalBtnClicked();
}

void Searchlistwidget::slotbtn2Clicked()
{
    emit signalSendData("singer",m_data);
    emit signalBtnClicked();
}

void Searchlistwidget::slotbtn3Clicked()
{
    emit signalSendData("album",m_data);
    emit signalBtnClicked();
}

void Searchlistwidget::slotbtn4Clicked()
{
    emit signalSendData("musicList",m_data);
    emit signalBtnClicked();
}

void Searchlistwidget::slotSaveSearchContent(QString name)
{
    m_data = name;
}
