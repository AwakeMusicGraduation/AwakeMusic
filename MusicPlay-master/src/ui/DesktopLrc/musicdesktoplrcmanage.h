#ifndef MUSICDESKTOPLRCMANAGE_H
#define MUSICDESKTOPLRCMANAGE_H

#include <QObject>
#include <QWidget>
#include <QTextEdit>
class QLabel;
class QVBoxLayout;
class LyrcToolBarWidget;
class QLinearGradient;

class MusicDesktopLrcManage : public QWidget
{
    Q_OBJECT
public:
    explicit MusicDesktopLrcManage(QWidget *parent = 0);
    ~MusicDesktopLrcManage();

    void startLrcMask(qint64 intervaltime);
    void stopLrcMask();
private:
    void initForm();
    void initWidget();
    void initConnect();

Q_SIGNALS:

private Q_SLOTS:
    void slotLock();
    void slotClose();
    void slotAnalyseLrc(QString name);
protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    //    virtual void contextMenuEvent(QContextMenuEvent *event);
    virtual void enterEvent(QEvent *event);
    virtual void leaveEvent(QEvent *event);
    virtual void closeEvent(QCloseEvent *event);
    void analysisLyrc(const QString &name);         //解析歌词 

public Q_SLOTS:
    void slotReceiveMusicInfo(QString name); //接收歌曲信息，准备解析歌词
    void slotReceiveCurrentPlayTime(qint64);        //接收当前播放的时间

private:
    LyrcToolBarWidget *m_toolBarWidget;
    QLabel *m_labelLrc;
    QVBoxLayout *m_mainLayout;
    QPoint m_offset, m_geometry;

    bool m_widgetLock;
    QTextEdit *m_lrcText;

    qreal length;
    qreal lrcWidth;
};

#endif // MUSICDESKTOPLRCMANAGE_H
