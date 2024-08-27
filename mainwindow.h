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
#include "spinboxdelegate.h"
#include "qstackedwidget.h"
#include <QStandardItemModel>
#include <QStandardItem>
#include <QTableView>
#include <QCheckBox>
#include <QTableWidget>

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

    /*
    std::vector<std::vector<std::pair<std::string, double>>> *laundryPrices;
    std::vector<std::vector<std::pair<std::string, double>>> *dryCleanPrices;
    std::vector<std::vector<std::pair<std::string, double>>> *alterationsPrices;
    */
private slots:
    void updateDropOffPage();

    //Main Page
    void on_btnDropOff_clicked();
    void on_btnPickUp_clicked();


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
    void showPickUpPage();
    void showCustomerSearchPagePU();
    void showOrderSearchPagePU();


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
    //New Customer Page (4)
    //

    void clearScreenNC();

    //
    //Order Laundry Page(5)
    //
    void setUpLaundryPage();
    void setLaundryPage();
    void on_btnLaundryReturn_clicked();

    //Shirts
    void on_btnLaundryShirts_clicked();

    //Pants
    void on_btnLaundryPants_clicked();


    //
    //Pick Up Page()
    //
    void on_btnCustomerPU_clicked();
    void on_btnOrderSearchPU_clicked();
    void on_btnSavePU_clicked();
    void on_btnReturnPU_clicked();





    //
    //Order Search Page PU()
    //
    void on_btnReturnOS_clicked();
    void on_btnSearchOrderOS_clicked();

    //Help functions
    void clearScreenDP();
    void clearScreenPU();
    void updateCOInformationDP();
    size_t updateTableView(std::vector<std::vector<std::pair<int, double>>> articles, QStandardItemModel *model, QString pieceType, size_t row);

private:
    Ui::MainWindow *ui;

    std::vector<std::vector<std::pair<std::string, double>>> laundryPrices;
    std::vector<std::vector<std::pair<std::string, double>>> dryCleanPrices;
    std::vector<std::vector<std::pair<std::string, double>>> alterationsPrices;

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
    QLineEdit *lineOrderTotalDP;

    QCheckBox *checkBoxPaidDP;

    QStandardItemModel *modelDP;
    QTableView *tableViewOrdersDP;
    QHeaderView* headerTVODP;

    //
    //PickUp Page
    //
    QLineEdit *lineCustomerIDPU;
    QLineEdit *lineDropOffPU;
    QLineEdit *lineFNamePU;
    QLineEdit *lineLNamePU;
    QLineEdit *lineOrderIDPU;
    QLineEdit *linePhonePU;
    QLineEdit *linePickUpPU;
    QLineEdit *lineOrderTotalPU;
    QLineEdit *lineRackPU;

    QCheckBox *checkBoxPUPU;
    QCheckBox *checkBoxPaidPU;

    QStandardItemModel *modelPU;
    QTableView *tableViewOrdersPU;

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

    QTableWidget *tableWidgetLaundryOptions;
    sbd::SpinBoxDelegate *spinBoxDelegate;
    QStandardItemModel *modelOL;


    //Shirts
    QLineEdit *lineLaundryPriceShirts;
    QSpinBox *spinLaundryShirts;
    QDoubleSpinBox *spinLaundryPriceShirts;

    //Pants
    QLineEdit *lineLaundryPricePants;
    QSpinBox *spinLaundryPants;

    //
    //Order Search PagePU
    //
    QLineEdit *lineSearchOrderIDOS;

};
#endif // MAINWINDOW_H
