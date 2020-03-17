#include <QApplication>
#include "musicmainwidget.h"
#include "myhelper.h"
#include "app.h"
#include "loginform_test.h"
#include <QtSql>
#include <QSqlQuery>

int main(int argc,char *argv[])
{
    QApplication app(argc,argv);
    //Mainform_test *main = new Mainform_test();
    //main->setWindowTitle("欢迎界面");

    //
    DataBase d;
    d.createConnection();
    d.createTable();
    loginform_test login;
    if(login.exec() == QDialog::Accepted){
            myHelper::SetChinese();     //加载中文翻译字符
            myHelper::SetUTF8Code();    //设置编码方式
            myHelper::SetStyle("blue"); //设置程序样式
        //    App::WriteConfig();         //写入配置文件
            App::ReadConfig();
            MusicMainWidget widget;
            widget.show();
        return app.exec();
    }
    else {
        return  0;
    }
}
