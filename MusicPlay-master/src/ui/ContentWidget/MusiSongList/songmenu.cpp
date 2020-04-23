#include "songmenu.h"
#include <QAction>


SongMenu::SongMenu(QWidget *parent) :
    QMenu(parent)
{
    initForm();
    initAction();
    initConnect();
}

SongMenu::~SongMenu()
{
}

void SongMenu::addModifyAction(QAction *action)
{
    addAction(action);
    connect(action, SIGNAL(triggered()),SIGNAL(signalModifyList()));
}

void SongMenu::initForm()
{
}

void SongMenu::initAction()
{
    m_actionAddNewList = new QAction(QIcon(":/image/contextMenu/context_add.png"),
                                     "新建列表",this);
    m_actionDeleteList = new QAction(QIcon(":/image/contextMenu/context_delete.png"),
                                     "删除列表",this);
    m_actionAddTipPicture = new QAction("添加歌单图片",this);
//    m_actionReName = new QAction("重命名",this);

    addAction(m_actionAddNewList);
    addSeparator();
    addAction(m_actionDeleteList);
    addSeparator();
    addAction(m_actionAddTipPicture);
//    addAction(m_actionReName);
}

void SongMenu::initConnect()
{
    connect(m_actionAddNewList,SIGNAL(triggered()),
            this,SIGNAL(signalAddNewList()));
    connect(m_actionDeleteList,SIGNAL(triggered()),
            this,SIGNAL(signalDeleteList()));
    connect(m_actionAddTipPicture,SIGNAL(triggered()),
            this,SIGNAL(signalAddTipPicture()));
    //connect(m_actionDeleteList,SIGNAL(triggered()),this,SIGNAL(obtainLsitName()));
//    connect(m_actionReName,SIGNAL(triggered()),
//            this,SIGNAL(signalRename()));
}
