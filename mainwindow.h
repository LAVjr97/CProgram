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
#include <QDateTimeEdit>
#include <QDateTime>
#include <QDate>
#include <QTime>
#include <QPrinter>
#include <QPainter>
#include <QPrintDialog>

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

    QPrinter printer;
    QPainter painter;

    /*
    std::vector<std::vector<std::pair<std::string, double>>> *laundryPrices;
    std::vector<std::vector<std::pair<std::string, double>>> *dryCleanPrices;
    std::vector<std::vector<std::pair<std::string, double>>> *alterationsPrices;
    */
private slots:
    //Main Page
    void on_btnDropOff_clicked();
    void on_btnPickUp_clicked();
    void on_btnEditOrder_clicked();

    void on_btnLaundry_clicked();
    void on_btnDryClean_clicked();
    void on_btnAlterations_clicked();

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
    void showCustomerSearchResultsPU();
    void showOrderSearchResultsPU();
    void showEditOrderPage();
    void showOrderSearchPageEO();
    void showCustomerSearchPageEO();
    void showCustomerSearchResultsEO();
    void showOrderSearchResultsEO();

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
    void on_btnLaundryReturn_clicked();
    void on_tableWidgetLaundryOptions_clicked(const QModelIndex &index);

    //
    //Order DryClean Page()
    //
    void setUpDryCleanPage();
    void on_btnDryCleanReturn_clicked();
    void on_tableWidgetDryCleanOptions_clicked(const QModelIndex &index);

    //
    //Order Alterations Page()
    //
    void setUpAlterationsPage();
    void on_btnAlterationsReturn_clicked();
    void on_tableWidgetAlterationsOptions_clicked(const QModelIndex &index);

    //
    //Pick Up Page()
    //
    void on_btnCustomerPU_clicked();
    void on_btnOrderSearchPU_clicked();
    void on_btnSavePU_clicked();
    void on_btnReturnPU_clicked();

    //
    //Customer Search Page PU()
    //
    void on_btnReturnCSPU_clicked();
    void on_btnSearchCSPU_clicked();

    //
    //Order Search Page PU(8)
    //
    void on_btnReturnOS_clicked();
    void on_btnSearchOrderOS_clicked();

    //
    //Customer Search ResultsPU (11)
    //
    void on_btnReturnCSRPU_clicked();
    void on_tableViewCSRPU_clicked(const QModelIndex &index);

    //
    //Order Search ResultsPU (12)
    //
    void on_btnReturnOSR_clicked();
    void on_tableViewOSR_clicked(const QModelIndex &index);

    //Edit Order Page (13)
    void on_btnCustomerEO_clicked();
    void on_btnOrderSearchEO_clicked();
    void on_btnSaveEO_clicked();
    void on_btnReturnEO_clicked();

    //Order Search EO Page (14)
    void on_btnReturnOSEO_clicked();
    void on_btnSearchOrderEO_clicked();

    //Customer Search Page (15)
    void on_btnReturnCSEO_clicked();
    void on_btnSearchCSEO_clicked();

    //Customer Search Results Page (16)
    void on_btnReturnCSREO_clicked();
    void on_tableViewCSREO_clicked(const QModelIndex &index);

    //Order Search Results EO Page (17)
    void on_btnReturnOSREO_clicked();
    void on_tableViewOSREO_clicked(const QModelIndex &index);


    //Help functions
    void clearScreenDP();
    void clearScreenPU();
    void clearScreenEO();

    void updateCOInformationDP();
    void updateCOInformationPU();
    void updateCOInformationEO();

    void setDate(QDateTimeEdit *dp, QDateTimeEdit *pu);

    void updateModel(QStandardItemModel *model);
    size_t updateTableView(std::vector<std::vector<std::tuple<std::string, int, double>>> articles, QStandardItemModel *model, QString pieceType, size_t row);

    std::string getTypeName(int curRow, std::vector<std::tuple<std::string, int, int>> articlePos);
    size_t getIndex(int curRow, std::vector<std::tuple<std::string, int, int>> articlePos);

    int calculateSize(std::vector<std::vector<std::pair<std::string, double>>> prices);
    int calculatePieceTotal(std::vector<std::vector<std::tuple<std::string, int, double>>> articles);

    void printReciept();

private:
    Ui::MainWindow *ui;

    std::vector<std::vector<std::pair<std::string, double>>> laundryPrices;
    std::vector<std::vector<std::pair<std::string, double>>> dryCleanPrices;
    std::vector<std::vector<std::pair<std::string, double>>> alterationsPrices;

    std::vector<std::tuple<std::string, int, int>> laundryPos;
    std::vector<std::tuple<std::string, int, int>> dryCleanPos;
    std::vector<std::tuple<std::string, int, int>> alterationsPos;

    size_t lPrices;
    size_t dcPrices;
    size_t aPrices;

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
    QDateTimeEdit *dateDTDropOffDP;
    QDateTimeEdit *dateDTPickUpDP;

    QCheckBox *checkBoxPaidDP;

    QStandardItemModel *modelDP;
    QTableView *tableViewOrdersDP;
    QHeaderView* headerTVODP;

    //
    //PickUp Page
    //
    QLineEdit *lineCustomerIDPU;
    QLineEdit *lineFNamePU;
    QLineEdit *lineLNamePU;
    QLineEdit *lineOrderIDPU;
    QLineEdit *linePhonePU;
    QLineEdit *lineOrderTotalPU;
    QLineEdit *lineRackPU;
    QDateTimeEdit *dateDTDropOffPU;
    QDateTimeEdit *dateDTPickUpPU;

    QCheckBox *checkBoxPUPU;
    QCheckBox *checkBoxPaidPU;

    QStandardItemModel *modelPU;
    QTableView *tableViewOrdersPU;

    //
    //Edit Order Page
    //
    QLineEdit *lineCustomerIDEO;
    QLineEdit *lineFNameEO;
    QLineEdit *lineLNameEO;
    QLineEdit *lineOrderIDEO;
    QLineEdit *linePhoneEO;
    QLineEdit *lineOrderTotalEO;
    QLineEdit *lineRackEO;
    QDateTimeEdit *dateDTDropOffEO;
    QDateTimeEdit *dateDTPickUpEO;

    QCheckBox *checkBoxPUEO;
    QCheckBox *checkBoxPaidEO;

    QStandardItemModel *modelEO;
    QTableView *tableViewOrdersEO;


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

    //Order Laundry Page
    QTableWidget *tableWidgetLaundryOptions;

    //Order DryClean Page()
    QTableWidget *tableWidgetDryCleanOptions;

    //Order Alterations Page()
    QTableWidget *tableWidgetAlterationsOptions;




    //Customer Search PagePU ()
    QLineEdit *lineSearchCustomerCSPU;
    QTableView *tableViewCSRPU;

    //Order Search PagePU ()
    QLineEdit *lineSearchOrderIDOS;
    QStandardItemModel *modelCSRPU;

    //Order Search Page ResultsPU
    QTableView *tableViewOSR;
    QStandardItemModel *modelOSR;

    //
    //Edit Order Page ()
    //

    //Order Search PageEO()
    QLineEdit *lineSearchOrderIDEO;

    //Customer Search PageEO ()
    QLineEdit *lineSearchCustomerCSEO;

    //Customer Search Results PageEO()
    QTableView *tableViewCSREO;
    QStandardItemModel *modelCSREO;

    //Order Search Page Results ();
    QTableView *tableViewOSREO;
    QStandardItemModel *modelOSREO;

};
#endif // MAINWINDOW_H
