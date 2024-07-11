#ifndef USER_REGISTER_FORM_H
#define USER_REGISTER_FORM_H

#include "toolHead.h"

namespace Ui {
class UserRegisterForm;
}

class UserRegisterForm : public QWidget
{
    Q_OBJECT

public:
    explicit UserRegisterForm(QWidget *parent = 0);
    ~UserRegisterForm();

    QSqlDatabase db;

    void initForm();        //初始化界面

private slots:
    void on_yes_btn_clicked();
    void on_no_btn_clicked();

private:
    Ui::UserRegisterForm *ui;
};

#endif // USER_REGISTER_FORM_H
