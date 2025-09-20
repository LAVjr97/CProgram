#include "mainwindow.h"
#include "qlabel.h"

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

void MainWindow::on_btnCustomerAP_clicked(){
    customerSetUpScreenCEP();
    showCustomerEditPage();
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
//***Customer Edit Page (21)***
//

void MainWindow::on_btnSaveCEP_clicked(){
    customer[0]->setFirstName(lineFNameCEP->text().toStdString());
    customer[0]->setLastName(lineLNameCEP->text().toStdString());
    customer[0]->setPhone(linePhoneCEP->text().toStdString());

    std::thread threadCust(&fi::File::updateCustomer, manager, customer[0]->getCustomerID());

    threadCust.join();
}

void MainWindow::on_btnReturnCEP_clicked(){
    clearScreenCEP();
    showAdminPage();
}

//Given a phone number
void MainWindow::on_btnSearchCEP_clicked(){
    QString entryQ;
    std::string entry;

    entryQ = lineSearchCEP->text();
    if(entryQ.isEmpty()){
        customerSetUpScreenCEP();
        return;
    }

    entry = entryQ.toStdString();

    if(search::Search::isPhoneNumber(entry) || search::Search::isName(entry))
        customer = search::Search::searchCustAlgo(entry, this->customers);

    if(customer.empty())
        return;

    updateCustomerInfoTable();
}


void MainWindow::updateCustomerInfoTable(){
    size_t i;

    modelCEP -> removeRows(0, modelCEP -> rowCount());

    for(i = 0; i < customer.size(); i++){
        QStandardItem *id = new QStandardItem(QString::number(customer[i]->getCustomerID()));
        id->setTextAlignment(Qt::AlignCenter);

        QStandardItem *firstNameItem = new QStandardItem(QString::fromStdString(customer[i]->getFirstName()));
        firstNameItem->setTextAlignment(Qt::AlignCenter);

        QStandardItem *lastNameItem = new QStandardItem(QString::fromStdString(customer[i]->getLastName()));
        lastNameItem->setTextAlignment(Qt::AlignCenter);

        QStandardItem *phoneItem = new QStandardItem(QString::fromStdString(customer[i]->getFormattedPhone()));
        phoneItem->setTextAlignment(Qt::AlignCenter);

        QStandardItem *visits = new QStandardItem(QString::number(customer[i]->getVisit()));
        visits->setTextAlignment(Qt::AlignCenter);

        modelCEP->setItem(i, 0, id);
        modelCEP->setItem(i, 1, firstNameItem);
        modelCEP->setItem(i, 2, lastNameItem);
        modelCEP->setItem(i, 3, phoneItem);
        modelCEP->setItem(i, 4, visits);
    }
}

void MainWindow::clearScreenCEP(){
    modelCEP -> removeRows(0, modelCEP -> rowCount());

    lineFNameCEP->clear();
    lineLNameCEP->clear();
    linePhoneCEP->clear();
    lineSearchCEP->clear();
}

void MainWindow::customerSetUpScreenCEP(){
    std::string entry;
    size_t i;

    customer.clear();
    customer = search::Search::copyVector(customers);

    clearScreenCEP();

    for(i = 0; i < customer.size(); i++){
        QStandardItem *id = new QStandardItem(QString::number(customer[i]->getCustomerID()));
        id->setTextAlignment(Qt::AlignCenter);

        QStandardItem *firstNameItem = new QStandardItem(QString::fromStdString(customer[i]->getFirstName()));
        firstNameItem->setTextAlignment(Qt::AlignCenter);

        QStandardItem *lastNameItem = new QStandardItem(QString::fromStdString(customer[i]->getLastName()));
        lastNameItem->setTextAlignment(Qt::AlignCenter);

        QStandardItem *phoneItem = new QStandardItem(QString::fromStdString(customer[i]->getFormattedPhone()));
        phoneItem->setTextAlignment(Qt::AlignCenter);

        QStandardItem *visits = new QStandardItem(QString::number(customer[i]->getVisit()));
        visits->setTextAlignment(Qt::AlignCenter);

        modelCEP->setItem(i, 0, id);
        modelCEP->setItem(i, 1, firstNameItem);
        modelCEP->setItem(i, 2, lastNameItem);
        modelCEP->setItem(i, 3, phoneItem);
        modelCEP->setItem(i, 4, visits);
    }
}

void MainWindow::on_tableViewCustomerInfoCEP_clicked(const QModelIndex &index){
    cust::customer *temp = customer[index.row()];

    customer.clear();
    customer.push_back(temp);
    modelCEP -> removeRows(0, modelCEP -> rowCount());

    lineFNameCEP->setText(QString::fromStdString(customer[0]->getFirstName()));
    lineLNameCEP->setText(QString::fromStdString(customer[0]->getLastName()));
    linePhoneCEP->setText(QString::fromStdString(customer[0]->getPhone()));

    updateCustomerInfoTable();
}
