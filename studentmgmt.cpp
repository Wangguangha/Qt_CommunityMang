#include "studentmgmt.h"
#include "ui_studentmgmt.h"

studentMgmt::studentMgmt(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::studentMgmt)
{
    ui->setupUi(this);
    ui->btn_agree->hide();
    ui->btn_refuse->hide();
    ui->btn_save->hide();
    ui->btn_input->hide();
}

studentMgmt::~studentMgmt()
{
    delete ui;
}

void studentMgmt::initWindow()
{
    //初始化窗口
    qryModel->clear();
    //初始化界面
    QSqlQuery userQuery;
    userQuery.exec("select * from user_permissions;");
    while (userQuery.next())
    {
        this->userIndex = userQuery.value(2).toInt();
        this->userName = userQuery.value(1).toString();
    }
    qDebug() << "The userName is: " << this->userName << "userFlag : " << this->userIndex;

    if(this->userIndex == 1)
    {
        qryModel->setQuery("select student_number,name,contact,class,gender,age,club_name from students;");
        ui->btn_save->show();
        ui->btn_input->show();
    }
    else if(this->userIndex == 2)
    {
        QString strSQL = "select managed_club_name from admin where username = '"+ this->userName  +"';";
        QSqlQuery infoQuery;
        infoQuery.exec(strSQL);
        infoQuery.next();

        QString club_name = infoQuery.value(0).toString();
        QString queryStu = "select student_number,name,contact,class,gender,age"
                           ",club_name from students where club_name = '" + club_name + "';";
        qryModel->setQuery(queryStu);
    }

    qryModel->setHeaderData(0, Qt::Horizontal, "学号");
    qryModel->setHeaderData(1, Qt::Horizontal, "姓名");
    qryModel->setHeaderData(2, Qt::Horizontal, "联系方式");
    qryModel->setHeaderData(3, Qt::Horizontal, "班级");
    qryModel->setHeaderData(4, Qt::Horizontal, "性别");
    qryModel->setHeaderData(5, Qt::Horizontal, "年龄");
    qryModel->setHeaderData(6, Qt::Horizontal, "社团");

    QItemSelectionModel *theSelection=new QItemSelectionModel(qryModel);

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

    ui->tableView->setModel(qryModel);
    ui->tableView->setSelectionModel(theSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->comboBox->setCurrentIndex(0);
}

void studentMgmt::closeEvent(QCloseEvent *)
{
    emit exitStudentMgmt();
}

void studentMgmt::on_tableView_clicked(const QModelIndex &index)
{
    //当前选中的成员变化
    QModelIndex clubNameIndex = qryModel->index(index.row(), 1);
    QVariant data = qryModel->data(clubNameIndex);
    selectStudent = data.toString();
    qDebug() << selectStudent;
}

void studentMgmt::update_apply_join()
{
    QString nameList = "student_number IN ('";
    qryModel->clear();

    QString sqlQuery = "select applicant_name from apply_join ";
    if(this->userIndex == 1)
    {
        //do nothing
        qDebug() << "This is superAdmin !!!";
    }else if(this->userIndex == 2)
    {
        QString queryStr = "select managed_club_name from admin where username = '" + this->userName + "';";
        QSqlQuery aquery(queryStr);
        aquery.exec();
        aquery.next();
        clubName = aquery.value(0).toString();
        sqlQuery += "where club_name = '" + clubName +"';";
    }

    QSqlQuery query(sqlQuery);
    if (query.exec()) {
        while (query.next()) {
            QString applicantName = query.value(0).toString();
            qDebug() << "Applicant Name:" << applicantName;
            // 在这里可以对每个申请者的名字执行相应的操作
            nameList.append(applicantName + "','");
        }
        nameList.chop(2);
        nameList.append(");");
        QString SQLstr = "select student_number,name,contact,class,gender,age from students where " + nameList;
        qDebug() << SQLstr;
        qryModel->setQuery(SQLstr);

        qryModel->setHeaderData(0, Qt::Horizontal, "学号");
        qryModel->setHeaderData(1, Qt::Horizontal, "姓名");
        qryModel->setHeaderData(2, Qt::Horizontal, "联系方式");
        qryModel->setHeaderData(3, Qt::Horizontal, "班级");
        qryModel->setHeaderData(4, Qt::Horizontal, "性别");
        qryModel->setHeaderData(5, Qt::Horizontal, "年龄");
        qryModel->setHeaderData(6, Qt::Horizontal, "社团");

        ui->tableView->setModel(qryModel);
    } else {
        qDebug() << "Query execution failed";
    }
}

void studentMgmt::on_comboBox_currentIndexChanged(const QString &arg1)
{
    //下拉框选中内容变化
    mgmtType = ui->comboBox->currentText();
    qDebug() << mgmtType;

    if(mgmtType == "成员管理")
    {
        qDebug() << "This is 成员管理";
        initWindow();
        ui->btn_agree->hide();
        ui->btn_refuse->hide();
        ui->btn_up->show();
        ui->btn_del->show();
    }
    else if(mgmtType == "入团申请")
    {
        if(this->userIndex != 3)
        {
            //社团管理员
            update_apply_join();
            ui->btn_up->hide();
            ui->btn_del->hide();
            ui->btn_agree->show();
            ui->btn_refuse->show();
        }
    }
}

void studentMgmt::on_btn_agree_clicked()
{
    //同意入团申请
    qDebug() << selectStudent;
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString currentDateTimeStr = currentDateTime.toString("yyyy-MM-dd");
    qDebug() << "当前时间：" << currentDateTimeStr;

    QSqlQuery query;
    // 准备 UPDATE 语句，更新 club_name 和 join_date 列
    QString sqlQuery = "UPDATE students SET club_name = :clubName, join_date = :joinDate WHERE name = :studentName";

    // 绑定参数
    query.prepare(sqlQuery);
    query.bindValue(":clubName", clubName);  // 新的社团名
    query.bindValue(":joinDate", QDateTime::currentDateTime());  // 当前时间作为入团时间
    query.bindValue(":studentName", selectStudent);

    // 执行更新操作
    if (query.exec()) {
        qDebug() << "更新成功！";

        QMessageBox messageBox;
        messageBox.setText("已成功加入社团！！！");
        messageBox.setStyleSheet("QMessageBox { background-color: white; }"
                                     "QLabel { color: black; }"  // 设置文本颜色为黑色，确保可读性
                                     "QPushButton { background-color: lightgray; }");

        // 显示消息框
        messageBox.exec();

        QString strSQL = "select student_number from students where name = '" + selectStudent + "';";
        query.exec(strSQL);
        if(query.next())
        {
            QString studentNum = query.value(0).toString();
            query.exec("DELETE FROM apply_join WHERE applicant_name = '"+ studentNum +"';");
            query.next();

            update_apply_join();
        }
    } else {
        qDebug() << "更新失败!";
    }
}

void studentMgmt::on_btn_refuse_clicked()
{
    //拒绝加入社团
    QSqlQuery query;

    // 准备 UPDATE 语句，更新 club_name 和 join_date 列
    QString sqlQuery = "DELETE FROM apply_join WHERE applicant_name = :studentName";

    // 绑定参数
    query.prepare(sqlQuery);
    query.bindValue(":studentName", selectStudent);

    // 执行更新操作
    if (query.exec()) {
        qDebug() << "更新成功！   " << sqlQuery << "   " << selectStudent;
        QMessageBox messageBox;
        messageBox.setText("已拒绝加入社团申请！！！");
        messageBox.setStyleSheet("QMessageBox { background-color: white; }"
                                     "QLabel { color: black; }"  // 设置文本颜色为黑色，确保可读性
                                     "QPushButton { background-color: lightgray; }");

        // 显示消息框
        messageBox.exec();
        QString strSQL = "select student_number from students where name = '" + selectStudent + "';";
        query.exec(strSQL);
        if(query.next())
        {
            QString studentNum = query.value(0).toString();
            query.exec("DELETE FROM apply_join WHERE applicant_name = '"+ studentNum +"';");
            query.next();

            update_apply_join();
        }
    } else {
        qDebug() << "更新失败!";
    }
}

void studentMgmt::on_btn_up_clicked()
{
    //任命功能

    bool ok;
    QStringList items;
    QString clubName;

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
        clubName = text;
    }

    //从当前选中的学生信息中获取 name、gender、contact、学号（username）、passwd、club_name
    QSqlQuery userQuery;
    userQuery.exec("select name,password,gender,contact,student_number, club_name from students where name = '" + selectStudent + "';");
    userQuery.next();

    QString studentName = userQuery.value(0).toString();
    QString studentPasswd = userQuery.value(1).toString();
    QString gender = userQuery.value(2).toString();
    QString contact = userQuery.value(3).toString();
    QString userName = userQuery.value(4).toString();
    if(clubName.length() == 0)
    {
        clubName = userQuery.value(5).toString();
    }

    // 假设权限级别为普通管理员，入职日期为当前日期
    int privilegeLevel = 2;
    QDate joinDate = QDate::currentDate();

    // 打印提取的参数
    qDebug() << "学生姓名:" << studentName;
    qDebug() << "学生密码:" << studentPasswd;
    qDebug() << "性别:" << gender;
    qDebug() << "联系方式:" << contact;
    qDebug() << "用户名:" << userName;
    qDebug() << "俱乐部名称:" << clubName;
    qDebug() << "权限级别:" << privilegeLevel;
    qDebug() << "入职日期:" << joinDate.toString("yyyy-MM-dd");

    // 构建插入admin表的SQL语句
    strSQL = QString(
        "INSERT INTO admin (username, password, name, gender, contact, privilege_level, join_date, managed_club_name) "
        "VALUES ('%1', '%2', '%3', '%4', '%5', %6, '%7', '%8')")
        .arg(userName)
        .arg(studentPasswd)
        .arg(studentName)
        .arg(gender)
        .arg(contact)
        .arg(privilegeLevel)
        .arg(joinDate.toString("yyyy-MM-dd"))
        .arg(clubName);


        QSqlQuery query;
        //更新学生表中的社团角色
        QString sqlQuery = "update students set club_name = '"+ clubName +"', club_role = '社团管理员', join_date = '"+
              joinDate.toString("yyyy-MM-dd")  +"' WHERE name = :studentName";

        // 绑定参数
        query.prepare(sqlQuery);
        query.bindValue(":studentName", selectStudent);

        // 执行更新操作
        if (query.exec()) {
            qDebug() << "更新成功！";
        } else {
            qDebug() << "更新失败! " << sqlQuery;
        }

    QSqlQuery insertQuery;
    if (!insertQuery.exec(strSQL)) {
        qDebug() << "插入失败";
        QMessageBox messageBox;
        messageBox.setText("任命管理员失败，请检查学生是否已经是社团管理员！！！");
        messageBox.setStyleSheet("QMessageBox { background-color: white; }"
                                     "QLabel { color: black; }"  // 设置文本颜色为黑色，确保可读性
                                     "QPushButton { background-color: lightgray; }");

        // 显示消息框
        messageBox.exec();
    } else {
        qDebug() << "插入成功";
        QMessageBox messageBox;
        messageBox.setText("任命管理员成功！！！");
        messageBox.setStyleSheet("QMessageBox { background-color: white; }"
                                     "QLabel { color: black; }"  // 设置文本颜色为黑色，确保可读性
                                     "QPushButton { background-color: lightgray; }");

        // 显示消息框
        messageBox.exec();
        initWindow();
    }
}

void studentMgmt::on_btn_save_clicked()
{
    //导出
    QString path = "C:/Users/Administrator/Desktop/test/";
    QString filePath = path.append("Excel.xlsx");

    QAxObject *excel = new QAxObject("Excel.Application");
    if (!excel) {
        qDebug() << "创建 Excel 对象失败";
        return;
    }

    excel->setProperty("Visible", false);
    QAxObject *workBooks = excel->querySubObject("WorkBooks");
    workBooks->dynamicCall("Add");
    QAxObject *workBook = excel->querySubObject("ActiveWorkBook");
    QAxObject *workSheets = workBook->querySubObject("Sheets");
    QAxObject *workSheet = workSheets->querySubObject("Item(int)", 1);
    workSheet->setProperty("Name", "数据");

    int colCount = ui->tableView->model()->columnCount();
    int rowCount = ui->tableView->model()->rowCount();

    // 创建一个二维 QVariant 数组存储数据
    QVariantList varRows;
    for (int i = 0; i < rowCount; ++i) {
        QVariantList varRow;
        for (int j = 0; j < colCount; ++j) {
            QModelIndex index = ui->tableView->model()->index(i, j);
            QString strData = ui->tableView->model()->data(index).toString();
            varRow << strData;
        }
        varRows << QVariant(varRow);
    }

    // 将数据写入 Excel
    QVariant varData(varRows);
    QString cellRange = QString("A2:%1%2").arg(QChar('A' + colCount - 1)).arg(rowCount + 1);
    QAxObject *range = workSheet->querySubObject("Range(const QString&)", cellRange);
    range->setProperty("Value", varData);

    // 写入列标题
    for (int i = 0; i < colCount; ++i) {
        QAxObject *col = workSheet->querySubObject("Cells(int, int)", 1, i + 1);
        QString columnName = ui->tableView->model()->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString();
        col->dynamicCall("SetValue(const QString&)", columnName);

        // 设置列标题样式
        QString cellAddress = QString("%1%2").arg(QChar('A' + i)).arg(1);
        QAxObject *cell = workSheet->querySubObject("Range(const QString&)", cellAddress);
        cell->setProperty("ColumnWidth", 20); // 设置列宽
        cell->setProperty("RowHeight", 30); // 设置行高
        cell->querySubObject("Font")->setProperty("Bold", true);
        cell->querySubObject("Interior")->setProperty("Color", QColor(150, 150, 150));
        cell->setProperty("HorizontalAlignment", -4108); // 居中对齐
    }

    // 绘制边框
    QString drawCellLine = QString("A1:%1%2").arg(QChar('A' + colCount - 1)).arg(rowCount + 1);
    range = workSheet->querySubObject("Range(const QString&)", drawCellLine);
    range->querySubObject("Borders")->setProperty("LineStyle", QString::number(1));
    range->querySubObject("Borders")->setProperty("Color", QColor(0, 0, 0));

    // 保存 Excel 文件
    workBook->dynamicCall("SaveAs(const QString&)", QDir::toNativeSeparators(filePath));
    workBook->dynamicCall("Close()");
    excel->dynamicCall("Quit()");

    delete excel;

    QMessageBox messageBox;
    messageBox.setText("学生信息已成功导出！！！");
    messageBox.setStyleSheet("QMessageBox { background-color: white; }"
                                 "QLabel { color: black; }"  // 设置文本颜色为黑色，确保可读性
                                 "QPushButton { background-color: lightgray; }");

    // 显示消息框
    messageBox.exec();
}

QString studentMgmt::extractStr(const QStringList& rowData)
{
    if (rowData.size() != 8) {
        qDebug() << "Invalid input format!";
        return "";
    }

    // 构建 SQL INSERT 语句
    QString sql = "INSERT INTO students (name, student_number, contact, class, password, gender, age, avatar_path) VALUES (";
    sql += "'" + rowData[1] + "', "; // name
    sql += rowData[0] + ", "; // student_number
    sql += "'" + rowData[2] + "', "; // contact
    sql += "'" + rowData[3] + "', "; // class
    sql += "'123456', "; // password
    sql += "'" + rowData[5] + "', "; // gender
    sql += "'" + rowData[6] + "', "; // age
    sql += "NULL);"; // avatar_path

    return sql;
}

void studentMgmt::on_btn_input_clicked()
{
    //导入
    // 创建 Excel 应用程序对象
    QAxObject* excel = new QAxObject("Excel.Application");
    excel->setProperty("Visible", false); // 隐藏 Excel 窗口

    QString filePath = QFileDialog::getOpenFileName(nullptr, "打开 Excel 文件", "", "Excel 文件 (*.xlsx *.xls)");
    if (!filePath.isEmpty()) {
        qDebug() << filePath;
    } else {
        qDebug() << "没有选择文件";
    }

    // 打开工作簿
    QAxObject* workbooks = excel->querySubObject("Workbooks");
    QAxObject* workbook = workbooks->querySubObject("Open(const QString&)", filePath);

    // 获取第一个工作表
    QAxObject* sheets = workbook->querySubObject("Sheets");
    QAxObject* sheet = sheets->querySubObject("Item(int)", 1);

    // 获取工作表的行数和列数
    QAxObject* usedRange = sheet->querySubObject("UsedRange");
    QAxObject* rows = usedRange->querySubObject("Rows");
    QAxObject* columns = usedRange->querySubObject("Columns");

    int rowCount = rows->property("Count").toInt();
    int colCount = columns->property("Count").toInt();

    // 读取每一行数据
    for (int row = 2; row <= rowCount; ++row) {
        QStringList rowData;
        for (int col = 1; col <= colCount; ++col) {
            QAxObject* cell = sheet->querySubObject("Cells(int,int)", row, col);
            QVariant value = cell->property("Value");
            rowData << value.toString();
        }

        QSqlQuery inputQuery;
        QString inputSql = extractStr(rowData);
        inputQuery.exec(inputSql);
    }

    // 关闭工作簿，不保存更改
    workbook->dynamicCall("Close(bool)", false);
    excel->dynamicCall("Quit()");

    // 释放内存
    delete excel;

    initWindow();
    QMessageBox messageBox;
    messageBox.setText("学生信息已成功导入！！！");
    messageBox.setStyleSheet("QMessageBox { background-color: white; }"
                                 "QLabel { color: black; }"  // 设置文本颜色为黑色，确保可读性
                                 "QPushButton { background-color: lightgray; }");

    // 显示消息框
    messageBox.exec();
}

void studentMgmt::on_btn_del_clicked()
{
    //移除社团按钮
    QSqlQuery query;

    // 准备 UPDATE 语句，更新 club_name 和 join_date 列
    QString sqlQuery = "UPDATE students SET club_name = '' WHERE name = :studentName";

    // 绑定参数
    query.prepare(sqlQuery);
    query.bindValue(":studentName", selectStudent);

    // 执行更新操作
    if (query.exec()) {
        qDebug() << "更新成功！";
        QMessageBox messageBox;
        messageBox.setText("已将学生从社团中移除！！！");
        messageBox.setStyleSheet("QMessageBox { background-color: white; }"
                                     "QLabel { color: black; }"  // 设置文本颜色为黑色，确保可读性
                                     "QPushButton { background-color: lightgray; }");

        // 显示消息框
        messageBox.exec();
        initWindow();
    } else {
        qDebug() << "更新失败!";
    }

    initWindow();
}
