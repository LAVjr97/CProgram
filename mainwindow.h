#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dropoffpage.h"
#include "customersearchpage.h"
#include "customer.h"
#include "order.h"
#include "qstackedwidget.h"

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
    std::unordered_map<int, std::vector<orderInfo::order>>& getOrders();
    std::vector<cust::customer>& getCustomers();


private slots:
    void on_btnDropOff_clicked();

    void on_btnLaundry_clicked();

    void on_btnCustomer_clicked();

    void on_btnReturn_clicked();

    void showMainPage();

    void showDropOffPage();

    void showSearchPage();

    void on_btnReturn_2_clicked();

    void on_btnNewCustomerPg_clicked();

    void on_btnReturn_3_clicked();

private:
    Ui::MainWindow *ui;

    //Stacked Widget
    QStackedWidget *stackedWidget;

    //Pages
    DropOffPage *dropOffPage;
    CustomerSearchPage *customerSearchPage;

    //Data Structures to hold the
    std::unordered_map<int, std::vector<orderInfo::order>> orders;
    std::vector<cust::customer> customers;
};
#endif // MAINWINDOW_H
