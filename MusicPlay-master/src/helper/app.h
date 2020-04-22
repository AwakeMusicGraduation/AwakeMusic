﻿#ifndef APP_H
#define APP_H

#include "controlvalues.h"
class QString;

class App
{
public:
    static QString user;                    //用户名
    static QString password;                //密码
    static QString AppPath;                 //应用程序路径
    static int AppFontSize;                 //应用程序字体大小
    static QString AppFontName;             //应用程序字体名称

    static QString AppSkin;                 //软件皮肤
    static int AppPlayMode;                 //播放模式

    static QString AppTitle;                //界面标题

    static bool IsPlaying;                  //播放器是否正在播放

    static void ReadConfig();               //读取配置文件
    static void WriteConfig();              //写入配置文件
    static bool FileIsExist(QString strFile);

};

#endif // APP_H
