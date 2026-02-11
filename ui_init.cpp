#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    std::string customerFile = "./data/customers.txt";
    std::string orderFile = "./data/orders.txt";
    std::string priceFile = "./data/prices.txt";
    std::string tempOrderFile = "./data/tempOrder.txt";
    std::string tempCustFile = "./data/tempCust.txt";
    std::string logFile = "./logs/log.txt";
    //*/
    //Release version uses these file paths
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
    widgetTaxDP = ui->widgetTaxDP;
    lineOrderTaxDP = ui->lineOrderTaxDP;
    lineOrderDiscountDP = ui->lineOrderDiscountDP;
    checkBoxPaidDP = ui->checkBoxPaidDP;
    checkBoxTaxDP = ui->checkBoxTaxDP;

    //connect(checkBoxTaxDP, &QCheckBox::toggled, widgetTaxDP, &QWidget::setVisible);
    connect(checkBoxTaxDP, &QCheckBox::toggled, this, &MainWindow::update_checkBoxToggleDP);
    checkBoxPaidDP->setCheckable(false);
    checkBoxTaxDP->setCheckable(false);
    widgetTaxDP->setVisible(false);

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
    checkBoxTaxPU = ui->checkBoxTaxPU;
    checkBoxPaidPU = ui->checkBoxPaidPU;

    checkBoxTaxPU->setEnabled(false);

    dateDTDropOffPU = ui->dateDTDropOffPU;
    dateDPickUpPU = ui->dateDPickUpPU;
    linePieceTotalPU = ui->linePieceTotalPU;
    lineOrderSubTotalPU = ui->lineOrderSubTotalPU;
    widgetTaxPU = ui->widgetTaxPU;
    widgetTaxPU->setVisible(false);
    lineOrderTaxPU = ui->lineOrderTaxPU;
    lineOrderDiscountPU = ui->lineOrderDiscountPU;
    widgetDiscountPU = ui->widgetDiscountPU;
    widgetDiscountPU->setVisible(false);

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
    checkBoxTaxEO = ui->checkBoxTaxEO;
    checkBoxPaidEO = ui->checkBoxPaidEO;

    connect(checkBoxTaxDP, &QCheckBox::toggled, this, &MainWindow::update_checkBoxToggleDP);
    checkBoxTaxEO->setCheckable(false);

    dateDTDropOffEO = ui->dateDTDropOffEO;
    dateDPickUpEO = ui->dateDPickUpEO;
    linePieceTotalEO = ui->linePieceTotalEO;
    lineOrderSubTotalEO = ui->lineOrderSubTotalEO;
    widgetTaxEO = ui->widgetTaxEO;
    widgetTaxEO->setVisible(false);
    lineOrderTaxEO = ui->lineOrderTaxEO;
    lineOrderDiscountEO = ui->lineOrderDiscountEO;
    widgetDiscountEO = ui->widgetDiscountEO;
    widgetDiscountEO->setVisible(false);
    widgetVoidOrderEO = ui->widgetVoidOrderEO;
    widgetVoidOrderEO->setVisible(false);

    ui->btnLaundryEO->setEnabled(false);
    ui->btnDryCleanEO->setEnabled(false);
    ui->btnAlterationsEO->setEnabled(false);


    modelEO = new QStandardItemModel(this);
    modelEO->setColumnCount(5);
    modelEO->setHorizontalHeaderLabels({"Number", "Type", "Piece", "Price Per Piece", "Price Total"});

    tableViewOrdersEO = ui->tableViewOrdersEO;
    tableViewOrdersEO->setModel(modelEO);
    tableViewOrdersEO->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    tableWidgetLaundryOptionsEO = ui->tableWidgetLaundryOptionsEO;
    tableWidgetDryCleanOptionsEO = ui->tableWidgetDryCleanOptionsEO;
    tableWidgetAlterationsOptionsEO = ui->tableWidgetAlterationsOptionsEO;

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


    //
    //***Customer Edit Page (20)***
    //
    modelCEP = new QStandardItemModel(this);
    modelCEP->setColumnCount(5);
    modelCEP->setHorizontalHeaderLabels({"ID", "First Name", "Last Name", "Phone Number", "Number of Orders"});

    tableViewCustomerInfoCEP = ui->tableViewCustomerInfoCEP;
    tableViewCustomerInfoCEP->setModel(modelCEP);
    tableViewCustomerInfoCEP->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    lineFNameCEP = ui->lineFNameCEP;
    lineLNameCEP = ui->lineLNameCEP;
    linePhoneCEP = ui->linePhoneCEP;
    lineSearchCEP = ui->lineSearchCEP;

    showMainPage();
}

MainWindow::~MainWindow()
{
    delete ui;
}
