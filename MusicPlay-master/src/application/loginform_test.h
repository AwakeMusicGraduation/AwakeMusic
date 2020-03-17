#ifndef LOGINFORM_TEST_H
#define LOGINFORM_TEST_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include "database.h"

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
    QLabel *pwdLbl;
    QLineEdit *userNameLEd;
    QLineEdit *pwdLEd;
    QPushButton *loginBtn;//登录
    QPushButton *reBtn;//注册
    QPushButton *exitBtn;//退出
};

#endif // LOGINFORM_TEST_H
