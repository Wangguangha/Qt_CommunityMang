QT       += core gui
QT       += sql
QT       += axcontainer

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    actionmgmt.cpp \
    clubmgmt.cpp \
    communityquery.cpp \
    infodispaly.cpp \
    infomgmt.cpp \
    interactivebuttonbase.cpp \
    main.cpp \
    community.cpp \
    personalcenter.cpp \
    quiwidget.cpp \
    sidehidelabel.cpp \
    slideshow.cpp \
    studentmgmt.cpp \
    sysconfig.cpp \
    user_login.cpp \
    user_register.cpp

HEADERS += \
    actionmgmt.h \
    clubmgmt.h \
    community.h \
    communityquery.h \
    infodispaly.h \
    infomgmt.h \
   interactivebuttonbase.h \
    personalcenter.h \
    quiwidget.h \
    sidehidelabel.h \
    slideshow.h \
    studentmgmt.h \
    sysconfig.h \
    toolHead.h \
    user_login.h \
    user_register.h

FORMS += \
    actionmgmt.ui \
    clubmgmt.ui \
    community.ui \
    communityquery.ui \
    infodispaly.ui \
    infomgmt.ui \
    personalcenter.ui \
    studentmgmt.ui \
    sysconfig.ui \
    user_login.ui \
    user_register.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    demo.qrc

DISTFILES += \
    images/img1.jpg \
    images/img2.jpg \
    images/img3.jpg \
    images/img4.jpg \
    images/img5.jpg \
