#include "mainwindow.h"
#include "server.h"
#include "sqltable.h"
#include "music.h"
#include "musicbroker.h"
#include <QApplication>
//1

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Server *server = new Server;
    server->show();
    Sqltable *sqltable = new Sqltable();
//    sqltable->query();
    //sqltable->insertParmeterUser("123","123");
    //sqltable->insertParmeterUser("123456","123456");
    //sqltable->login("123456","123456");
//    sqltable->login("123","123");
    //sqltable->createMusicList("favor");
//    sqltable->insertMusicList("favor","初学者","初学者","薛之谦");
//    sqltable->deleteMusicList("favor","初学者","初学者","薛之谦");
    //MainWindow *w=new MainWindow;
    //w->show();
    return a.exec();
}
