#ifndef MUSICLYRCWIDGET_H
#define MUSICLYRCWIDGET_H

#include <QFrame>
#include <QPushButton>
class QLabel;
class QTextStream;
class QTextEdit;

class MusicLyrcWidget : public QFrame
{
    Q_OBJECT
public:
    explicit MusicLyrcWidget(QWidget *parent);
    ~MusicLyrcWidget();
protected:
    virtual void mouseMoveEvent(QMouseEvent *);
private:
    void initForm();
    void initConnect();
    void analysisLyrc(const QString &name);         //解析歌词

Q_SIGNALS:
    void signalHideLrc();

public Q_SLOTS:
    void slotReceiveMusicInfo(const QString &name); //接收歌曲信息，准备解析歌词
    void slotReceiveCurrentPlayTime(qint64);        //接收当前播放的时间
    void slotAnalyseMedia(QString name);
private:
    QLabel *m_labelLyrc;
    QTextEdit *m_lrcText;
    QTextEdit *m_lrcText1;
    QPushButton *m_hideLrc;
};

#endif // MUSICLYRCWIDGET_H
