//分类列表
#ifndef CLASSIFYLIST_H
#define CLASSIFYLIST_H

#include <QTableWidget>
#include <vector>
class MusicListMenu;

class classifyList : public QTableWidget
{
    Q_OBJECT
public:
    explicit classifyList(QWidget *parent);
    void removeAllItem();
    void initCurrent();
private:
    void initForm();
    void initConnect();
private Q_SLOTS:
    void slotCellClicked(int,int);
public Q_SLOTS:
    void addItemContent(QString content);
Q_SIGNALS:
    void signalSendData(QString catagory,QString data);
    void signalCategoryClicked();
private:
    std::vector<QString> m_catagory;
public:
    int m_currentCatagory;
};

#endif // CLASSIFYLIST_H
