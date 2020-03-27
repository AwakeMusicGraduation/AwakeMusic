#ifndef TITLEWIDGET_H
#define TITLEWIDGET_H

#include <QWidget>
class QPushButton;
class QLabel;
class QHBoxLayout;
class SearchLineEdit;

class TitleWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TitleWidget(QWidget *parent = 0);
    ~TitleWidget();
    
    //自定义信号
Q_SIGNALS:
    void signalLogin();
    void signalSkin();
    void signalMin();
    void signalClose();
    void signalSearchContent(const QString &test);
    void signalSearchClicked();
public Q_SLOTS:
    void slotUpdateName(QString name);//更新用户名
private Q_SLOTS:


private:
    void initForm();                    //样式初始化
    void initWidget();                  //界面初始化
    void initLayout();                  //布局初始化
    void initConnect();                 //信号和槽初始化

private:
    QLabel *m_labelIcon;                //程序图标
    QLabel *m_labelTitle;               //程序标题
    SearchLineEdit *m_search;           //搜索歌曲框
    QPushButton *m_pbnLogin;            //登录
    QPushButton *m_pbnSkin;             //换肤按钮
    QPushButton *m_pbnMin;              //最小化
    QPushButton *m_pbnClose;            //关闭
    QHBoxLayout *m_mainLayout;          //主布局
    
};

#endif // TITLEWIDGET_H
