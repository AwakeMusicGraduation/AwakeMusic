#include "mymediaplaylist.h"
#include "ui_mymediaplaylist.h"
#include "musicsongslistwidget.h"
#include <QTabWidget>
#include <QTableWidget>
#include <QDebug>
#include <QMap>
#include <QMenu>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QPalette>
#include <QTimer>
#include "playmusic.h"

MyMediaPlayList::MyMediaPlayList(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::MyMediaPlayList)
{
    ui->setupUi(this);

    initWidget();
    initForm();
    initMenu();
    initConnect();
}

MyMediaPlayList::~MyMediaPlayList()
{
    delete ui;
}

void MyMediaPlayList::initWidget()
{
    m_tab = new QTabWidget(this);
    m_table1 = new QTableWidget;
    m_tab->addTab(m_table1, tr("播放列表"));
    m_table2 = new QTableWidget(this);
    m_tab->addTab(m_table2, tr("历史记录"));

    this->setWidget(m_tab);
}

void MyMediaPlayList::initForm()
{
    this->setStyleSheet("selection-background-color:lightblue;");
    m_table1->setAlternatingRowColors(true);
    m_table2->setAlternatingRowColors(true);
    //设置没有焦点，这样就可以避免删除时，不选中行也能删除的问题!
    setFocusPolicy(Qt::NoFocus);
    m_table1->setColumnCount(3);
    m_table1->setRowCount(0);
    m_table1->setShowGrid(false);//display the grid
    m_table1->setEditTriggers(QAbstractItemView::NoEditTriggers);     //设置表格不能编辑
    m_table1->setSelectionBehavior(QAbstractItemView::SelectRows);    //进整行选择
    m_table1->setSelectionMode(QAbstractItemView::SingleSelection);
    m_table1->verticalHeader()->setDefaultSectionSize(25);
    m_table1->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);    //设置不可滑动
    m_table1->setContextMenuPolicy(Qt::CustomContextMenu);//允许m_table1接收QWidget::customContextMenuRequested()信号。


    //进行“列设置”
    //    m_table1->setSelectionBehavior(QAbstractItemView::SelectColumns);
    m_table1->setColumnWidth(0,250);

    QHeaderView *headerview = m_table1->horizontalHeader();
    headerview->setVisible(false);
    m_table1->verticalHeader()->setVisible(false);

    //鼠标右键初始化
    //    m_menu = new MusicListMenu(this);
    setFocusPolicy(Qt::NoFocus);
    m_table2->setColumnCount(3);
    m_table2->setRowCount(0);
    m_table2->setShowGrid(false);//display the grid
    m_table2->setEditTriggers(QAbstractItemView::NoEditTriggers);     //设置表格不能编辑
    m_table2->setSelectionBehavior(QAbstractItemView::SelectRows);    //进整行选择
    m_table2->setSelectionMode(QAbstractItemView::SingleSelection);
    m_table2->verticalHeader()->setDefaultSectionSize(25);
    m_table2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);    //设置不可滑动


    //进行“列设置”
    //    m_table1->setSelectionBehavior(QAbstractItemView::SelectColumns);
    m_table2->setColumnWidth(0,250);
    m_table2->horizontalHeader()->setVisible(false);
    m_table2->verticalHeader()->setVisible(false);
}

void MyMediaPlayList::initMenu()
{
    qDebug()<<"初始化菜单";
    m_menu = new QMenu(m_table1);
    m_furthermenu = new QMenu("加入播放列表");

    QAction *actionpPlayMusic = new QAction("播放",this);
    QAction *actionDeleteFromPlayList = new QAction("从列表中删除",this);
    QAction *actionDeleteAll = new QAction("清空",this);

    m_menu->addAction(actionpPlayMusic);

    m_menu->addSeparator();
    m_menu->addAction(actionDeleteFromPlayList);
    m_menu->addSeparator();
    m_menu->addAction(actionDeleteAll);
    m_menu->addSeparator();
    m_menu->addMenu(m_furthermenu);

    connect(m_table1, SIGNAL(customContextMenuRequested(QPoint)),this, SLOT(slotShowQmenu(QPoint)));
    connect(actionpPlayMusic,SIGNAL(triggered(bool)),this,SLOT(slotPlayMusic()));
    connect(actionDeleteAll,SIGNAL(triggered(bool)),this,SLOT(slotRemoveAllItem()));
    connect(actionDeleteFromPlayList,SIGNAL(triggered(bool)), this, SLOT(slotDeleFromPlayList()));
}

void MyMediaPlayList::initConnect()
{

    connect(this->m_table1,SIGNAL(cellDoubleClicked(int,int)),
            this,SLOT(slotCellDoubleClicked(int,int)));
}

void MyMediaPlayList::addContenItem(QStringList m,int i)
{
    qDebug()<<m.at(0);
    //总函数加1
    m_table1->insertRow(i);
    //添加一条记录到表格中来
    m_table1->setItem(i,0,new QTableWidgetItem(m.at(0)));
    m_table1->setItem(i,1,new QTableWidgetItem(m.at(1)));
    m_table1->setItem(i,2,new QTableWidgetItem(m.at(2)));

}

void MyMediaPlayList::addItemToHistoryList(QStringList m)
{
    int rowIndex = m_table2->rowCount();
    m_table2->setRowCount(rowIndex+1);
    m_table2->setItem(rowIndex,0,new QTableWidgetItem(m.at(0)));
    m_table2->setItem(rowIndex,1,new QTableWidgetItem(m.at(1)));
    m_table2->setItem(rowIndex,2,new QTableWidgetItem(m.at(2)));
}

void MyMediaPlayList::slotRemoveAllItem()
{
    m_table1->setRowCount(0);
    m_table1->clearContents();
    m_musicpath.clear();
}

void MyMediaPlayList::slotDeleFromPlayList()
{
    int row = m_table1->currentRow();
    m_musicpath.removeAt(row);
    m_table1->removeRow(row);
}

bool MyMediaPlayList::checkRepeatMusic(QString &path)
{
    for(int i=0; i<m_musicpath.size(); i++)
        if(m_musicpath.at(i).path==path)
            return false;
    return true;
}

void MyMediaPlayList::playMusicByOrder()
{
    //判断当前列表是否为空
    if (m_table1->rowCount()<0)
        return;
    //获取当前行
    int rowIndex = m_currentplay;
    int totalRow = m_table1->rowCount();
    qDebug()<<"rowIndex:"<<rowIndex;
    QString str = "";
    //到到歌曲列表末尾时，从第一首开始播放
    if (rowIndex < totalRow - 1)
    {
        qDebug()<<"rowIndex:"<<rowIndex;
        str = m_table1->item(rowIndex + 1,0)->text();
        //设置焦点，若不设置焦点，会总是从第一首个播放
        m_table1->setCurrentCell(0,0,QItemSelectionModel::Clear);
        m_table1->setCurrentCell(rowIndex + 1,0,QItemSelectionModel::SelectCurrent);
        m_currentplay++;
        emit signalSendPlayNextMusic(m_musicpath.at(m_currentplay).path,m_musicpath.at(m_currentplay).i);
    }
    else {
        //播放到最后一首歌曲时停止播放
        m_currentplay=0;
        //发送改变底部播放按钮的信号
    }
#if QDEBUG_OUT
    qDebug()<<"获取下一首歌曲"<<str;
#endif
}

void MyMediaPlayList::playMusicByDisorder()
{
    //判断当前列表是否为空
    if (m_table1->rowCount()<0)
        return;
    int totalRow = m_table1->rowCount();
    int m_currentplay =  qrand()%totalRow;
    qDebug()<<"playIndex:"<<m_currentplay;
    m_table1->setCurrentCell(m_currentplay,0,QItemSelectionModel::SelectCurrent);

    emit signalSendPlayNextMusic(m_musicpath.at(m_currentplay).path,m_musicpath.at(m_currentplay).i);
}

void MyMediaPlayList::addMusicToHistoryList()
{
    if(m_historypath.size()<30){
        m_historypath.push_back(m_musicpath.at(m_currentplay).path);
        QStringList s;
        s<<m_table1->item(m_currentplay,0)->text()<<m_table1->item(m_currentplay,1)->text()<<m_table1->item(m_currentplay,2)->text();
        addItemToHistoryList(s);
    }
    else {
        m_historypath.pop_front();
        m_historypath.push_back(m_musicpath.at(m_currentplay).path);
        m_table2->removeRow(0);
        QStringList s;
        s<<m_table1->item(m_currentplay,0)->text()<<m_table1->item(m_currentplay,1)->text()<<m_table1->item(m_currentplay,2)->text();
        addItemToHistoryList(s);
    }
}

void MyMediaPlayList::signalForPlay()
{

}

void MyMediaPlayList::slotCellDoubleClicked(int row, int column)
{
    //    qDebug() << "接收到播放列表信号";
    m_currentplay = row;
    QString musicPath = m_musicpath.at(row).path;
    qDebug()<<"路径"<<musicPath;
    if(m_musicpath.at(row).i==0){
        emit signalPlayMusic(musicPath);
    }
    else {
        emit signalPlayMediaMusic(musicPath);
        emit signalshowPictureandLrc(m_table1->item(row,0)->text());
    }
    emit signalSendNameAndSinger(m_table1->item(row,0)->text(),m_table1->item(row,1)->text());
    addMusicToHistoryList();

}

void MyMediaPlayList::slotPlayMusic()
{
    int rowIndex = m_table1->currentRow();
    m_currentplay = rowIndex;
    QString musicPath = m_musicpath.at(rowIndex).path;

    if(m_musicpath.at(rowIndex).i==0){
        emit signalPlayMusic(musicPath);
    }
    else {
        emit signalPlayMediaMusic(musicPath);
        emit signalshowPictureandLrc(m_table1->item(m_currentplay,0)->text());
    }
    emit signalSendNameAndSinger(m_table1->item(m_currentplay,0)->text(),m_table1->item(m_currentplay,1)->text());
    addMusicToHistoryList();

}

void MyMediaPlayList::slotAddNextLocalPlayMusic(QString& path)
{
    PlayMusic playmusic;
    if(checkRepeatMusic(path)){
        int rowIndex = m_table1->currentRow();
        playInfo playinfo = {0,path};
        m_musicpath.insert(rowIndex, playinfo);
        QStringList s = playmusic.ResolutionMusicPath(path);
        addContenItem(s, rowIndex+1 );
    }
    else {
        //弹出提示框
        emit signalReatMusic();
    }
}

void MyMediaPlayList::slotAddNextOnlinePlayMusic(QStringList &musicinfo)
{
    qDebug() << "接受到在线歌曲";
    QString s = musicinfo.at(3);
    if(checkRepeatMusic(s)){
        int rowIndex = m_table1->currentRow();
        playInfo playinfo = {1,s};
        m_musicpath.insert(rowIndex, playinfo);
        QStringList m ;
        m << musicinfo.at(0) << musicinfo.at(1) << musicinfo.at(2);
        addContenItem(m, rowIndex+1 );
    }
    else {
        //弹出提示框
        emit signalReatMusic();
    }
}

//接收并显示本地音乐
void MyMediaPlayList::slotReceiveList1(QList<QString>  &musicname,int row)
{
    PlayMusic playmusic;
    qDebug()<<"接收到默认播放列表";
    slotRemoveAllItem();
    for(int i=0; i<musicname.size(); i++){
        QStringList s;
        s=playmusic.ResolutionMusicPath(musicname.at(i));
        playInfo playinfo={0,musicname.at(i)};
        m_musicpath.append(playinfo);
        addContenItem(s,i);
    }
    m_currentplay=row;//设置当前播放的歌曲的行数
    m_table1->setCurrentCell(m_currentplay,0,QItemSelectionModel::SelectCurrent);
    emit signalSendNameAndSinger(m_table1->item(m_currentplay,0)->text(),m_table1->item(m_currentplay,1)->text());
    addMusicToHistoryList();

}

void MyMediaPlayList::slotReceiveList2(QList<QStringList> &musicinfo, int row)
{
    slotRemoveAllItem();
    m_musicpath.clear();
    for(int i=0; i<musicinfo.size(); i++){
        QStringList s = musicinfo.at(i);
        QStringList m;
        m << s.at(0) << s.at(1) << s.at(2);
        playInfo playinfo = {1, s.at(3)};
        m_musicpath.append(playinfo);
        addContenItem(m,i);
    }
    m_currentplay=row;//设置当前播放的歌曲的行数
    m_table1->setCurrentCell(m_currentplay,0,QItemSelectionModel::SelectCurrent);
    emit signalSendNameAndSinger(m_table1->item(m_currentplay,0)->text(),m_table1->item(m_currentplay,1)->text());
    addMusicToHistoryList();
    if(m_musicpath.at(m_currentplay).i==1)
        emit signalshowPictureandLrc(m_table1->item(m_currentplay,0)->text());
}

void MyMediaPlayList::slotShowQmenu(QPoint pos)
{
    emit signalObtainListName();
    qDebug() << "接收到菜单信号";
    QModelIndex index = m_table1->indexAt(pos);
    if(index.row()>=0){
        m_menu->exec(QCursor::pos());
    }
}

void MyMediaPlayList::slotGetNextMusic()
{
    //判断当前列表是否为空
    if (m_table1->rowCount()<0)
        return;
    //获取当前行
    int rowIndex = m_currentplay;
    int totalRow = m_table1->rowCount();
    qDebug()<<"rowIndex:"<<rowIndex;
    QString str = "";
    if (rowIndex >= 0)
    {
        //到到歌曲列表末尾时，从第一首开始播放
        if (rowIndex < totalRow - 1)
        {
            qDebug()<<"rowIndex:"<<rowIndex;
            str = m_table1->item(rowIndex + 1,0)->text();
            //设置焦点，若不设置焦点，会总是从第一首个播放
            m_table1->setCurrentCell(0,0,QItemSelectionModel::Clear);
            m_table1->setCurrentCell(rowIndex + 1,0,QItemSelectionModel::SelectCurrent);
            m_currentplay++;
        }
        else {
            str = m_table1->item(0,0)->text();
            //设置焦点，若不设置焦点，会总是从第一首个播放
            m_table1->setCurrentCell(totalRow,0,QItemSelectionModel::Clear);
            m_table1->setCurrentCell(0,0,QItemSelectionModel::Select);
            m_currentplay=0;
        }
#if QDEBUG_OUT
        qDebug()<<"获取下一首歌曲"<<str;
#endif
    }else
    {
        str = m_table1->item(0,0)->text();
        //设置焦点在第一行
        m_table1->setCurrentCell(0,0,QItemSelectionModel::Select);
    }

    emit signalSendPlayNextMusic(m_musicpath.at(m_currentplay).path,m_musicpath.at(m_currentplay).i);
    emit signalSendNameAndSinger(m_table1->item(m_currentplay,0)->text(),m_table1->item(m_currentplay,1)->text());
    addMusicToHistoryList();
    if(m_musicpath.at(m_currentplay).i==1)
        emit signalshowPictureandLrc(m_table1->item(m_currentplay,0)->text());
}

void MyMediaPlayList::slotGetPreviouseMusic()
{
    //判断当前列表是否为空
    if (m_table1->rowCount()<0)
        return;
    //获取当前行
    int rowIndex = m_currentplay;
    QString str = "";
    if (rowIndex >= 1)
    {
        str = m_table1->item(rowIndex - 1,0)->text();
        //设置焦点，若不设置焦点，会总是从第一首个播放
        m_table1->setCurrentCell(rowIndex - 1,0,QItemSelectionModel::SelectCurrent);
        m_currentplay--;
#if QDEBUG_OUT
        qDebug()<<"获取上一首歌曲"<<str;
#endif
    }else
    {
        //        str = m_table1->item(0,0)->text();
        //设置焦点在最后一行
        m_table1->setCurrentCell(0,0,QItemSelectionModel::Clear);
        //        m_table1->setCurrentCell(0,0,QItemSelectionModel::Select);
        m_table1->setCurrentCell(m_table1->rowCount()-1,0,QItemSelectionModel::Select);
        m_currentplay=m_table1->rowCount()-1;
    }

    emit signalSendPreviousMusic(m_musicpath.at(m_currentplay).path,m_musicpath.at(m_currentplay).i);
    emit signalSendNameAndSinger(m_table1->item(m_currentplay,0)->text(),m_table1->item(m_currentplay,1)->text());
    addMusicToHistoryList();
    if(m_musicpath.at(m_currentplay).i==1)
        emit signalshowPictureandLrc(m_table1->item(m_currentplay,0)->text());
}

void MyMediaPlayList::slotGetFirstPlayMusic()
{

}

void MyMediaPlayList::slotSendPlayCmd(int mode)
{
    switch(mode)
    {
    case ORDER_PLAY:            //顺序循环
        playMusicByOrder();
        break;
    case LIST_CIRCUAL:          //列表循环
        slotGetNextMusic();
        break;
    case SINGLE_CIRCUAL:        //单曲循环
        emit signalSendPlayNextMusic(m_musicpath.at(m_currentplay).path,m_musicpath.at(m_currentplay).i);
        break;
    case RADOM_PLAY:            //随机播放
        playMusicByDisorder();
        break;
    default:
        break;
    }
    emit signalSendNameAndSinger(m_table1->item(m_currentplay,0)->text(),m_table1->item(m_currentplay,1)->text());
    addMusicToHistoryList();
    if(m_musicpath.at(m_currentplay).i==1)
        emit signalshowPictureandLrc(m_table1->item(m_currentplay,0)->text());
}

void MyMediaPlayList::slotReceiveListName(std::vector<QString> listname)
{
    qDebug() << "初始化二级菜单";
    QAction *action1;
    if(!listname.empty()){
        m_furthermenu->clear();
        for(auto l:listname)
        {
            qDebug() <<"接收到列表名" << l << "listnamename";
            action1 = new QAction(l,this);
            m_furthermenu->addAction(action1);
            m_furthermenu->addSeparator();
        }
    }
    else {
        m_furthermenu->clear();
        action1 = new QAction("无列表，请新增列表");
        m_furthermenu->addAction(action1);
    }
    connect(m_furthermenu,SIGNAL(triggered(QAction*)),SLOT(slotResponse(QAction*)));
}

void MyMediaPlayList::slotResponse(QAction *action)
{
    QString list = action->text();
    qDebug() << "like the name" << list;
    int row = m_table1->currentRow();
    QString label = "addmusictolist";
    QString name = m_table1->item(row,0)->text();
    QString singer = m_table1->item(row,1)->text();
    QString album = m_table1->item(row,2)->text();
    qDebug() << name << singer << album;
    emit signalAddMusicToList(label,list,name,singer,album);
}


