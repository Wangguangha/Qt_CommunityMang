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

    UserLogin(QString username,QWidget *parent = nullptr);//���캯����Ĭ��ֵ��Ҫ���ұߣ�����ӵĲ�����Ҫ�������

    QSqlDatabase db;
    QString dataUrl;

    void initWindow();      //��ʼ������
    void connectDatabase(); //�������ݿ�

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
