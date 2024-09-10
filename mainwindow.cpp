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
    std::string priceFile = "C:/Code/repos/LAVjr97/CProgram/price.txt";
    std::string tempOrderFile = "C:/Code/repos/LAVjr97/CProgram/tempOrder.txt";
    std::string tempCustFile = "C:/Code/repos/LAVjr97/CProgram/tempCust.txt";

    

    manager = new fi::File(customerFile, orderFile, priceFile, tempOrderFile, tempCustFile, this->customers, this->orders, this->laundryPrices, this->dryCleanPrices, this->alterationsPrices, this->laundryPos, this->dryCleanPos, this->alterationsPos);

    //Indepently load up customers and orders
    std::thread threadCust(&fi::File::loadCustomers, manager);
    std::thread threadOrder(&fi::File::loadOrders, manager);
    std::thread threadPrices(&fi::File::loadPrices, manager);

    threadCust.join();
    threadOrder.join();
    threadPrices.join();
/*
    laundryPrices = {{{"Pants", 4.99}, {"Jeans", 4.59}}, {{"Shirts", 3.99},{"T-Shirts", 3.49}}};
    dryCleanPrices = {{{"Pants", 6.99}, {"Jeans", 5.59}}, {{"Shirts", 4.99},{"T-Shirts", 4.49}}};
    alterationsPrices = {{{"Pants", 3.99}, {"Jeans", 3.59}}, {{"Shirts", 2.99},{"T-Shirts", 1.49}}};

    laundryPos = {{"Pants", 0, 2}, {"Shirts", 3, 5}};
    dryCleanPos = {{"Pants", 0, 2}, {"Shirts", 3, 5}}; //only 2 pants but because of the label, it increaseses by 1 for every type, so if there are 2 pieces in a type of article, then theres 3 "pieces"
    alterationsPos = {{"Pants", 0, 2}, {"Shirts", 3, 5}};

    manager->savePrices();
*/
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
    lineVisitsDP = ui->lineVisitsDP;
    linePieceTotalDP = ui->linePieceTotalDP;
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
    tableViewCSR->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

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
    //tableWidgetLaundryOptions->setRowCount(lPrices);
    tableWidgetLaundryOptions->setColumnCount(3);

    //Order DryClean Page
    tableWidgetDryCleanOptions = ui->tableWidgetDryCleanOptions;
    //tableWidgetDryCleanOptions->setRowCount(dcPrices);
    tableWidgetDryCleanOptions->setColumnCount(3);

    //Order Alterations Page
    tableWidgetAlterationsOptions = ui->tableWidgetAlterationsOptions;
    //tableWidgetAlterationsOptions->setRowCount(aPrices);
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
    linePieceTotalPU = ui->linePieceTotalPU;

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
    modelOSR->setColumnCount(4);
    modelOSR->setHorizontalHeaderLabels({"Order ID", "Drop Off", "Pick Up", "Total"});

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
    dateDTPickUpEO = ui->dateDTPickUpEO;
    linePieceTotalEO = ui->linePieceTotalEO;

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
    modelOSREO->setColumnCount(4);
    modelOSREO->setHorizontalHeaderLabels({"Order ID", "Drop Off", "Pick Up", "Total"});

    tableViewOSREO = ui->tableViewOSREO;
    tableViewOSREO->setModel(modelOSREO);
    tableViewOSREO->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableViewOSREO -> setSelectionBehavior(QAbstractItemView::SelectRows);

    //
    //
    //
    //modelCIP = new QStanardItemModel(this);
    tableWidgetLaundryCIP = ui->tableWidgetLaundryCIP;
    //tableWidgetLaundryCIP->setRowCount(lPrices + laundryPrices.size());
    tableWidgetLaundryCIP->setColumnCount(2);

    tableWidgetDryCleanCIP = ui->tableWidgetDryCleanCIP;
    //tableWidgetDryCleanCIP->setRowCount(dcPrices + dryCleanPrices.size());
    tableWidgetDryCleanCIP->setColumnCount(2);

    tableWidgetAlterationsCIP = ui->tableWidgetAlterationsCIP;
    //tableWidgetAlterationsCIP->setRowCount(aPrices + alterationsPrices.size());
    tableWidgetAlterationsCIP->setColumnCount(2);
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

void MainWindow::showEditOrderPage(){
    ui->stackedWidget->setCurrentIndex(13);
}

void MainWindow::showOrderSearchPageEO(){
    ui->stackedWidget->setCurrentIndex(14);
}

void MainWindow::showCustomerSearchPageEO(){
    ui->stackedWidget->setCurrentIndex(15);
}

void MainWindow::showCustomerSearchResultsEO(){
    ui->stackedWidget->setCurrentIndex(16);
}

void MainWindow::showOrderSearchResultsEO(){
    ui->stackedWidget->setCurrentIndex(17);
}

void MainWindow::showAdminPage(){
    ui->stackedWidget->setCurrentIndex(18);
}

void MainWindow::showItemsAndPricePage(){
    ui->stackedWidget->setCurrentIndex(19);
}


//
//***Main Home Page (0)***
//
void MainWindow::on_btnDropOff_clicked(){
    dateDTDropOffDP->hide();
    dateDTPickUpDP->hide();
    ui->btnOneRecieptDP->hide();
    ui->btnTwoRecieptDP->hide();

    showDropOffPage();
    //printReciept();
}

void MainWindow::on_btnPickUp_clicked(){
    dateDTDropOffPU->hide();
    dateDTPickUpPU->hide();
    showPickUpPage();
}

void MainWindow::on_btnEditOrder_clicked(){
    dateDTDropOffEO->hide();
    dateDTPickUpEO->hide();
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

    setUpAlterationsPage();

    MainWindow::showOrderAlterationsPage();
}

void MainWindow::on_btnSaveDP_clicked()
{
    if(lineFNameDP->text().isEmpty())
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


    std::thread threadOrder(&fi::File::saveOrders, manager, std::ref(orders[curOrderID]));
    std::thread threadCust(&fi::File::updateCustomer, manager, customer[0]->getCustomerID());
    threadOrder.join();
    threadCust.join();

    ui->btnOneRecieptDP->show();
    ui->btnTwoRecieptDP->show();


    //printReciept();
    //showMainPage();
}

void MainWindow::on_btnOneRecieptDP_clicked()
{
    printReciept();

    customer.clear();
    order.clear();
    curOrderID = NULL;
    clearScreenDP();

    showMainPage();
}

void MainWindow::on_btnTwoRecieptDP_clicked()
{
    printReciept();
    printReciept();

    customer.clear();
    order.clear();
    curOrderID = NULL;
    clearScreenDP();

    showMainPage();
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
        QStandardItem *phoneItem = new QStandardItem(QString::fromStdString(customer[i]->getFormattedPhone()));

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
    QFont font;

    tableWidgetLaundryOptions->setRowCount(calculateSize(laundryPrices));

    for(i = 0; i < laundryPrices.size(); i++)
        for(j = 0; j < laundryPrices[i].size(); j++){
            if(j == 0){
                QLabel *label = new QLabel(QString::fromStdString(std::get<0>(laundryPos[i])));
                label->setAlignment(Qt::AlignCenter);
                font = label->font();
                font.setBold(true);
                label->setFont(font);

                tableWidgetLaundryOptions->setCellWidget(row, 0, label);

                row++;
            }

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
    lineOrderTotalDP->setText(QString::number(order[0]->calculateCostO()));
    showDropOffPage();
}

void MainWindow::on_tableWidgetLaundryOptions_clicked(const QModelIndex &index){
    double price;
    int n, pos, row = index.row(), col = index.column();

    std::string article;
    std::tuple<std::string, int, double> tup;
    QTableWidgetItem *type;
    QSpinBox *spinBox;
    QDoubleSpinBox *dSpinBox;

    //Make this into case and switch, so i can allow a col to be a delete button
    spinBox = qobject_cast<QSpinBox*>(tableWidgetLaundryOptions->cellWidget(row, 1));

    if(col != 0 || spinBox == nullptr)
        return;

    spinBox = qobject_cast<QSpinBox*>(tableWidgetLaundryOptions->cellWidget(row, 1));
    n = spinBox->value();
    if(n == 0)
        return;

    dSpinBox = qobject_cast<QDoubleSpinBox*>(tableWidgetLaundryOptions->cellWidget(row, 2));
    price = dSpinBox->value();

    article = qobject_cast<QLabel*>(tableWidgetLaundryOptions->cellWidget(row, 0))->text().toStdString();
    pos = getIndex(row, laundryPos);

    order[0]->setLaundryPiece(pos, n, price, article);

    //type = tableWidgetLaundryOptions->item(row, col);
    //QColor bgColor = type->background().color();
    //qDebug() << "BackGroundColor: " << bgColor.red() << " " << bgColor.green() << " " << bgColor.blue();
    //type->setBackground(Qt::green);


}



//
//***DryClean Order Page (5)***
//
void MainWindow::setUpDryCleanPage(){
    size_t row = 0, i, j;
    QFont font;

    tableWidgetDryCleanOptions->setRowCount(calculateSize(dryCleanPrices));


    for(i = 0; i < dryCleanPrices.size(); i++)
        for(j = 0; j < dryCleanPrices[i].size(); j++){
            if(j == 0){
                QLabel *label = new QLabel(QString::fromStdString(std::get<0>(dryCleanPos[i])));
                label->setAlignment(Qt::AlignCenter);
                font = label->font();
                font.setBold(true);
                label->setFont(font);

                tableWidgetDryCleanOptions->setCellWidget(row, 0, label);
                row++;
            }

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
    lineOrderTotalDP->setText(QString::number(order[0]->calculateCostO()));
    showDropOffPage();
}

void MainWindow::on_tableWidgetDryCleanOptions_clicked(const QModelIndex &index){
    double price;
    int n, pos, row = index.row(), col = index.column();

    std::string article;
    std::tuple<std::string, int, double> tup;
    QSpinBox *spinBox;
    QDoubleSpinBox *dSpinBox;

    //Make this into case and switch, so i can allow a col to be a delete button
    spinBox = qobject_cast<QSpinBox*>(tableWidgetDryCleanOptions->cellWidget(row, 1));

    if(col != 0 || spinBox == nullptr)
        return;

    n = spinBox->value();
    if(n == 0)
        return;

    dSpinBox = qobject_cast<QDoubleSpinBox*>(tableWidgetDryCleanOptions->cellWidget(row, 2));
    price = dSpinBox->value();

    article = qobject_cast<QLabel*>(tableWidgetDryCleanOptions->cellWidget(row, 0))->text().toStdString();

    pos = getIndex(row, dryCleanPos);

    order[0]->setDryCleanPiece(pos, n, price, article);

}



//
//***Alterations Order Page (7)***
//
void MainWindow::setUpAlterationsPage(){
    size_t row = 0, i, j;
    QFont font;

    tableWidgetAlterationsOptions->setRowCount(calculateSize(alterationsPrices));


    for(i = 0; i < alterationsPrices.size(); i++)
        for(j = 0; j < alterationsPrices[i].size(); j++){
            if(j == 0){
                QLabel *label = new QLabel(QString::fromStdString(std::get<0>(alterationsPos[i])));
                label->setAlignment(Qt::AlignCenter);
                font = label->font();
                font.setBold(true);
                label->setFont(font);

                tableWidgetAlterationsOptions->setCellWidget(row, 0, label);
                row++;
            }

            QLabel *type = new QLabel(QString::fromStdString(alterationsPrices[i][j].first));
            type->setAlignment(Qt::AlignCenter);

            QSpinBox *count = new QSpinBox(tableWidgetAlterationsOptions);
            count->setValue(0);

            QDoubleSpinBox *price = new QDoubleSpinBox(tableWidgetAlterationsOptions);
            price->setDecimals(2);
            price->setValue(alterationsPrices[i][j].second);

            tableWidgetAlterationsOptions->setCellWidget(row, 0, type);
            tableWidgetAlterationsOptions->setCellWidget(row, 1, count);
            tableWidgetAlterationsOptions->setCellWidget(row, 2, price);
            row++;
        }


}

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
    lineOrderTotalDP->setText(QString::number(order[0]->calculateCostO()));
    showDropOffPage();
}

void MainWindow::on_tableWidgetAlterationsOptions_clicked(const QModelIndex &index){
    double price;
    int n, pos, row = index.row(), col = index.column();

    std::string article;
    std::tuple<std::string, int, double> tup;
    QSpinBox *spinBox;
    QDoubleSpinBox *dSpinBox;

    //Make this into case and switch, so i can allow a col to be a delete button
    spinBox = qobject_cast<QSpinBox*>(tableWidgetAlterationsOptions->cellWidget(row, 1));
    if(col != 0 || spinBox == nullptr)
        return;

    spinBox = qobject_cast<QSpinBox*>(tableWidgetAlterationsOptions->cellWidget(row, 1));
    n = spinBox->value();
    if(n == 0)
        return;

    dSpinBox = qobject_cast<QDoubleSpinBox*>(tableWidgetAlterationsOptions->cellWidget(row, 2));
    price = dSpinBox->value();

    article = qobject_cast<QLabel*>(tableWidgetAlterationsOptions->cellWidget(row, 0))->text().toStdString();

    pos = getIndex(row, alterationsPos);

    order[0]->setAlterationsPiece(pos, n, price, article);
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

    orders[curOrderID].setPaid(checkBoxPaidPU->isChecked());
    orders[curOrderID].setPickUp(checkBoxPUPU->isChecked());

    std::thread threadOrder(&fi::File::updateOrder, manager, curOrderID);
    std::thread threadCust(&fi::File::updateCustomer, manager, orders[curOrderID].getCustomerID());
    threadOrder.join();
    threadCust.join();

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
    customer.clear();
    order.clear();

    showCustomerSearchPagePU();
}

void MainWindow::on_tableViewCSRPU_clicked(const QModelIndex &index){
    size_t i;
    cust::customer *temp = customer[index.row()];
    std::vector<orderInfo::order*> oTemp;

    customer.clear();
    order.clear();
    customer.push_back(temp);

    lineSearchCustomerCSPU->clear();

    std::vector<int> orderIDs = customer[0]->getOrders();

    for(i = 0; i < orderIDs.size(); i++)
        oTemp.push_back(&orders[orderIDs[i]]);

    size_t size = oTemp.size();

    for(i = 0; i < size; i++){
        order.push_back(oTemp.back());
        oTemp.pop_back();

        QStandardItem *orderIDItem = new QStandardItem(QString::number(order[i]->getOrderID()));
        QStandardItem *dropOffItem = new QStandardItem(QString::fromStdString(order[i]->dropOff->getDate()));
        QStandardItem *pickUpItem = new QStandardItem(QString::fromStdString(order[i]->pickUp->getDate()));
        QStandardItem *totalItem = new QStandardItem(QString::number(order[i]->getCost()));

        modelOSR->setItem(i, 0, orderIDItem);
        modelOSR->setItem(i, 1, dropOffItem);
        modelOSR->setItem(i, 2, pickUpItem);
        modelOSR->setItem(i, 3, totalItem);
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
    updateCOInformationPU();
    updateModel(modelPU);
    lineOrderTotalPU->setText(QString::number(order[0]->getCost()));

    showPickUpPage();
}



//
//***Edit Order Page (13)***
//
void MainWindow::on_btnCustomerEO_clicked(){
    showCustomerSearchPageEO();
}

void MainWindow::on_btnOrderSearchEO_clicked(){
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

    /*
    for(int row = 0; row < modelEO ->rowCount(); row++){
        QModelIndex indexPiece = modelEO->index(row, 2);
        QModelIndex indexN = modelEO->index(row, 0);
        QModelIndex indexPrice = modelEO->index(row, 3);

        QVariant itemPiece = modelEO->data(indexPiece);
        QVariant itemN = modelEO->data(indexN);
        QVariant itemPrice = modelEO->data(indexPrice);

        temp = std::make_tuple(itemPiece.toString().toStdString(), itemN.toInt(), itemPrice.toDouble());
    }
    */

    std::thread threadOrder(&fi::File::updateOrder, manager, curOrderID);
    std::thread threadCust(&fi::File::updateCustomer, manager, orders[curOrderID].getCustomerID());
    threadOrder.join();
    threadCust.join();

    printReciept();

    customer.clear();
    order.clear();
    curOrderID = NULL;

    showMainPage();
    clearScreenEO();
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

    lineOrderTotalEO->setText(QString::number(order[0]->getCost()));

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
    QString entryQ;
    std::string entry;
    size_t i;

    customer.clear();

    entryQ = lineSearchCustomerCSEO->text();
    if(entryQ.isEmpty())
        return;

    entry = entryQ.toStdString();

    if(search::Search::isPhoneNumber(entry) || search::Search::isName(entry))
        customer = search::Search::searchCustAlgo(entry, this->customers);

    for(i = 0; i < customer.size(); i++){
        QStandardItem *firstNameItem = new QStandardItem(QString::fromStdString(customer[i]->getFirstName()));
        QStandardItem *lastNameItem = new QStandardItem(QString::fromStdString(customer[i]->getLastName()));
        QStandardItem *phoneItem = new QStandardItem(QString::fromStdString(customer[i]->getFormattedPhone()));

        modelCSREO->setItem(i, 0, firstNameItem);
        modelCSREO->setItem(i, 1, lastNameItem);
        modelCSREO->setItem(i, 2, phoneItem);
    }
    tableViewCSREO -> setSelectionBehavior(QAbstractItemView::SelectRows);
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
    size_t i;
    cust::customer *temp = customer[index.row()];
    std::vector<orderInfo::order*> oTemp;

    customer.clear();
    order.clear();
    customer.push_back(temp);

    lineSearchCustomerCSEO->clear();

    std::vector<int> orderIDs = customer[0]->getOrders();

    for(i = 0; i < orderIDs.size(); i++)
        oTemp.push_back(&orders[orderIDs[i]]);

    size_t size = oTemp.size();

    for(i = 0; i < size; i++){
        order.push_back(oTemp.back());
        oTemp.pop_back();

        QStandardItem *orderIDItem = new QStandardItem(QString::number(order[i]->getOrderID()));
        QStandardItem *dropOffItem = new QStandardItem(QString::fromStdString(order[i]->dropOff->getDate()));
        QStandardItem *pickUpItem = new QStandardItem(QString::fromStdString(order[i]->pickUp->getDate()));
        QStandardItem *totalItem = new QStandardItem(QString::number(order[i]->getCost()));

        modelOSREO->setItem(i, 0, orderIDItem);
        modelOSREO->setItem(i, 1, dropOffItem);
        modelOSREO->setItem(i, 2, pickUpItem);
        modelOSREO->setItem(i, 3, totalItem);
    }

    showOrderSearchResultsEO();
    lineRackEO->setFocus();

    modelCSREO->removeRows(0, modelCSRPU->rowCount());
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

    order.push_back(&orders[curOrderID]);
    updateCOInformationEO();
    updateModel(modelEO);
    lineOrderTotalEO->setText(QString::number(order[0]->getCost()));

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
    showAdminPage();
}

void MainWindow::on_btnSaveCIP_clicked(){

    saveTableCIP(laundryPrices, laundryPos, tableWidgetLaundryCIP);
    saveTableCIP(dryCleanPrices, dryCleanPos, tableWidgetDryCleanCIP);
    saveTableCIP(alterationsPrices, alterationsPos, tableWidgetAlterationsCIP);

    manager->savePrices();
    //showAdminPage();
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
        if(piece.empty() && price == 0)
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
        if(piece != prices[typeI][pieceI].first){
            prices[typeI][pieceI].first = piece;
            //if(pieceI == 0)
            //    std::get<0>(pos[typeI]) = piece;
        }

        //if the price has been changed
        if(price != prices[typeI][pieceI].second)
            prices[typeI][pieceI].second = price;

        pieceI++;
    }
    pieceI = 0;
    //typeI++;

    newType = qobject_cast<QLineEdit*>(tableWidget->cellWidget(row, 1));

    if(newType != nullptr)
        if(!newType->text().isEmpty())
            createType(typeI, pos, prices, newType->text().toStdString());

    row++;
    /*
    linePiece = qobject_cast<QLineEdit*>(tableWidget->cellWidget(row, 0));
    dSpinBox = qobject_cast<QDoubleSpinBox*>(tableWidget->cellWidget(row, 1));
    piece = linePiece->text().toStdString();
    price = dSpinBox->value();

    //if a new type has been added
    if(!piece.empty() && price != 0)
        createType(typeI, pos, prices, piece, price);
    */
}


void MainWindow::setUpCIPPage(){
    //lPrices = calculateSize(laundryPrices);
    //dcPrices = calculateSize(dryCleanPrices);
    //aPrices = calculateSize(alterationsPrices);

    setUpTableWidgetsCIP(laundryPrices, laundryPos, tableWidgetLaundryCIP);
    setUpTableWidgetsCIP(dryCleanPrices, dryCleanPos, tableWidgetDryCleanCIP);
    setUpTableWidgetsCIP(alterationsPrices, alterationsPos, tableWidgetAlterationsCIP);
}

void MainWindow::setUpTableWidgetsCIP(std::vector<std::vector<std::pair<std::string, double>>> &prices, std::vector<std::tuple<std::string, int, int>> &pos, QTableWidget *tableWidget){
    size_t row = 0, i, j;
    QFont font;

    if(prices[0][0].first == "" && std::get<0>(pos[0]) == "")
        tableWidget->setRowCount(1);

    else{
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
    //row++;
    /*
    QLineEdit *type = new QLineEdit(tableWidget);
    QDoubleSpinBox *newPrice = new QDoubleSpinBox(tableWidget);
    newPrice ->setDecimals(2);
    tableWidget->setCellWidget(row, 0, type);
    tableWidget->setCellWidget(row, 1, newPrice);
    */
}




//
//Helper Functions
//
void MainWindow::updateCOInformationDP(){
    lineFNameDP->setText(QString::fromStdString(customer[0]->getFirstName()));
    lineLNameDP->setText(QString::fromStdString(customer[0]->getLastName()));
    linePhoneDP->setText(QString::fromStdString(customer[0]->getFormattedPhone()));
    lineCustomerIDDP->setText(QString::number(customer[0]->getCustomerID()));
    lineOrderIDDP->setText(QString::number(order[0]->getOrderID()));
    lineVisitsDP->setText(QString::number(customer[0]->getVisit() + 1));

    setDate(dateDTDropOffDP, dateDTPickUpDP);

    dateDTDropOffDP->show();
    dateDTPickUpDP->show();
}

void MainWindow::updateCOInformationPU(){
    lineFNamePU->setText(QString::fromStdString(customer[0]->getFirstName()));
    lineLNamePU->setText(QString::fromStdString(customer[0]->getLastName()));
    linePhonePU->setText(QString::fromStdString(customer[0]->getFormattedPhone()));
    lineCustomerIDPU->setText(QString::number(customer[0]->getCustomerID()));
    lineOrderIDPU->setText(QString::number(order[0]->getOrderID()));
    linePieceTotalPU->setText(QString::number(order[0]->getPieceTotal()));
    
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

void MainWindow::updateCOInformationEO(){
    lineFNameEO->setText(QString::fromStdString(customer[0]->getFirstName()));
    lineLNameEO->setText(QString::fromStdString(customer[0]->getLastName()));
    linePhoneEO->setText(QString::fromStdString(customer[0]->getFormattedPhone()));
    lineCustomerIDEO->setText(QString::number(customer[0]->getCustomerID()));
    lineOrderIDEO->setText(QString::number(order[0]->getOrderID()));
    linePieceTotalEO->setText(QString::number(order[0]->getPieceTotal()));

    //Set Date
    setDate(dateDTDropOffEO, dateDTPickUpEO);
    dateDTDropOffEO->show();
    dateDTPickUpEO->show();

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
    dateDTPickUpDP->clear();
    lineCustomerIDDP->clear();
    lineOrderIDDP->clear();
    lineOrderTotalDP ->clear();
    lineVisitsDP->clear();
    linePieceTotalDP->clear();

    checkBoxPaidDP->setCheckState(Qt::Unchecked);

    dateDTDropOffDP->hide();
    dateDTPickUpDP->hide();
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

    checkBoxPaidEO->setCheckState(Qt::Unchecked);
    checkBoxPUEO->setCheckState(Qt::Unchecked);
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

int MainWindow::calculatePieceTotal(std::vector<std::vector<std::tuple<std::string, int, double>>> articles){
    size_t i, j;
    int size = 0;

    for(i = 0; i < articles.size(); i++)
        for(j = 0; j < articles[i].size(); j++)
            size++;

    return size;
}

void MainWindow::printReciept(){

    int x = 50, y = 10, yInc = 35;
    size_t i, j;
    std::vector<std::vector<std::tuple<std::string, int, double>>> laundry = order[0]->getLaundry(), dryClean = order[0]->getDryCleanO(), alterations = order[0]->getAlterationsO();
    std::vector<QString> info;

    int lPos = 0, dcPos = 0, altPos = 0, totalLines = 0, height, width = 360, difX = 30, difY = 22;

    QPrintDialog printDialog(&printer, this);



    QPainter painter(&printer);
    QFont font = painter.font();
    QFontMetrics metrics(font);

    //calculate box length;
    if(calculatePieceTotal(laundry)){
        lPos = 1;
        for(i = 0; i < laundry.size(); i++)
            if(laundry[i].empty() == false)
                for(j = 0; j < laundry[i].size(); j++)
                    lPos++;
    }

    if(calculatePieceTotal(dryClean)){
        dcPos = 1;
        for(i = 0; i < dryClean.size(); i++)
            if(dryClean[i].empty() == false)
                for(j = 0; j < dryClean[i].size(); j++)
                    dcPos++;
    }
    if(calculatePieceTotal(alterations)){
        altPos = 1;
        for(i = 0; i < alterations.size(); i++)
            if(alterations[i].empty() == false)
                for(j = 0; j < alterations[i].size(); j++)
                    altPos++;
    }

    totalLines = lPos + dcPos + altPos;
    //Height in Pixels
    height = 50;

    //Height in lines
    //height = (height * totalLines) - 15;


    font.setPointSize(12);
    font.setBold(true);
    painter.setFont(font);

    //Order ID
    painter.drawText(QRect(x, y, width, metrics.height()), Qt::AlignCenter, QString::number(curOrderID));
    y = y + yInc + 15;


    font.setPointSize(9);
    font.setBold(false);
    painter.setFont(font);

    //Shop Information
    painter.drawText(QRect(x, y, width, metrics.height()), Qt::AlignCenter, "Cleaning and Alteration Shop");
    y += yInc - 5;
    painter.drawText(QRect(x, y, width, metrics.height()), Qt::AlignCenter, "1709 Tully Rd, Suite C");
    y += yInc - 5;
    painter.drawText(QRect(x, y, width, metrics.height()), Qt::AlignCenter, "(408) 258-5705");

    y = y + yInc + 19;

    //Customer Information
    painter.drawText(x, y, QString::fromStdString(customer[0]->getLastName()) + ", " + QString::fromStdString(customer[0]->getFirstName()));
    y += yInc;
    painter.drawText(x, y, "Phone: " + QString::fromStdString(customer[0]->getFormattedPhone()));
    y += yInc;

    //Dates
    painter.drawText(x, y, "Drop Off: " + QString::fromStdString(order[0]->dropOff->dayOfWeekString()) + " " + QString::fromStdString(order[0]->dropOff->getDate_Time()));
    y += yInc;
    painter.drawText(x, y, "Pick Up: " + QString::fromStdString(order[0]->pickUp->dayOfWeekString()) + " " + QString::fromStdString(order[0]->pickUp->getDate()));
    y += yInc;

    //Order Information
    painter.drawText(x, y, "=========================");
    yInc = 25;
    y += yInc;
    if(calculatePieceTotal(laundry)){
        painter.drawText(x, y, "Laundry: ");
        y += yInc;

        for(i = 0; i < laundry.size(); i++)
            if(laundry[i].empty() == false)
                for(j = 0; j < laundry[i].size(); j++){
                    painter.drawText(x, y, QString::number(std::get<1>(laundry[i][j])));
                    painter.drawText(QRect(x + difX, y - difY, width, metrics.height()), Qt::AlignLeft, QString::fromStdString(std::get<0>(laundry[i][j])));
                    painter.drawText(QRect(x, y - difY, width, metrics.height()), Qt::AlignRight, QString::number(std::get<1>(laundry[i][j]) * std::get<2>(laundry[i][j])));
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
                    painter.drawText(x, y, QString::number(std::get<1>(dryClean[i][j])));
                    painter.drawText(QRect(x + difX, y - difY, width, metrics.height()), Qt::AlignLeft, QString::fromStdString(std::get<0>(dryClean[i][j])));
                    painter.drawText(QRect(x, y - difY, width, metrics.height()), Qt::AlignRight, QString::number(std::get<1>(dryClean[i][j]) * std::get<2>(dryClean[i][j])));
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
                    painter.drawText(x, y, QString::number(std::get<1>(alterations[i][j])));
                    painter.drawText(QRect(x + difX, y - difY, width, metrics.height()), Qt::AlignLeft, QString::fromStdString(std::get<0>(alterations[i][j])));
                    painter.drawText(QRect(x, y - difY, width, metrics.height()), Qt::AlignRight, QString::number(std::get<1>(alterations[i][j]) * std::get<2>(alterations[i][j])));
                    y += yInc;
                }
        y += yInc;
    }
    painter.drawText(x, y - yInc, "=========================");

    //Total Information
    painter.drawText(QRect(x, y, width, metrics.height()), Qt::AlignLeft, "Pieces: " + QString::number(order[0]->getPieceTotal()));
    if(order[0]->getPaid())
        painter.drawText(QRect(x, y, width, metrics.height()), Qt::AlignCenter, "Paid");
    painter.drawText(QRect(x, y, width, metrics.height()), Qt::AlignRight, "Total: " + QString::number(order[0]->getCost()));


    y += 80;
    font.setPointSize(12);
    font.setBold(true);
    painter.setFont(font);
    painter.drawText(QRect(x, y, width, metrics.height()), Qt::AlignCenter, QString::number(curOrderID));


    // End the printing process
    painter.end();
}




