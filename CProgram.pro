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
    dropoffpage.cpp \
    file.cpp \
    handle.cpp \
    main.cpp \
    mainwindow.cpp \
    order.cpp \
    search.cpp \
    spinboxdelegate.cpp

HEADERS += \
    customer.h \
    date.h \
    dropoffpage.h \
    file.h \
    handle.h \
    main.h \
    mainwindow.h \
    order.h \
    search.h \
    spinboxdelegate.h

FORMS += \
    dropoffpage.ui \
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
