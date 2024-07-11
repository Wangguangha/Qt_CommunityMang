#include "user_register.h"
#include "ui_user_register.h"
#include "user_login.h"

#include <QMessageBox>
#include <QString>
#include <QSqlQuery>


UserRegisterForm::UserRegisterForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserRegisterForm)
{
    ui->setupUi(this);
    this->setWindowTitle("用户注册");
    initForm();
}


UserRegisterForm::~UserRegisterForm()
{
    delete ui;
}

void UserRegisterForm::initForm()
{
    ui->rpwd_le->setEchoMode(QLineEdit::Password);//密文输入
    ui->rpwd_confim_le->setEchoMode(QLineEdit::Password);//密文输入

    ui->register_lab->setStyleSheet("font: 25 14pt '微软雅黑 Light';" //字体
                            "color: rgb(31,31,31);"		//字体颜色
                            );

    this->setObjectName("wang");
    this->setStyleSheet("#wang{background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(251,102,102, 200), stop:1 rgba(20,196,188, 210));}");

    ui->yes_btn->setStyleSheet("QPushButton{font: 25 14pt '微软雅黑 Light';color: rgb(255,255,255);background-color: rgb(20,196,188);"
                                    "border: none;border-radius:15px;}"
                                    "QPushButton:hover{background-color: rgb(22,218,208);}"//hover
                                    "QPushButton:pressed{background-color: rgb(17,171,164);}");//pressed

    ui->no_btn->setStyleSheet("QPushButton{font: 25 14pt '微软雅黑 Light';color: rgb(255,255,255);background-color: rgb(20,196,188);"
                                    "border: none;border-radius:15px;}"
                                    "QPushButton:hover{background-color: rgb(22,218,208);}"//hover
                                    "QPushButton:pressed{background-color: rgb(17,171,164);}");//pressed

    ui->label->setStyleSheet("font: 25 14pt '微软雅黑 Light';" //字体
                             "color: rgb(31,31,31);"		//字体颜色
                             "padding-left:20px;"       //内边距-字体缩进
                             );

    ui->rno_le->setStyleSheet("font: 25 14pt '微软雅黑 Light';" //字体
                                    "color: rgb(31,31,31);"		//字体颜色
                                    "padding-left:20px;"       //内边距-字体缩进
                                    "background-color: rgb(255, 255, 255);" //背景颜色
                                    "border:2px solid rgb(20,196,188);border-radius:15px;");//边框粗细-颜色-圆角设置

    ui->rpwd_le->setStyleSheet("font: 25 14pt '微软雅黑 Light';" //字体
                                    "color: rgb(31,31,31);"		//字体颜色
                                    "padding-left:20px;"       //内边距-字体缩进
                                    "background-color: rgb(255, 255, 255);" //背景颜色
                                    "border:2px solid rgb(20,196,188);border-radius:15px;");//边框粗细-颜色-圆角设置

    ui->rname_le->setStyleSheet("font: 25 14pt '微软雅黑 Light';" //字体
                                    "color: rgb(31,31,31);"		//字体颜色
                                    "padding-left:20px;"       //内边距-字体缩进
                                    "background-color: rgb(255, 255, 255);" //背景颜色
                                    "border:2px solid rgb(20,196,188);border-radius:15px;");//边框粗细-颜色-圆角设置

    ui->rtel_le->setStyleSheet("font: 25 14pt '微软雅黑 Light';" //字体
                                    "color: rgb(31,31,31);"		//字体颜色
                                    "padding-left:20px;"       //内边距-字体缩进
                                    "background-color: rgb(255, 255, 255);" //背景颜色
                                    "border:2px solid rgb(20,196,188);border-radius:15px;");//边框粗细-颜色-圆角设置

    ui->rpwd_confim_le->setStyleSheet("font: 25 14pt '微软雅黑 Light';" //字体
                                    "color: rgb(31,31,31);"		//字体颜色
                                    "padding-left:20px;"       //内边距-字体缩进
                                    "background-color: rgb(255, 255, 255);" //背景颜色
                                    "border:2px solid rgb(20,196,188);border-radius:15px;");//边框粗细-颜色-圆角设置

    ui->rsex_cmx->setStyleSheet("font: 25 14pt '微软雅黑 Light';" //字体
                                    "color: rgb(31,31,31);"		//字体颜色
                                    "padding-left:20px;"       //内边距-字体缩进
                                    "background-color: rgb(255, 255, 255);" //背景颜色
                                    "border:2px solid rgb(20,196,188);border-radius:15px;");//边框粗细-颜色-圆角设置

    ui->rclass_le->setStyleSheet("font: 25 14pt '微软雅黑 Light';" //字体
                                 "color: rgb(31,31,31);"		//字体颜色
                                 "padding-left:20px;"       //内边距-字体缩进
                                 "background-color: rgb(255, 255, 255);" //背景颜色
                                 "border:2px solid rgb(20,196,188);border-radius:15px;");//边框粗细-颜色-圆角设置

    ui->spinBox->setStyleSheet("font: 25 14pt '微软雅黑 Light';" //字体
                                    "color: rgb(31,31,31);"		//字体颜色
                                    "padding-left:20px;"       //内边距-字体缩进
                                    "background-color: rgb(255, 255, 255);" //背景颜色
                                    "border:2px solid rgb(20,196,188);border-radius:15px;");//边框粗细-颜色-圆角设置

    this->resize(800, 600);
}

void UserRegisterForm::on_yes_btn_clicked()
{
    QString reader_name;
    QString reader_id;
    QString reader_pwd;
    QString reader_pwd_confim;
    QString reader_tel;
    QString reader_sex;
    QString properties;
    QString ageStr;
    QString values;

    QSqlQuery query;

    if (!ui->rname_le->text().trimmed().isEmpty())
        reader_name = ui->rname_le->text().trimmed();
    else
    {
        QMessageBox::warning(this, tr("警告"), tr("用户名不能为空！"));
        return ;
    }

    if (!ui->rno_le->text().trimmed().isEmpty())
        reader_id = ui->rno_le->text().trimmed();
    else
    {
        QMessageBox::warning(this, tr("警告"), tr("账号不能为空！"));
        return ;
    }

    if (!ui->rpwd_le->text().trimmed().isEmpty())
        reader_pwd = ui->rpwd_le->text().trimmed();
    else
    {
        QMessageBox::warning(this, tr("警告"), tr("密码不能为空！"));
        return ;
    }

    if (!ui->rpwd_confim_le->text().trimmed().isEmpty())
        reader_pwd_confim = ui->rpwd_confim_le->text().trimmed();
    else
    {
        QMessageBox::warning(this, tr("警告"), tr("确认密码不能为空！"));
        return ;
    }

    reader_tel = ui->rtel_le->text().trimmed();
    reader_sex = ui->rsex_cmx->currentText().trimmed();
    ageStr = ui->spinBox->text();

    QString sexFlag = 0;
    if(reader_sex == "男")
        sexFlag = "1";
    else
        sexFlag = "0";

    if (reader_pwd.compare(reader_pwd_confim) != 0)
    {
        QMessageBox::warning(this, tr("警告"), tr("确认密码与密码不同！"));
        return ;
    }

    query.exec("select * from students where student_number = '" + reader_id + "'");
    if(!query.next())
    {
        properties = "student_number, name, password, contact, gender, age";
        values = reader_id + ",'" + reader_name + "','" + reader_pwd + "','" + reader_tel + "'," + sexFlag + "," + ageStr;
        QString sqlStr = "insert into students(" + properties + ") values(" +
                values + ");";
        qDebug() << sqlStr;
        query.prepare(sqlStr);
        query.exec();

        if (query.isActive())
        {
            QMessageBox::information(this, tr("提示"), tr("注册成功"));
            this->close();
        }
    }
    else
        QMessageBox::warning(this, tr("警告"), tr("用户名已经存在！"));

    UserLogin *userLogin = new UserLogin();
    userLogin->show();
    this->close();
}


void UserRegisterForm::on_no_btn_clicked()
{
    this->close();
}
