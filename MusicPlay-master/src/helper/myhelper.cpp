#include "myhelper.h"
#include <QApplication>
#include "app.h"
#include <QTime>
#include <QProcess>
#include <QSqlQuery>
#include <QDebug>
#include <QCompleter>
#include <QStandardItemModel>
#include <QLineEdit>

myHelper::myHelper(QObject *parent) :
    QObject(parent)
{
}


/*设置编码格式为GB2312*/
void myHelper::SetGBK2312Code()
{
    QTextCodec *codec=QTextCodec::codecForName("GB2312");
    QTextCodec::setCodecForLocale(codec);
}

/*设置编码格式为UTF8*/
void myHelper::SetUTF8Code()
{
#if(QT_VERSION <= QT_VERSION_CHECK(5,0,0))
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForTr(codec);

#endif
}

/*设置皮肤样式*/
void myHelper::SetStyle(const QString &StyleName)
{
    QFile file(QString(":/image/qss/%1.css").arg(StyleName));
    file.open(QFile::ReadOnly);
    QString qss = QLatin1String(file.readAll());
    qApp->setStyleSheet(qss);
    qApp->setPalette(QPalette(QColor("#F0F0F0")));
}

/*加载中文字符*/
void myHelper::SetChinese()
{
    QTranslator *translator = new QTranslator(qApp);
    translator->load(":/image/qt_zh_CN.qm");
    qApp->installTranslator(translator);
}


/*
 *函数功能：延时函数
 *输入参数：所要延时的时间
 *输出参数：无
 *返回值：无
*/
void myHelper::Sleep(int sec)
{
    QTime dieTime = QTime::currentTime().addMSecs(sec);
    while (QTime::currentTime() < dieTime)
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents,100);
    }
}


//返回播放支持的格式
QStringList myHelper::supportFormatsFilterDialogString()
{
    return QStringList() <<"*.mp3" <<"*.mp2" <<"*.mp1" <<"*.wav" <<"*.ogg";
}

QStringList myHelper::supportFormatsPicture()
{
    return  QStringList() << "*.JPG";
}
