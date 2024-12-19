#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>

//Mac: /Users/luisvillalta/CProgram
//Windows: C:/Code/repos/LAVjr97/CProgram/


//
//***Constructor***
//
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Cleaning_and_Alteration_Shop)
{
    //Debug uses main folder, where source files are located, change file locations to just "[...].txt"

    //Setting up database
    ///*
    std::string customerFile = "./data/customers.txt";
    std::string orderFile = "./data/orders.txt";
    std::string priceFile = "./data/prices.txt";
    std::string tempOrderFile = "./data/tempOrder.txt";
    std::string tempCustFile = "./data/tempCust.txt";
    std::string logFile = "./logs/log.txt";
    //*/
    //Release versiom uses these file paths
    /*
    std::string customerFile = "customers.txt";
    std::string orderFile = "orders.txt";
    std::string priceFile = "prices.txt";
    std::string tempOrderFile = "tempOrder.txt";
    std::string tempCustFile = "tempCust.txt";
    std::string logFile = "log.txt";
    */
    manager = new fi::File(customerFile, orderFile, priceFile, tempOrderFile, tempCustFile, this->customers, this->orders, this->laundryPrices, this->dryCleanPrices, this->alterationsPrices, this->laundryPos, this->dryCleanPos, this->alterationsPos, logFile);
    /*
    manager->checkAndCreateFile(customerFile);
    manager->checkAndCreateFile(orderFile);
    manager->checkAndCreateFile(priceFile);
    manager->checkAndCreateFile(tempOrderFile);
    manager->checkAndCreateFile(tempCustFile);
    manager->checkAndCreateFile(logFile);
        */
    //Indepently load up customers, orders and prices
    std::thread threadCust(&fi::File::loadCustomers, manager);
    std::thread threadOrder(&fi::File::loadOrders, manager);
    std::thread threadPrices(&fi::File::loadPrices, manager);

    threadCust.join();
    threadOrder.join();
    threadPrices.join();

    curOrderID = 0;

    //Everything after this point is GUI related
    ui->setupUi(this);
    this->showMaximized();
    stackedWidget = ui->stackedWidget;

    //
    //Drop Off Page
    //
    lineCustomerIDDP = ui->lineCustomerIDDP;
    lineFNameDP = ui->lineFNameDP;
    lineLNameDP = ui->lineLNameDP;
    lineOrderIDDP = ui->lineOrderIDDP;
    linePhoneDP = ui->linePhoneDP;
    lineOrderTotalDP = ui->lineOrderTotalDP;
    lineVisitsDP = ui->lineVisitsDP;
    linePieceTotalDP = ui->linePieceTotalDP;
    lineOrderSubTotalDP = ui->lineOrderSubTotalDP;
    lineOrderDiscountDP = ui->lineOrderDiscountDP;
    checkBoxPaidDP = ui->checkBoxPaidDP;

    dateDTDropOffDP = ui->dateDTDropOffDP;
    dateDPickUpDP = ui->dateDPickUpDP;

    modelDP = new QStandardItemModel(this);
    modelDP->setColumnCount(5);
    modelDP->setHorizontalHeaderLabels({"Number", "Type", "Piece", "Price Per Piece", "Price Total"});

    tableViewOrdersDP = ui->tableViewOrdersDP;
    tableViewOrdersDP->setModel(modelDP);
    headerTVODP = tableViewOrdersDP->horizontalHeader();
    tableViewOrdersDP->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    //
    //Search Customer Page
    //
    lineSearchCustomerCS = ui->lineSearchCustomerCS;
    connect(lineSearchCustomerCS, &QLineEdit::returnPressed, this, &MainWindow::on_btnSearchCS_clicked);

    //
    //Search Customer Results Page
    //
    modelCSR = new QStandardItemModel(this);
    modelCSR->setColumnCount(3);
    modelCSR->setHorizontalHeaderLabels({"First Name", "Last Name", "Phone Number"});

    tableViewCSR = ui->tableViewCSR;
    tableViewCSR->setModel(modelCSR);
    tableViewCSR->resizeColumnsToContents();
    tableViewCSR -> setSelectionBehavior(QAbstractItemView::SelectRows);
    tableViewCSR->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    //connect(tableViewCSR, &QTableView::entered, this, &MainWindow::on_btnSearchCS_clicked);

    //
    //New Customer Page
    //
    lineFNameNC = ui -> lineFNameNC;
    lineLNameNC = ui -> lineLNameNC;
    linePhoneNC = ui -> linePhoneNC;

    //Order Laundry Page
    tableWidgetLaundryOptions = ui->tableWidgetLaundryOptions;
    tableWidgetLaundryOptions->setColumnCount(3);
    tableWidgetLaundryOptions->setColumnWidth(0, 345);
    tableWidgetLaundryOptions->setColumnWidth(1, 172);
    tableWidgetLaundryOptions->setColumnWidth(2, 172);

    //Order DryClean Page
    tableWidgetDryCleanOptions = ui->tableWidgetDryCleanOptions;
    tableWidgetDryCleanOptions->setColumnCount(3);
    tableWidgetDryCleanOptions->setColumnWidth(0, 345);
    tableWidgetDryCleanOptions->setColumnWidth(1, 172);
    tableWidgetDryCleanOptions->setColumnWidth(2, 172);

    //Order Alterations Page
    tableWidgetAlterationsOptions = ui->tableWidgetAlterationsOptions;
    tableWidgetAlterationsOptions->setColumnCount(3);
    tableWidgetAlterationsOptions->setColumnWidth(0, 345);
    tableWidgetAlterationsOptions->setColumnWidth(1, 172);
    tableWidgetAlterationsOptions->setColumnWidth(2, 172);

    //
    //Pick Up Page
    //
    lineCustomerIDPU = ui->lineCustomerIDPU;
    lineFNamePU = ui->lineFNamePU;
    lineLNamePU = ui->lineLNamePU;
    lineOrderIDPU = ui->lineOrderIDPU;
    linePhonePU = ui->linePhonePU;
    lineOrderTotalPU = ui->lineOrderTotalPU;
    lineRackPU = ui->lineRackPU;
    checkBoxPUPU = ui->checkBoxPUPU;
    checkBoxPaidPU = ui->checkBoxPaidPU;
    dateDTDropOffPU = ui->dateDTDropOffPU;
    dateDPickUpPU = ui->dateDPickUpPU;
    linePieceTotalPU = ui->linePieceTotalPU;
    lineOrderSubTotalPU = ui->lineOrderSubTotalPU;
    lineOrderDiscountPU = ui->lineOrderDiscountPU;


    modelPU = new QStandardItemModel(this);
    modelPU->setColumnCount(5);
    modelPU->setHorizontalHeaderLabels({"Number", "Type", "Piece", "Price Per Piece", "Price Total"});

    tableViewOrdersPU = ui->tableViewOrdersPU;
    tableViewOrdersPU->setModel(modelPU);
    tableViewOrdersPU->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    //
    //Customer Search PagePU
    //
    lineSearchCustomerCSPU = ui->lineSearchCustomerCSPU;
    connect(lineSearchCustomerCSPU, &QLineEdit::returnPressed, this, &MainWindow::on_btnSearchCSPU_clicked);

    //
    //Order Search PagePU
    //
    lineSearchOrderIDOS = ui->lineSearchOrderIDOS;
    connect(lineSearchOrderIDOS, &QLineEdit::returnPressed, this, &MainWindow::on_btnSearchOrderOS_clicked);

    //
    //***Customer Search ResultsPU (11)***
    //
    modelCSRPU = new QStandardItemModel(this);
    modelCSRPU->setColumnCount(3);
    modelCSRPU->setHorizontalHeaderLabels({"First Name", "Last Name", "Phone Number"});

    tableViewCSRPU = ui->tableViewCSRPU;
    tableViewCSRPU->setModel(modelCSR);
    tableViewCSRPU->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    //
    //Order Search ResultsPU
    //
    modelOSR = new QStandardItemModel(this);
    modelOSR->setColumnCount(5);
    modelOSR->setHorizontalHeaderLabels({"Order ID", "Drop Off", "Picked Up", "Pieces", "Total $"});

    tableViewOSR = ui->tableViewOSR;
    tableViewOSR->setModel(modelOSR);
    tableViewOSR->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableViewOSR -> setSelectionBehavior(QAbstractItemView::SelectRows);

    //
    //***Edit Order Page ()***
    //
    lineCustomerIDEO = ui->lineCustomerIDEO;
    lineFNameEO = ui->lineFNameEO;
    lineLNameEO = ui->lineLNameEO;
    lineOrderIDEO = ui->lineOrderIDEO;
    linePhoneEO = ui->linePhoneEO;
    lineOrderTotalEO = ui->lineOrderTotalEO;
    lineRackEO = ui->lineRackEO;
    checkBoxPUEO = ui->checkBoxPUEO;
    checkBoxPaidEO = ui->checkBoxPaidEO;
    dateDTDropOffEO = ui->dateDTDropOffEO;
    dateDPickUpEO = ui->dateDPickUpEO;
    linePieceTotalEO = ui->linePieceTotalEO;
    lineOrderSubTotalEO = ui->lineOrderSubTotalEO;
    lineOrderDiscountEO = ui->lineOrderDiscountEO;

    modelEO = new QStandardItemModel(this);
    modelEO->setColumnCount(5);
    modelEO->setHorizontalHeaderLabels({"Number", "Type", "Piece", "Price Per Piece", "Price Total"});

    tableViewOrdersEO = ui->tableViewOrdersEO;
    tableViewOrdersEO->setModel(modelEO);
    tableViewOrdersEO->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //
    //Order Search PageEO ()
    //
    lineSearchOrderIDEO = ui->lineSearchOrderIDEO;
    connect(lineSearchOrderIDEO, &QLineEdit::returnPressed, this, &MainWindow::on_btnSearchOrderEO_clicked);

    //
    //Customer Search PageEO ()
    //
    lineSearchCustomerCSEO = ui->lineSearchCustomerCSEO;
    connect(lineSearchCustomerCSEO, &QLineEdit::returnPressed, this, &MainWindow::on_btnSearchCSEO_clicked);

    //
    //***Customer Search ResultsEO ()***
    //
    modelCSREO = new QStandardItemModel(this);
    modelCSREO->setColumnCount(3);
    modelCSREO->setHorizontalHeaderLabels({"First Name", "Last Name", "Phone Number"});

    tableViewCSREO = ui->tableViewCSREO;
    tableViewCSREO->setModel(modelCSREO);
    tableViewCSREO->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    //
    //***Order Search ResultsEO ()***
    //
    modelOSREO = new QStandardItemModel(this);
    modelOSREO->setColumnCount(5);
    modelOSREO->setHorizontalHeaderLabels({"Order ID", "Drop Off", "Picked Up", "Pieces", "Total $"});

    tableViewOSREO = ui->tableViewOSREO;
    tableViewOSREO->setModel(modelOSREO);
    tableViewOSREO->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableViewOSREO -> setSelectionBehavior(QAbstractItemView::SelectRows);

    //
    //
    //
    tableWidgetLaundryCIP = ui->tableWidgetLaundryCIP;
    tableWidgetLaundryCIP->setColumnCount(2);
    tableWidgetLaundryCIP->setColumnWidth(0, 300);
    tableWidgetLaundryCIP->setColumnWidth(1, 125);


    tableWidgetDryCleanCIP = ui->tableWidgetDryCleanCIP;
    tableWidgetDryCleanCIP->setColumnCount(2);
    tableWidgetDryCleanCIP->setColumnWidth(0, 300);
    tableWidgetDryCleanCIP->setColumnWidth(1, 125);

    tableWidgetAlterationsCIP = ui->tableWidgetAlterationsCIP;
    tableWidgetAlterationsCIP->setColumnCount(2);
    tableWidgetAlterationsCIP->setColumnWidth(0, 300);
    tableWidgetAlterationsCIP->setColumnWidth(1, 125);

    showMainPage();
}

MainWindow::~MainWindow()
{
    delete ui;
}



//
//***Page Movement***
//
void MainWindow::showMainPage(){
    recentStackedWidgetIndex = ui->stackedWidget->currentIndex();
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::showDropOffPage(){
    recentStackedWidgetIndex = ui->stackedWidget->currentIndex();
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::showSearchPage(){
    recentStackedWidgetIndex = ui->stackedWidget->currentIndex();
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::showCustomerSearchResultsPage(){
    recentStackedWidgetIndex = ui->stackedWidget->currentIndex();
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::showNewCustomerPage(){
    recentStackedWidgetIndex = ui->stackedWidget->currentIndex();
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::showOrderLaundryPage(){
    recentStackedWidgetIndex = ui->stackedWidget->currentIndex();
    ui->stackedWidget->setCurrentIndex(5);
}

void MainWindow::showOrderDryCleanPage(){
    recentStackedWidgetIndex = ui->stackedWidget->currentIndex();
    ui->stackedWidget->setCurrentIndex(6);
}

void MainWindow::showOrderAlterationsPage(){
    recentStackedWidgetIndex = ui->stackedWidget->currentIndex();
    ui->stackedWidget->setCurrentIndex(7);
}

void MainWindow::showPickUpPage(){
    recentStackedWidgetIndex = ui->stackedWidget->currentIndex();
    ui->stackedWidget->setCurrentIndex(8);
}

void MainWindow::showCustomerSearchPagePU(){
    recentStackedWidgetIndex = ui->stackedWidget->currentIndex();
    ui->stackedWidget->setCurrentIndex(9);
}

void MainWindow::showOrderSearchPagePU(){
    recentStackedWidgetIndex = ui->stackedWidget->currentIndex();
    ui->stackedWidget->setCurrentIndex(10);
}

void MainWindow::showCustomerSearchResultsPU(){
    recentStackedWidgetIndex = ui->stackedWidget->currentIndex();
    ui->stackedWidget->setCurrentIndex(11);
}

void MainWindow::showOrderSearchResultsPU(){
    recentStackedWidgetIndex = ui->stackedWidget->currentIndex();
    ui->stackedWidget->setCurrentIndex(12);
}

void MainWindow::showEditOrderPage(){
    recentStackedWidgetIndex = ui->stackedWidget->currentIndex();
    ui->stackedWidget->setCurrentIndex(13);
}

void MainWindow::showOrderSearchPageEO(){
    recentStackedWidgetIndex = ui->stackedWidget->currentIndex();
    ui->stackedWidget->setCurrentIndex(14);
}

void MainWindow::showCustomerSearchPageEO(){
    recentStackedWidgetIndex = ui->stackedWidget->currentIndex();
    ui->stackedWidget->setCurrentIndex(15);
}

void MainWindow::showCustomerSearchResultsEO(){
    recentStackedWidgetIndex = ui->stackedWidget->currentIndex();
    ui->stackedWidget->setCurrentIndex(16);
}

void MainWindow::showOrderSearchResultsEO(){
    recentStackedWidgetIndex = ui->stackedWidget->currentIndex();
    ui->stackedWidget->setCurrentIndex(17);
}

void MainWindow::showAdminPage(){
    recentStackedWidgetIndex = ui->stackedWidget->currentIndex();
    ui->stackedWidget->setCurrentIndex(18);
}

void MainWindow::showItemsAndPricePage(){
    recentStackedWidgetIndex = ui->stackedWidget->currentIndex();
    ui->stackedWidget->setCurrentIndex(19);
}


//
//***Main Home Page (0)***
//
void MainWindow::on_btnDropOff_clicked(){
    dateDTDropOffDP->hide();
    dateDPickUpDP->hide();
    ui->btnOneRecieptDP->setEnabled(false);
    ui->btnTwoRecieptDP->setEnabled(false);
    order.clear();
    showDropOffPage();
}

void MainWindow::on_btnPickUp_clicked(){
    dateDTDropOffPU->hide();
    dateDPickUpPU->hide();
    order.clear();
    showPickUpPage();
}

void MainWindow::on_btnEditOrder_clicked(){
    dateDTDropOffEO->hide();
    dateDPickUpEO->hide();
    ui->btnOneRecieptEO->setEnabled(false);
    ui->btnTwoRecieptEO->setEnabled(false);
    order.clear();
    showEditOrderPage();
}

void MainWindow::on_btnAdmin_clicked(){
    showAdminPage();
}



//
//***Drop Off Page (1)***
//
void MainWindow::on_btnCustomer_clicked()
{
    if(!order.empty()){ //bug might be here
        orders.pop_back();
        order.clear();
        curOrderID = -1;
        clearScreenDP();


    }

    lineSearchCustomerCS->setFocus();
    MainWindow::showSearchPage();
}

void MainWindow::on_btnLaundry_clicked(){
    if(lineFNameDP->text().isEmpty())
        return;

    setUpOptionsTables(tableWidgetLaundryOptions, laundryPrices, laundryPos);

    MainWindow::showOrderLaundryPage();
    ui->btnOneRecieptDP->setEnabled(false);
    ui->btnTwoRecieptDP->setEnabled(false);
}

void MainWindow::on_btnDryClean_clicked(){
    if(lineFNameDP->text().isEmpty())
        return;

    setUpOptionsTables(tableWidgetDryCleanOptions, dryCleanPrices, dryCleanPos);

    MainWindow::showOrderDryCleanPage();
    ui->btnOneRecieptDP->setEnabled(false);
    ui->btnTwoRecieptDP->setEnabled(false);
}

void MainWindow::on_btnAlterations_clicked(){
    if(lineFNameDP->text().isEmpty())
        return;

    setUpOptionsTables(tableWidgetAlterationsOptions, alterationsPrices, alterationsPos);

    MainWindow::showOrderAlterationsPage();
    ui->btnOneRecieptDP->setEnabled(false);
    ui->btnTwoRecieptDP->setEnabled(false);
}

void MainWindow::on_btnSaveDP_clicked()
{
    if(lineFNameDP->text().isEmpty() || (!lineFNameDP->text().isEmpty() && modelDP->rowCount() == 0))
        return;

    saveModel(modelDP);
    updateModel(modelDP);

    linePieceTotalDP->setText(QString::number(order[0]->getPieceTotal()));
    lineOrderSubTotalDP->setText(QString::number(order[0]->getCost(), 'f', 2));
    lineOrderTotalDP->setText(QString::number(order[0]->getDiscountedCost(), 'f', 2));

    ui->btnOneRecieptDP->setEnabled(true);
    ui->btnTwoRecieptDP->setEnabled(true);

}

void MainWindow::on_btnOneRecieptDP_clicked(){
    //Add orderID to customer's orders
    customer[0]->setLatestOrder(curOrderID);
    customer[0]->updateVisits(customer[0]->getVisit() + 1);

    saveAndPrint(1, dateDPickUpDP, checkBoxPaidDP);
    clearScreenDP();

    showMainPage();
}

void MainWindow::on_btnTwoRecieptDP_clicked(){
    //Add orderID to customer's orders
    customer[0]->setLatestOrder(curOrderID);
    customer[0]->updateVisits(customer[0]->getVisit() + 1);

    //Setting Date
    saveAndPrint(2, dateDPickUpDP, checkBoxPaidDP);
    clearScreenDP();

    showMainPage();
    manager->logger->log("Two reciepts printed, order saved");
}

void MainWindow::on_btnApplyDiscountDP_clicked(){
    if(lineFNameDP->text().isEmpty())
        return;

    QInputDialog inputDialog(this, Qt::Dialog);
    bool ok;
    double discount;
    // QFont font = inputDialog.font();

    // inputDialog.setWindowTitle("Enter Discount Percentage");
    // inputDialog.setLabelText("Discount Percentage (%):");

    // font.setPointSize(14);
    // inputDialog.setFont(font);
    // inputDialog.setMinimumSize(400, 200); // Set minimum size
    // inputDialog.setMaximumSize(400, 200);  // Adjust width and height

    discount = inputDialog.getInt(this, tr("Enter Discount Percentage"), tr("Discount Percentage (%):"), 0, 0, 100, 1, &ok);

    if(ok){
        if(discount == 0){
            order[0]->setDiscount(0);
            order[0]->setDiscountApplied(false);
            lineOrderDiscountDP->setText("None");
        }
        else{
            order[0]->setDiscount(discount);
            order[0]->setDiscountApplied(true);
            lineOrderDiscountDP->setText(QString::number(discount) + "%");
        }
        lineOrderTotalDP->setText(QString::number(order[0]->getDiscountedCost(), 'f', 2)); //discountedCost will use applyDiscount() to update the cost
    }

}

void MainWindow::on_btnCIPDP_clicked(){
    showItemsAndPricePage();
}

void MainWindow::on_btnReturn_clicked(){
    showMainPage();
    //If customer information was pulled up but nothing was added to order, delete order
    //if(!lineFNameDP ->text().isEmpty() || (!lineFNameDP ->text().isEmpty() && ui->btnOneRecieptDP->isEnabled())){
    //if(!lineFNameDP ->text().isEmpty() && ui->btnOneRecieptDP->isEnabled()){
      //  orders.pop_back();
        //curOrderID--;
    //}


    curOrderID = -1;

    //Clear
    customer.clear();
    order.clear();
    clearScreenDP();
}



//
//***Customer Search Page (2)***
//
void MainWindow::on_btnReturnCS_clicked(){
    clearScreenDP();
    MainWindow::showDropOffPage();
    lineSearchCustomerCS -> clear();
}

void MainWindow::on_btnNewCustomersCS_clicked(){
    MainWindow::showNewCustomerPage();
    lineFNameNC->setFocus();
    lineSearchCustomerCS -> clear();
}

void MainWindow::on_btnSearchCS_clicked(){
    customerSearchPageSetUp(tableViewCSR, modelCSR, lineSearchCustomerCS);
    showCustomerSearchResultsPage();    
}

//
//***Customer Search Results Page (3)***
//
void MainWindow::on_btnReturnCSR_clicked(){
    modelCSR -> removeRows(0, modelCSR -> rowCount());
    showSearchPage();
}

void MainWindow::on_tableViewCSR_clicked(const QModelIndex &index){
    cust::customer* temp = customer[index.row()];
    curOrderID = orders.size();
    modelCSR -> removeRows(0, modelCSR -> rowCount());

    customer.clear();
    customer.push_back(temp); //Customer contains the pointer that points to the current customer that will be worked on

    lineSearchCustomerCS ->clear(); //search entry from the customer search page, clears so it looks cleaner

    if(orders[curOrderID - 1].getOrderID() == curOrderID){
        std::string message = "New OrderID: " + std::to_string(curOrderID) + " with CustomerID: " + std::to_string(customer[0]->getCustomerID()) +  " already exists, existing customerID is: " + std::to_string(orders[curOrderID - 1].getOrderID()) + " Occured in 'on_tableViewCSR_clicked'";
        manager->logger->log(message);
        handleCritcalError();
    }

    //Add order to orders
    orders.emplace_back(customer[0]->getCustomerID(), curOrderID);
    order.clear();
    order.push_back(&orders[curOrderID]);
    updateCOInformationDP();

    showDropOffPage();
}



//
//***New Customer Page (4)***
//
void MainWindow::on_btnReturn_3_clicked(){
    clearScreenDP();
    lineSearchCustomerCS->setFocus();
    MainWindow::showSearchPage();
    clearScreenNC();
}

void MainWindow::on_btnCreate_clicked(){//(fi::File &manager){
    if(lineFNameNC->text().isEmpty() || lineLNameNC->text().isEmpty() || linePhoneNC->text().isEmpty())
        return;

    int customerID;
    std::string firstName, lastName, phone;
    curOrderID = orders.size();

    firstName = lineFNameNC ->text().toStdString();
    lastName = lineLNameNC -> text().toStdString();
    phone = linePhoneNC -> text().toStdString();

    firstName = cust::customer::autoCapatilize(firstName);
    lastName = cust::customer::autoCapatilize(lastName);

    if(checkForDuplicates(firstName, lastName, phone))
        return;

    clearScreenNC();

    //Setting up the new customer
    customerID = customers.size();
    customers.emplace_back(customerID, firstName, lastName, phone);
    customer.clear();
    customer.push_back(&customers[customerID]); //contains only the customer that will be worked on

    if(orders[curOrderID - 1].getOrderID() == curOrderID){
        std::string message = "New OrderID: " + std::to_string(curOrderID) + " with CustomerID: " + std::to_string(customer[0]->getCustomerID()) +  " already exists, existing customerID is: " + std::to_string(orders[curOrderID - 1].getOrderID()) + " Occured in 'on_tableViewCSR_clicked'";
        manager->logger->log(message);
        handleCritcalError();
    }

    //Creating a new order object
    orders.emplace_back(customerID, curOrderID);
    order.clear();
    order.push_back(&orders[curOrderID]); //have only 1 order

    //Update on-screen information
    clearScreenDP();
    updateCOInformationDP();

    manager->saveCustomers(customers[customerID]);
    showDropOffPage();
}



//
//***Laundry Order Page (5)***
//

void MainWindow::on_btnLaundryReturn_clicked(){
    QSpinBox *spinBox;
    bool empty = true;

    if(modelDP->rowCount() == 0 && lineFNameDP->text().isEmpty()){
        showDropOffPage();
        return;
    }

    for(int row = 0; row < tableWidgetLaundryOptions->rowCount(); row++){
        spinBox = qobject_cast<QSpinBox*>(tableWidgetLaundryOptions->cellWidget(row, 1));
        if(spinBox == nullptr)
            continue;

        if(spinBox->value() != 0){
            empty = false;
            break;
        }
    }

    if(empty == true){
        showDropOffPage();
        return;
    }

    updateModel(modelDP);
    linePieceTotalDP->setText(QString::number(order[0]->calculatePieceTotal()));
    lineOrderSubTotalDP->setText(QString::number(order[0]->calculateCostO(), 'f', 2));
    lineOrderTotalDP->setText(QString::number(order[0]->getDiscountedCost(), 'f', 2));

    showDropOffPage();
}

void MainWindow::on_tableWidgetLaundryOptions_clicked(const QModelIndex &index){
    tableWidgetOptions(tableWidgetLaundryOptions, index, laundryPos, 1);
}



//
//***DryClean Order Page (5)***
//
void MainWindow::on_btnDryCleanReturn_clicked(){
    QSpinBox *spinBox;
    bool empty = true;

    //If the model is empty and a customer hasn't been selected
    if(modelDP->rowCount() == 0 && lineFNameDP->text().isEmpty()){
        showDropOffPage();
        return;
    }

    //Checks every row, to see if an article has been added
    for(int row = 0; row < tableWidgetDryCleanOptions->rowCount(); row++){
        spinBox = qobject_cast<QSpinBox*>(tableWidgetDryCleanOptions->cellWidget(row, 1));
        //Skips the row that has a label
        if(spinBox == nullptr)
            continue;

        if(spinBox->value() != 0){
            empty = false;
            break;
        }
    }

    if(empty == true){
        showDropOffPage();
        return;
    }

    updateModel(modelDP);
    linePieceTotalDP->setText(QString::number(order[0]->calculatePieceTotal()));
    lineOrderSubTotalDP->setText(QString::number(order[0]->calculateCostO(), 'f', 2));
    lineOrderTotalDP->setText(QString::number(order[0]->getDiscountedCost(), 'f', 2));

    showDropOffPage();
}

void MainWindow::on_tableWidgetDryCleanOptions_clicked(const QModelIndex &index){
    tableWidgetOptions(tableWidgetDryCleanOptions, index, dryCleanPos, 2);
}



//
//***Alterations Order Page (7)***
//

void MainWindow::on_btnAlterationsReturn_clicked(){
    QSpinBox *spinBox;
    bool empty = true;

    if(modelDP->rowCount() == 0 && lineFNameDP->text().isEmpty()){
        showDropOffPage();
        return;
    }

    for(int row = 0; row < tableWidgetAlterationsOptions->rowCount(); row++){
        spinBox = qobject_cast<QSpinBox*>(tableWidgetAlterationsOptions->cellWidget(row, 1));
        if(spinBox == nullptr)
            continue;

        if(spinBox->value() != 0){
            empty = false;
            break;
        }
    }

    if(empty == true){
        showDropOffPage();
        return;
    }

    updateModel(modelDP);
    linePieceTotalDP->setText(QString::number(order[0]->calculatePieceTotal()));
    lineOrderSubTotalDP->setText(QString::number(order[0]->calculateCostO(), 'f', 2));
    lineOrderTotalDP->setText(QString::number(order[0]->getDiscountedCost(), 'f', 2));

    showDropOffPage();
}

void MainWindow::on_tableWidgetAlterationsOptions_clicked(const QModelIndex &index){
    tableWidgetOptions(tableWidgetAlterationsOptions, index, alterationsPos, 3);
}



//
//***Pick Up Page (8)***
//
void MainWindow::on_btnCustomerPU_clicked(){
    showCustomerSearchPagePU();
}

void MainWindow::on_btnOrderSearchPU_clicked(){
    showOrderSearchPagePU();
    lineSearchOrderIDOS -> setFocus();
}

void MainWindow::on_btnSavePU_clicked(){
    if(lineFNamePU->text().isEmpty())
        return;


    if(curOrderID != orders[curOrderID].getOrderID()){
        std::string logmsg = "Critical Error in Saving Picked Up Order! Mismatch in curOrderID and object OrderID, curOrderID: " + std::to_string(curOrderID) + " Object OrderID: " + std::to_string(orders[curOrderID].getOrderID());
        manager->logger->log(logmsg);
        handleCritcalError();
    }

    int errors = manager->checkOrderIDs();
    if(errors != 0){
        std::string logmsg = "Critical Error in Saving Edited Order! Error in File, there are multiple matches of differnt orderIDs: " + std::to_string(errors) + " times";
        manager->logger->log(logmsg);
        handleCritcalError();
    }

    orders[curOrderID].setPaid(checkBoxPaidPU->isChecked());
    orders[curOrderID].setPickUp(checkBoxPUPU->isChecked());

    std::thread threadOrder(&fi::File::updateOrder, manager, curOrderID);
    std::thread threadCust(&fi::File::updateCustomer, manager, orders[curOrderID].getCustomerID());
    threadOrder.join();
    threadCust.join();

    customer.clear();
    order.clear();
    curOrderID = -1;

    showMainPage();
    clearScreenPU();
}

void MainWindow::on_btnReturnPU_clicked(){
    showMainPage();
    clearScreenPU();
}



//
//***Customer Search Page (9)***
//
void MainWindow::on_btnReturnCSPU_clicked(){
    clearScreenPU();
    showPickUpPage();
    lineSearchCustomerCSPU->clear();
}

void MainWindow::on_btnSearchCSPU_clicked(){
    customerSearchPageSetUp(tableViewCSRPU, modelCSR, lineSearchCustomerCSPU);
    showCustomerSearchResultsPU();
}



//
//***Order Search Page (10)***
//
void MainWindow::on_btnReturnOS_clicked(){
    showPickUpPage();
    lineSearchOrderIDOS->clear();
}

void MainWindow::on_btnSearchOrderOS_clicked(){
    int customerID;
    std::string orderID = lineSearchOrderIDOS->text().toStdString();

    if(orderID.empty())
        return;

    customer.clear();
    order.clear();
    lineSearchOrderIDOS->clear();
    clearScreenPU();

    order = search::Search::searchOrderID(orderID, orders);

    if(order.empty() == true)
        return;

    customerID = order[0]->getCustomerID();
    customer.push_back(&customers[customerID]);
    curOrderID = std::stoi(orderID);


    //Set information
    updateCOInformationPU();
    updateModel(modelPU);

    lineOrderTotalPU->setText(QString::number(order[0]->getCost(), 'f', 2));

    showPickUpPage();
}



//
//***Customer Search ResultsPU (11)***
//
void MainWindow::on_btnReturnCSRPU_clicked(){
    modelCSRPU->removeRows(0, modelCSRPU->rowCount());
    customer.clear();
    order.clear();

    showCustomerSearchPagePU();
}

void MainWindow::on_tableViewCSRPU_clicked(const QModelIndex &index){
    size_t i;
    cust::customer *temp = customer[index.row()];
    std::vector<orderInfo::order*> oTemp;
    QStandardItem *pickUpItem;

    customer.clear();
    order.clear();
    customer.push_back(temp);

    lineSearchCustomerCSPU->clear();
    modelOSR->removeRows(0, modelOSR -> rowCount());


    std::vector<int> orderIDs = customer[0]->getOrders();

    for(i = 0; i < orderIDs.size(); i++)
        oTemp.push_back(&orders[orderIDs[i]]);

    size_t size = oTemp.size();

    for(i = 0; i < size; i++){
        order.push_back(oTemp.back());
        oTemp.pop_back();

        QStandardItem *orderIDItem = new QStandardItem(QString::number(order[i]->getOrderID()));
        orderIDItem->setTextAlignment(Qt::AlignCenter);
        QStandardItem *dropOffItem = new QStandardItem(QString::fromStdString(order[i]->dropOff->getDate()));
        dropOffItem->setTextAlignment(Qt::AlignCenter);
        QStandardItem *totalPiecesItem = new QStandardItem(QString::number(order[i]->getPieceTotal()));
        totalPiecesItem->setTextAlignment(Qt::AlignCenter);
        QStandardItem *totalItem = new QStandardItem(QString::number(order[i]->getCost(), 'f', 2));
        totalItem->setTextAlignment(Qt::AlignCenter);

        if(order[i]->getPickUp())
            pickUpItem = new QStandardItem("Yes");
        else
            pickUpItem = new QStandardItem("No");

        pickUpItem->setTextAlignment(Qt::AlignCenter);

        modelOSR->setItem(i, 0, orderIDItem);
        modelOSR->setItem(i, 1, dropOffItem);
        modelOSR->setItem(i, 2, pickUpItem);
        modelOSR->setItem(i, 3, totalPiecesItem);
        modelOSR->setItem(i, 4, totalItem);
    }

    showOrderSearchResultsPU();
    modelCSRPU->removeRows(0, modelCSRPU->rowCount());
}



//
//***Order Search ResultsPU (12)***
//
void MainWindow::on_btnReturnOSR_clicked(){
    modelOSR->removeRows(0, modelOSR->rowCount());
    order.clear();
    customer.clear();
    showPickUpPage();
}

void MainWindow::on_tableViewOSR_clicked(const QModelIndex &index){
    curOrderID = order[index.row()]->getOrderID();
    order.clear();

    order.push_back(&orders[curOrderID]);

    if(curOrderID != orders[curOrderID].getOrderID()){
        std::string logmsg = "Critical Error in Saving Edited Order, selecting order from table! Mismatch in curOrderID and object OrderID, curOrderID: " + std::to_string(curOrderID) + " Object OrderID: " + std::to_string(orders[curOrderID].getOrderID());
        manager->logger->log(logmsg);
        handleCritcalError();
    }

    updateCOInformationPU();
    updateModel(modelPU);
    lineOrderTotalPU->setText(QString::number(order[0]->getCost(), 'f', 2));

    showPickUpPage();
}



//
//***Edit Order Page (13)***
//
void MainWindow::on_btnCustomerEO_clicked(){

    showCustomerSearchPageEO();
}

void MainWindow::on_btnOrderSearchEO_clicked(){
    lineOrderIDEO->setFocus();
    showOrderSearchPageEO();
}

void MainWindow::on_btnSaveEO_clicked(){
    std::tuple<std::string, int, double> temp;
    if(lineFNameEO->text().isEmpty())
        return;

    orders[curOrderID].setPaid(checkBoxPaidEO->isChecked());
    orders[curOrderID].setPickUp(checkBoxPUEO->isChecked());

    if(!lineRackEO->text().isEmpty())
        orders[curOrderID].setRack(lineRackEO->text().toInt());
    else
        orders[curOrderID].setRack(-1);

    saveModel(modelEO);
    updateModel(modelEO);

    if(curOrderID != orders[curOrderID].getOrderID()){
        std::string logmsg = "Critical Error in Saving Edited Order! Mismatch in curOrderID and object OrderID, curOrderID: " + std::to_string(curOrderID) + " Object OrderID: " + std::to_string(orders[curOrderID].getOrderID());
        manager->logger->log(logmsg);
        handleCritcalError();
    }

    int errors = manager->checkOrderIDs();
    if(errors != 0){
        std::string logmsg = "Critical Error in Saving Edited Order! Error in File, there are multiple matches of differnt orderIDs: " + std::to_string(errors) + " times";
        manager->logger->log(logmsg);
        handleCritcalError();
    }

    std::thread threadOrder(&fi::File::updateOrder, manager, curOrderID);
    std::thread threadCust(&fi::File::updateCustomer, manager, orders[curOrderID].getCustomerID());
    threadOrder.join();
    threadCust.join();

    customer.clear();
    order.clear();
    curOrderID = NULL;

    showMainPage();
    clearScreenEO();
}

void MainWindow::on_btnOneRecieptEO_clicked(){
    printReciept();
}

void MainWindow::on_btnTwoRecieptEO_clicked(){
    printReciept();
    printReciept();
}


void MainWindow::on_btnReturnEO_clicked(){
    showMainPage();
    clearScreenEO();
}

//
//***Order Search EO Page (14)***
//
void MainWindow::on_btnReturnOSEO_clicked(){
    showEditOrderPage();
    lineSearchOrderIDEO->clear();
}

void MainWindow::on_btnSearchOrderEO_clicked(){
    int customerID;
    std::string orderID = lineSearchOrderIDEO->text().toStdString();

    if(orderID.empty() || !search::Search::isID(orderID))
        return;

    customer.clear();
    order.clear();
    lineSearchOrderIDEO->clear();
    clearScreenEO();

    order = search::Search::searchOrderID(orderID, orders);

    if(order.empty() == true)
        return;

    customerID = order[0]->getCustomerID();
    customer.push_back(&customers[customerID]);
    curOrderID = std::stoi(orderID);


    //Set information
    updateCOInformationEO();
    updateModel(modelEO);

    lineOrderSubTotalEO->setText(QString::number(order[0]->getCost(), 'f', 2));
    lineOrderTotalEO->setText(QString::number(order[0]->getDiscountedCost(), 'f', 2));

    ui->btnOneRecieptEO->setEnabled(true);
    ui->btnTwoRecieptEO->setEnabled(true);

    showEditOrderPage();
    lineRackEO->setFocus();
}



//
//***Customer Search EO Page (15)***
//
void MainWindow::on_btnReturnCSEO_clicked(){
    clearScreenEO();
    showEditOrderPage();
    lineSearchCustomerCSEO->clear();
}

void MainWindow::on_btnSearchCSEO_clicked(){
    customerSearchPageSetUp(tableViewCSREO, modelCSREO, lineSearchCustomerCSEO);
    showCustomerSearchResultsEO();
}


//
//***Customer Search Results EO Page (16)***
//
void MainWindow::on_btnReturnCSREO_clicked(){
    modelCSREO->removeRows(0, modelCSREO->rowCount());
    customer.clear();
    order.clear();

    showCustomerSearchPageEO();
}

void MainWindow::on_tableViewCSREO_clicked(const QModelIndex &index){
    //Make into 1 function, passing model and index
    size_t i;
    cust::customer *temp = customer[index.row()];
    std::vector<orderInfo::order*> oTemp;
    QStandardItem *pickUpItem;

    customer.clear();
    order.clear();
    customer.push_back(temp);

    lineSearchCustomerCSEO->clear();

    modelOSREO->removeRows(0, modelOSREO -> rowCount());

    std::vector<int> orderIDs = customer[0]->getOrders();

    for(i = 0; i < orderIDs.size(); i++)
        oTemp.push_back(&orders[orderIDs[i]]);

    size_t size = oTemp.size();

    for(i = 0; i < size; i++){
        order.push_back(oTemp.back());
        oTemp.pop_back();

        QStandardItem *orderIDItem = new QStandardItem(QString::number(order[i]->getOrderID()));
        orderIDItem->setTextAlignment(Qt::AlignCenter);
        QStandardItem *dropOffItem = new QStandardItem(QString::fromStdString(order[i]->dropOff->getDate()));
        dropOffItem->setTextAlignment(Qt::AlignCenter);
        QStandardItem *totalPiecesItem = new QStandardItem(QString::number(order[i]->getPieceTotal()));
        totalPiecesItem->setTextAlignment(Qt::AlignCenter);
        QStandardItem *totalItem = new QStandardItem(QString::number(order[i]->getCost(), 'f', 2));
        totalItem->setTextAlignment(Qt::AlignCenter);

        if(order[i]->getPickUp())
            pickUpItem = new QStandardItem("Yes");
        else
            pickUpItem = new QStandardItem("No");

        pickUpItem->setTextAlignment(Qt::AlignCenter);

        modelOSREO->setItem(i, 0, orderIDItem);
        modelOSREO->setItem(i, 1, dropOffItem);
        modelOSREO->setItem(i, 2, pickUpItem);
        modelOSREO->setItem(i, 3, totalPiecesItem);
        modelOSREO->setItem(i, 4, totalItem);

    }

    showOrderSearchResultsEO();
    modelCSREO->removeRows(0, modelCSREO->rowCount());

    lineRackEO->setFocus();
}



//
//***Order Search Results EO Page (17)***
//
void MainWindow::on_btnReturnOSREO_clicked(){
    modelOSREO->removeRows(0, modelOSREO->rowCount());
    order.clear();
    customer.clear();
    showEditOrderPage();
}

void MainWindow::on_tableViewOSREO_clicked(const QModelIndex &index){
    curOrderID = order[index.row()]->getOrderID();
    order.clear();

    if(curOrderID != orders[curOrderID].getOrderID()){
        std::string logmsg = "Critical Error in Saving Edited Order! Mismatch in curOrderID and object OrderID, curOrderID: " + std::to_string(curOrderID) + " Object OrderID: " + std::to_string(orders[curOrderID].getOrderID());
        manager->logger->log(logmsg);
        handleCritcalError();
    }
    order.push_back(&orders[curOrderID]);
    updateCOInformationEO();
    updateModel(modelEO);
    lineOrderTotalEO->setText(QString::number(order[0]->getCost(), 'f', 2));

    ui->btnOneRecieptEO->setEnabled(true);
    ui->btnTwoRecieptEO->setEnabled(true);

    showEditOrderPage();
}




//
//***Admin Page (18)***
//

void MainWindow::on_btnReturnAP_clicked(){
    showMainPage();
}

void MainWindow::on_btnCIP_clicked(){
    setUpCIPPage();
    showItemsAndPricePage();
}

void MainWindow::on_btnExportData_clicked(){

}

//
//***Create Items and Price (19)***
//
void MainWindow::on_btnReturnCIP_clicked(){
    tableWidgetDryCleanCIP->clear();
    returnToRecentStackedWidget();
}

void MainWindow::on_btnSaveCIP_clicked(){

    saveTableCIP(laundryPrices, laundryPos, tableWidgetLaundryCIP);
    saveTableCIP(dryCleanPrices, dryCleanPos, tableWidgetDryCleanCIP);
    saveTableCIP(alterationsPrices, alterationsPos, tableWidgetAlterationsCIP);

    manager->savePrices();
    tableWidgetDryCleanCIP->clear();
    setUpCIPPage();
}


void MainWindow::saveTableCIP(std::vector<std::vector<std::pair<std::string, double>>> &prices, std::vector<std::tuple<std::string, int, int>> &pos, QTableWidget *tableWidget){
    size_t row, pieceI = 0, typeI = 0, index, rowCount = tableWidget->rowCount() - 1;
    double price;
    std::string piece;
    QDoubleSpinBox *dSpinBox;
    QLineEdit *linePiece, *newType;

    for(row = 0; row < rowCount; row++){
        dSpinBox = qobject_cast<QDoubleSpinBox*>(tableWidget->cellWidget(row, 1));
        if(dSpinBox == nullptr){
            if(row == 0)
                continue;

            pieceI = 0;
            typeI++;
            continue;
        }

        price = dSpinBox->value();
        linePiece = qobject_cast<QLineEdit*>(tableWidget->cellWidget(row, 0));
        piece = linePiece->text().toStdString();

        piece = cust::customer::autoCapatilize(piece);

        //if an item has been deleted basically and the price hasn't been set to 0
        if(piece.empty() && price != 0){
            tableWidget->removeRow(row);
            index = getIndex(row, pos); //interchange typeI and index, might be the same values. UPDATE: Index is giving the incorrext postion, either typeI or pieceI are wrong
            if(removeItemPrice(index, prices, pieceI))
                removeIndex(index, pos);
            row--;
            continue;
        }

        //The empty row, where price is still 0, gets skipped
        if(price == 0)
            continue;

        //if an item has been added
        if(pieceI >= prices[typeI].size()){
            if(prices[typeI][0].first == "" && prices[typeI][0].second == 0.00){
                prices[typeI].pop_back();
                prices[typeI].push_back(std::make_pair(piece, price));
            }
            else{
                prices[typeI].push_back(std::make_pair(piece, price));
                increaseIndex(typeI, pos);
            }
        }

        //if the name has been changed
        if(piece != prices[typeI][pieceI].first)
            prices[typeI][pieceI].first = piece;


        //if the price has been changed
        if(price != prices[typeI][pieceI].second)
            prices[typeI][pieceI].second = price;

        pieceI++;
    }
    newType = qobject_cast<QLineEdit*>(tableWidget->cellWidget(row, 1));

    if(newType != nullptr)
        if(!newType->text().isEmpty())
            createType(typeI, pos, prices, cust::customer::autoCapatilize(newType->text().toStdString()));

    row++;

}


void MainWindow::setUpCIPPage(){
    setUpTableWidgetsCIP(laundryPrices, laundryPos, tableWidgetLaundryCIP);
    setUpTableWidgetsCIP(dryCleanPrices, dryCleanPos, tableWidgetDryCleanCIP);
    setUpTableWidgetsCIP(alterationsPrices, alterationsPos, tableWidgetAlterationsCIP);
}

void MainWindow::setUpTableWidgetsCIP(std::vector<std::vector<std::pair<std::string, double>>> &prices, std::vector<std::tuple<std::string, int, int>> &pos, QTableWidget *tableWidget){
    size_t row = 0, i, j;
    QFont font;

    if(prices[0][0].first == "" && std::get<0>(pos[0]) == "")
        tableWidget->setRowCount(1);

    else{ // was +1
        tableWidget->setRowCount(calculateSize(prices) + prices.size() + 1);

        for(i = 0; i < prices.size(); i++)
            for(j = 0; j < prices[i].size(); j++){
                if(j == 0){
                    QLabel *label = new QLabel(QString::fromStdString(std::get<0>(pos[i])));
                    label->setAlignment(Qt::AlignCenter);
                    font = label->font();
                    font.setBold(true);
                    label->setFont(font);

                    tableWidget->setCellWidget(row, 0, label);
                    tableWidget->setCellWidget(row, 1, nullptr);
                    row++;
                }

                //If the type hasn't just been created so there arent any piece types
                if(prices[i][j].first != "" && prices[i][j].second != 0.00){
                    QLineEdit *piece = new QLineEdit(QString::fromStdString(prices[i][j].first), nullptr);
                    piece->setAlignment(Qt::AlignCenter);

                    QDoubleSpinBox *price = new QDoubleSpinBox(tableWidget);
                    price->setMaximum(9999);
                    price->setDecimals(2);
                    price->setValue(prices[i][j].second);

                    tableWidget->setCellWidget(row, 0, piece);
                    tableWidget->setCellWidget(row, 1, price);
                    row++;
                }

                if((j == prices[i].size() - 1) || (prices[i][j].first == "" && prices[i][j].second == 0.00) ){
                    QLineEdit *newPiece = new QLineEdit(tableWidget);
                    newPiece->setAlignment(Qt::AlignCenter);

                    QDoubleSpinBox *newPrice = new QDoubleSpinBox(tableWidget);
                    newPrice->setMaximum(9999);
                    newPrice->setDecimals(2);
                    newPrice->setValue(0.00);

                    tableWidget->setCellWidget(row, 0, newPiece);
                    tableWidget->setCellWidget(row, 1, newPrice);
                    row++;
                }
            }
    }

    QLabel *newTypeLabel = new QLabel("New Type");
    newTypeLabel->setAlignment(Qt::AlignCenter);

    QLineEdit *newTypeLine = new QLineEdit(this);

    tableWidget->setCellWidget(row, 0, newTypeLabel);
    tableWidget->setCellWidget(row, 1, newTypeLine);
}



//
//***Customer Data Page (20)***
//
//void


//
//***Helper Functions***
//
void MainWindow::updateCOInformationDP(){
    lineFNameDP->setText(QString::fromStdString(customer[0]->getFirstName()));
    lineLNameDP->setText(QString::fromStdString(customer[0]->getLastName()));
    linePhoneDP->setText(QString::fromStdString(customer[0]->getFormattedPhone()));
    lineCustomerIDDP->setText(QString::number(customer[0]->getCustomerID()));
    lineOrderIDDP->setText(QString::number(order[0]->getOrderID()));
    lineVisitsDP->setText(QString::number(customer[0]->getVisit() + 1));

    if(!order[0]->getDiscountApplied())
        lineOrderDiscountDP->setText("None");
    else
        lineOrderDiscountDP->setText(QString::number(order[0]->getDiscount()) + "%");

    setDate(dateDTDropOffDP, dateDPickUpDP);

    dateDTDropOffDP->show();
    dateDPickUpDP->show();
}

void MainWindow::updateCOInformationPU(){
    lineFNamePU->setText(QString::fromStdString(customer[0]->getFirstName()));
    lineLNamePU->setText(QString::fromStdString(customer[0]->getLastName()));
    linePhonePU->setText(QString::fromStdString(customer[0]->getFormattedPhone()));
    lineCustomerIDPU->setText(QString::number(customer[0]->getCustomerID()));
    lineOrderIDPU->setText(QString::number(order[0]->getOrderID()));
    linePieceTotalPU->setText(QString::number(order[0]->getPieceTotal()));

    if(!order[0]->getDiscountApplied())
        lineOrderDiscountPU->setText("None");
    else
        lineOrderDiscountPU->setText(QString::number(order[0]->getDiscount()) + "%");

    //Set Date
    setDate(dateDTDropOffPU, dateDPickUpPU);
    dateDTDropOffPU->show();
    dateDPickUpPU->show();

    if(order[0]->getPaid() == true)
        checkBoxPaidPU->setCheckState(Qt::Checked);
    if(order[0]->getPickUp() == true)
        checkBoxPUPU->setCheckState(Qt::Checked);
    if(order[0]->getRack() != -1)
        lineRackPU->setText(QString::number(order[0]->getRack()));
}

void MainWindow::updateCOInformationEO(){
    lineFNameEO->setText(QString::fromStdString(customer[0]->getFirstName()));
    lineLNameEO->setText(QString::fromStdString(customer[0]->getLastName()));
    linePhoneEO->setText(QString::fromStdString(customer[0]->getFormattedPhone()));
    lineCustomerIDEO->setText(QString::number(customer[0]->getCustomerID()));
    lineOrderIDEO->setText(QString::number(order[0]->getOrderID()));
    linePieceTotalEO->setText(QString::number(order[0]->getPieceTotal()));

    if(!order[0]->getDiscountApplied())
        lineOrderDiscountEO->setText("None");
    else
        lineOrderDiscountEO->setText(QString::number(order[0]->getDiscount()) + "%");

    //Set Date
    setDate(dateDTDropOffEO, dateDPickUpEO);
    dateDTDropOffEO->show();
    dateDPickUpEO->show();

    if(order[0]->getPaid() == true)
        checkBoxPaidEO->setCheckState(Qt::Checked);
    if(order[0]->getPickUp() == true)
        checkBoxPUEO->setCheckState(Qt::Checked);
    if(order[0]->getRack() != -1)
        lineRackEO->setText(QString::number(order[0]->getRack()));
}

void MainWindow::clearScreenDP(){
    modelDP -> removeRows(0, modelDP -> rowCount());
    lineFNameDP -> clear();
    lineLNameDP -> clear();
    linePhoneDP -> clear();
    dateDTDropOffDP -> clear();
    dateDPickUpDP->clear();
    lineCustomerIDDP->clear();
    lineOrderIDDP->clear();
    lineOrderTotalDP ->clear();
    lineVisitsDP->clear();
    linePieceTotalDP->clear();
    lineOrderSubTotalDP->clear();
    lineOrderDiscountDP->clear();

    checkBoxPaidDP->setCheckState(Qt::Unchecked);

    dateDTDropOffDP->hide();
    dateDPickUpDP->hide();
}

void MainWindow::clearScreenNC(){
    lineFNameNC->clear();
    lineLNameNC->clear();
    linePhoneNC->clear();
}

void MainWindow::clearScreenPU(){
    modelPU -> removeRows(0, modelPU -> rowCount());
    lineFNamePU -> clear();
    lineLNamePU -> clear();
    linePhonePU -> clear();
    lineCustomerIDPU->clear();
    lineOrderIDPU->clear();
    lineOrderTotalPU->clear();
    lineRackPU->clear();
    linePieceTotalPU->clear();
    lineOrderSubTotalPU->clear();
    lineOrderDiscountPU->clear();

    checkBoxPaidPU->setCheckState(Qt::Unchecked);
    checkBoxPUPU->setCheckState(Qt::Unchecked);
}

void MainWindow::clearScreenEO(){
    modelEO -> removeRows(0, modelEO -> rowCount());
    lineFNameEO -> clear();
    lineLNameEO -> clear();
    linePhoneEO -> clear();
    lineCustomerIDEO->clear();
    lineOrderIDEO->clear();
    lineOrderTotalEO->clear();
    lineRackEO->clear();
    linePieceTotalEO->clear();
    lineOrderSubTotalEO->clear();
    lineOrderDiscountEO->clear();

    checkBoxPaidEO->setCheckState(Qt::Unchecked);
    checkBoxPUEO->setCheckState(Qt::Unchecked);
}

void MainWindow::setUpOptionsTables(QTableWidget *tableWidget, std::vector<std::vector<std::pair<std::string, double>>> prices, std::vector<std::tuple<std::string, int, int>> pos){
    size_t row = 0, i, j;
    QFont font;
    int size = calculateSize(prices);
    if(size == 0)
        return;

    tableWidget->setRowCount(size);

    for(i = 0; i < prices.size(); i++)
        for(j = 0; j < prices[i].size(); j++){
            if(j == 0){
                if(prices[i][j].first == "")
                    continue;
                QLabel *label = new QLabel(QString::fromStdString(std::get<0>(pos[i])));
                label->setAlignment(Qt::AlignLeft);
                font = label->font();
                font.setBold(true);
                label->setFont(font);

                tableWidget->setCellWidget(row, 0, label);
                row++;
            }

            QLabel *type = new QLabel(QString::fromStdString(prices[i][j].first));
            type->setAlignment(Qt::AlignCenter);

            QSpinBox *count = new QSpinBox(tableWidget);
            count->setValue(0);

            QDoubleSpinBox *price = new QDoubleSpinBox(tableWidget);
            price->setMaximum(9999);
            price->setDecimals(2);
            price->setValue(prices[i][j].second);

            tableWidget->setCellWidget(row, 0, type);
            tableWidget->setCellWidget(row, 1, count);
            tableWidget->setCellWidget(row, 2, price);
            row++;
        }
}

void MainWindow::tableWidgetOptions(QTableWidget *tableWidget, const QModelIndex &index, std::vector<std::tuple<std::string, int, int>> &pos, int type){
    double price;
    int n, row = index.row(), col = index.column();

    std::string article;
    std::tuple<std::string, int, double> tup;
    QSpinBox *spinBox;
    QDoubleSpinBox *dSpinBox;

    //Make this into case and switch, so i can allow a col to be a delete button
    spinBox = qobject_cast<QSpinBox*>(tableWidget->cellWidget(row, 1));

    if(col != 0 || spinBox == nullptr)
        return;

    n = spinBox->value();
    if(n == 0)
        return;

    dSpinBox = qobject_cast<QDoubleSpinBox*>(tableWidget->cellWidget(row, 2));
    price = dSpinBox->value();

    article = qobject_cast<QLabel*>(tableWidget->cellWidget(row, 0))->text().toStdString();

    //position = getIndex(row, pos);
    //type = tableWidgetLaundryOptions->item(row, col);
    //QColor bgColor = type->background().color();
    //qDebug() << "BackGroundColor: " << bgColor.red() << " " << bgColor.green() << " " << bgColor.blue();
    //type->setBackground(Qt::green);

    switch(type){
    case 1:
        order[0]->setLaundryPiece(getTypeName(row, pos), n, price, article);
        break;

    case 2:
        order[0]->setDryCleanPiece(getTypeName(row, pos), n, price, article);
        break;

    case 3:
        order[0]->setAlterationsPiece(getTypeName(row, pos), n, price, article);
        break;
    }

    //tableWidget->item(row, 0)->setBackground(Qt::green);

}


void MainWindow::customerSearchPageSetUp(QTableView *tableView, QStandardItemModel *model, QLineEdit *lineSearch){
    QString entryQ;
    std::string entry;
    size_t i;

    customer.clear();
    model -> removeRows(0, model -> rowCount());

    entryQ = lineSearch->text();
    if(entryQ.isEmpty())
        return;

    entry = entryQ.toStdString();

    if(search::Search::isPhoneNumber(entry) || search::Search::isName(entry))
        customer = search::Search::searchCustAlgo(entry, this->customers);

    if(customer.empty())
        return;

    for(i = 0; i < customer.size(); i++){
        QStandardItem *firstNameItem = new QStandardItem(QString::fromStdString(customer[i]->getFirstName()));
        firstNameItem->setTextAlignment(Qt::AlignCenter);
        QStandardItem *lastNameItem = new QStandardItem(QString::fromStdString(customer[i]->getLastName()));
        lastNameItem->setTextAlignment(Qt::AlignCenter);

        QStandardItem *phoneItem = new QStandardItem(QString::fromStdString(customer[i]->getFormattedPhone()));
        phoneItem->setTextAlignment(Qt::AlignCenter);

        model->setItem(i, 0, firstNameItem);
        model->setItem(i, 1, lastNameItem);
        model->setItem(i, 2, phoneItem);
    }
    tableView -> setSelectionBehavior(QAbstractItemView::SelectRows);
}

void MainWindow::setDate(QDateTimeEdit *dp, QDateEdit *pu){
    QDate dateD(order[0]->dropOff->getYear(), order[0]->dropOff->getMonth(), order[0]->dropOff->getDay());
    QTime timeD(order[0]->dropOff->getHour(), order[0]->dropOff->getMin());
    QDateTime dateTimeD(dateD, timeD);
    dp->setDateTime(dateTimeD);

    QDate dateP(order[0]->pickUp->getYear(), order[0]->pickUp->getMonth(), order[0]->pickUp->getDay());
    pu->setDate(dateP);
}

void MainWindow::saveModel(QStandardItemModel *model){
    size_t row = 0;
    std::vector<std::vector<std::tuple<std::string, std::string, int, double>>> laundry = order[0]->getLaundry(), dryClean = order[0]->getDryClean(), alterations = order[0]->getAlterations();
    std::pair<size_t, std::vector<std::vector<std::tuple<std::string, std::string, int, double>>>> pair;

    pair = saveTableView(laundry, model, "Laundry", row);
    row = pair.first;
    order[0]->setLaundry(pair.second);

    pair = saveTableView(dryClean, model, "Dry Clean", row);
    row = pair.first;
    order[0]->setDryClean(pair.second);

    pair = saveTableView(alterations, model, "Alterations", row);
    order[0]->setAlterations(pair.second);

    order[0]->calculatePieceTotal();
    order[0]->calculateCostO();
    order[0]->applyDiscount();
}

std::pair<size_t, std::vector<std::vector<std::tuple<std::string, std::string, int, double>>>> MainWindow::saveTableView(std::vector<std::vector<std::tuple<std::string, std::string, int, double>>> article, QStandardItemModel *model, QString pieceType, size_t row){
    size_t i = 0, posArt = 0, posPiece = 0, size = calculatePieceTotal(article);

    while(i < size){
        //size_t artSize = article[posArt].size();
        while(posPiece < article[posArt].size()){
            QModelIndex index = model->index(row, 0);
            QVariant dataNumber = model->data(index);

            index = model->index(row, 3);
            QVariant dataPrice = model->data(index);

            //If the number of pieces has changed
            if(dataNumber.toInt() != std::get<2>(article[posArt][posPiece])){
                if(dataNumber.toInt() == 0){
                    //Remove piece from order
                    article[posArt].erase(article[posArt].begin() + posPiece);
                    i++;
                    row++;
                    continue;
                }
                //update data structure
                std::get<2>(article[posArt][posPiece]) = dataNumber.toInt();
            }
            //If the price has changed of a piece
            if(dataPrice.toDouble() != std::get<3>(article[posArt][posPiece])){
                std::get<3>(article[posArt][posPiece]) = dataPrice.toDouble();
            }

            posPiece++;
            i++;
            row++;
        }
        posPiece = 0;
        posArt++;
    }
    return std::make_pair(row, article);;
}

void MainWindow::updateModel(QStandardItemModel *model){
    size_t row = 0;
    std::vector<std::vector<std::tuple<std::string, std::string, int, double>>> laundry = order[0]->getLaundry(), dryClean = order[0]->getDryClean(), alterations = order[0]->getAlterations();

    model->removeRows(0, model->rowCount());

    row = updateTableView(laundry, model, "Laundry", row);
    row = updateTableView(dryClean, model, "Dry Clean", row);
    updateTableView(alterations, model, "Alterations", row);

}

size_t MainWindow::updateTableView(std::vector<std::vector<std::tuple<std::string, std::string, int, double>>> articles, QStandardItemModel *model, QString pieceType, size_t row){
    double pTotal;
    size_t i, j;
    QStandardItem *number, *type, *piece, *pricePerPiece, *priceTotal;

    for(i = 0; i < articles.size(); i++)
        if(articles[i].empty() == false)
            for(j = 0; j < articles[i].size(); j++){
                number = new QStandardItem(QString::number(std::get<2>(articles[i][j])));
                number->setTextAlignment(Qt::AlignCenter);

                type = new QStandardItem(pieceType);
                type->setTextAlignment(Qt::AlignCenter);

                piece = new QStandardItem(QString::fromStdString(std::get<0>(articles[i][j])) + " " + QString::fromStdString(std::get<1>(articles[i][j])));
                piece->setTextAlignment(Qt::AlignCenter);

                pricePerPiece = new QStandardItem(QString::number(std::get<3>(articles[i][j]), 'f', 2));
                pricePerPiece->setTextAlignment(Qt::AlignCenter);

                pTotal = std::get<2>(articles[i][j]) * std::get<3>(articles[i][j]);
                priceTotal = new QStandardItem(QString::number(pTotal, 'f', 2));
                priceTotal->setTextAlignment(Qt::AlignCenter);

                model->setItem(row, 0, number);
                model->setItem(row, 1, type);
                model->setItem(row, 2, piece);
                model->setItem(row, 3, pricePerPiece);
                model->setItem(row, 4, priceTotal);

                row++;
            }

    return row;
}

void MainWindow::saveCustomerTable(){

}

void MainWindow::updateCustomerTable(){

}

std::string MainWindow::getTypeName(int curRow, std::vector<std::tuple<std::string, int, int>> articlePos){
    size_t i;
    std::string typeName;
    typeName.clear();

    for(i = 0; i < articlePos.size(); i++)
        if(curRow >= std::get<1>(articlePos[i]) && curRow <= std::get<2>(articlePos[i]))
            typeName = get<0>(articlePos[i]);

    return typeName;
}

//index for articleType, so like pants type, shirt type etc...
size_t MainWindow::getIndex(int curRow, std::vector<std::tuple<std::string, int, int>> articlePos){
    size_t i;

    for(i = 0; i < articlePos.size(); i++)
        if(curRow >= std::get<1>(articlePos[i]) && curRow <= std::get<2>(articlePos[i]))
            return i;

    return NULL;
}

bool MainWindow::removeItemPrice(size_t index, std::vector<std::vector<std::pair<std::string, double>>> &prices, size_t pieceI){
    size_t i;

    for(i = 0; i < prices[index].size(); i++){
        if(i == pieceI){
            prices[index].erase(prices[index].begin() + i);
            return true;
        }
    }

    return false;
}

void MainWindow::removeIndex(size_t index, std::vector<std::tuple<std::string, int, int>> &pos){
    size_t i;
    int lpos, rpos;

    for(i = index; i < pos.size(); i++){
        rpos = std::get<2>(pos[i]);
        std::get<2>(pos[i]) = rpos - 1;

        //Doesn't remove the first index in the article type, since the range is being decreased from the end of the range
        if(i == index)
            continue;

        lpos = std::get<1>(pos[i]);
        std::get<1>(pos[i]) = lpos - 1;
        //if((lpos + 1) == rpos) if there isnt a current piece/price tuple in prices, so this will be pos.erase since it doesn't exist anymore;
    }
}

void MainWindow::increaseIndex(size_t index, std::vector<std::tuple<std::string, int, int>> &pos){
    size_t i;
    int lpos, rpos;

    for(i = index; i < pos.size(); i++){
        rpos = std::get<2>(pos[i]);
        std::get<2>(pos[i]) = rpos + 1;

        if(i == index)
            continue;

        lpos = std::get<1>(pos[i]);
        std::get<1>(pos[i]) = lpos + 1;
    }

}

void MainWindow::createType(size_t curIndex, std::vector<std::tuple<std::string, int, int>> &pos, std::vector<std::vector<std::pair<std::string, double>>> &prices, std::string newPiece){
    int lpos = 0, rpos = 1;
    std::vector<std::pair<std::string, double>> newType;

    if(curIndex == 0 && std::get<0>(pos[curIndex]) == ""){
        std::get<0>(pos[curIndex]) = newPiece;
        std::get<1>(pos[curIndex]) = lpos;
        std::get<2>(pos[curIndex]) = rpos;
        return;
    }

    rpos = std::get<2>(pos[curIndex]);
    lpos = rpos + 1;
    rpos += 2;

    pos.push_back(std::make_tuple(newPiece, lpos, rpos));

    newType.push_back(std::make_pair("", 0.00));
    prices.push_back(newType);
}

int MainWindow::calculateSize(std::vector<std::vector<std::pair<std::string, double>>> prices){
    size_t i, j;
    int size = 0;

    for(i = 0; i < prices.size(); i++)
        for(j = 0; j < prices[i].size(); j++){
            if(j == 0)
                size++;
            if(prices[i][j].first == "")
                continue;
            size++;
        }
    return size;
}

int MainWindow::calculateSizeOptions(std::vector<std::vector<std::pair<std::string, double>>> prices){
    size_t i, j;
    int size = 0;

    for(i = 0; i < prices.size(); i++)
        for(j = 0; j < prices[i].size(); j++){
            if(prices[i][j].first == "")
                continue;
            if(j == 0)
                size++;
            size++;
        }
    return size;
}

int MainWindow::calculatePieceTotal(std::vector<std::vector<std::tuple<std::string, std::string, int, double>>> articles){
    size_t i, j;
    int size = 0;

    for(i = 0; i < articles.size(); i++)
        for(j = 0; j < articles[i].size(); j++)
            size++;

    return size;
}

bool MainWindow::checkForDuplicates(std::string firstName, std::string lastName, std::string phone){
    size_t i;

    phone = cust::customer::createPhone(phone);

    for(i = 0; i < customers.size(); i++)
        if(((firstName == customers[i].getFirstName()) && (lastName == customers[i].getLastName()) && phone == customers[i].getPhone()) || phone == customers[i].getPhone())
            return true;


    return false;
}

void MainWindow::returnToRecentStackedWidget(){
    size_t temp = stackedWidget->currentIndex();
    ui->stackedWidget->setCurrentIndex(recentStackedWidgetIndex);
    recentStackedWidgetIndex = temp;
}

void MainWindow::handleCritcalError(){
    QMessageBox messageBox;

    manager->logger->log("File will be saved as a new log!");
    manager->logger->saveAsNewLog();

    messageBox.critical(0,"Error","An error has occured !");
    messageBox.setFixedSize(500,200);
    QCoreApplication::quit();
    QCoreApplication::exit();
}

void MainWindow::saveAndPrint(int n, QDateEdit *p, QCheckBox *b){
    std::string message;
    //Setting Date
    QDateTime dateTime = p->dateTime();
    order[0]->pickUp->setYear(dateTime.date().year());
    order[0]->pickUp->setMonth(dateTime.date().month());
    order[0]->pickUp->setDay(dateTime.date().day());
    order[0]->pickUp->updateClass();

    order[0]->setPaid(b->isChecked());

    std::thread threadOrder(&fi::File::saveOrders, manager, std::ref(orders[curOrderID]));
    std::thread threadCust(&fi::File::updateCustomer, manager, customer[0]->getCustomerID());

    for(int i = 0; i < n; i++)
        printReciept();

    threadOrder.join();
    threadCust.join();

    customer.clear();
    order.clear();
    curOrderID = NULL;

    if(n > 1)
        message = std::to_string(n) + " Reciepts printed";
    else
        message = std::to_string(n) + " Reciept printed";
    manager->logger->log(message);
}

void MainWindow::printReciept(){
    int x = 5, y = 15, yInc = 20;
    size_t i, j;
    std::vector<std::vector<std::tuple<std::string, std::string, int, double>>> laundry = order[0]->getLaundry(), dryClean = order[0]->getDryClean(), alterations = order[0]->getAlterations();
    std::vector<QString> info;

    int width = 250, difX = 45, difY = 12;

    QPrintDialog printDialog(&printer, this);
    QPainter painter(&printer);
    QFont font = painter.font();
    QFontMetrics metrics(font);

    font.setPointSize(16);
    font.setBold(true);
    painter.setFont(font);

    //Order ID
    painter.drawText(QRect(x, y, width, metrics.height() + 8), Qt::AlignCenter, QString::number(curOrderID));
    y = y + yInc + 15;

    //Was 11
    font.setPointSize(13);
    painter.setFont(font);

    //Shop Information
    painter.drawText(QRect(x, y, width, metrics.height() + 8), Qt::AlignCenter, "Cleaning & Alteration Shop");
    y += yInc;

    font.setBold(false);
    painter.setFont(font);

    painter.drawText(QRect(x, y, width, metrics.height() + 8), Qt::AlignCenter, "1709 Tully Rd, Suite C");
    y += yInc;
    painter.drawText(QRect(x, y, width, metrics.height() + 8), Qt::AlignCenter, "San Jose, CA, 95122");
    y += yInc;
    painter.drawText(QRect(x, y, width, metrics.height() + 8), Qt::AlignCenter, "(408) 258-5705");

    y = y + yInc + 45;

    //Customer Information
    font.setBold(true);
    painter.setFont(font);
    painter.drawText(x, y, QString::fromStdString(customer[0]->getLastName()) + ", " + QString::fromStdString(customer[0]->getFirstName()));
    y += yInc;

    font.setBold(false);
    painter.setFont(font);
    painter.drawText(x, y, "Phone: " + QString::fromStdString(customer[0]->getFormattedPhone()));
    y += yInc;

    //Dates
    painter.drawText(x, y, "Drop Off: " + QString::fromStdString(order[0]->dropOff->dayOfWeekString()) + " " + QString::fromStdString(order[0]->dropOff->getAbbreviatedMonth()) +" " + QString::number(order[0]->dropOff->getDay()) + " " + QString::number(order[0]->dropOff->getYear()));
    y += yInc;
    painter.drawText(x, y, "Pick Up: " + QString::fromStdString(order[0]->pickUp->dayOfWeekString()) + " " + QString::fromStdString(order[0]->pickUp->getAbbreviatedMonth()) +" " + QString::number(order[0]->pickUp->getDay()) + " " + QString::number(order[0]->pickUp->getYear()));
    y += yInc;

    //Order Information
    y += 10;
    painter.drawText(x, y, "=====================");
    y += yInc;
    if(calculatePieceTotal(laundry)){
        painter.drawText(x, y, "Laundry: ");
        y += yInc;

        for(i = 0; i < laundry.size(); i++)
            if(laundry[i].empty() == false)
                for(j = 0; j < laundry[i].size(); j++){
                    painter.drawText(QRect(x, y - difY, width, metrics.height() + 5), Qt::AlignLeft, QString::number(std::get<2>(laundry[i][j])));
                    painter.drawText(QRect(x + difX, y - difY, width, metrics.height() + 5), Qt::AlignLeft, QString::fromStdString(std::get<0>(laundry[i][j]) + " " + std::get<1>(laundry[i][j])));
                    painter.drawText(QRect(x, y - difY, width, metrics.height() + 5), Qt::AlignRight, QString::number(std::get<2>(laundry[i][j]) * std::get<3>(laundry[i][j]), 'f', 2));
                    y += yInc;
                }
        y += yInc;
    }

    if(calculatePieceTotal(dryClean)){
        painter.drawText(x, y, "Dry Clean: ");
        y += yInc;

        for(i = 0; i < dryClean.size(); i++)
            if(dryClean[i].empty() == false)
                for(j = 0; j < dryClean[i].size(); j++){
                    painter.drawText(QRect(x, y - difY, width, metrics.height() + 5), Qt::AlignLeft, QString::number(std::get<2>(dryClean[i][j])));
                    painter.drawText(QRect(x + difX, y - difY, width, metrics.height() + 5), Qt::AlignLeft, QString::fromStdString(std::get<0>(dryClean[i][j]) + " " + std::get<1>(dryClean[i][j])));
                    painter.drawText(QRect(x, y - difY, width, metrics.height() + 5), Qt::AlignRight, QString::number(std::get<2>(dryClean[i][j]) * std::get<3>(dryClean[i][j]), 'f', 2));
                    y += yInc;
                }
        y += yInc;
    }

    if(calculatePieceTotal(alterations)){
        painter.drawText(x, y, "Alterations: ");
        y += yInc;

        for(i = 0; i < alterations.size(); i++)
            if(alterations[i].empty() == false)
                for(j = 0; j < alterations[i].size(); j++){
                    painter.drawText(QRect(x, y - difY, width, metrics.height() + 5), Qt::AlignLeft, QString::number(std::get<2>(alterations[i][j])));
                    painter.drawText(QRect(x + difX, y - difY, width, metrics.height() + 5), Qt::AlignLeft, QString::fromStdString(std::get<0>(alterations[i][j]) + " " + std::get<1>(alterations[i][j])));
                    painter.drawText(QRect(x, y - difY, width, metrics.height() + 5), Qt::AlignRight, QString::number(std::get<2>(alterations[i][j]) * std::get<3>(alterations[i][j]), 'f', 2));
                    y += yInc;
                }
        y += yInc;
    }
    painter.drawText(x, y - yInc + 5, "=====================");

    //Total Information
    if(!order[0]->getDiscountApplied()){
        painter.drawText(QRect(x, y, width, metrics.height() + 5), Qt::AlignLeft, QString::number(order[0]->getPieceTotal()) + " Pieces");
        if(order[0]->getPaid())
            painter.drawText(QRect(x, y, width, metrics.height() + 5), Qt::AlignCenter, "Paid");
        painter.drawText(QRect(x, y, width, metrics.height() + 5), Qt::AlignRight, "Total: $" + QString::number(order[0]->getCost(), 'f', 2));
    }
    else{
        painter.drawText(QRect(x, y, width, metrics.height() + 5), Qt::AlignLeft, QString::number(order[0]->getPieceTotal()) + " Pieces");
        painter.drawText(QRect(x, y, width, metrics.height() + 5), Qt::AlignRight, "Subtotal: $" + QString::number(order[0]->getCost(), 'f', 2));
        y+=yInc;
        painter.drawText(QRect(x, y, width, metrics.height() + 5), Qt::AlignLeft, "Discount: " + QString::number(order[0]->getDiscount()) + "%");
        painter.drawText(QRect(x, y, width, metrics.height() + 5), Qt::AlignRight, "Total: $" + QString::number(order[0]->getDiscountedCost(), 'f', 2));
        if(order[0]->getPaid()){
            y += yInc;
            painter.drawText(QRect(x, y, width, metrics.height() + 5), Qt::AlignCenter, "Paid");
        }
    }

    y += 75;
    painter.drawText(QRect(x, y, width, metrics.height() + 50), Qt::AlignCenter, "Thank You Very Much");//QString::number(curOrderID));

    painter.end();
}




