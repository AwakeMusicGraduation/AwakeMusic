#ifndef LYRCTOOLBARWIDGET_H
#define LYRCTOOLBARWIDGET_H

#include <QWidget>

class LyrcPushButton;
class QHBoxLayout;

class LyrcToolBarWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LyrcToolBarWidget(QWidget *parent = 0);
    ~LyrcToolBarWidget();
Q_SIGNALS:
    void signalLock();
    void signalClose();
private Q_SLOTS:
private:
    void initForm();
    void initWidget();
    void initLayout();
    void initConnect();

private:
    LyrcPushButton *m_pbnMainMusic;
    LyrcPushButton *m_pbnPreviousMusic;
    LyrcPushButton *m_pbnNextMusic;
    LyrcPushButton *m_pbnPlayMusic;
    LyrcPushButton *m_pbnSetting;
    LyrcPushButton *m_pbnLock;
    LyrcPushButton *m_pbnClose;

    QHBoxLayout *m_mainLayout;
};

#endif // LYRCTOOLBARWIDGET_H
