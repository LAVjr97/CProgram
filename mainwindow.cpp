#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "handle.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>

//Mac: /Users/luisvillalta/CProgram
//Windows: C:/Code/repos/LAVjr97/CProgram/

//
//Constructor
//
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //Setting up database
    std::string customerFile = "C:/Code/repos/LAVjr97/CProgram/customers.txt";
    std::string orderFile = "C:/Code/repos/LAVjr97/CProgram/orders.txt";
    std::string tempFile = "C:/Code/repos/LAVjr97/CProgram/temp.txt";

    //vector<cust::customer> customers;
    //vector<orderInfo::order> orders;

    fi::File manager = fi::File(customerFile, orderFile, tempFile, this->customers, this->orders);

    //Indepently load up customers and orders
    std::thread threadCust(&fi::File::loadCustomers, &manager);
    std::thread threadOrder(&fi::File::loadOrders, &manager);

    threadCust.join();
    threadOrder.join();

    //Everything after this point is GUI related
    ui->setupUi(this);
    stackedWidget = new QStackedWidget(this);

    /*this->dropOffPage = new DropOffPage(this);
    this->dropOffPage->setDataStructures(&orders, &customers);

    stackedWidget->addWidget(this->dropOffPage);
    QPushButton *btnDropOff = new QPushButton("Drop Off", this);
    */

    //
    //Drop Off Page
    //
    lineCustomerIDDP = ui -> lineCustomerIDDP;
    lineDropOffDP = ui -> lineOrderIDDP;
    lineFNameDP = ui -> lineFNameDP;
    lineLNameDP = ui -> lineLNameDP;
    lineOrderIDDP = ui -> lineOrderIDDP;
    linePhoneDP = ui -> linePhoneDP;
    linePickUpDP = ui -> linePickUpDP;

    model = new QStandardItemModel(this);
    ui -> listViewDP ->setModel(model);

    //
    //Search Customer Page
    //
    lineSearchCustomerCS = ui -> lineSearchCustomerCS;

    //
    //new Customer Page
    //
    lineFNameNC = ui -> lineFNameNC;
    lineLNameNC = ui -> lineLNameNC;
    linePhoneNC = ui -> linePhoneNC;


    //
    //connect buttons to slots
    //

    connect(ui->btnCreate, &QPushButton::clicked, this, [this, &manager](){
        custom_on_btnCreate_clicked(manager);
    });
    //connect(btnDropOff, &QPushButton::clicked, this, &MainWindow::showDropOffPage);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//
//Main Home Page
//
void MainWindow::on_btnDropOff_clicked()
{
    MainWindow::showDropOffPage();
}


void MainWindow::on_btnLaundry_clicked()
{

}

//
//Drop Off Page
//

void MainWindow::updateDropOffPage(){

}

void MainWindow::on_btnCustomer_clicked()
{
    MainWindow::showSearchPage();

    //CustomerSelect custWindow;
    //custWindow.setModal(true);
    //custWindow.exec();
}


void MainWindow::on_btnReturn_clicked()
{
    MainWindow::showMainPage();
}

//
//Page Movement
//
void MainWindow::showMainPage(){
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::showDropOffPage(){
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::showSearchPage(){
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::showCustomerSearchResultsPage(){
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::showNewCustomerPage(){
    ui->stackedWidget->setCurrentIndex(4);
}

//
//Customer Search Page (2)
//
void MainWindow::on_btnReturnCS_clicked()
{
    MainWindow::showDropOffPage();
}

void MainWindow::on_btnNewCustomersCS_clicked()
{
    MainWindow::showNewCustomerPage();
}

void MainWindow::on_btnSearchCS_clicked()
{
    QString entryQ;
    std::string entry;
    search::Search search;

    std::vector<cust::customer> customer;

    //Makes sure that the line entry isnt empyt before continuing
    entryQ = lineSearchCustomerCS -> text();
    if(entryQ.isEmpty())
        return;

    entry = entryQ.toStdString();

    if(search::Search::isPhoneNumber(entry) || search::Search::isName(entry))
        search::Search::searchCustAlgo(entry, this->customers);

//look at latest chatgpt to get context for how to populate list view model

    MainWindow::showCustomerSearchResultsPage();


}


//
//Customer Search Results Page (3)
//
void MainWindow::on_btnReturnCSR_clicked()
{
    MainWindow::showSearchPage();
}



//
//New Customer Page (4)
//
void MainWindow::on_btnReturn_3_clicked()
{
    MainWindow::showSearchPage();
}

void MainWindow::on_btnCreate_clicked()
{

}

void MainWindow::custom_on_btnCreate_clicked(fi::File &manager){
    int customerID;
    QString firstName, lastName, phone;
    firstName = lineFNameNC ->text();
    lastName = lineLNameNC -> text();
    phone = linePhoneNC -> text();

    customerID = this->customers.size();
    this->customers.emplace_back(customerID, firstName.toStdString(), lastName.toStdString(), phone.toStdString());

    manager.saveCustomers(this->customers[customerID]);

    std::cout << "\nafter creating customer\n";

    lineFNameDP->setText(QString::fromStdString(customers[customerID].getFirstName()));
    lineLNameDP->setText(QString::fromStdString(customers[customerID].getLastName()));
    linePhoneDP->setText(QString::fromStdString(customers[customerID].getPhone()));
    lineCustomerIDDP->setText(QString::number(customers[customerID].getCustomerID()));

    MainWindow::showDropOffPage();
}
//
//Get Functions
//



