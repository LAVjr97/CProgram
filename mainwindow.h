#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include "main.h"
#include "customer.h"
#include "order.h"
#include "file.h"
#include "qstackedwidget.h"
#include <QStandardItemModel>
#include <QStandardItem>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    std::vector<orderInfo::order> orders;
    std::vector<cust::customer> customers;

private slots:
    void updateDropOffPage();

    void on_btnDropOff_clicked();

    void on_btnLaundry_clicked();

    void on_btnCustomer_clicked();

    void on_btnReturn_clicked();

    void showMainPage();

    void showDropOffPage();

    void showSearchPage();

    void showCustomerSearchResultsPage();

    void showNewCustomerPage();

    void on_btnReturnCS_clicked();

    void on_btnNewCustomersCS_clicked();

    void on_btnReturn_3_clicked();

    void on_btnCreate_clicked();

    //
    //Custom Private Slots For...
    //

    //Customer Search Page
    void custom_on_btnCreate_clicked(fi::File &manager);

    //Customer Search Results
    //void custom_on_btnSearchCS_clicked(fi::File &manager);

    void on_btnReturnCSR_clicked();

    void on_btnSearchCS_clicked();

private:
    Ui::MainWindow *ui;

    //Stacked Widget
    QStackedWidget *stackedWidget;

    //Pages

    //Data Structures to hold the

    //
    //DropOffPage
    //
    QLineEdit *lineCustomerIDDP;
    QLineEdit *lineDropOffDP;
    QLineEdit *lineFNameDP;
    QLineEdit *lineLNameDP;
    QLineEdit *lineOrderIDDP;
    QLineEdit *linePhoneDP;
    QLineEdit *linePickUpDP;

    QStandardItemModel *model;

    //
    //Customer Search Page
    //
    QLineEdit *lineSearchCustomerCS;

    QString lastName;
    QString phone;

    //
    //New Customer Page
    //
    QLineEdit *lineFNameNC;
    QLineEdit *lineLNameNC;
    QLineEdit *linePhoneNC;
};
#endif // MAINWINDOW_H
