#include "sysconfig.h"
#include "ui_sysconfig.h"
#include "user_login.h"

sysConfig::sysConfig(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sysConfig)
{
    ui->setupUi(this);
    initWindows();
}

sysConfig::~sysConfig()
{
    delete ui;
}

void sysConfig::initWindows()
{
    //初始化窗体
    ui->lineEdit_dataUrl->setText("localhost");
    ui->lineEdit_version->setText("V3.9.1");
    QString filePath = QCoreApplication::applicationDirPath();
    ui->lineEdit_filePath->setText(filePath);
}

void sysConfig::on_btn_changePath_clicked()
{
    //修改文件路径
    QString file_name = QFileDialog::getExistingDirectory (NULL,"文件保存路径",".");
    qDebug() << file_name;
    ui->lineEdit_filePath->setText(file_name);
}

void sysConfig::on_btn_openDir_clicked()
{
    //打开文件路径
    QDesktopServices::openUrl(QUrl(ui->lineEdit_filePath->text()));
}

void sysConfig::on_btnApply_clicked()
{
    //应用系统设置
    //如果修改了数据库的url，则将退出当前数据库连接，连接新的数据库
    if(ui->lineEdit_dataUrl->text() != "localhost")
    {
        //UserLogin login(ui->lineEdit_dataUrl->text());
        //login.show();
        qDebug() << ui->lineEdit_dataUrl->text();
    }
}
