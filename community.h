#ifndef COMMUNITY_H
#define COMMUNITY_H

#include "toolHead.h"
#include "quiwidget.h"
#include "user_register.h"
#include "communityquery.h"
#include "sysconfig.h"
#include "user_login.h"
#include "actionmgmt.h"
#include "infodispaly.h"
#include "infomgmt.h"
#include "studentmgmt.h"
#include "personalcenter.h"
#include "clubmgmt.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Community; }
QT_END_NAMESPACE

class Community : public QMainWindow
{
    Q_OBJECT

public:
    Community(QWidget *parent = nullptr);
    ~Community();

    Community(QString username,QWidget *parent = nullptr);//构造函数有默认值的要放右边，新添加的参数需要放在左边

    bool max;
    QRect location;
    QString userName;
    int userFlag = 0;   //用户权限

    QStringList menuList = {"社团管理", "用户管理", "活动管理", "个人中心", "信息展示", "公告管理"};
    QStringList topMenuList = {"主界面", "系统设置", "社团查询", "用户退出"};
    QStringList clubNameList = {"", "音乐社", "篮球社", "摄影社", "舞蹈社", "书法社", "乒乓球社", "英语交流社"};

    clubMgmt *club = new clubMgmt();
    actionMgmt *action = new actionMgmt();
    infoMgmt *infoManagment = new infoMgmt();
    infoDispaly *infoShow = new infoDispaly();
    studentMgmt *userMgmt = new studentMgmt();
    personalCenter *personal = new personalCenter();

    communityQuery *comQuery = new communityQuery();
    sysConfig *sysconf = new sysConfig();

    void setAppBtnShow();
    void getUserNameFlag();

signals:
    void exitActionMgmt();

private slots:
    void initForm();
    void buttonClick();
    void btnClick();

    void showComminutityForAct();
    void showComminutityForClub();
    void showComminutityForInfoDispaly();
    void showComminutityForInfoMgmt();
    void showComminutityForPersonalCenter();
    void showComminutityForStudentMgmt();
    void showComminutityForInfoDisClub(QString clubName);

private slots:
    void on_btnMenu_Min_clicked();
    void on_btnMenu_Max_clicked();
    void on_btnMenu_Close_clicked();

private:
    Ui::Community *ui;
};
#endif // COMMUNITY_H
