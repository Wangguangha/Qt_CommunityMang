#include "infodispaly.h"
#include "ui_infodispaly.h"

infoDispaly::infoDispaly(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::infoDispaly)
{
    ui->setupUi(this);

    ui->widgetShow->addImage(QPixmap(":/images/img1.jpg"));
    ui->widgetShow->addImage(QPixmap(":/images/img2.jpg"));
    ui->widgetShow->addImage(QPixmap(":/images/img3.jpg"));
    ui->widgetShow->addImage(QPixmap(":/images/img4.jpg"));
    ui->widgetShow->addImage(QPixmap(":/images/img5.jpg"));
    ui->widgetShow->addImage(QPixmap(":/images/img6.jpg"));
    ui->widgetShow->addImage(QPixmap(":/images/img7.jpg"));
    ui->widgetShow->addImage(QPixmap(":/images/img8.jpg"));
    ui->widgetShow->setCurrentIndex(0);
    ui->widgetShow->adjustSize();
    ui->widgetShow->setAutoSlide(5000);

    connect(ui->widgetShow, &SlideShow::signalImageClicked, this, [=](int index){
        clickPicIndex(index);
    });
    ui->pushButton->hide();
}

infoDispaly::~infoDispaly()
{
    delete ui;
}

void infoDispaly::clickPicIndex(int index)
{
    qDebug() << "用户点击了： " << index;
    this->clubName = QString::number(index);
    emit clubInfoDisplay(this->clubName);
}

void infoDispaly::showData()
{
    clubNum = 0;
    actionNum = 0;
    sutdentNum = 0;
    infoNum = 0;

    //展示信息
    QString strSQL = "select * from clubinfo;";
    QSqlQuery infoQuery;
    infoQuery.exec(strSQL);

    while(infoQuery.next())
    {
        clubNum++;
    }
    QString clubNumValue = "社团数：" + QString::number(clubNum);

    qDebug() << clubNumValue;
    ui->label->setText(clubNumValue);

    strSQL = "select * from students;";
    infoQuery.exec(strSQL);
    while(infoQuery.next())
    {
        sutdentNum++;
    }
    QString studentNumValue = "学生数：" + QString::number(sutdentNum);

    qDebug() << studentNumValue;
    ui->label_2->setText(studentNumValue);


    strSQL = "select * from activityinfo;";
    infoQuery.exec(strSQL);
    while(infoQuery.next())
    {
        actionNum++;
    }
    QString actNumValue = "活动数：" + QString::number(actionNum);

    qDebug() << actNumValue;
    ui->label_3->setText(actNumValue);


    strSQL = "select * from announcement;;";
    infoQuery.exec(strSQL);
    while(infoQuery.next())
    {
        infoNum++;
    }
    QString announcement = "公告数：" + QString::number(infoNum);


    qDebug() << announcement;
    ui->label_4->setText(announcement);

    qryModel->clear();
    qryModel->setQuery("SELECT announcement_name, announcement_content FROM announcement;");

    // 设置表头数据
    qryModel->setHeaderData(0, Qt::Horizontal, "公告名");
    qryModel->setHeaderData(1, Qt::Horizontal, "公告详情");

    QItemSelectionModel *theSelection=new QItemSelectionModel(qryModel);

    ui->tableView->setModel(qryModel);
    ui->tableView->setColumnWidth(0,160);
    ui->tableView->setColumnWidth(1,677);
    for (int i = 0; i < 50; i++) {
        ui->tableView->setRowHeight(i,60);
    }

    ui->tableView->horizontalHeader()->setStyleSheet(
        "QHeaderView::section {"
        "    background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
        "                                      stop:0 rgba(255, 255, 255, 0),"
        "                                      stop:0.5 rgba(255, 255, 255, 0),"
        "                                      stop:0.6 rgba(255, 255, 255, 0),"
        "                                      stop:1 rgba(255, 255, 255, 0));"
        "    color: white;"
        "}"
    );

    ui->tableView->setSelectionModel(theSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);


    qryModeForAction->clear();
    qryModeForAction->setQuery("SELECT activity_name, location, approval_date, introduction, organizer FROM activityinfo;");

    // 设置表头数据
    qryModeForAction->setHeaderData(0, Qt::Horizontal, "活动名称");
    qryModeForAction->setHeaderData(1, Qt::Horizontal, "活动地点");
    qryModeForAction->setHeaderData(2, Qt::Horizontal, "活动时间");
    qryModeForAction->setHeaderData(3, Qt::Horizontal, "活动简介");
    qryModeForAction->setHeaderData(4, Qt::Horizontal, "负责社团");

    QItemSelectionModel *selectionForAction=new QItemSelectionModel(qryModeForAction);

    ui->tableView_action->setModel(qryModeForAction);

    for (int i = 0; i < 50; i++) {
        ui->tableView_action->setRowHeight(i,60);
    }

    ui->tableView_action->setColumnWidth(0,160);
    ui->tableView_action->setColumnWidth(1,160);
    ui->tableView_action->setColumnWidth(2,160);
    ui->tableView_action->setColumnWidth(3,357);
    ui->tableView_action->setColumnWidth(4,160);

    ui->tableView_action->horizontalHeader()->setStyleSheet(
        "QHeaderView::section {"
        "    background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
        "                                      stop:0 rgba(255, 255, 255, 0),"
        "                                      stop:0.5 rgba(255, 255, 255, 0),"
        "                                      stop:0.6 rgba(255, 255, 255, 0),"
        "                                      stop:1 rgba(255, 255, 255, 0));"
        "    color: white;"
        "}"
    );

    ui->tableView_action->setSelectionModel(selectionForAction);
    ui->tableView_action->setSelectionBehavior(QAbstractItemView::SelectRows);
}


void infoDispaly::closeEvent(QCloseEvent *)
{
    emit exitInfoDisplay();
}

void infoDispaly::on_pushButton_clicked()
{
    QSqlQuery userQuery;

    //申请参加活动
    QString getActionName = "SELECT join_action FROM students where student_number=" + this->userName +";";
    userQuery.clear();
    userQuery.exec(getActionName);
    userQuery.next();
    QString sqlRes = userQuery.value(0).toString();

    if(selectActionName != sqlRes)
    {
        qDebug() << "申请加入了活动： " << sqlRes;

        QString addJoinNumStr = "UPDATE activityinfo SET join_num = join_num + 1 where activity_name='" + selectActionName +"';";
        userQuery.clear();
        userQuery.exec(addJoinNumStr);

        if (userQuery.isActive())
        {
            QMessageBox messageBox;
            messageBox.setText("申请参加活动成功！！！");
            messageBox.setStyleSheet("QMessageBox { background-color: white; }"
                                         "QLabel { color: black; }"  // 设置文本颜色为黑色，确保可读性
                                         "QPushButton { background-color: lightgray; }");

            // 显示消息框
            messageBox.exec();
        }
    }
    else
    {
        QMessageBox messageBox;
        messageBox.setText("申请失败，您已申请参加了该活动！！！！");
        messageBox.setStyleSheet("QMessageBox { background-color: white; }"
                                     "QLabel { color: black; }"  // 设置文本颜色为黑色，确保可读性
                                     "QPushButton { background-color: lightgray; }");

        // 显示消息框
        messageBox.exec();
    }
}

void infoDispaly::on_tableView_action_clicked(const QModelIndex &index)
{
    //点击槽函数
    QModelIndex clubNameIndex = qryModel->index(index.row(), 0);
    QVariant data = qryModeForAction->data(clubNameIndex);
    selectActionName = data.toString();
    qDebug() << "当前选中的活动为：" << selectActionName;

    QSqlQuery userQuery;
    userQuery.exec("select * from user_permissions;");

    while (userQuery.next())
    {
        this->userIndex = userQuery.value(2).toInt();
        this->userName = userQuery.value(1).toString();
    }

    if(this->userIndex != 1)
    {
        ui->pushButton->show();
    }
}
