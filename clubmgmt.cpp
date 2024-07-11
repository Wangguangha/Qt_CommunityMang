#include "clubmgmt.h"
#include "ui_clubmgmt.h"

clubMgmt::clubMgmt(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::clubMgmt)
{
    ui->setupUi(this);

    ui->spinBox->hide();
    ui->label_6->hide();
}

clubMgmt::~clubMgmt()
{
    delete ui;
}

void clubMgmt::closeEvent(QCloseEvent *)
{
    emit exitClubMgmt();
}

void clubMgmt::initWindow()
{
    //初始化界面
    QSqlQuery userQuery;
    userQuery.exec("select * from user_permissions;");
    while (userQuery.next())
    {
        this->userIndex = userQuery.value(2).toInt();
        this->userName = userQuery.value(1).toString();
    }

    if(this->userIndex == 2)
    {
        QString strSQL = "select managed_club_name from admin where username = '"+ this->userName  +"';";
        QSqlQuery infoQuery;
        infoQuery.exec(strSQL);
        infoQuery.next();

        QString club_name = infoQuery.value(0).toString();
        fillClubMgmt(club_name);
    }
    else if(this->userIndex == 1)
    {
        showChoiceDialog();
    }else
        ui->btn_join->show();

    ui->btn_join->hide();
}

void clubMgmt::fillCombox()
{
    QString strSQL = "select * from clubinfo;";
    QSqlQuery infoQuery;
    infoQuery.exec(strSQL);

    ui->comboBox->clear();

    QSet<QString> existingItems; // 使用 QSet 来存储已经添加的字符串，确保唯一性
    while(infoQuery.next())
    {
        QString item = infoQuery.value(2).toString();
        if (!existingItems.contains(item)) // 检查 QSet 中是否已经包含该字符串
        {
            ui->comboBox->addItem(item);
            existingItems.insert(item); // 将新添加的字符串插入 QSet
        }
    }
}

void clubMgmt::fillClubMgmt(QString clubName)
{
    //初始化界面
    QSqlQuery userQuery;
    userQuery.exec("select * from user_permissions;");
    while (userQuery.next())
    {
        this->userIndex = userQuery.value(2).toInt();
        this->userName = userQuery.value(1).toString();
    }
    ui->btn_join->hide();

    QString strSQL = "select managed_club_name from admin where username = '"+ this->userName  +"';";
    QSqlQuery infoQuery;
    infoQuery.exec(strSQL);
    infoQuery.next();

    QString club_name = infoQuery.value(0).toString();

    if(((club_name == clubName) && (this->userIndex == 2)) || (this->userIndex == 1)){
        ui->btn_join->hide();
        ui->spinBox->setEnabled(true);
        ui->lineEdit->setEnabled(true);
        ui->comboBox->setEnabled(true);
        ui->lineEdit_5->setEnabled(true);
        ui->lineEdit_4->setEnabled(true);
        ui->textEdit->setEnabled(true);
        ui->btn_save->show();
        if(this->userIndex == 1)
            ui->btn_create->show();
        else
            ui->btn_create->hide();
        ui->btn_changePic->show();
    }
    else
    {
        if(this->userIndex == 3)
            ui->btn_join->show();
        ui->spinBox->setEnabled(false);
        ui->lineEdit->setEnabled(false);
        ui->comboBox->setEnabled(false);
        ui->lineEdit_5->setEnabled(false);
        ui->lineEdit_4->setEnabled(false);
        ui->textEdit->setEnabled(false);
        ui->btn_save->hide();
        ui->btn_create->hide();
        ui->btn_changePic->hide();
    }

    this->lunboName = clubName;
    QString queryInfoID = "select * from clubinfo where club_name = '" + clubName + "';";
    infoQuery.exec(queryInfoID);

    infoQuery.next();
    QString club_id  = infoQuery.value(0).toString();
    club_name = infoQuery.value(1).toString();
    QString club_type = infoQuery.value(2).toString();
    QString club_leader = infoQuery.value(4).toString();
    QString club_tel = infoQuery.value(5).toString();
    QString club_intro = infoQuery.value(6).toString();
    QString club_pic = infoQuery.value(8).toString();

    qDebug() << "Club ID:" << club_id;
    qDebug() << "Club Name:" << club_name;
    qDebug() << "Club Type:" << club_type;
    qDebug() << "Club Leader:" << club_leader;
    qDebug() << "Club Tel:" << club_tel;
    qDebug() << "Club Intro:" << club_intro;
    qDebug() << "Club Pic:" << club_pic;

    //ui->spinBox->setValue(club_id.toInt());
    ui->lineEdit->setText(clubName);
    ui->comboBox->setCurrentText(club_type);
    ui->lineEdit_5->setText(club_leader);
    ui->lineEdit_4->setText(club_tel);
    ui->textEdit->setText(club_intro);

    qDebug() << club_pic;
    QPixmap *pixmap = new QPixmap(club_pic);
    QSize labelSize = QSize(this->width()/4,this->height()/3);
    QPixmap scaledPixmap = pixmap->scaled(labelSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    ui->label_picture->setScaledContents(false); // 确保 setScaledContents 设置为 false
    ui->label_picture->setPixmap(scaledPixmap);  // 设置缩放后的 pixmap
}

void clubMgmt::showChoiceDialog()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("选择操作");
    msgBox.setText("请选择要执行的操作：");
    QString text;

    QPushButton *newAnnouncementButton = msgBox.addButton(tr("新建社团"), QMessageBox::ActionRole);
    QPushButton *manageAnnouncementButton = msgBox.addButton(tr("管理社团"), QMessageBox::ActionRole);
    QPushButton *cancelButton = msgBox.addButton(QMessageBox::Cancel);
    cancelButton->hide();
    msgBox.exec();

    if (msgBox.clickedButton() == newAnnouncementButton) {
        qDebug() << "用户选择了新建社团";
        // 执行新建社团的操作
        ui->spinBox->setValue(0);
        ui->lineEdit->setText("");
        ui->comboBox->setCurrentText("");
        ui->lineEdit_5->setText("");
        ui->lineEdit_4->setText("");
        ui->textEdit->setText("");
        ui->label_picture->clear();

        ui->btn_create->show();
        ui->btn_save->hide();
    }else if (msgBox.clickedButton() == manageAnnouncementButton) {
        qDebug() << "用户选择了管理社团";
        // 执行管理社团的操作
        ui->btn_save->show();
        ui->btn_create->hide();

        bool ok;
        QStringList items;

        QString strSQL = "select * from clubinfo;";
        QSqlQuery infoQuery;
        infoQuery.exec(strSQL);

        while(infoQuery.next())
        {
            items << infoQuery.value(1).toString();
        }

        QString text = QInputDialog::getItem(nullptr,
                                             "输入社团名",
                                             "请选择社团名:",
                                             items,
                                             0, // 默认选择第一个项目
                                             false, // 不可编辑
                                             &ok);
        if (ok && !text.isEmpty()) {
            qDebug() << "用户输入的社团名称是：" << text;
            // 执行管理公告的操作，并使用 text 作为输入的社团名称
            fillClubMgmt(text);
        } else {
            qDebug() << "用户取消了输入";
        }
    } else {
        qDebug() << "用户取消了操作";
        ui->spinBox->setValue(0);
        ui->lineEdit->setText("");
        ui->comboBox->setCurrentText("");
        ui->lineEdit_5->setText("");
        ui->lineEdit_4->setText("");
        ui->textEdit->setText("");
        ui->label_picture->clear();

        ui->btn_create->show();
        ui->btn_save->hide();
    }

}

void clubMgmt::on_btn_changePic_clicked()
{
    //修改头像
    fileName = QFileDialog::getOpenFileName(this, tr("选择一张图片"), "C:\\Users\\Administrator\\Pictures\\", tr("Image Files (*.png *.jpg)"));

    QPixmap *pixmap = new QPixmap(fileName);
    QSize labelSize = ui->label_picture->size();
    QPixmap scaledPixmap = pixmap->scaled(labelSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    ui->label_picture->setScaledContents(false); // 确保 setScaledContents 设置为 false
    ui->label_picture->setPixmap(scaledPixmap);  // 设置缩放后的 pixmap
}

void clubMgmt::on_btn_save_clicked()
{
    QString actName = ui->lineEdit->text();
    QString actTel = ui->lineEdit_4->text();
    QString actTran = ui->textEdit->toPlainText();
    QString actType = ui->comboBox->currentText();
    QString actLeader = ui->lineEdit_5->text();

    QString sqlStr = "UPDATE clubinfo SET ";

    //保存按钮
    QSqlQuery query;
    query.exec("select * from clubinfo where leader = '" + this->userName + "'");
    if((this->userIndex == 1) || (!query.next() && (this->userIndex == 0)))
    {
        if(actName.length() > 0)
        {
            sqlStr += "club_name = '" + actName + "',";
        }

        if(actTel.length() > 0)
        {
            sqlStr += "contact = '" + actTel + "',";
        }

        if(actTran.length() > 0)
        {
            sqlStr += "introduction = '" + actTran + "',";
        }

        if(actType.length() > 0)
        {
            sqlStr += "category = '" + actType + "',";
        }

        if(fileName.length() > 0)
        {
            sqlStr += "picture = '" + fileName + "',";
        }

        if(actLeader.length() > 0)
        {
            sqlStr += "leader = '" + actLeader + "',";
        }

        sqlStr.chop(1);
        sqlStr += " WHERE club_id = " + ui->spinBox->text() + ";";
        qDebug() << sqlStr;
        query.prepare(sqlStr);
        query.exec();

        if (query.isActive())
        {
            QMessageBox::information(this, tr("提示"), tr("保存成功"));
        }
    }
}

void clubMgmt::on_btn_create_clicked()
{
    //创建社团
    QString actName = ui->lineEdit->text();
    QString actTel = ui->lineEdit_4->text();
    QString actTran = ui->textEdit->toPlainText();
    QString actType = ui->comboBox->currentText();
    QString actLeader = ui->lineEdit_5->text();

    //保存按钮
    QSqlQuery query;
    query.exec("select * from clubinfo where leader = '" + this->userName + "'");

    if(this->userIndex == 1)
    {
        if(!query.next())
        {
            //do nothing
        }else
            QMessageBox::warning(this, tr("警告"), tr("社团已经存在！"));

        QString properties = "club_name, leader, contact, introduction, category, picture";
        QString values = "'" +actName + "','" + actLeader + "','" + actTel + "','" + actTran + "','" + actType  + "','" + fileName;
        QString sqlStr = "insert into clubinfo(" + properties + ") values(" +
                values + "');";
        qDebug() << sqlStr;
        query.prepare(sqlStr);
        query.exec();

        if (query.isActive())
        {
            QMessageBox::information(this, tr("提示"), tr("社团创建成功！！！"));
            this->close();
        }else
        {
            QMessageBox::information(this, tr("提示"), tr("社团创建失败，请检查社团ID是否已经存在！！！"));
        }
    }
}

void clubMgmt::on_btn_join_clicked()
{
    //申请加入社团
    QString properties = "applicant_name,club_name";
    QString values = "'" + this->userName + "','" + this->lunboName;
    QString sqlStr = "insert into apply_join(" + properties + ") values(" +
            values + "');";

    QSqlQuery query;
    query.prepare(sqlStr);
    query.exec();

    if (query.isActive())
    {
        QMessageBox::information(this, tr("提示"), tr("申请加入社团成功！！！"));
        this->close();
    }
}
