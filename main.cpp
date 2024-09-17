#include "mainwindow.h"
#include "main.h"
#include "customer.h"
#include "order.h"

#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QString lockFilePath = QStandardPaths::writableLocation(QStandardPaths::TempLocation) + "/MyApp.lock";
    QLockFile lockFile(lockFilePath);
    lockFile.setStaleLockTime(30000);
    if(!lockFile.tryLock()){
        QMessageBox::warning(nullptr, "Warning", "Application is already runnning");
        return 0;
    }

    app.setStyle("windows");
    app.setWindowIcon(QIcon(":/images/app_icon.png"));

    MainWindow w;
    w.show();
    return app.exec();
}
