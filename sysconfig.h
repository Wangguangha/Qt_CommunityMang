#ifndef SYSCONFIG_H
#define SYSCONFIG_H

#include "toolHead.h"

namespace Ui {
class sysConfig;
}

class sysConfig : public QWidget
{
    Q_OBJECT

public:
    explicit sysConfig(QWidget *parent = nullptr);
    ~sysConfig();

    void initWindows();     //初始化窗体

private slots:
    void on_btn_changePath_clicked();

    void on_btn_openDir_clicked();

    void on_btnApply_clicked();

private:
    Ui::sysConfig *ui;
};

#endif // SYSCONFIG_H
