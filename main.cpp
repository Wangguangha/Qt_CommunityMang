#include "user_login.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    UserLogin login("localhost");
    login.show();

    return a.exec();
}
