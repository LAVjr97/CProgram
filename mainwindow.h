#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QSpinBox>
#include "main.h"
#include "customer.h"
#include "order.h"
#include "file.h"
#include "search.h"
#include "qstackedwidget.h"
#include <QStandardItemModel>
#include <QStandardItem>
#include <QTableView>

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

    std::vector<cust::customer*> customer;
    std::vector<orderInfo::order*> order;
    fi::File* manager;

private slots:
    void updateDropOffPage();

    void on_btnDropOff_clicked();

    void on_btnLaundry_clicked();

    void on_btnCustomer_clicked();

    void on_btnReturn_clicked();

    void on_btnSaveDP_clicked();//fi::File &manager);

    //Page Movement
    void showMainPage();

    void showDropOffPage();

    void showSearchPage();

    void showCustomerSearchResultsPage();

    void showNewCustomerPage();

    void showOrderLaundryPage();

    void showOrderDryCleanPage();

    void showOrderAlterationsPage();



    void on_btnReturnCS_clicked();

    void on_btnNewCustomersCS_clicked();

    void on_btnReturn_3_clicked();

    void on_btnCreate_clicked();

    //
    //Custom Private Slots For...
    //

    //Customer Search Page
    //void custom_on_btnCreate_clicked(fi::File &manager);

    //Customer Search Results
    //void custom_on_btnSearchCS_clicked(fi::File &manager);
    //void custom_on_tableViewCSR_Row_Clicked(const QModelIndex &index);

    void on_btnReturnCSR_clicked();

    void on_btnSearchCS_clicked();

    void on_tableViewCSR_clicked(const QModelIndex &index);




    //
    //Order Laundry Page(5)
    //
    void on_btnLaundryReturn_clicked();

    //Shirts
    void on_btnLaundryShirts_clicked();

    //Pants
    void on_btnLaundryPants_clicked();


    //Help functions
    void clearScreenDP();

private:
    Ui::MainWindow *ui;

    size_t curOrderID, lau, dc, alt;

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

    QStandardItemModel *modelDP;
    QTableView *tableViewOrdersDP;


    //
    //Customer Search Page
    //
    QLineEdit *lineSearchCustomerCS;

    QString lastName;
    QString phone;

    //
    //Custome Search Resutls Page
    //
    QStandardItemModel *modelCSR;
    QTableView *tableViewCSR;

    //
    //New Customer Page
    //
    QLineEdit *lineFNameNC;
    QLineEdit *lineLNameNC;
    QLineEdit *linePhoneNC;

    //
    //Order Laundry Page
    //

    //Shirts
    QLineEdit *lineLaundryPriceShirts;
    QSpinBox *spinLaundryShirts;

    //Pants
    QLineEdit *lineLaundryPricePants;
    QSpinBox *spinLaundryPants;

};
#endif // MAINWINDOW_H
