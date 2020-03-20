#ifndef LOGINFORM_TEST_H
#define LOGINFORM_TEST_H

#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include "database.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;

class loginform_test :public QDialog
{
    Q_OBJECT
public:
    loginform_test(QDialog *parent = 0);
signals:
public slots:
    void login();
    void regis();
private:
    DataBase d;
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
};

#endif // LOGINFORM_TEST_H
