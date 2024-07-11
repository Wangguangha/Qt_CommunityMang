#include "personalcenter.h"
#include "ui_personalcenter.h"

personalCenter::personalCenter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::personalCenter)
{
    ui->setupUi(this);
}

personalCenter::~personalCenter()
{
    delete ui;
}

void personalCenter::closeEvent(QCloseEvent *)
{
    emit exitPersonalCenter();
}

void personalCenter::initWindow()
{
    ui->line_clubname->setEnabled(false);
    ui->line_role->setEnabled(false);
    ui->lineEdit->setEnabled(false);
    ui->line_num->setEnabled(false);

    QSqlQuery userQuery;
    userQuery.exec("select * from user_permissions;");
    while (userQuery.next())
    {
        this->userIndex = userQuery.value(2).toInt();
        this->userName = userQuery.value(1).toString();
    }
    qDebug() << "The userName is: " << this->userName << "userFlag : " << this->userIndex;

    QSqlQuery infoQuery;
    QString sqlStr;

    if(this->userIndex == 1){
        sqlStr = "select * from Superadmin where username = '" + this->userName +"';";
        ui->btn_picture->hide();
    }else if(this->userIndex == 2){
        sqlStr = "select  name, student_number, contact, club_name, club_role, class, "
                 "department, age, gender, join_date, avatar_path from Students where student_number = '" + this->userName +"';";
        ui->btn_picture->show();
    }else if(this->userIndex == 3){
        sqlStr = "select  name, student_number, contact, club_name, club_role, class, department, age, gender, "
                 "join_date, avatar_path from Students where student_number = '"+ this->userName +"';";
        ui->btn_picture->show();
    }

    qDebug()<< sqlStr;

    infoQuery.exec(sqlStr);
    while (infoQuery.next())
    {
       if(this->userIndex != 1)
       {
           ui->line_name->setText(infoQuery.value(0).toString());
           ui->line_num->setText(infoQuery.value(1).toString());
           ui->line_tel->setText(infoQuery.value(2).toString());
           ui->line_clubname->setText(infoQuery.value(3).toString());
           ui->line_role->setText(infoQuery.value(4).toString());
           ui->line_class->setText(infoQuery.value(5).toString());
           ui->line_type->setText(infoQuery.value(6).toString());
           ui->spinbox->setValue(infoQuery.value(7).toInt());
           if(infoQuery.value(8).toString() == "男")
               ui->comboBox->setCurrentText("男");
           else
               ui->comboBox->setCurrentText("女");
           ui->lineEdit->setText(infoQuery.value(9).toString());

           QPixmap *pixmap = new QPixmap(infoQuery.value(10).toString());

           QSize labelSize = QSize(this->width()/4,this->height()/3);
           QPixmap scaledPixmap = pixmap->scaled(labelSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);

           ui->label_picture->setScaledContents(false); // 确保 setScaledContents 设置为 false
           ui->label_picture->setPixmap(scaledPixmap);  // 设置缩放后的 pixmap
           ui->line_clubname->show();
           ui->line_role->show();
           ui->line_class->show();
           ui->line_type->show();
           ui->label_2->show();
           ui->label_7->show();
           ui->label_8->show();
           ui->label_9->show();
           ui->label_10->show();
           ui->spinbox->show();
       }
       else
       {
           ui->line_name->setText(infoQuery.value(3).toString());
           ui->line_num->setText(infoQuery.value(1).toString());
           ui->line_tel->setText(infoQuery.value(5).toString());
           ui->line_clubname->hide();
           ui->line_role->hide();
           ui->line_class->hide();
           ui->line_type->hide();
           ui->label_2->hide();
           ui->label_7->hide();
           ui->label_8->hide();
           ui->label_9->hide();
           ui->label_10->hide();
           ui->spinbox->hide();
           if(infoQuery.value(4).toString() == "男")
               ui->comboBox->setCurrentText("男");
           else
               ui->comboBox->setCurrentText("女");
           ui->lineEdit->setText(infoQuery.value(7).toString());
       }
    }
}

void personalCenter::on_btn_picture_clicked()
{
    //修改头像
    fileName = QFileDialog::getOpenFileName(this, tr("选择一张图片"), "C:\\Users\\Administrator\\Pictures\\", tr("Image Files (*.png *.jpg)"));

    QPixmap *pixmap = new QPixmap(fileName);
    QSize labelSize = QSize(this->width()/4,this->height()/3);
    QPixmap scaledPixmap = pixmap->scaled(labelSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    ui->label_picture->setScaledContents(false); // 确保 setScaledContents 设置为 false
    ui->label_picture->setPixmap(scaledPixmap);  // 设置缩放后的 pixmap
}

void personalCenter::on_yes_btn_2_clicked()
{
    //确认按钮
    QSqlQuery query;

    // 读取控件内容到变量中
    QString lineName = ui->line_name->text();
    QString lineNum = ui->line_num->text();
    QString lineTel = ui->line_tel->text();
    QString lineClubName = ui->line_clubname->text();
    QString lineRole = ui->line_role->text();
    QString lineClass = ui->line_class->text();
    QString lineType = ui->line_type->text();
    int spinBoxValue = ui->spinbox->value();
    QString comboBoxText = ui->comboBox->currentText();
    QString lineEditText = ui->lineEdit->text();

    // 可以在其他地方使用这些变量的值，例如输出到调试控制台
    qDebug() << "lineNum:" << lineNum;
    qDebug() << "lineTel:" << lineTel;
    qDebug() << "lineClubName:" << lineClubName;
    qDebug() << "lineRole:" << lineRole;
    qDebug() << "lineClass:" << lineClass;
    qDebug() << "lineType:" << lineType;
    qDebug() << "spinBoxValue:" << spinBoxValue;
    qDebug() << "comboBoxText:" << comboBoxText;
    qDebug() << "lineEditText:" << lineEditText;


    QString condition = "student_number = '" + lineNum + "'";

    QString sqlStr = "UPDATE students SET "
        "name = '" + lineName + "', "
        "contact = '" + lineTel + "', "
        "club_name = '" + lineClubName + "', "
        "club_role = '" + lineRole + "', "
        "class = '" + lineClass + "', "
        "department = '" + lineType + "', "
        "age = " + QString::number(spinBoxValue) + ", "
        "gender = '" + comboBoxText + "', "
        "join_date = '" + lineEditText + "', "
        "avatar_path = '" + fileName + "' "
        "WHERE " + condition + ";";

    // 输出生成的 SQL 语句
    qDebug() << sqlStr;
    query.prepare(sqlStr);
    query.exec();

    this->close();
}

void personalCenter::on_no_btn_2_clicked()
{
    //取消
    this->close();
}
