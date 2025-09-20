#include "mainwindow.h"
#include "ui_mainwindow.h"

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
        std::string logmsg = "Critical Error in Saving Picked Up Order! Error in File, there are multiple matches of differnt orderIDs: " + std::to_string(errors) + " times";
        manager->logger->log(logmsg);
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
