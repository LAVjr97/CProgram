#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "handle.h"

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

     manager = new fi::File(customerFile, orderFile, tempFile, this->customers, this->orders);

    //Indepently load up customers and orders
    std::thread threadCust(&fi::File::loadCustomers, manager);
    std::thread threadOrder(&fi::File::loadOrders, manager);

    threadCust.join();
    threadOrder.join();

    lau = 0;
    dc = 0;
    alt = 0;

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
    lineCustomerIDDP = ui->lineCustomerIDDP;
    lineDropOffDP = ui->lineDropOffDP;
    lineFNameDP = ui->lineFNameDP;
    lineLNameDP = ui->lineLNameDP;
    lineOrderIDDP = ui->lineOrderIDDP;
    linePhoneDP = ui->linePhoneDP;
    linePickUpDP = ui->linePickUpDP;

    tableViewOrdersDP = new QTableView(this);

    modelDP = new QStandardItemModel(this);
    modelDP->setColumnCount(5);
    modelDP->setHorizontalHeaderLabels({"Number", "Type", "Piece", "Price Per Piece", "Price Total"});

    ui->tableViewOrdersDP->setModel(modelDP);
    ui->tableViewOrdersDP->resizeColumnsToContents();

    //connect(tableViewCSR, &QTableView::entered, this, &MainWindow::on)

    /*
    connect(ui->btnSaveDP, &QPushButton::clicked, this, [this, &manager](){
        custom_on_btnSaveDP_clicked(manager);
    });
    */



    //
    //Search Customer Page
    //
    lineSearchCustomerCS = ui->lineSearchCustomerCS;

    connect(lineSearchCustomerCS, &QLineEdit::returnPressed, this, &MainWindow::on_btnSearchCS_clicked);

    //
    //Search Customer Results Page
    //
    tableViewCSR = new QTableView(this);

    modelCSR = new QStandardItemModel(this);
    modelCSR->setColumnCount(3);
    modelCSR->setHorizontalHeaderLabels({"First Name", "Last Name", "Phone Number"});

    //ui->tableViewCSR->setModel(modelCSR);
    ui->tableViewCSR->setModel(modelCSR);
    ui->tableViewCSR->resizeColumnsToContents();

    //connect(tableViewCSR, &QTableView::entered, this, &MainWindow::on_btnSearchCS_clicked);

    //
    //New Customer Page
    //
    lineFNameNC = ui -> lineFNameNC;
    lineLNameNC = ui -> lineLNameNC;
    linePhoneNC = ui -> linePhoneNC;


    //
    //Order Laundry Page
    //

    //Shirts
    lineLaundryPriceShirts = ui->lineLaundryPriceShirts;
    spinLaundryShirts = ui->spinLaundryShirts;

    //Pants
    lineLaundryPricePants = ui -> lineLaundryPricePants;
    spinLaundryPants = ui -> spinLaundryPants;

    //
    //connect buttons to slots
    //
    /*
    connect(ui->btnCreate, &QPushButton::clicked, this, [this, manager](){
        custom_on_btnCreate_clicked(manager);
    });
    */
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

//
//Drop Off Page
//

void MainWindow::updateDropOffPage(){

}

void MainWindow::on_btnCustomer_clicked()
{
    MainWindow::showSearchPage();
}

void MainWindow::on_btnLaundry_clicked()
{
    if(lineFNameDP->text().isEmpty())
        return;

    //Assign prices
    lineLaundryPriceShirts->setText(QString::number(4.99));
    lineLaundryPricePants->setText(QString::number(5.99));


    MainWindow::showOrderLaundryPage();
}

void MainWindow::on_btnSaveDP_clicked()//fi::File &manager)
{
    //size_t orderID = orders.size() - 1; //really the real order ID is just order.size() but because the size changed with the latest order, it must be subtracted

    customer[0]->setLatestOrder(curOrderID);
    customer[0]->updateVisits(customer[0]->getVisit() + 1);

    orders[curOrderID].calculateCost();

    manager->saveOrders(orders[curOrderID]);
    manager->updateCustomer(customer[0]->getCustomerID());

    customer.clear();
    order.clear();

    MainWindow::showMainPage();
    clearScreenDP();
}

void MainWindow::on_btnReturn_clicked()
{
    MainWindow::showMainPage();
    customer.clear();
    order.clear();
    clearScreenDP();
}

void MainWindow::clearScreenDP(){
    modelDP -> removeRows(0, modelDP -> rowCount());
    lineFNameDP -> clear();
    lineLNameDP -> clear();
    linePhoneDP -> clear();
    lineDropOffDP -> clear();
    linePickUpDP->clear();
    lineCustomerIDDP->clear();
    lineOrderIDDP->clear();
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

void MainWindow::showOrderLaundryPage(){
    ui->stackedWidget->setCurrentIndex(5);
}

void MainWindow::showOrderDryCleanPage(){
    ui->stackedWidget->setCurrentIndex(6);
}

void MainWindow::showOrderAlterationsPage(){
    ui->stackedWidget->setCurrentIndex(7);
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
    //search::Search search;
    size_t i;
    customer.clear();

    //Makes sure that the line entry isnt empyt before continuing
    entryQ = lineSearchCustomerCS -> text();
    if(entryQ.isEmpty())
        return;

    entry = entryQ.toStdString();

    if(search::Search::isPhoneNumber(entry) || search::Search::isName(entry))
        customer = search::Search::searchCustAlgo(entry, this->customers);

    //look at latest chatgpt to get context for how to populate list view model

    for(i = 0; i < customer.size(); i++){
        //QString itemText = QString("%1, %2").arg(QString::fromStdString(customer[i]->getName())).arg(QString::fromStdString(customer[i]->getPhone()));
        //QStandardItem *item = new QStandardItem(itemText);
        //this->modelCSR->appendRow(item);
        QStandardItem *firstNameItem = new QStandardItem(QString::fromStdString(customer[i]->getFirstName()));
        QStandardItem *lastNameItem = new QStandardItem(QString::fromStdString(customer[i]->getLastName()));
        QStandardItem *phoneItem = new QStandardItem(QString::fromStdString(customer[i]->getPhone()));

        modelCSR->setItem(i, 0, firstNameItem);
        modelCSR->setItem(i, 1, lastNameItem);
        modelCSR->setItem(i, 2, phoneItem);
    }

    tableViewCSR -> setColumnWidth(0, 300);
    tableViewCSR -> setColumnWidth(1, 300);
    tableViewCSR -> setColumnWidth(2, 300);
    tableViewCSR -> setSelectionBehavior(QAbstractItemView::SelectRows);

    MainWindow::showCustomerSearchResultsPage();

}




//
//Customer Search Results Page (3)
//
void MainWindow::on_btnReturnCSR_clicked()
{
    modelCSR -> removeRows(0, modelCSR -> rowCount());
    MainWindow::showSearchPage();
}

void MainWindow::on_tableViewCSR_clicked(const QModelIndex &index)
{
    cust::customer* temp = customer[index.row()];
    curOrderID = orders.size();
    //cout << std::endl << "custom_on_tableViewCSR_Clicked" << i << std::endl;

    lineFNameDP -> setText(QString::fromStdString(temp->getFirstName()));
    lineLNameDP -> setText(QString::fromStdString(temp->getLastName()));
    linePhoneDP -> setText(QString::fromStdString(temp->getPhone()));
    lineCustomerIDDP->setText(QString::number(temp->getCustomerID()));

    modelCSR -> removeRows(0, modelCSR -> rowCount());
    customer.clear();
    customer.push_back(temp); //Customer contains the pointer that points to the current customer that will be worked on

    lineSearchCustomerCS ->clear(); //search entry from the customer search page, clears so it looks cleaner

    //customer[0]->setLatestOrder(orderID);

    //Add order to orders
    orders.emplace_back(customer[0]->getCustomerID(), curOrderID);
    order.push_back(&orders[curOrderID]);

    lineDropOffDP->setText(QString::fromStdString(order[0]->dropOff->getDate_Time()));
    linePickUpDP->setText(QString::fromStdString(order[0]->pickUp->getDate_Time()));
    lineOrderIDDP->setText(QString::number(curOrderID));

    MainWindow::showDropOffPage();
}




//
//New Customer Page (4)
//
void MainWindow::on_btnReturn_3_clicked()
{
    MainWindow::showSearchPage();
}

/*
void MainWindow::on_btnCreate_clicked()
{

}
*/

void MainWindow::on_btnCreate_clicked(){//(fi::File &manager){
    int customerID;
    curOrderID = orders.size();
    QString firstName, lastName, phone;

    firstName = lineFNameNC ->text();
    lastName = lineLNameNC -> text();
    phone = linePhoneNC -> text();

    //Setting up the new customer and updating the file
    customerID = customers.size();
    customers.emplace_back(customerID, firstName.toStdString(), lastName.toStdString(), phone.toStdString());
    customer.push_back(&customers[customerID]); //contains only the customer that will be worked on
    manager->saveCustomers(customers[customerID]);

    //Creating a new order object
    orders.emplace_back(customerID, curOrderID);
    order.push_back(&orders[curOrderID]);

    std::cout << "\nafter creating customer\n";

    //Update on-screen information
    lineFNameDP->setText(QString::fromStdString(customers[customerID].getFirstName()));
    lineLNameDP->setText(QString::fromStdString(customers[customerID].getLastName()));
    linePhoneDP->setText(QString::fromStdString(customers[customerID].getPhone()));
    lineCustomerIDDP->setText(QString::number(customerID));
    lineDropOffDP->setText(QString::fromStdString(order[0]->dropOff->getDate_Time()));
    linePickUpDP->setText(QString::fromStdString(order[0]->pickUp->getDate_Time()));
    lineOrderIDDP->setText(QString::number(curOrderID));

    MainWindow::showDropOffPage();
}




//
//Laundry Order Page (5)
//



void MainWindow::on_btnLaundryReturn_clicked()
{
    if(!spinLaundryShirts -> value() && !spinLaundryPants -> value()){
        MainWindow::showDropOffPage();
        return;
    }

    double pTotal;
    QString pieces[] = {"Shirts", "Pants", "Sweaters", "Coats", "Blouses", "2pc Suit", "Jacket", "Vest"};
    size_t i, j, temp = 0;
    std::vector<std::vector<std::pair<int, double>>> laundry = order[curOrderID]->getDetails();
    QStandardItem *number, *type, *piece, *pricePerPiece, *priceTotal;

    modelDP -> removeRows(0, modelDP->rowCount());

    for(i = 0; i < laundry.size(); i++)
        if(laundry[i].empty() == false)
            for(j = 0; j < laundry[i].size(); j++){
                number = new QStandardItem(QString::number(laundry[i][j].first));
                type = new QStandardItem("Laundry");
                piece = new QStandardItem(pieces[i]);
                pricePerPiece = new QStandardItem(QString::number(laundry[i][j].second));
                pTotal = laundry[i][j].first * laundry[i][j].second;
                priceTotal = new QStandardItem(QString::number(pTotal));

                modelDP->setItem(temp, 0, number);
                modelDP->setItem(temp, 1, type);
                modelDP->setItem(temp, 2, piece);
                modelDP->setItem(temp, 3, pricePerPiece);
                modelDP->setItem(temp, 4, priceTotal);

                temp++;
            }

    this->lau = temp;

    MainWindow::showDropOffPage();
}


void MainWindow::on_btnLaundryShirts_clicked(){
    double price;
    int n, shirts = 0;
    bool foundPrice;

    price = lineLaundryPriceShirts -> text().toDouble();
    n = spinLaundryShirts -> value();

    if(n == 0)
        return;

    foundPrice = order[0]->setLaundryPiece(shirts, n, price);

    //Updates the number in the spinBox if
    if(foundPrice == true){
        n = orders[curOrderID].getLaundryNumber(shirts, price);
        spinLaundryPants->setValue(n);
    }
}

void MainWindow::on_btnLaundryPants_clicked()
{
    double price;
    int n, pants = 1;
    bool foundPrice;

    price = lineLaundryPricePants -> text().toDouble();
    n = spinLaundryPants -> value();

    if(n == 0)
        return;

    foundPrice = order[0]->setLaundryPiece(pants, n, price);

    //Updates the number in the spinBox if
    if(foundPrice == true){
        n = orders[curOrderID].getLaundryNumber(pants, price);
        spinLaundryPants->setValue(n);
    }

}




//
//Get Functions
//



