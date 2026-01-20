#include "mainwindow.h"
#include "ui_mainwindow.h"

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

    setUpOptionsTables(tableWidgetLaundryOptions, laundry);

    MainWindow::showOrderLaundryPage();
    ui->btnOneRecieptDP->setEnabled(false);
    ui->btnTwoRecieptDP->setEnabled(false);
}

void MainWindow::on_btnDryClean_clicked(){
    if(lineFNameDP->text().isEmpty())
        return;

    setUpOptionsTables(tableWidgetDryCleanOptions, dryClean);

    MainWindow::showOrderDryCleanPage();
    ui->btnOneRecieptDP->setEnabled(false);
    ui->btnTwoRecieptDP->setEnabled(false);
}

void MainWindow::on_btnAlterations_clicked(){
    if(lineFNameDP->text().isEmpty())
        return;

    setUpOptionsTables(tableWidgetAlterationsOptions, alterations);

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
    lineOrderSubTotalDP->setText(QString::number(order[0]->calculateSubTotal(), 'f', 2));
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
    manager->logger.log("Two reciepts printed, order saved");
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

    if(!lineFNameDP->text().isEmpty()){
        orders.pop_back();
        curOrderID = -1;
    }

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

    if(curOrderID != 0){
        size_t prevOrderID = orders[curOrderID - 1].getOrderID();
        if(curOrderID - 1 != prevOrderID)
            curOrderID = prevOrderID++;

        if(orders[curOrderID - 1].getOrderID() == curOrderID){
            std::string message = "New OrderID: " + std::to_string(curOrderID) + " with CustomerID: " + std::to_string(customer[0]->getCustomerID()) +  " already exists, existing customerID is: " + std::to_string(orders[curOrderID - 1].getCustomerID()) + ", Existing OrderID: " + std::to_string(orders[curOrderID - 1].getOrderID()) + " Occured in 'on_tableViewCSR_clicked'";
            manager->logger.log(message);
            handleCritcalError();
        }
    }
    else
        manager->logger.log("CurOrderID was 0");

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

    if(curOrderID != 0){
        size_t prevOrderID = orders[curOrderID - 1].getOrderID();
        if(curOrderID - 1 != prevOrderID)
            curOrderID = prevOrderID++;

        if(orders[curOrderID - 1].getOrderID() == curOrderID){
            std::string message = "New OrderID: " + std::to_string(curOrderID) + " with CustomerID: " + std::to_string(customer[0]->getCustomerID()) +  " already exists, existing customerID is: " + std::to_string(orders[curOrderID - 1].getCustomerID()) + " Occured in 'on_btnCreate_clicked'";
            manager->logger.log(message);
            handleCritcalError();
        }
    }
    else
        manager->logger.log("CurOrderID was 0");


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
    lineOrderSubTotalDP->setText(QString::number(order[0]->calculateSubTotal(), 'f', 2));
    lineOrderTotalDP->setText(QString::number(order[0]->getDiscountedCost(), 'f', 2));

    showDropOffPage();
}

void MainWindow::on_tableWidgetLaundryOptions_clicked(const QModelIndex &index){
    tableWidgetOptions(tableWidgetLaundryOptions, index, laundry, 1);
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
    lineOrderSubTotalDP->setText(QString::number(order[0]->calculateSubTotal(), 'f', 2));
    lineOrderTotalDP->setText(QString::number(order[0]->getDiscountedCost(), 'f', 2));

    showDropOffPage();
}

void MainWindow::on_tableWidgetDryCleanOptions_clicked(const QModelIndex &index){
    tableWidgetOptions(tableWidgetDryCleanOptions, index, dryClean, 2);
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
    lineOrderSubTotalDP->setText(QString::number(order[0]->calculateSubTotal(), 'f', 2));
    lineOrderTotalDP->setText(QString::number(order[0]->getDiscountedCost(), 'f', 2));

    showDropOffPage();
}

void MainWindow::on_tableWidgetAlterationsOptions_clicked(const QModelIndex &index){
    tableWidgetOptions(tableWidgetAlterationsOptions, index, alterations, 3);
}
