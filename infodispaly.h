#ifndef INFODISPALY_H
#define INFODISPALY_H

#include "toolHead.h"

namespace Ui {
class infoDispaly;
}

class infoDispaly : public QWidget
{
    Q_OBJECT

public:
    explicit infoDispaly(QWidget *parent = nullptr);
    ~infoDispaly();

    void showData();

    QString userIndex = 0;
    QString userName= "";

    int clubNum = 0;
    int actionNum = 0;
    int sutdentNum = 0;
    int infoNum = 0;
    QString clubName = "";
    QString selectActionName = "";

    void closeEvent(QCloseEvent *);

    void showEvent(QShowEvent *event)
    {
        showData();
        QWidget::showEvent(event);
    }

    void clickPicIndex(int index);
    QSqlQueryModel *qryModeForAction = new QSqlQueryModel(this);
    QSqlQueryModel *qryModel = new QSqlQueryModel(this);

signals:
    void exitInfoDisplay();
    void clubInfoDisplay(QString clubName);

private slots:
    void on_pushButton_clicked();

    void on_tableView_action_clicked(const QModelIndex &index);

private:
    Ui::infoDispaly *ui;
};

#endif // INFODISPALY_H
