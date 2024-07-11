#ifndef USER_LOGIN_H
#define USER_LOGIN_H

#include "toolHead.h"

#include "user_register.h"
#include "community.h"

namespace Ui {
class UserLogin;
}


class UserLogin : public QDialog
{
    Q_OBJECT

public:
    explicit UserLogin(QWidget *parent = 0);
    ~UserLogin();

    UserLogin(QString username,QWidget *parent = nullptr);//构造函数有默认值的要放右边，新添加的参数需要放在左边

    QSqlDatabase db;
    QString dataUrl;

    void initWindow();      //初始化窗口
    void connectDatabase(); //连接数据库

private slots:
    void on_login_btn_clicked();
    void on_reg_btn_clicked();

private:
    Ui::UserLogin *ui;
    int admin_counter;
    int reader_counter;
    int counter;
};

#endif // USER_LOGIN_H
