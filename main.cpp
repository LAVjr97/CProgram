#include "mainwindow.h"
#include "main.h"
#include "customer.h"
#include "order.h"

#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
