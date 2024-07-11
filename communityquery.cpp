#include "communityquery.h"
#include "ui_communityquery.h"

communityQuery::communityQuery(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::communityQuery)
{
    ui->setupUi(this);
    initWindows();
}

communityQuery::~communityQuery()
{
    delete ui;
}

void communityQuery::initWindows()
{
    //初始化窗口
    qryModel->setQuery("select club_name,category,leader,contact,introduction from clubinfo;");
    qryModel->setHeaderData(0, Qt::Horizontal, "社团名");
    qryModel->setHeaderData(1, Qt::Horizontal, "社团类型");
    //qryModel->setHeaderData(2, Qt::Horizontal, "创建时间");
    qryModel->setHeaderData(2, Qt::Horizontal, "管理员");
    qryModel->setHeaderData(3, Qt::Horizontal, "联系方式");
    qryModel->setHeaderData(4, Qt::Horizontal, "社团介绍");



    QItemSelectionModel *theSelection=new QItemSelectionModel(qryModel);
    ui->tableView->setModel(qryModel);
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

    ui->tableView->setColumnWidth(0,150);
    ui->tableView->setColumnWidth(1,150);
    ui->tableView->setColumnWidth(2,150);
    ui->tableView->setColumnWidth(3,150);
    ui->tableView->setColumnWidth(4,430);
    for (int i = 0; i < 50; i++) {
        ui->tableView->setRowHeight(i,60);
    }

    ui->tableView->setSelectionModel(theSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    QSqlQuery userQuery;
    userQuery.exec("select * from user_permissions;");
    while (userQuery.next())
    {
        this->userIndex = userQuery.value(2).toInt();
        this->userName = userQuery.value(1).toString();
    }
    qDebug() << "The userName is: " << this->userName << "userFlag : " << this->userIndex;

    if(this->userIndex != 3)
        ui->btn_join->hide();
}

void communityQuery::on_btn_Query_clicked()
{
    //社团查询按钮
    qryModel->clear();
    QString SQLstr ;
    SQLstr = "select club_name,category,leader,contact,introduction from clubinfo WHERE TRIM(club_name) LIKE '%" + ui->lineEdit->text() +"%' ;";

    if(this->queryType == "社团类型")
    {
        SQLstr = "select club_name,category,leader,contact,introduction from clubinfo WHERE TRIM(category) LIKE '%" + ui->lineEdit->text() +"%' ;";
    }
    else if(this->queryType == "社团名称")
    {
        SQLstr = "select club_name,category,leader,contact,introduction from clubinfo WHERE TRIM(club_name) LIKE '%" + ui->lineEdit->text() +"%' ;";
    }
    qDebug() << SQLstr;
    qryModel->setQuery(SQLstr);

    ui->tableView->setModel(qryModel);
    qryModel->setHeaderData(0, Qt::Horizontal, "社团名");
    qryModel->setHeaderData(1, Qt::Horizontal, "社团类型");
    qryModel->setHeaderData(2, Qt::Horizontal, "管理员");
    qryModel->setHeaderData(3, Qt::Horizontal, "联系方式");
    qryModel->setHeaderData(4, Qt::Horizontal, "社团介绍");
    ui->tableView->setColumnWidth(0,150);
    ui->tableView->setColumnWidth(1,150);
    ui->tableView->setColumnWidth(2,150);
    ui->tableView->setColumnWidth(3,150);
    ui->tableView->setColumnWidth(4,430);
    for (int i = 0; i < 50; i++) {
        ui->tableView->setRowHeight(i,60);
    }

}

void communityQuery::updateInfo(int page)
{
    QString updateSQL = "SELECT club_name,category,leader,contact,introduction FROM clubInfo LIMIT "+ QString::number((page-1)*10) +", 10;";
    qDebug() << updateSQL;
    qryModel->clear();
    qryModel->setQuery(updateSQL);

    ui->tableView->setModel(qryModel);
    qryModel->setHeaderData(0, Qt::Horizontal, "社团名");
    qryModel->setHeaderData(1, Qt::Horizontal, "社团类型");
    qryModel->setHeaderData(2, Qt::Horizontal, "管理员");
    qryModel->setHeaderData(3, Qt::Horizontal, "联系方式");
    qryModel->setHeaderData(4, Qt::Horizontal, "社团介绍");
    ui->tableView->setColumnWidth(0,150);
    ui->tableView->setColumnWidth(1,150);
    ui->tableView->setColumnWidth(2,150);
    ui->tableView->setColumnWidth(3,150);
    ui->tableView->setColumnWidth(4,430);
    for (int i = 0; i < 50; i++) {
        ui->tableView->setRowHeight(i,60);
    }
}

void communityQuery::on_btnSkip_clicked()
{
    //跳转到指定页
    qDebug() << "跳转到: " << ui->spinBox->text();
    updateInfo(ui->spinBox->text().toInt());
}

void communityQuery::on_btnBefore_clicked()
{
    //前一页
    int currentPage = ui->spinBox->value();
    currentPage -= 1;
    ui->spinBox->setValue(currentPage);
    qDebug() << "前一页: " << currentPage;
    updateInfo(ui->spinBox->text().toInt());
}

void communityQuery::on_btnNext_clicked()
{
    //后一页
    int currentPage = ui->spinBox->value();
    currentPage += 1;
    ui->spinBox->setValue(currentPage);
    qDebug() << "后一页: " << ui->spinBox->text();
    updateInfo(ui->spinBox->text().toInt());
}

void communityQuery::on_btn_join_clicked()
{
    //申请加入社团
    qDebug() << "The userName is: " << this->userName << endl;
    if(this->userIndex == 3){
        qDebug() << "这是普通用户，可以申请加入社团";
        qDebug() << selectClubName;
        QString properties = "applicant_name,club_name";
        QString values = "'" + this->userName + "','" + selectClubName;
        QString sqlStr = "insert into apply_join(" + properties + ") values(" +
                values + "');";

        qDebug() << sqlStr;

        QSqlQuery query;
        query.prepare(sqlStr);
        query.exec();

        if (query.isActive())
        {

            QMessageBox messageBox;
            messageBox.setText("申请加入社团成功！！！");
            messageBox.setStyleSheet("QMessageBox { background-color: white; }"
                                         "QLabel { color: black; }"  // 设置文本颜色为黑色，确保可读性
                                         "QPushButton { background-color: lightgray; }");

            // 显示消息框
            messageBox.exec();
            this->close();
        }
    }
}

void communityQuery::closeEvent(QCloseEvent *)
{
    emit exitComQuery();
}

void communityQuery::on_tableView_clicked(const QModelIndex &index)
{
    //点击事件槽函数
    QModelIndex clubNameIndex = qryModel->index(index.row(), 0);
    QVariant data = qryModel->data(clubNameIndex);
    selectClubName = data.toString();
}

void communityQuery::on_comboBox_currentTextChanged(const QString &arg1)
{
    //查询方式变化
    this->queryType = arg1;
    qDebug() << "当前选中的查询方式是：" << this->queryType;
}
