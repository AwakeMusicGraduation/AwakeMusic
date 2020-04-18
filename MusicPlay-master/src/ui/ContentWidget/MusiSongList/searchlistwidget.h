#ifndef SEARCHLISTWIDGET_H
#define SEARCHLISTWIDGET_H
#include <QWidget>
class QPushButton;


class Searchlistwidget : public QWidget
{
    Q_OBJECT
public:
    Searchlistwidget(QWidget *parent = nullptr);
    void initWidget(QWidget *w);
    void initConnect();
private:
    QPushButton *m_btn1;
    QPushButton *m_btn2;
    QPushButton *m_btn3;
    QPushButton *m_btn4;
    QString m_data;//搜索传过来的信息
Q_SIGNALS:
    void signalSendData(QString name,QString data);
    void signalBtnClicked();
public Q_SLOTS:
    void slotbtn1Clicked();
    void slotbtn2Clicked();
    void slotbtn3Clicked();
    void slotbtn4Clicked();
    void slotSaveSearchContent(QString name);
};

#endif // SEARCHLISTWIDGET_H
