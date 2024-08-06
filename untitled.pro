QT       += core gui
QT += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    add_auto.cpp \
    add_drivers.cpp \
    add_routes.cpp \
    attaching_auto.cpp \
    auto.cpp \
    client.cpp \
    del_auto.cpp \
    del_drivers.cpp \
    drivers.cpp \
    edit_auto.cpp \
    edit_drivers.cpp \
    main.cpp \
    mainwindow.cpp \
    roles.cpp \
    routes.cpp

HEADERS += \
    add_auto.h \
    add_drivers.h \
    add_routes.h \
    attaching_auto.h \
    auto.h \
    client.h \
    del_auto.h \
    del_drivers.h \
    drivers.h \
    edit_auto.h \
    edit_drivers.h \
    mainwindow.h \
    roles.h \
    routes.h

FORMS += \
    add_auto.ui \
    add_drivers.ui \
    add_routes.ui \
    attaching_auto.ui \
    auto.ui \
    client.ui \
    del_auto.ui \
    del_drivers.ui \
    drivers.ui \
    edit_auto.ui \
    edit_drivers.ui \
    mainwindow.ui \
    roles.ui \
    routes.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
