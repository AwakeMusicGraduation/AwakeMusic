#ifndef MINIPLAYLAYOUT_H
#define MINIPLAYLAYOUT_H

#include <QDockWidget>

class QLabel;
class ClickableLabel;

namespace Ui {
class MiniPlayLayout;
}

class MiniPlayLayout : public QDockWidget
{
    Q_OBJECT

public:
    explicit MiniPlayLayout(QWidget *parent = nullptr);
    ~MiniPlayLayout();

Q_SIGNALS:
    void signalShowOrHide();

public Q_SLOTS:
    void slotReceiveImage(QImage);
    void slotReceiveNameAndSinger(QString,QString);


private:
        void slotShowOrHidedddd();

private:
    void initWidget();

private:
    Ui::MiniPlayLayout *ui;
    ClickableLabel *m_label1;
    ClickableLabel *m_label2;
    bool showorhide;
};

#endif // MINIPLAYLAYOUT_H
