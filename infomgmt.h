#ifndef INFOMGMT_H
#define INFOMGMT_H

#include "toolHead.h"

namespace Ui {
class infoMgmt;
}

class infoMgmt : public QWidget
{
    Q_OBJECT

public:
    explicit infoMgmt(QWidget *parent = nullptr);
    ~infoMgmt();

    QString userName;
    int userIndex;
    void closeEvent(QCloseEvent *);
    void initWindow();
    void showChoiceDialog();
    void editInfo(QString infoName);
    void fillComBox();

signals:
    void exitInfoMgmt();

private slots:
    void on_btn_ok_clicked();

    void on_btn_cancel_clicked();

    void on_btn_save_clicked();

private:
    Ui::infoMgmt *ui;
};

#endif // INFOMGMT_H
