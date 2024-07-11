#ifndef PERSONALCENTER_H
#define PERSONALCENTER_H

#include "toolHead.h"

namespace Ui {
class personalCenter;
}

class personalCenter : public QWidget
{
    Q_OBJECT

public:
    explicit personalCenter(QWidget *parent = nullptr);
    ~personalCenter();

    QString userName, fileName;
    int userIndex;
    void closeEvent(QCloseEvent *);

    void initWindow();

signals:
    void exitPersonalCenter();

private slots:
    void on_btn_picture_clicked();

    void on_yes_btn_2_clicked();

    void on_no_btn_2_clicked();

private:
    Ui::personalCenter *ui;
};

#endif // PERSONALCENTER_H
