#include "actionmgmt.h"
#include "ui_actionmgmt.h"

actionMgmt::actionMgmt(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::actionMgmt)
{
    ui->setupUi(this);
}

actionMgmt::~actionMgmt()
{
    delete ui;
}

void actionMgmt::initWindow()
{
    ui->dateTimeEdit_stop->setStyleSheet("background-color: rgba(0, 0, 0, 0);");
    ui->dateTimeEdit_start->setStyleSheet("background-color: rgba(0, 0, 0, 0);");
    ui->dateTimeEdit_check->setStyleSheet("background-color: rgba(0, 0, 0, 0);");
    ui->dateTimeEdit_creat->setStyleSheet("background-color: rgba(0, 0, 0, 0);");
    ui->line_status->setEnabled(false);
    ui->line_num->setEnabled(false);
    ui->line_admin->setEnabled(false);

    QSqlQuery userQuery;
    userQuery.exec("select * from user_permissions;");
    while (userQuery.next())
    {
        this->userIndex = userQuery.value(2).toInt();
        this->currentUserName = userQuery.value(1).toString();
    }
    qDebug() << "The userName is: " << this->currentUserName << "userFlag : " << this->userIndex;
    showDiagInfo();
}

void actionMgmt::fillActionInfo(QString actionName)
{
    ui->comboBox->addItem("小型");
    ui->comboBox->addItem("中型");
    ui->comboBox->addItem("大型");

    QString queryInfoID = "select * from activityinfo where activity_name = '" + actionName + "';";
    QSqlQuery infoQuery;
    infoQuery.exec(queryInfoID);

    infoQuery.next();
    QString actNum = infoQuery.value(0).toString();
    QString actName  = infoQuery.value(1).toString();
    QString actAppDate = infoQuery.value(2).toString();
    QString actlocation = infoQuery.value(3).toString();
    QString actClubNum= infoQuery.value(13).toString();
    QString actApprovalDate = infoQuery.value(5).toString();
    QString actApprovalStatus = infoQuery.value(6).toString();
    QString actIntroduction = infoQuery.value(7).toString();
    QString actLeader = infoQuery.value(8).toString();
    QString actScale = infoQuery.value(9).toString();
    QString actBudget = infoQuery.value(10).toString();
    QDateTime startTime = infoQuery.value(11).toDateTime();
    QDateTime endTime = infoQuery.value(12).toDateTime();

    ui->line_id->setText(actNum);
    ui->line_Name->setText(actName);
    ui->line_pos->setText(actlocation);
    ui->line_money->setText(actBudget);
    ui->line_num->setText(actClubNum);
    ui->line_status->setText(actApprovalStatus);
    ui->line_admin->setText(actLeader);
    ui->comboBox->setCurrentText(actScale);

    ui->dateTimeEdit_check->setDate(QDate::fromString(actApprovalDate, "yyyy-MM-dd"));
    ui->dateTimeEdit_creat->setDate(QDate::fromString(actAppDate, "yyyy-MM-dd"));
    ui->dateTimeEdit_start->setDateTime(startTime);
    ui->dateTimeEdit_stop->setDateTime(endTime);
    ui->textEdit->setText(actIntroduction);
}

void actionMgmt::clearInfo()
{
    ui->pushButton->hide();
    ui->btn_del->hide();
    ui->btn_ok->show();
    ui->btn_clear->hide();

    if(this->userIndex == 2)
    {
        QString strSQL = "select managed_club_name from admin where username = '"+ this->currentUserName  +"';";
        QSqlQuery infoQuery;
        infoQuery.exec(strSQL);
        infoQuery.next();

        club_name = infoQuery.value(0).toString();
        ui->line_admin->setText(club_name);
    }
    else{
        ui->line_admin->setText("");
        ui->line_admin->setEnabled(true);
    }

    ui->line_id->setText("");
    ui->line_Name->setText("");
    ui->line_pos->setText("");
    ui->line_money->setText("");
    ui->line_num->setText("");
    ui->line_status->setText("");

    ui->comboBox->setCurrentText("");

    ui->dateTimeEdit_check->setDate(QDate::fromString("2024-01-01", "yyyy-MM-dd"));
    ui->dateTimeEdit_creat->setDate(QDate::fromString("2024-01-01", "yyyy-MM-dd"));
    ui->dateTimeEdit_start->setDateTime(QDateTime::fromString("2024-01-01 00:00:00", "yyyy-MM-dd hh:mm:ss"));
    ui->dateTimeEdit_stop->setDateTime(QDateTime::fromString("2024-01-01 00:00:00", "yyyy-MM-dd hh:mm:ss"));
    ui->textEdit->setText("");

}

void actionMgmt::showDiagInfo()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("选择操作");
    msgBox.setText("请选择要执行的操作：");

    QPushButton *newAnnouncementButton = msgBox.addButton(tr("新建活动"), QMessageBox::ActionRole);
    QPushButton *manageAnnouncementButton = msgBox.addButton(tr("管理活动"), QMessageBox::ActionRole);
    QPushButton *cancelButton = msgBox.addButton(QMessageBox::Cancel);
    cancelButton->hide();
    msgBox.exec();

    if (msgBox.clickedButton() == newAnnouncementButton) {
        qDebug() << "用户选择了新建活动";
        // 执行新建活动的操作
        clearInfo();
    } else if (msgBox.clickedButton() == manageAnnouncementButton) {
        qDebug() << "用户选择了管理活动";
        ui->btn_ok->hide();
        if(this->userIndex == 1)
        {
            ui->pushButton->show();
            ui->line_admin->setEnabled(true);
        }
        else
        {
            ui->pushButton->hide();
            ui->line_admin->setEnabled(false);
        }
        ui->btn_del->show();
        ui->btn_clear->show();

        // 执行管理活动的操作
        bool ok;
        QStringList items;
        QString strSQL1;

        if(this->userIndex == 1)
        {
            strSQL1 = "select * from activityinfo;";
        }
        else if(this->userIndex == 2)
        {
            QString strSQL = "select managed_club_name from admin where username = '"+ this->currentUserName  +"';";
            QSqlQuery infoQuery;
            infoQuery.exec(strSQL);
            infoQuery.next();

            club_name = infoQuery.value(0).toString();

            strSQL1 = "select * from activityinfo where organizer ='"+ club_name +"';";
        }

        QSqlQuery infoQuery;
        infoQuery.exec(strSQL1);

        ui->comboBox->clear();
        while(infoQuery.next())
        {
            items << infoQuery.value(1).toString();
        }

        text = QInputDialog::getItem(nullptr,
                                     "选择活动",
                                     "请选择活动:",
                                     items,
                                     0, // 默认选择第一个项目
                                     false, // 不可编辑
                                     &ok);

        if (ok && !text.isEmpty()) {
            qDebug() << "用户输入的活动名称是：" << text;
            // 执行管理活动的操作，并使用 text 作为输入的活动名称
            fillActionInfo(text);
        } else {
            qDebug() << "用户取消了输入";
        }
    } else {
        qDebug() << "用户取消了操作";
        clearInfo();
    }
}

void actionMgmt::on_btn_ok_clicked()
{
    //创建活动
    QString actName, actLocation, actAdmin, actScale, actNum, actComNum, actPrice, actText;
    QSqlQuery query;

    actNum = ui->line_id->text();
    actName = ui->line_Name->text();
    actAdmin = ui->line_admin->text();
    actLocation = ui->line_pos->text();
    actPrice = ui->line_money->text();
    actScale = ui->comboBox->currentText();
    actText = ui->textEdit->toPlainText();
    QString actCreatTime = ui->dateTimeEdit_creat->dateTime().toString("yyyy-MM-dd HH:mm:ss");
    QString actStatusTime = ui->dateTimeEdit_check->dateTime().toString("yyyy-MM-dd HH:mm:ss");
    QString actStopTime = ui->dateTimeEdit_stop->dateTime().toString("yyyy-MM-dd HH:mm:ss");
    QString actStartTime = ui->dateTimeEdit_start->dateTime().toString("yyyy-MM-dd HH:mm:ss");

    qDebug() << "actNum:" << actNum;
    qDebug() << "actName:" << actName;
    qDebug() << "actAdmin:" << actAdmin;
    qDebug() << "actLocation:" << actLocation;
    qDebug() << "actPrice:" << actPrice;
    qDebug() << "actScale:" << actScale;
    qDebug() << "actCreatTime:" << actCreatTime;
    qDebug() << "actStatusTime:" << actStatusTime;
    qDebug() << "actStopTime:" << actStopTime;
    qDebug() << "actStartTime:" << actStartTime;

    QString approval_status = "待审核";

    query.exec("select * from activityinfo where activity_id = '" + actNum + "'");
    if(!query.next())
    {
        //活动ID、活动名称、活动组织者、活动地点、活动经费、活动规模、活动时间（4个）
        QString properties = "activity_id, activity_name, organizer, location, budget, scale, application_date, approval_date, start_time, end_time, introduction";
        QString values = actNum + ",'" + actName + "','" + actAdmin + "','" + actLocation + "'," + actPrice + ",'" + actScale + "','" + actCreatTime + "','" +
                actStatusTime + "','" + actStopTime + "','" + actStartTime + "','" + actText +"'";
        QString sqlStr = "insert into activityinfo(" + properties + ") values(" +
                values + ");";
        qDebug() << sqlStr;
        query.prepare(sqlStr);
        query.exec();

        if (query.isActive())
        {
            QMessageBox::information(this, tr("提示"), tr("创建活动成功！！"));
            this->close();
        }
    }
    else
    {
        QMessageBox::warning(this, tr("警告"), tr("活动已经存在！！！"));
        return;
    }

    this->close();
}

void actionMgmt::on_btn_clear_clicked()
{
    //保存活动
    QString actName, actLocation, actAdmin, actScale, actNum, actPrice, actText;
    QSqlQuery query;

    actNum = ui->line_id->text();
    actName = ui->line_Name->text();
    actAdmin = ui->line_admin->text();
    actLocation = ui->line_pos->text();
    actPrice = ui->line_money->text();
    actScale = ui->comboBox->currentText();
    actText = ui->textEdit->toPlainText();
    QString actCreatTime = ui->dateTimeEdit_creat->dateTime().toString("yyyy-MM-dd HH:mm:ss");
    QString actStatusTime = ui->dateTimeEdit_check->dateTime().toString("yyyy-MM-dd HH:mm:ss");
    QString actStopTime = ui->dateTimeEdit_stop->dateTime().toString("yyyy-MM-dd HH:mm:ss");
    QString actStartTime = ui->dateTimeEdit_start->dateTime().toString("yyyy-MM-dd HH:mm:ss");

    qDebug() << "actNum:" << actNum;
    qDebug() << "actName:" << actName;
    qDebug() << "actAdmin:" << actAdmin;
    qDebug() << "actLocation:" << actLocation;
    qDebug() << "actPrice:" << actPrice;
    qDebug() << "actScale:" << actScale;
    qDebug() << "actCreatTime:" << actCreatTime;
    qDebug() << "actStatusTime:" << actStatusTime;
    qDebug() << "actStopTime:" << actStopTime;
    qDebug() << "actStartTime:" << actStartTime;
    qDebug() << "actText" << actText;

    QString approval_status = "待审核";

    query.exec("SELECT * FROM activityinfo WHERE activity_id = '" + actNum + "'");
    if (query.next())
    {
        // 记录存在，执行更新操作
        QString sqlStr = "UPDATE activityinfo SET "
                         "activity_name = :actName, "
                         "organizer = :actAdmin, "
                         "location = :actLocation, "
                         "budget = :actPrice, "
                         "scale = :actScale, "
                         "application_date = :actCreatTime, "
                         "approval_date = :actStatusTime, "
                         "start_time = :actStartTime, "
                         "end_time = :actStopTime, "
                         "approval_status = :approvalStatus, "
                         "introduction = :actText "
                         "WHERE activity_id = :actNum;";

        query.prepare(sqlStr);
        query.bindValue(":actName", actName);
        query.bindValue(":actAdmin", actAdmin);
        query.bindValue(":actLocation", actLocation);
        query.bindValue(":actPrice", actPrice);
        query.bindValue(":actScale", actScale);
        query.bindValue(":actCreatTime", actCreatTime);
        query.bindValue(":actStatusTime", actStatusTime);
        query.bindValue(":actStopTime", actStopTime);
        query.bindValue(":actStartTime", actStartTime);
        query.bindValue(":approvalStatus", approval_status);
        query.bindValue(":actText", actText);
        query.bindValue(":actNum", actNum);

        if (query.exec())
        {
            QMessageBox::information(this, tr("提示"), tr("活动信息更新成功！！"));
            this->close();
        }
        else
        {
            QMessageBox::warning(this, tr("错误"), tr("更新活动信息时出错: "));
        }
    }
    this->close();

}

void actionMgmt::on_btn_cancel_clicked()
{
    //取消
    this->close();
}

void actionMgmt::closeEvent(QCloseEvent *)
{
    emit exitActionMgmt();
}

void actionMgmt::on_pushButton_clicked()
{
    //批准
    QString actionId = ui->line_id->text();
    QString sqlStr = "UPDATE activityinfo SET approval_status = '已通过' where activity_id = '" + actionId + "';";

    qDebug() << sqlStr;
    QSqlQuery query(sqlStr);
    query.exec();

    if (query.isActive())
    {
        QMessageBox::information(this, tr("提示"), tr("批准活动成功！！"));
        this->close();
    }
}

void actionMgmt::on_btn_del_clicked()
{
    //撤销活动按钮
    QString actionId = ui->line_id->text();
    QString sqlStr = "delete from activityinfo where activity_id = '" + actionId + "';";

    qDebug() << sqlStr;
    QSqlQuery query(sqlStr);
    query.exec();

    if (query.isActive())
    {
        QMessageBox::information(this, tr("提示"), tr("撤销活动成功！！"));
        this->close();
    }
}
