#include "app.h"
#include "myhelper.h"
#include <QSettings>
#include "controlvalues.h"

QString App::AppPath = "/root/MusicPlay-master/";
int App::AppFontSize = 13;
QString App::AppFontName = "文泉驿微米黑";

QString App::AppSkin = DEFAULT_SKIN;
int App::AppPlayMode = DEFAULT_PLAY_MODE;

QString App::AppTitle = "音乐播放器";

//bool App::AutoRun = false;

//默认开始没有播放音乐
bool App::IsPlaying = false;


//读取配置文件
void App::ReadConfig()
{
    QString fileName = App::AppPath + "MusicConfig.txt";
    //如果配置文件不存在,则以初始值继续运行,并生成新的配置文件
    if (!FileIsExist(fileName)) {
        //对应中文转成正确的编码
        App::AppTitle = App::AppTitle.toLatin1();
        WriteConfig();
        return;
    }

    QSettings *set = new QSettings(fileName, QSettings::IniFormat);

    set->beginGroup("AppConfig");
    App::AppSkin = set->value("AppSkin").toString();
    App::AppPlayMode = set->value("AppPlayMode").toInt();
    App::AppTitle = set->value("AppTitle").toString();
    App::IsPlaying = set->value("IsPlaying").toBool();
    set->endGroup();
}

//写入配置文件
void App::WriteConfig()
{
    QString fileName = App::AppPath + "MusicConfig.txt";
    QSettings *set = new QSettings(fileName, QSettings::IniFormat);

    set->beginGroup("AppConfig");
    set->setValue("AppSkin",App::AppSkin);
    set->setValue("AppPlayMode",App::AppPlayMode);
    set->setValue("AppTitle", App::AppTitle);
    set->setValue("IsPlaying",App::IsPlaying);
    set->endGroup();
}

bool App::FileIsExist(QString strFile)
{
    QFile tempFile(strFile);
    return tempFile.exists();
}
