#include "user_login.h"
#include "ui_user_login.h"

UserLogin::UserLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserLogin)
{
    ui->setupUi(this);
    initWindow();
}


UserLogin::~UserLogin()
{
    delete ui;
}

UserLogin::UserLogin(QString username, QWidget *parent )
    :QDialog(parent)
    ,ui(new Ui::UserLogin)

{
    ui->setupUi(this);
    this->dataUrl = username;
    this->initWindow();
}

void UserLogin::initWindow()
{
    admin_counter = 0;
    reader_counter = 0;
    counter = 0;

    ui->pwd_le->setEchoMode(QLineEdit::Password);//密文输入

    ui->label->setStyleSheet("font: 25 14pt '微软雅黑 Light';" //字体
                            "color: rgb(31,31,31);"		//字体颜色
                            );

    this->setObjectName("wang");
    this->setStyleSheet("#wang{background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(251,102,102, 200), stop:1 rgba(20,196,188, 210));}");

    ui->login_btn->setStyleSheet("QPushButton{font: 25 14pt '微软雅黑 Light';color: rgb(255,255,255);background-color: rgb(20,196,188);"
                                    "border: none;border-radius:15px;}"
                                    "QPushButton:hover{background-color: rgb(22,218,208);}"//hover
                                    "QPushButton:pressed{background-color: rgb(17,171,164);}");//pressed
    ui->reg_btn->setStyleSheet("QPushButton{font: 25 14pt '微软雅黑 Light';color: rgb(255,255,255);background-color: rgb(20,196,188);"
                                    "border: none;border-radius:15px;}"
                                    "QPushButton:hover{background-color: rgb(22,218,208);}"//hover
                                    "QPushButton:pressed{background-color: rgb(17,171,164);}");//pressed
    ui->acnt_le->setStyleSheet("font: 25 14pt '微软雅黑 Light';" //字体
                                    "color: rgb(31,31,31);"		//字体颜色
                                    "padding-left:20px;"       //内边距-字体缩进
                                    "background-color: rgb(255, 255, 255);" //背景颜色
                                    "border:2px solid rgb(20,196,188);border-radius:15px;");//边框粗细-颜色-圆角设置

    ui->pwd_le->setStyleSheet("font: 25 14pt '微软雅黑 Light';" //字体
                                    "color: rgb(31,31,31);"		//字体颜色
                                    "padding-left:20px;"       //内边距-字体缩进
                                    "background-color: rgb(255, 255, 255);" //背景颜色
                                    "border:2px solid rgb(20,196,188);border-radius:15px;");//边框粗细-颜色-圆角设置

    this->setWindowTitle("登录界面");
    this->resize(QSize(800, 600));

    connectDatabase();
}

void UserLogin::connectDatabase()
{
    if(QSqlDatabase::contains("qt_sql_default_connection"))
    {
        db = QSqlDatabase::database("qt_sql_default_connection");
        return;
    }else
      db = QSqlDatabase::addDatabase("QMYSQL");

    db.setHostName(this->dataUrl);
    db.setDatabaseName("communitymanagement");
    db.setUserName("root");
    db.setPassword("123456");

    if (!db.open())
    {
        QMessageBox::warning(this, tr("连接mysql数据库失败"), tr("请确保您已安装mysql5.x!"));
    }
}

void UserLogin::on_login_btn_clicked()
{
    bool flag = false;
    QString user_account;
    QString user_pwd;

    user_account = ui->acnt_le->text();
    user_pwd  = ui->pwd_le->text();

    QSqlQuery query;
    QString userType = "";

    QString username, passwd;

    for (int userIndex = 0; userIndex < 3; userIndex++) {

        if(userIndex == 0)
            userType = "select * from SuperAdmin";
        else if(userIndex == 1)
            userType = "select * from Admin";
        else if(userIndex == 2)
            userType = "select * from Students";

        query.exec(userType);
        while (query.next())
        {
            qDebug() <<query.value(1).toString() << " " << query.value(2).toString() << endl;


            if(userIndex == 0){
                username = query.value(1).toString();
                passwd = query.value(2).toString();
            }
            else if (userIndex == 1) {
                username = query.value(1).toString();
                passwd = query.value(2).toString();
            }else if(userIndex == 2)
            {
                username = query.value(2).toString();
                passwd = query.value(10).toString();
            }

            if ((username == user_account) && (passwd == user_pwd))
            {
                flag = true;
                QSqlQuery userQuery;
                userQuery.exec("DELETE FROM user_permissions;");
                QString writeUserName = "INSERT INTO user_permissions (username, permissions) VALUES ('"+
                        user_account + "', " + QString::number(userIndex + 1) +");";
                qDebug() << writeUserName;
                userQuery.exec(writeUserName);


                Community *community = new Community(user_account, nullptr);    //主窗体
                community->show();
                community->move((QApplication::desktop()->width() -
                             community->width()) / 2,
                            (QApplication::desktop()->height() -
                             community->height()) / 2);

                this->hide();
                reader_counter++;

                break;
            }
        }
        if(reader_counter > 0)
            break;
    }

    if (!flag)
        QMessageBox::warning(this, tr("警告"), tr("用户名或密码错误!"));
}

void UserLogin::on_reg_btn_clicked()
{
    UserRegisterForm *user_register = new UserRegisterForm();
    user_register->show();
    user_register->move((QApplication::desktop()->width() -
                         user_register->width()) / 2,
                        (QApplication::desktop()->height() -
                         user_register->height()) / 2);
    this->hide();
}
