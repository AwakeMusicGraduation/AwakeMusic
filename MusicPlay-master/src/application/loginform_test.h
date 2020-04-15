#ifndef LOGINFORM_TEST_H
#define LOGINFORM_TEST_H

#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>


class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class Client;

class loginform_test :public QDialog
{
    Q_OBJECT
public:
    loginform_test(QDialog *parent = 0);
signals:
public slots:
    void login();
    void slotAcceptUserMessage(std::vector<QString> userMessage);//接收传回的登录信息
    void regis();
    void slotAcceptRegisterMessage(QString message);
Q_SIGNALS:
    void signalLoginClicked(QString user,QString name,QString password);//向服务端传输用户名和密码
    void signalUpdateList(std::vector<QString> userMessage);//更新登录传回的用户列表
    void signalUpdateName(QString name);//显示登录进去的用户
    void signalRegisterClicked(QString user,QString name,QString password);//向服务端注册用户名和密码
private:
    QLabel *userNameLbl;
    //QLabel *pwdLbl;
    QLineEdit *userNameLEd;
    QLineEdit *pwdLEd;
    QPushButton *loginBtn;//登录
    QPushButton *reBtn;//注册
    QPushButton *exitBtn;//退出
    QVBoxLayout *m_layout;//垂直布局
    QHBoxLayout *m_layout1;//水平布局
    QGridLayout *m_grid;
    Client *m_client;
    QString m_name;
};

#endif // LOGINFORM_TEST_H
