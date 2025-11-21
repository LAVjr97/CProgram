QT       += core gui
QT += printsupport

RC_ICONS = resources/app_ico.ico

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    customer.cpp \
    date.cpp \
    file.cpp \
    levenshtein.cpp \
    logger.cpp \
    main.cpp \
    mainwindow.cpp \
    order.cpp \
    pieces.cpp \
    search.cpp \
    service.cpp \
    ui_admin.cpp \
    ui_dropoff.cpp \
    ui_init.cpp \
    ui_pickup.cpp \
    ui_util.cpp

HEADERS += \
    customer.h \
    date.h \
    file.h \
    levenshtein.h \
    logger.h \
    main.h \
    mainwindow.h \
    order.h \
    pieces.h \
    search.h \
    service.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    customers.txt \
    orders.txt \
    prices.txt \
    temp.txt \
    temp.txt \
    todo.txt

RESOURCES += \
    resources.qrc
