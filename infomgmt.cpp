#include "infomgmt.h"
#include "ui_infomgmt.h"

infoMgmt::infoMgmt(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::infoMgmt)
{
    ui->setupUi(this);
}

infoMgmt::~infoMgmt()
{
    delete ui;
}

void infoMgmt::showChoiceDialog() {
    QMessageBox msgBox;
    msgBox.setWindowTitle("选择操作");
    msgBox.setText("请选择要执行的操作：");
    QString text;

    QPushButton *newAnnouncementButton = msgBox.addButton(tr("新建公告"), QMessageBox::ActionRole);
    QPushButton *manageAnnouncementButton = msgBox.addButton(tr("管理公告"), QMessageBox::ActionRole);
    QPushButton *cancelButton = msgBox.addButton(QMessageBox::Cancel);
    cancelButton->hide();
    msgBox.exec();

    if (msgBox.clickedButton() == newAnnouncementButton) {
        qDebug() << "用户选择了新建公告";
        // 执行新建公告的操作
        ui->btn_save->hide();
        ui->btn_ok->setEnabled(true);
        ui->lineEdit->clear();
        ui->textEdit->clear();

    } else if (msgBox.clickedButton() == manageAnnouncementButton) {
        qDebug() << "用户选择了管理公告";
        // 执行管理公告的操作
        ui->btn_save->show();

        bool ok;
        QStringList items;
        QString strSQL1;

        if(this->userIndex == 1)
        {
            strSQL1 = "select announcement_name from announcement;";
            ui->comboBox->setEnabled(true);
        }
        else if(this->userIndex == 2)
        {
            QString strSQL = "select managed_club_name from admin where username = '"+ this->userName  +"';";
            QSqlQuery infoQuery;
            infoQuery.exec(strSQL);
            infoQuery.next();

            QString club_name = infoQuery.value(0).toString();
            strSQL1 = "select announcement_name from announcement where publisher ='"+ club_name +"';";
            ui->comboBox->setEnabled(false);
        }

        QSqlQuery infoQuery;
        infoQuery.exec(strSQL1);

        while(infoQuery.next())
        {
            items << infoQuery.value(0).toString();
        }

        text = QInputDialog::getItem(nullptr,
                                     "选择公告",
                                     "请选择公告:",
                                     items,
                                     0, // 默认选择第一个项目
                                     false, // 不可编辑
                                     &ok);

        if (ok && !text.isEmpty()) {
            qDebug() << "用户输入的公告ID是：" << text;
            // 执行管理公告的操作，并使用 text 作为输入的公告ID
            editInfo(text);
        } else {
            qDebug() << "用户取消了输入";
        }
    } else {
        qDebug() << "用户取消了操作";
    }
}

void infoMgmt::fillComBox()
{
    QString strSQL = "select * from announcement;";
    QSqlQuery infoQuery;
    infoQuery.exec(strSQL);

    ui->comboBox->clear();
    while(infoQuery.next())
    {
        ui->comboBox->addItem(infoQuery.value(4).toString());
    }
}

void infoMgmt::editInfo(QString infoName)
{
    QString queryInfoID = "select * from announcement where announcement_name = '" + infoName + "';";
    QSqlQuery infoQuery;
    infoQuery.exec(queryInfoID);

    infoQuery.next();
    QString announcement_name = infoQuery.value(1).toString();
    QString announcement_content = infoQuery.value(2).toString();
    QString publisher = infoQuery.value(4).toString();

    qDebug() << announcement_name << announcement_content << publisher ;

    ui->lineEdit->setText(announcement_name);
    ui->textEdit->setText(announcement_content);
    ui->comboBox->setCurrentText(publisher);

    ui->btn_ok->setEnabled(false);
}

void infoMgmt::initWindow()
{
    fillComBox();

    //初始化界面
    qDebug() << "The userName is: " << this->userName ;
    QSqlQuery userQuery;
    userQuery.exec("select * from user_permissions;");

    while (userQuery.next())
    {
        this->userIndex = userQuery.value(2).toInt();
        this->userName = userQuery.value(1).toString();
    }
    qDebug() << "The userName is: " << this->userName << "userFlag : " << this->userIndex;

    showChoiceDialog();
}

void infoMgmt::closeEvent(QCloseEvent *)
{
    emit exitInfoMgmt();
}

void infoMgmt::on_btn_ok_clicked()
{
    //发布公告
    QString infoName = ui->lineEdit->text();
    QString infoText = ui->textEdit->toPlainText();
    QString infoCreate = ui->comboBox->currentText();

    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString formattedDateTime = currentDateTime.toString("yyyy-MM-dd HH:mm:ss");

    //保存按钮
    QSqlQuery query;
    query.exec("select * from announcement where announcement_name = '" + infoName + "';");
    if((this->userIndex == 1) || (!query.next() && (this->userIndex == 2)))
    {
        QString properties = "announcement_name, announcement_content, publish_date, publisher";
        QString values = "'" + infoName +"','" + infoText + "','" + formattedDateTime + "','" + infoCreate;
        QString sqlStr = "insert into announcement(" + properties + ") values(" +
                values + "');";
        qDebug() << sqlStr;
        query.prepare(sqlStr);
        query.exec();

        if (query.isActive())
        {
            QMessageBox::information(this, tr("提示"), tr("公告发布成功！！！"));
            this->close();
        }
    }
    this->close();
}

void infoMgmt::on_btn_cancel_clicked()
{
    //取消
    this->close();
}

void infoMgmt::on_btn_save_clicked()
{
    //保存
    QString infoName = ui->lineEdit->text();
    QString infoText = ui->textEdit->toPlainText();
    QString infoCreate = ui->comboBox->currentText();

    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString formattedDateTime = currentDateTime.toString("yyyy-MM-dd HH:mm:ss");

    // 保存按钮
    QSqlQuery query;
    query.exec("SELECT * FROM announcement WHERE announcement_name = '" + infoName + "';");

    // 检查用户权限和是否存在记录
    if ((this->userIndex == 1) || (!query.next() && (this->userIndex == 0)))
    {
        QString sqlStr;

        if (query.next()) {
            // 记录存在，执行更新操作
            sqlStr = "UPDATE announcement SET "
                     "announcement_content = :content, "
                     "publish_date = :date, "
                     "publisher = :publisher "
                     "WHERE announcement_name = :name;";
        } else {
            QMessageBox::warning(this, tr("错误"), tr("未定位到指定公告数据！！！"));
        }

        query.prepare(sqlStr);
        query.bindValue(":name", infoName);
        query.bindValue(":content", infoText);
        query.bindValue(":date", formattedDateTime);
        query.bindValue(":publisher", infoCreate);
        query.exec();

        if (query.isActive()) {
            QMessageBox::information(this, tr("提示"), tr("公告信息保存成功！！！"));
            this->close();
        } else {
            QMessageBox::warning(this, tr("错误"), tr("保存公告信息时出错"));
        }
    }
    this->close();
}
