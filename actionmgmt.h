#ifndef ACTIONMGMT_H
#define ACTIONMGMT_H

#include "toolHead.h"

namespace Ui {
class actionMgmt;
}

class actionMgmt : public QWidget
{
    Q_OBJECT

public:
    explicit actionMgmt(QWidget *parent = nullptr);
    ~actionMgmt();

    QString currentUserName;
    int userIndex;
    QString text;
    QString club_name;

    void closeEvent(QCloseEvent *);

    void initWindow();
    void fillActionInfo(QString actionName);
    void showDiagInfo();
    void clearInfo();

signals:
    void exitActionMgmt();

private slots:
    void on_btn_ok_clicked();

    void on_btn_clear_clicked();

    void on_btn_cancel_clicked();

    void on_pushButton_clicked();

    void on_btn_del_clicked();

private:
    Ui::actionMgmt *ui;
};

#endif // ACTIONMGMT_H
