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
    , ui(new Ui::MainWindow)
{
    //Setting up database
    std::string customerFile = "C:/Code/repos/LAVjr97/CProgram/customers.txt";
    std::string orderFile = "C:/Code/repos/LAVjr97/CProgram/orders.txt";
    std::string tempFile = "C:/Code/repos/LAVjr97/CProgram/temp.txt";

    manager = new fi::File(customerFile, orderFile, tempFile, this->customers, this->orders);

    //Indepently load up customers and orders
    std::thread threadCust(&fi::File::loadCustomers, manager);
    std::thread threadOrder(&fi::File::loadOrders, manager);
    threadCust.join();
    threadOrder.join();

    laundryPrices = {{{"Pants", 4.99}, {"Jeans", 4.59}}, {{"Shirts", 3.99},{"T-Shirts", 3.49}}};
    dryCleanPrices = {{{"Pants", 6.99}, {"Jeans", 5.59}}, {{"Shirts", 4.99},{"T-Shirts", 4.49}}};
    alterationsPrices = {{{"Pants", 3.99}, {"Jeans", 3.59}}, {{"Shirts", 2.99},{"T-Shirts", 1.49}}};

    laundryPos = {{"Pants", 0, 1}, {"Shirts", 2, 3}};
    dryCleanPos = {{"Pants", 0, 1}, {"Shirts", 2, 3}};
    alterationsPos = {{"Pants", 0, 1}, {"Shirts", 2, 3}};

    curOrderID = 0;

    //Everything after this point is GUI related
    ui->setupUi(this);

    //
    //Drop Off Page
    //
    lineCustomerIDDP = ui->lineCustomerIDDP;
    lineFNameDP = ui->lineFNameDP;
    lineLNameDP = ui->lineLNameDP;
    lineOrderIDDP = ui->lineOrderIDDP;
    linePhoneDP = ui->linePhoneDP;
    lineOrderTotalDP = ui->lineOrderTotalDP;
    checkBoxPaidDP = ui->checkBoxPaidDP;

    dateDTDropOffDP = ui->dateDTDropOffDP;
    dateDTPickUpDP = ui->dateDTPickUpDP;

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

    //connect(tableViewCSR, &QTableView::entered, this, &MainWindow::on_btnSearchCS_clicked);

    //
    //New Customer Page
    //
    lineFNameNC = ui -> lineFNameNC;
    lineLNameNC = ui -> lineLNameNC;
    linePhoneNC = ui -> linePhoneNC;

    lPrices = calculateSize(laundryPrices);
    dcPrices = calculateSize(dryCleanPrices);
    aPrices = calculateSize(alterationsPrices);

    //Order Laundry Page
    tableWidgetLaundryOptions = ui->tableWidgetLaundryOptions;
    tableWidgetLaundryOptions->setRowCount(lPrices);
    tableWidgetLaundryOptions->setColumnCount(3);

    //Order DryClean Page
    tableWidgetDryCleanOptions = ui->tableWidgetDryCleanOptions;
    tableWidgetDryCleanOptions->setRowCount(dcPrices);
    tableWidgetDryCleanOptions->setColumnCount(3);

    //Order Alterations Page
    tableWidgetAlterationsOptions = ui->tableWidgetAlterationsOptions;
    tableWidgetAlterationsOptions->setRowCount(aPrices);
    tableWidgetAlterationsOptions->setColumnCount(3);

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
    dateDTPickUpPU = ui->dateDTPickUpPU;

    modelPU = new QStandardItemModel(this);
    modelPU->setColumnCount(5);
    modelPU->setHorizontalHeaderLabels({"Number", "Type", "Piece", "Price Per Piece", "Price Total"});

    tableViewOrdersPU = ui->tableViewOrdersPU;
    tableViewOrdersPU->setModel(modelPU);
    tableViewOrdersPU->resizeColumnsToContents();

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
    tableViewCSRPU->resizeColumnsToContents();

    //
    //Order Search ResultsPU
    //
    modelOSR = new QStandardItemModel(this);
    modelOSR->setColumnCount(4);
    modelOSR->setHorizontalHeaderLabels({"Order ID", "Drop Off", "Pick Up", "Total"});

    tableViewOSR = ui->tableViewOSR;
    tableViewOSR->setModel(modelOSR);
    tableViewOSR->resizeColumnsToContents();
    tableViewOSR -> setSelectionBehavior(QAbstractItemView::SelectRows);

}

MainWindow::~MainWindow()
{
    delete ui;
}



//
//***Page Movement***
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

void MainWindow::showPickUpPage(){
    ui->stackedWidget->setCurrentIndex(8);
}

void MainWindow::showCustomerSearchPagePU(){
    ui->stackedWidget->setCurrentIndex(9);
}

void MainWindow::showOrderSearchPagePU(){
    ui->stackedWidget->setCurrentIndex(10);
}

void MainWindow::showCustomerSearchResultsPU(){
    ui->stackedWidget->setCurrentIndex(11);
}

void MainWindow::showOrderSearchResultsPU(){
    ui->stackedWidget->setCurrentIndex(12);
}



//
//***Main Home Page (0)***
//
void MainWindow::on_btnDropOff_clicked(){
    dateDTDropOffDP->hide();
    dateDTPickUpDP->hide();
    showDropOffPage();
}

void MainWindow::on_btnPickUp_clicked(){
    dateDTDropOffPU->hide();
    dateDTPickUpPU->hide();
    showPickUpPage();
}



//
//***Drop Off Page (1)***
//
void MainWindow::on_btnCustomer_clicked()
{
    if(!order.empty()){
        orders.pop_back();
        order.clear();
        curOrderID--;
    }

    MainWindow::showSearchPage();
}

void MainWindow::on_btnLaundry_clicked()
{
    if(lineFNameDP->text().isEmpty())
        return;

    setUpLaundryPage();

    MainWindow::showOrderLaundryPage();
}

void MainWindow::on_btnDryClean_clicked()
{
    if(lineFNameDP->text().isEmpty())
        return;

    setUpDryCleanPage();

    MainWindow::showOrderDryCleanPage();
}

void MainWindow::on_btnAlterations_clicked()
{
    if(lineFNameDP->text().isEmpty())
        return;

    //setUpAlterationsPage();

    MainWindow::showOrderAlterationsPage();
}

void MainWindow::on_btnSaveDP_clicked()
{
    if(modelDP->rowCount() == 0)
        return;

    //Add orderID to customer's orders
    customer[0]->setLatestOrder(curOrderID);
    customer[0]->updateVisits(customer[0]->getVisit() + 1);

    //Setting Date
    QDateTime dateTime = dateDTPickUpDP->dateTime();
    order[0]->pickUp->setYear(dateTime.date().year());
    order[0]->pickUp->setMonth(dateTime.date().month());
    order[0]->pickUp->setDay(dateTime.date().day());
    order[0]->pickUp->setHour(dateTime.time().hour());
    order[0]->pickUp->setMin(dateTime.time().minute());
    order[0]->pickUp->updateClass();

    orders[curOrderID].setPaid(checkBoxPaidDP->isChecked());

    //Save
    manager->saveOrders(orders[curOrderID]);
    manager->updateCustomer(customer[0]->getCustomerID());

    printReciept();
    showMainPage();

    //Clear
    customer.clear();
    order.clear();
    curOrderID = NULL;
    clearScreenDP();

}

void MainWindow::on_btnReturn_clicked()
{
    showMainPage();

    //If customer information was pulled up but nothing was added to order, delete order
    if(modelDP->rowCount() == 0 && !lineFNameDP ->text().isEmpty()){
        orders.pop_back();
        curOrderID--;
    }

    //Clear
    customer.clear();
    order.clear();
    clearScreenDP();
}



//
//***Customer Search Page (2)***
//
void MainWindow::on_btnReturnCS_clicked()
{
    clearScreenDP();
    MainWindow::showDropOffPage();
    lineSearchCustomerCS -> clear();
}

void MainWindow::on_btnNewCustomersCS_clicked()
{
    MainWindow::showNewCustomerPage();
    lineSearchCustomerCS -> clear();
}

void MainWindow::on_btnSearchCS_clicked()
{
    std::string entry = lineSearchCustomerCS->text().toStdString();
    size_t i;
    customer.clear();

    //Makes sure that the line entry isnt empyt before continuing
    if(lineSearchCustomerCS->text().isEmpty())
        return;

    //Make sure its a name or phone number before searching
    if(search::Search::isPhoneNumber(entry) || search::Search::isName(entry))
        customer = search::Search::searchCustAlgo(entry, this->customers);

    //Create List of matching customers
    for(i = 0; i < customer.size(); i++){
        QStandardItem *firstNameItem = new QStandardItem(QString::fromStdString(customer[i]->getFirstName()));
        QStandardItem *lastNameItem = new QStandardItem(QString::fromStdString(customer[i]->getLastName()));
        QStandardItem *phoneItem = new QStandardItem(QString::fromStdString(customer[i]->getPhone()));

        modelCSR->setItem(i, 0, firstNameItem);
        modelCSR->setItem(i, 1, lastNameItem);
        modelCSR->setItem(i, 2, phoneItem);
    }

    showCustomerSearchResultsPage();
}



//
//***Customer Search Results Page (3)***
//
void MainWindow::on_btnReturnCSR_clicked()
{
    modelCSR -> removeRows(0, modelCSR -> rowCount());
    showSearchPage();
}

void MainWindow::on_tableViewCSR_clicked(const QModelIndex &index)
{
    cust::customer* temp = customer[index.row()];
    curOrderID = orders.size();

    modelCSR -> removeRows(0, modelCSR -> rowCount());

    customer.clear();
    customer.push_back(temp); //Customer contains the pointer that points to the current customer that will be worked on

    lineSearchCustomerCS ->clear(); //search entry from the customer search page, clears so it looks cleaner    

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
void MainWindow::on_btnReturn_3_clicked()
{
    clearScreenDP();
    MainWindow::showSearchPage();
    clearScreenNC();
}

void MainWindow::on_btnCreate_clicked(){//(fi::File &manager){
    if(lineFNameNC->text().isEmpty() || lineLNameNC->text().isEmpty() || linePhoneNC->text().isEmpty())
        return;

    int customerID;
    QString firstName, lastName, phone;
    curOrderID = orders.size();

    firstName = lineFNameNC ->text();
    lastName = lineLNameNC -> text();
    phone = linePhoneNC -> text();

    clearScreenNC();

    //Setting up the new customer
    customerID = customers.size();
    customers.emplace_back(customerID, firstName.toStdString(), lastName.toStdString(), phone.toStdString());
    customer.clear();
    customer.push_back(&customers[customerID]); //contains only the customer that will be worked on

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
void MainWindow::setUpLaundryPage(){
    size_t row = 0, i, j;

    //tableWidgetLaundryOptions->setRowCount(0);

    if(modelDP->rowCount() == 0)
        for(i = 0; i < laundryPrices.size(); i++)
            for(j = 0; j < laundryPrices[i].size(); j++){
                QLabel *type = new QLabel(QString::fromStdString(laundryPrices[i][j].first));
                type->setAlignment(Qt::AlignCenter);

                QSpinBox *count = new QSpinBox(tableWidgetLaundryOptions);
                count->setValue(0);

                QDoubleSpinBox *price = new QDoubleSpinBox(tableWidgetLaundryOptions);
                price->setDecimals(2);
                price->setValue(laundryPrices[i][j].second);

                tableWidgetLaundryOptions->setCellWidget(row, 0, type);
                tableWidgetLaundryOptions->setCellWidget(row, 1, count);
                tableWidgetLaundryOptions->setCellWidget(row, 2, price);

                row++;
            }

}

void MainWindow::on_btnLaundryReturn_clicked(){
    QSpinBox *spinBox;
    bool empty = true;

    if(modelDP->rowCount() == 0 && lineFNameDP->text().isEmpty()){
        showDropOffPage();
        return;
    }
    for(int row = 0; row < tableWidgetLaundryOptions->rowCount(); row++){
        spinBox = qobject_cast<QSpinBox*>(tableWidgetLaundryOptions->cellWidget(row, 1));
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
    lineOrderTotalDP->setText(QString::number(order[0]->calculateCostO()));
    showDropOffPage();
}

void MainWindow::on_tableWidgetLaundryOptions_clicked(const QModelIndex &index){
    double price;
    int n, pos, row = index.row(), col = index.column();

    bool foundPrice;
    std::string article;
    std::tuple<std::string, int, double> tup;
    QSpinBox *spinBox;
    QDoubleSpinBox *dSpinBox;

    //Make this into case and switch, so i can allow a col to be a delete button

    if(col != 0)
        return;

    spinBox = qobject_cast<QSpinBox*>(tableWidgetLaundryOptions->cellWidget(row, 1));
    n = spinBox->value();
    if(n == 0)
        return;

    dSpinBox = qobject_cast<QDoubleSpinBox*>(tableWidgetLaundryOptions->cellWidget(row, 2));
    price = dSpinBox->value();

    article = qobject_cast<QLabel*>(tableWidgetLaundryOptions->cellWidget(row, 0))->text().toStdString();

    pos = getIndex(row, laundryPos);

    foundPrice = order[0]->setLaundryPiece(pos, n, price, article);

    if(foundPrice == true){
        n = orders[0].getLaundryNumberO(pos, article, price); //there's a crash somewhere here when adding two of the same articles at the same price twice
        spinBox->setValue(n);
    }
}



//
//***DryClean Order Page (5)***
//
void MainWindow::setUpDryCleanPage(){
    size_t row = 0, i, j;

    if(modelDP->rowCount() == 0)
        for(i = 0; i < dryCleanPrices.size(); i++)
            for(j = 0; j < dryCleanPrices[i].size(); j++){
                QLabel *type = new QLabel(QString::fromStdString(dryCleanPrices[i][j].first));
                type->setAlignment(Qt::AlignCenter);

                QSpinBox *count = new QSpinBox(tableWidgetDryCleanOptions);
                count->setValue(0);

                QDoubleSpinBox *price = new QDoubleSpinBox(tableWidgetDryCleanOptions);
                price->setDecimals(2);
                price->setValue(dryCleanPrices[i][j].second);

                tableWidgetDryCleanOptions->setCellWidget(row, 0, type);
                tableWidgetDryCleanOptions->setCellWidget(row, 1, count);
                tableWidgetDryCleanOptions->setCellWidget(row, 2, price);

                row++;
            }
    //else, clearing dry clean page

}

void MainWindow::on_btnDryCleanReturn_clicked(){
    QSpinBox *spinBox;
    bool empty = true;

    if(modelDP->rowCount() == 0 && lineFNameDP->text().isEmpty()){
        showDropOffPage();
        return;
    }

    for(int row = 0; row < tableWidgetDryCleanOptions->rowCount(); row++){
        spinBox = qobject_cast<QSpinBox*>(tableWidgetDryCleanOptions->cellWidget(row, 1));
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
    lineOrderTotalDP->setText(QString::number(order[0]->calculateCostO()));
    showDropOffPage();
}

void MainWindow::on_tableWidgetDryCleanOptions_clicked(const QModelIndex &index){
    double price;
    int n, pos, row = index.row(), col = index.column();

    bool foundPrice;
    std::string article;
    std::tuple<std::string, int, double> tup;
    QSpinBox *spinBox;
    QDoubleSpinBox *dSpinBox;

    //Make this into case and switch, so i can allow a col to be a delete button

    if(col != 0)
        return;

    spinBox = qobject_cast<QSpinBox*>(tableWidgetDryCleanOptions->cellWidget(row, 1));
    n = spinBox->value();
    if(n == 0)
        return;

    dSpinBox = qobject_cast<QDoubleSpinBox*>(tableWidgetDryCleanOptions->cellWidget(row, 2));
    price = dSpinBox->value();

    article = qobject_cast<QLabel*>(tableWidgetDryCleanOptions->cellWidget(row, 0))->text().toStdString();

    pos = getIndex(row, dryCleanPos);

    //setDryCleanPiece
    foundPrice = order[0]->setDryCleanPiece(pos, n, price, article);
    //getCleanNumberO
    if(foundPrice == true){
        n = orders[0].getDryCleanNumberO(pos, article, price); //there's a crash somewhere here when adding two of the same articles at the same price twice
        spinBox->setValue(n);
    }
}



//
//***Laundry Order Page (5)***
//



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
    orders[curOrderID].setPaid(checkBoxPaidPU->isChecked());
    orders[curOrderID].setPickUp(checkBoxPUPU->isChecked());

    manager->updateOrder(curOrderID);
    manager->updateCustomer(orders[curOrderID].getCustomerID());

    customer.clear();
    order.clear();
    curOrderID = NULL;

    showMainPage();
    clearScreenPU();
}

void MainWindow::on_btnReturnPU_clicked(){
    showMainPage();
    clearScreenPU();
}

void MainWindow::clearScreenPU(){
    modelPU -> removeRows(0, modelPU -> rowCount());
    lineFNamePU -> clear();
    lineLNamePU -> clear();
    linePhonePU -> clear();
    lineCustomerIDPU->clear();
    lineOrderIDPU->clear();
    lineOrderTotalPU->clear();
    checkBoxPaidPU->setCheckState(Qt::Unchecked);
    checkBoxPUPU->setCheckState(Qt::Unchecked);
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
    QString entryQ;
    std::string entry;
    size_t i;

    customer.clear();

    entryQ = lineSearchCustomerCSPU->text();
    if(entryQ.isEmpty())
        return;

    entry = entryQ.toStdString();

    if(search::Search::isPhoneNumber(entry) || search::Search::isName(entry))
        customer = search::Search::searchCustAlgo(entry, this->customers);

    for(i = 0; i < customer.size(); i++){
        QStandardItem *firstNameItem = new QStandardItem(QString::fromStdString(customer[i]->getFirstName()));
        QStandardItem *lastNameItem = new QStandardItem(QString::fromStdString(customer[i]->getLastName()));
        QStandardItem *phoneItem = new QStandardItem(QString::fromStdString(customer[i]->getPhone()));

        modelCSR->setItem(i, 0, firstNameItem);
        modelCSR->setItem(i, 1, lastNameItem);
        modelCSR->setItem(i, 2, phoneItem);
    }
    tableViewCSRPU -> setSelectionBehavior(QAbstractItemView::SelectRows);
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

    lineOrderTotalPU->setText(QString::number(order[0]->getCost()));

    showPickUpPage();
}



//
//***Customer Search ResultsPU (11)***
//
void MainWindow::on_btnReturnCSRPU_clicked(){
    modelCSRPU->removeRows(0, modelCSRPU->rowCount());
    showCustomerSearchPagePU();
}

void MainWindow::on_tableViewCSRPU_clicked(const QModelIndex &index){
    size_t i;
    cust::customer *temp = customer[index.row()];
    orderInfo::order *oTemp;

    customer.clear();
    order.clear();
    customer.push_back(temp);

    lineSearchCustomerCSPU->clear();

    std::vector<int> orderIDs = customer[0]->getOrders();

    for(i = 0; i < orderIDs.size(); i++)
        order.push_back(&orders[orderIDs[i]]);

    for(i = 0; i < order.size(); i++){
        oTemp = order.back();
        order.pop_back();

        QStandardItem *orderIDItem = new QStandardItem(QString::number(oTemp->getOrderID()));
        QStandardItem *dropOffItem = new QStandardItem(QString::fromStdString(oTemp->dropOff->getDate()));
        QStandardItem *pickUpItem = new QStandardItem(QString::fromStdString(oTemp->pickUp->getDate()));
        QStandardItem *totalItem = new QStandardItem(QString::number(oTemp->getCost()));

        modelOSR->setItem(i, 0, orderIDItem);
        modelOSR->setItem(i, 1, dropOffItem);
        modelOSR->setItem(i, 2, pickUpItem);
        modelOSR->setItem(i, 3, totalItem);
    }

    showOrderSearchResultsPU();
}



//
//***Order Search ResultsPU (12)***
//
void MainWindow::on_btnReturnOSR_clicked(){
    modelOSR->removeRows(0, modelOSR->rowCount());
    showCustomerSearchResultsPU();
}

void MainWindow::on_tableViewOSR_clicked(const QModelIndex &index){
    //orderInfo::order *temp;
    //int row = index.row(), col = index.column();
    //QModelIndex ind = modelOSR->index(row, col);
    order.clear();

    QVariant data = modelOSR->data(index, Qt::DisplayRole);

    curOrderID = data.toInt();
    order.push_back(&orders[curOrderID]);
    customer.push_back(&customers[order[0]->getCustomerID()]);

    updateCOInformationPU();
    updateModel(modelPU);

    lineOrderTotalPU->setText(QString::number(order[0]->getCost()));

    showPickUpPage();
}



//
//Helper Functions
//
void MainWindow::updateCOInformationDP(){
    lineFNameDP->setText(QString::fromStdString(customer[0]->getFirstName()));
    lineLNameDP->setText(QString::fromStdString(customer[0]->getLastName()));
    linePhoneDP->setText(QString::fromStdString(customer[0]->getPhone()));
    lineCustomerIDDP->setText(QString::number(customer[0]->getCustomerID()));
    lineOrderIDDP->setText(QString::number(order[0]->getOrderID()));

    setDate(dateDTDropOffDP, dateDTPickUpDP);

    dateDTDropOffDP->show();
    dateDTPickUpDP->show();
}

void MainWindow::updateCOInformationPU(){
    lineFNamePU->setText(QString::fromStdString(customer[0]->getFirstName()));
    lineLNamePU->setText(QString::fromStdString(customer[0]->getLastName()));
    linePhonePU->setText(QString::fromStdString(customer[0]->getPhone()));
    lineCustomerIDPU->setText(QString::number(customer[0]->getCustomerID()));
    lineOrderIDPU->setText(QString::number(order[0]->getOrderID()));

    //Set Date
    setDate(dateDTDropOffPU, dateDTPickUpPU);
    dateDTDropOffPU->show();
    dateDTPickUpPU->show();

    if(order[0]->getPaid() == true)
        checkBoxPaidPU->setCheckState(Qt::Checked);
    if(order[0]->getPickUp() == true)
        checkBoxPUPU->setCheckState(Qt::Checked);
    if(order[0]->getRack() != -1)
        lineRackPU->setText(QString::number(order[0]->getRack()));
}

void MainWindow::clearScreenDP(){
    modelDP -> removeRows(0, modelDP -> rowCount());
    lineFNameDP -> clear();
    lineLNameDP -> clear();
    linePhoneDP -> clear();
    dateDTDropOffDP -> clear();
    dateDTPickUpDP->clear();
    lineCustomerIDDP->clear();
    lineOrderIDDP->clear();
    lineOrderTotalDP ->clear();
    checkBoxPaidDP->setCheckState(Qt::Unchecked);

    dateDTDropOffDP->hide();
    dateDTPickUpDP->hide();
}

void MainWindow::clearScreenNC(){
    lineFNameNC->clear();
    lineLNameNC->clear();
    linePhoneNC->clear();
}

void MainWindow::setDate(QDateTimeEdit *dp, QDateTimeEdit *pu){
    QDate dateD(order[0]->dropOff->getYear(), order[0]->dropOff->getMonth(), order[0]->dropOff->getDay());
    QTime timeD(order[0]->dropOff->getHour(), order[0]->dropOff->getMin());
    QDateTime dateTimeD(dateD, timeD);
    dp->setDateTime(dateTimeD);

    QDate dateP(order[0]->pickUp->getYear(), order[0]->pickUp->getMonth(), order[0]->pickUp->getDay());
    QTime timeP(order[0]->pickUp->getHour(), order[0]->pickUp->getMin());
    QDateTime dateTimeP(dateP, timeP);
    pu->setDateTime(dateTimeP);
}

void MainWindow::updateModel(QStandardItemModel *model){
    size_t row = 0;
    std::vector<std::vector<std::tuple<std::string, int, double>>> laundry = order[0]->getLaundry(), dryClean = order[0]->getDryCleanO(), alterations = order[0]->getAlterationsO();

    model->removeRows(0, model->rowCount());

    row = updateTableView(laundry, model, "Laundry", row);
    row = updateTableView(dryClean, model, "Dry Clean", row);
    updateTableView(alterations, model, "Alterations", row);

}

size_t MainWindow::updateTableView(std::vector<std::vector<std::tuple<std::string, int, double>>> articles, QStandardItemModel *model, QString pieceType, size_t row){
    double pTotal;
    size_t i, j;
    QStandardItem *number, *type, *piece, *pricePerPiece, *priceTotal;

    for(i = 0; i < articles.size(); i++)
        if(articles[i].empty() == false)
            for(j = 0; j < articles[i].size(); j++){
                number = new QStandardItem(QString::number(std::get<1>(articles[i][j])));
                type = new QStandardItem(pieceType);
                piece = new QStandardItem(QString::fromStdString(std::get<0>(articles[i][j])));
                pricePerPiece = new QStandardItem(QString::number(std::get<2>(articles[i][j])));
                pTotal = std::get<1>(articles[i][j]) * std::get<2>(articles[i][j]);
                priceTotal = new QStandardItem(QString::number(pTotal));

                model->setItem(row, 0, number);
                model->setItem(row, 1, type);
                model->setItem(row, 2, piece);
                model->setItem(row, 3, pricePerPiece);
                model->setItem(row, 4, priceTotal);

                row++;
            }

    return row;
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

size_t MainWindow::getIndex(int curRow, std::vector<std::tuple<std::string, int, int>> articlePos){
    size_t i;

    for(i = 0; i < articlePos.size(); i++)
        if(curRow >= std::get<1>(articlePos[i]) && curRow <= std::get<2>(articlePos[i]))
            return i;

    return NULL;
}

int MainWindow::calculateSize(std::vector<std::vector<std::pair<std::string, double>>> prices){
    size_t i, j;
    int size = 0;

    for(i = 0; i < prices.size(); i++)
        for(j = 0; j < prices[i].size(); j++)
            size++;

    return size;
}

int MainWindow::calculatePieceTotal(std::vector<std::vector<std::tuple<std::string, int, double>>> articles){
    size_t i, j;
    int size = 0;

    for(i = 0; i < articles.size(); i++)
        for(j = 0; j < articles[i].size(); j++)
            size++;

    return size;
}

void MainWindow::printReciept(){
    int x = 50, y = 50;
    size_t i, j;
    std::vector<std::vector<std::tuple<std::string, int, double>>> laundry = order[0]->getLaundry(), dryClean = order[0]->getDryCleanO(), alterations = order[0]->getAlterationsO();
    QPainter painter(&printer);
    QFont font = painter.font();


    font.setPointSize(8);
    painter.setFont(font);

    painter.drawText(200, y, QString::number(curOrderID));
    y += 50;
    painter.drawText(x, y, QString::fromStdString(customer[0]->getLastName()) + ", " + QString::fromStdString(customer[0]->getFirstName()));
    y += 50;
    painter.drawText(x, y, "Phone: " + QString::fromStdString(customer[0]->getFormattedPhone()));
    y += 50;
    painter.drawText(x, y, "Drop Off: " + QString::fromStdString(order[0]->dropOff->dayOfWeekString()) + " " + QString::fromStdString(order[0]->dropOff->getDate_Time()));
    y += 50;
    painter.drawText(x, y, "Pick Up: " + QString::fromStdString(order[0]->pickUp->dayOfWeekString()) + " " + QString::fromStdString(order[0]->pickUp->getDate()));
    y += 50;

    painter.drawText(x, y, "==============================");
    y += 25;

    if(calculatePieceTotal(laundry)){
        painter.drawText(x, y, "Laundry: ");
        y += 25;

        for(i = 0; i < laundry.size(); i++)
            if(laundry[i].empty() == false)
                for(j = 0; j < laundry[i].size(); j++){
                    painter.drawText(x, y, QString::number(std::get<1>(laundry[i][j])) + "    " + QString::fromStdString(std::get<0>(laundry[i][j])) + "    " + QString::number(std::get<1>(laundry[i][j]) * std::get<2>(laundry[i][j])));
                    y += 25;
                }
        y += 25;
    }

    if(calculatePieceTotal(dryClean)){
        painter.drawText(x, y, "Dry Clean: ");
        y += 25;

        for(i = 0; i < dryClean.size(); i++)
            if(dryClean[i].empty() == false)
                for(j = 0; j < dryClean[i].size(); j++){
                    painter.drawText(x, y, QString::number(std::get<1>(dryClean[i][j])) + "    " + QString::fromStdString(std::get<0>(dryClean[i][j])) + "    " + QString::number(std::get<1>(dryClean[i][j]) * std::get<2>(dryClean[i][j])));
                    y += 25;
                }
        y += 25;
    }

    if(calculatePieceTotal(alterations)){
        painter.drawText(x, y, "Alterations: ");
        y += 25;

        for(i = 0; i < dryClean.size(); i++)
            if(dryClean[i].empty() == false)
                for(j = 0; j < dryClean[i].size(); j++){
                    painter.drawText(x, y, QString::number(std::get<1>(dryClean[i][j])) + "    " + QString::fromStdString(std::get<0>(dryClean[i][j])) + "    " + QString::number(std::get<1>(dryClean[i][j]) * std::get<2>(dryClean[i][j])));
                    y += 25;
                }
        y += 25;
    }

    painter.drawText(x, y, "==============================");
    y += 50;

    painter.drawText(x, y, "Total: " + QString::number(order[0]->getCost()));
    y += 50;
    if(order[0]->getPaid())
        painter.drawText(x, y, "Paid");

    y += 150;
    painter.drawText(x, y, "   ");

    // End the printing process
    painter.end();
}

