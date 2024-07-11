#include "community.h"
#include "ui_community.h"


Community::Community(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Community)
{
    ui->setupUi(this);
    this->initForm();
    QUIWidget::setFormInCenter(this);
}

Community::~Community()
{
    delete ui;
}

Community::Community(QString username, QWidget *parent )
    :QMainWindow(parent)
    ,ui(new Ui::Community)

{
    ui->setupUi(this);
    this->userName = username;
    this->initForm();
    QUIWidget::setFormInCenter(this);
}

void Community::getUserNameFlag()
{
    QSqlQuery userQuery;
    userQuery.exec("select * from user_permissions;");
    while (userQuery.next())
    {
        this->userFlag = userQuery.value(2).toInt();
        this->userName = userQuery.value(1).toString();
    }
}

void Community::initForm()
{
    ui->btnConfig->hide();
    getUserNameFlag();
    this->setObjectName("wang");
    this->setStyleSheet("#wang{background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(251,102,102, 200), stop:1 rgba(20,196,188, 210));}");

    connect(infoShow, &infoDispaly::clubInfoDisplay, this, &Community::showComminutityForInfoDisClub);

    this->max = false;
    this->location = this->geometry();
    this->setProperty("form", true);
    IconHelper::Instance()->setIcon(ui->lab_Ico, QChar(0xF099), 30);

    QSize icoSize(32, 32);
    int icoWidth = 85;

    //设置顶部导航按钮
    QList<QToolButton *> tbtns = ui->widget_top->findChildren<QToolButton *>();
    foreach (QToolButton *btn, tbtns) {
        btn->setIconSize(icoSize);
        btn->setMinimumWidth(icoWidth);
        btn->setCheckable(true);
        connect(btn, SIGNAL(clicked()), this, SLOT(buttonClick()));
    }

    ui->btnMain->click();

    //设置左侧导航按钮
    QList<QPushButton *> btns = ui->widget_left->findChildren<QPushButton *>();
    foreach (QPushButton *btn, btns) {
        btn->setCheckable(true);
        connect(btn, SIGNAL(clicked()), this, SLOT(btnClick()));
    }

    //显示当前登录用户名
    ui->label_username->setText(this->userName);

    //隐藏tabWidget上方的tab标签
    ui->tabWidget->tabBar()->hide();
    setAppBtnShow();

}

void Community::setAppBtnShow()
{
    //设置界面显示
    if(this->userFlag == 1)
    {
        //超级管理员
        //do nothing
    }
    else if(this->userFlag == 2)
    {
        //do nothing
    }
    else if(this->userFlag == 3)
    {
        ui->btn1->hide();
        ui->btn2->hide();
        ui->btn3->hide();
        ui->btn_info->hide();
    }
}

void Community::buttonClick()
{
    QToolButton *btn = (QToolButton *)sender();
    QString name = btn->text();

    QList<QToolButton *> btns = ui->widget_top->findChildren<QToolButton *>();
    foreach (QToolButton *b, btns) {
        if (b == btn) {
            b->setChecked(true);
        } else {
            b->setChecked(false);
        }
    }

    qDebug() << "你单击了顶部导航菜单" << name;

    ui->tabWidget->clear();

    UserLogin *login;

    switch (topMenuList.indexOf(name)) {
        case 0:
            ui->tabWidget->addTab(infoShow, "");
            break;
        case 1:
            ui->tabWidget->addTab(sysconf, "");
            break;
        case 2:
            ui->tabWidget->addTab(comQuery, "");
            connect(comQuery, SIGNAL(exitComQuery()), this, SLOT(showComminutityForClub()));
            break;
        case 3:
            this->close();
            login = new UserLogin("localhost");
            login->show();
            break;
        default :
            ui->tabWidget->addTab(comQuery, "");
            break;
    }
}

void Community::btnClick()
{
    QPushButton *b = (QPushButton *)sender();
    QString name = b->text();

    QList<QPushButton *> btns = ui->widget_left->findChildren<QPushButton *>();
    foreach (QPushButton *btn, btns) {
        if (btn == b) {
            btn->setChecked(true);
        } else {
            btn->setChecked(false);
        }
    }

    qDebug()<< "你单击了左侧导航菜单" << name;

    ui->tabWidget->clear();

    qDebug() << menuList.indexOf(name);

    switch (menuList.indexOf(name)) {
        case 0:
            club->initWindow();
            connect(club, SIGNAL(exitClubMgmt()), this, SLOT(showComminutityForClub()));
            ui->tabWidget->addTab(club, "");
            break;
        case 1:
            userMgmt->initWindow();
            ui->tabWidget->addTab(userMgmt, "");
            connect(userMgmt, SIGNAL(exitStudentMgmt()), this, SLOT(showComminutityForStudentMgmt()));
            break;
        case 2:
            action->initWindow();
            connect(action, SIGNAL(exitActionMgmt()), this, SLOT(showComminutityForAct()));
            ui->tabWidget->addTab(action, "");
            break;
        case 3:
            personal->initWindow();
            connect(personal, SIGNAL(exitPersonalCenter()), this, SLOT(showComminutityForPersonalCenter()));
            ui->tabWidget->addTab(personal, "");
            break;
        case 4:
            infoShow->showData();
            connect(infoShow, &infoDispaly::exitInfoDisplay, this, &Community::showComminutityForInfoDispaly);
            ui->tabWidget->addTab(infoShow, "");
            break;
        case 5:
            infoManagment->initWindow();
            connect(infoManagment, SIGNAL(exitInfoMgmt()), this, SLOT(showComminutityForInfoMgmt()));
            ui->tabWidget->addTab(infoManagment, "");
            break;
        default :
            ui->tabWidget->addTab(club, "");
            connect(club, SIGNAL(exitClubMgmt()), this, SLOT(showComminutityForClub()));
            break;
    }

}

void Community::showComminutityForAct()
{
    ui->tabWidget->clear();
    ui->tabWidget->addTab(infoShow, "");
}

void Community::showComminutityForClub()
{
    ui->tabWidget->clear();
    ui->tabWidget->addTab(infoShow, "");
}

void Community::showComminutityForInfoDispaly()
{
    ui->tabWidget->clear();
    ui->tabWidget->addTab(infoShow, "");
}

void Community::showComminutityForInfoDisClub(QString clubName)
{
    if(clubName != "0")
    {
        connect(club, SIGNAL(exitClubMgmt()), this, SLOT(showComminutityForClub()));
        QString club_name = clubNameList[clubName.toInt()];
        ui->tabWidget->clear();
        club->fillClubMgmt(club_name);
        ui->tabWidget->addTab(club, "");
    }
}

void Community::showComminutityForInfoMgmt()
{
    ui->tabWidget->clear();
    ui->tabWidget->addTab(infoShow, "");
}


void Community::showComminutityForPersonalCenter()
{
    ui->tabWidget->clear();
    ui->tabWidget->addTab(infoShow, "");
}

void Community::showComminutityForStudentMgmt()
{
    ui->tabWidget->clear();
    ui->tabWidget->addTab(infoShow, "");
}


void Community::on_btnMenu_Min_clicked()
{
    showMinimized();
}

void Community::on_btnMenu_Max_clicked()
{
    if (max) {
        this->setGeometry(location);
        this->setWindowFlags(Qt::WindowTitleHint|Qt::WindowSystemMenuHint|Qt::WindowMinMaxButtonsHint|Qt::WindowCloseButtonHint);
        this->showNormal();
    } else {
        location = this->geometry();

        this->setWindowFlags(Qt::Window|Qt::WindowStaysOnTopHint);
        this->showFullScreen();
    }

    max = !max;
}

void Community::on_btnMenu_Close_clicked()
{
    this->close();
}
