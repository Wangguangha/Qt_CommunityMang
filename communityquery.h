#ifndef COMMUNITYQUERY_H
#define COMMUNITYQUERY_H

#include "toolHead.h"

namespace Ui {
class communityQuery;
}

class communityQuery : public QWidget
{
    Q_OBJECT

public:
    explicit communityQuery(QWidget *parent = nullptr);
    ~communityQuery();

    QSqlQueryModel *qryModel = new QSqlQueryModel(this);
    int table_query_begin;  //开始页
    int table_query_end;    //结束页

    QString queryType;

    void initWindows();     //初始化窗口

    QString userName;
    int userIndex;
    QString selectClubName;
    void closeEvent(QCloseEvent *);
    void updateInfo(int page);

signals:
    void exitComQuery();

private slots:
    void on_btn_Query_clicked();

    void on_btnSkip_clicked();

    void on_btnBefore_clicked();

    void on_btnNext_clicked();

    void on_btn_join_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_comboBox_currentTextChanged(const QString &arg1);

private:
    Ui::communityQuery *ui;
};

#endif // COMMUNITYQUERY_H
