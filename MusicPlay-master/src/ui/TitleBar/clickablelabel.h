#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H
#include<QLabel>
#include<QDebug>
#include<QMouseEvent>

class ClickableLabel:public QLabel
{
    Q_OBJECT
public:
    explicit ClickableLabel(const QString text,QWidget *parent = 0):QLabel(parent)
    {
        setText(text);
    }
    ~ClickableLabel()
    {

    }
signals:
    void clicked();
protected:
    virtual void mousePressEvent(QMouseEvent* event)
    {
        qDebug() << "显示首页";
        emit clicked();
    }

};




#endif // CLICKABLELABEL_H
