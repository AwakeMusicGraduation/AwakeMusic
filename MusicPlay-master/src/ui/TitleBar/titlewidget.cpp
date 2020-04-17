#include "titlewidget.h"
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include "controlvalues.h"
#include "searchlineedit.h"
#include <QDebug>
#include "clickablelabel.h"
//#include "iconhelper.h"

//构造函数
TitleWidget::TitleWidget(QWidget *parent) :
    QWidget(parent)
{
    initForm();
    initWidget();
    initLayout();
    initConnect();
}

//析构函数
TitleWidget::~TitleWidget()
{
    delete m_labelIcon;
    delete m_labelTitle;
    delete m_pbnLogin;
    delete m_pbnSkin;
    delete m_pbnMin;
    delete m_pbnClose;
}

//样式初始化
void TitleWidget::initForm()
{
    //设置标题栏固定宽度
    setFixedHeight(TITLE_HEIGHT);
}

//界面初始化
void TitleWidget::initWidget()
{
    //程序图标
    m_labelIcon = new QLabel(this);
    //IconHelper::Instance()->SetIcoMain(m_labelIcon);
    //程序标题
    m_labelTitle  = new ClickableLabel("AwakeMusic",this);
//    m_labelTitle->setPixmap(QPixmap(":/image/MusicTitle.png"));
   // m_labelTitle->setText("AwakeMusic");
    QPalette pe;
    pe.setColor(QPalette::WindowText,Qt::white);
    m_labelTitle->setPalette(pe);

    m_labelTitle->setFont(QFont("Times New Roman", 20, QFont::Bold));
    m_labelTitle->setObjectName("whiteLabel");

    //搜索框
    m_search = new SearchLineEdit(this);

    //登录按钮
    m_pbnLogin = new QPushButton(this);
    m_pbnLogin->setCursor(Qt::PointingHandCursor);
    m_pbnLogin->setToolTip("登录");
    m_pbnLogin->setObjectName("pbnLogin");
    m_pbnLogin->setFixedSize(80,26);
    m_pbnLogin->setIcon(QIcon(":/image/title/login.jpg"));
    m_pbnLogin->setIconSize(QSize(80,26));
    //m_pbnLogin->setText("未登录");


    //皮肤按钮
    m_pbnSkin = new QPushButton(this);
    m_pbnSkin->setCursor(Qt::PointingHandCursor);
    m_pbnSkin->setToolTip("皮肤");
    m_pbnSkin->setIcon(QIcon(":/image/title/skin.png"));
    m_pbnSkin->setObjectName("pbnSkin");
    //最小化
    m_pbnMin = new QPushButton(this);
    m_pbnMin->setFlat(true);
    m_pbnMin->setCursor(Qt::PointingHandCursor);
    m_pbnMin->setToolTip("最小化");
    m_pbnMin->setIcon(QIcon(":/image/title/min.png"));
    m_pbnMin->setObjectName("pbnMin");
    //关闭
    m_pbnClose = new QPushButton(this);
    m_pbnClose->setFlat(true);
    m_pbnClose->setObjectName("pbnClose");
    m_pbnClose->setIcon(QIcon(":/image/title/close.png"));
    m_pbnClose->setCursor(Qt::PointingHandCursor);
    m_pbnClose->setToolTip("关闭");

}

//布局初始化
void TitleWidget::initLayout()
{
    m_mainLayout = new QHBoxLayout(this);
    m_mainLayout->addSpacing(2);
    m_mainLayout->addWidget(m_labelIcon);
    m_mainLayout->addWidget(m_labelTitle);
    m_mainLayout->addStretch();
    m_mainLayout->addWidget(m_search);
    m_mainLayout->addStretch();
    m_mainLayout->addWidget(m_pbnLogin);
    m_mainLayout->addWidget(m_pbnSkin);
    m_mainLayout->addWidget(m_pbnMin);
    m_mainLayout->addWidget(m_pbnClose);
    m_mainLayout->setContentsMargins(0,0,0,0);
    setLayout(m_mainLayout);
}

//信号和槽初始化
void TitleWidget::initConnect()
{
    //依次为：登录、皮肤、最小化、关闭按钮的信号关联
    connect(m_pbnLogin,SIGNAL(clicked()),
            this,SIGNAL(signalLogin()));
    connect(m_pbnSkin,SIGNAL(clicked()),
            this,SIGNAL(signalSkin()));
    connect(m_pbnMin,SIGNAL(clicked()),
            this,SIGNAL(signalMin()));
    connect(m_pbnClose,SIGNAL(clicked()),
            this,SIGNAL(signalClose()));
    connect(m_search,SIGNAL(signalSearchContent(QString)),
            this,SIGNAL(signalSearchContent(QString)));
    connect(m_search,SIGNAL(signalSearchClicked()),
            this,SIGNAL(signalSearchClicked()));
    connect(m_labelTitle,&ClickableLabel::clicked,this,&TitleWidget::signalShowHomePage);
}

void TitleWidget::slotUpdateName(QString name)
{
    m_pbnLogin->setText(name);
    m_pbnLogin->setFont(QFont("Times New Roman", 15, QFont::Black));
    m_pbnLogin->setIconSize(QSize(0,0));
    qDebug() << name;
}
