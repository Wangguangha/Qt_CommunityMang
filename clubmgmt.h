#ifndef CLUBMGMT_H
#define CLUBMGMT_H

#include "toolHead.h"

namespace Ui {
class clubMgmt;
}

class clubMgmt : public QWidget
{
    Q_OBJECT

public:
    explicit clubMgmt(QWidget *parent = nullptr);
    ~clubMgmt();

    QString userName;
    int userIndex;
    void closeEvent(QCloseEvent *);

    QString fileName = "";
    QString lunboName = "";

    void initWindow();
    void fillCombox();
    void showChoiceDialog();
    void fillClubMgmt(QString clubName);

signals:
    void exitClubMgmt();

private slots:

    void on_btn_changePic_clicked();

    void on_btn_save_clicked();

    void on_btn_create_clicked();

    void on_btn_join_clicked();

private:
    Ui::clubMgmt *ui;
};

#endif // CLUBMGMT_H
