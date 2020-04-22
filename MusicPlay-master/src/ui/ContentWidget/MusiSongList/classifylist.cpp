#include "classifylist.h"
#include "controlvalues.h"
#include <QVBoxLayout>
#include <QHeaderView>

classifyList::classifyList(QWidget *parent)
    :QTableWidget(parent)
{
    initForm();
    initConnect();
    initCurrent();
}

void classifyList::addItemContent(QString content)
{
    QTableWidgetItem *item = new QTableWidgetItem (content);
    item->setTextAlignment(Qt::AlignLeft |Qt::AlignVCenter);
    int rowIndex = rowCount();
    if (rowIndex >= 0)
    {
        //总函数加1
        setRowCount(rowIndex + 1);
        //添加一条记录到表格中来
        setItem(rowIndex,0,item);
    }
}

void classifyList::removeAllItem()
{
    setRowCount(0);
    clearContents();
}

void classifyList::initCurrent()
{
    m_currentCatagory = 0;
    removeAllItem();
    addItemContent("男歌手");
    addItemContent("女歌手");
    addItemContent("乐队");
}

void classifyList::initForm()
{
    setFixedWidth(CENTERWIDGET_RIGHT);
    this->setStyleSheet("selection-background-color:lightblue;");
    setAlternatingRowColors(true);
    setFixedWidth(CENTERWIDGET_RIGHT);
    setFocusPolicy(Qt::NoFocus);
    setColumnCount(1);
    setColumnWidth(0,CENTERWIDGET_RIGHT);
    setRowCount(0);
    setShowGrid(false);//display the grid
    setEditTriggers(QAbstractItemView::NoEditTriggers);     //设置表格不能编辑
    setSelectionBehavior(QAbstractItemView::SelectRows);    //设置整行选中
    setSelectionMode(QAbstractItemView::SingleSelection);
    //    horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    verticalHeader()->setDefaultSectionSize(45);

    QHeaderView *headerview = horizontalHeader();
    headerview->setVisible(false);
    headerview->resizeSection(0, 600);
    verticalHeader()->setVisible(false);
    QVBoxLayout *mainLayout = new QVBoxLayout;
    setLayout(mainLayout);

    m_catagory.push_back("singer");
    m_catagory.push_back("album");
    m_catagory.push_back("music");
}

void classifyList::initConnect()
{
    connect(this,SIGNAL(cellClicked(int,int)),
            this,SLOT(slotCellClicked(int,int)));
}

void classifyList::slotCellClicked(int row, int column)
{
    QString data = item(row,0)->text();
    removeAllItem();
    emit signalCategoryClicked();
    emit signalSendData(m_catagory.at(m_currentCatagory),data);
    m_currentCatagory += 1;
}
