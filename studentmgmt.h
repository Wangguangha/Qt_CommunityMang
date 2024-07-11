#ifndef STUDENTMGMT_H
#define STUDENTMGMT_H

#include "toolHead.h"

namespace Ui {
class studentMgmt;
}

class studentMgmt : public QWidget
{
    Q_OBJECT

public:
    explicit studentMgmt(QWidget *parent = nullptr);
    ~studentMgmt();

    QString userName;
    int userIndex;
    QString mgmtType;
    QString selectStudent;
    QString clubName;

    QSqlQueryModel *qryModel = new QSqlQueryModel(this);

    void closeEvent(QCloseEvent *);
    void initWindow();
    void update_apply_join();
    QString extractStr(const QStringList& rowData);

signals:
    void exitStudentMgmt();

private slots:
    void on_tableView_clicked(const QModelIndex &index);

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_btn_agree_clicked();

    void on_btn_refuse_clicked();

    void on_btn_up_clicked();

    void on_btn_save_clicked();

    void on_btn_input_clicked();

    void on_btn_del_clicked();

private:
    Ui::studentMgmt *ui;
};

#endif // STUDENTMGMT_H
