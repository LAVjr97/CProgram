#include "mainwindow.h"
#include "qlabel.h"


Q_DECLARE_METATYPE(std::vector<pieces::piece>*);
Q_DECLARE_METATYPE(pieces::piece*);


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

    saveTableCIP(laundry, tableWidgetLaundryCIP);
    saveTableCIP(dryClean, tableWidgetDryCleanCIP);
    saveTableCIP(alterations, tableWidgetAlterationsCIP);

    manager->savePrices();
    tableWidgetDryCleanCIP->clear();
    setUpCIPPage();
}


void MainWindow::saveTableCIP(services::serviceList service, QTableWidget *tableWidget){/*
    size_t row, pieceI = 0, typeI = 0, index, rowCount = tableWidget->rowCount() - 1;
    float price;
    std::string piece;
    QDoubleSpinBox *dSpinBox;
    QLineEdit *linePiece, *newType;



    for(row = 0; row < rowCount; row++){
        QWidget *w = tableWidget->cellWidget(row, 0);


        //If the current row is the type Name
        if(QLabel* label = qobject_cast<QLabel*>(w)){
            typeI++;
            pieceI = 0;
            continue;
        }

        //if the current row is an individual piece
        if(QLineEdit* lineEdit = qobject_cast<QLineEdit*>(w)){
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

            //if an item has been deleted and the price hasn't been set to 0
            if(piece.empty() && price != 0){
                tableWidget->removeRow(row);

                //remove this
                index = getIndex(row, pos); //interchange typeI and index, might be the same values. UPDATE: Index is giving the incorrext postion, either typeI or pieceI are wrong
                if(removeItemPrice(index, prices, pieceI))
                    removeIndex(index, pos);
                row--;
                continue;
            }

            if(price == 0)
                continue;

        }



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

        //if an item has been deleted and the price hasn't been set to 0
        if(piece.empty() && price != 0){
            tableWidget->removeRow(row);

            //remove this
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

    if(row > 1




    // size_t row, pieceI = 0, typeI = 0, index, rowCount = tableWidget->rowCount() - 1;
    // double price;
    // std::string piece;
    // QDoubleSpinBox *dSpinBox;
    // QLineEdit *linePiece, *newType;

    // for(row = 0; row < rowCount; row++){
    //     dSpinBox = qobject_cast<QDoubleSpinBox*>(tableWidget->cellWidget(row, 1));
    //     if(dSpinBox == nullptr){
    //         if(row == 0)
    //             continue;

    //         pieceI = 0;
    //         typeI++;
    //         continue;
    //     }

    //     price = dSpinBox->value();
    //     linePiece = qobject_cast<QLineEdit*>(tableWidget->cellWidget(row, 0));
    //     piece = linePiece->text().toStdString();

    //     piece = cust::customer::autoCapatilize(piece);

    //     //if an item has been deleted basically and the price hasn't been set to 0
    //     if(piece.empty() && price != 0){
    //         tableWidget->removeRow(row);
    //         index = getIndex(row, pos); //interchange typeI and index, might be the same values. UPDATE: Index is giving the incorrext postion, either typeI or pieceI are wrong
    //         if(removeItemPrice(index, prices, pieceI))
    //             removeIndex(index, pos);
    //         row--;
    //         continue;
    //     }

    //     //The empty row, where price is still 0, gets skipped
    //     if(price == 0)
    //         continue;

    //     //if an item has been added
    //     if(pieceI >= prices[typeI].size()){
    //         if(prices[typeI][0].first == "" && prices[typeI][0].second == 0.00){
    //             prices[typeI].pop_back();
    //             prices[typeI].push_back(std::make_pair(piece, price));
    //         }
    //         else{
    //             prices[typeI].push_back(std::make_pair(piece, price));
    //             increaseIndex(typeI, pos);
    //         }
    //     }

    //     //if the name has been changed
    //     if(piece != prices[typeI][pieceI].first)
    //         prices[typeI][pieceI].first = piece;


    //     //if the price has been changed
    //     if(price != prices[typeI][pieceI].second)
    //         prices[typeI][pieceI].second = price;

    //     pieceI++;
    // }
    // newType = qobject_cast<QLineEdit*>(tableWidget->cellWidget(row, 1));

    // if(newType != nullptr)
    //     if(!newType->text().isEmpty())
    //         createType(typeI, pos, prices, cust::customer::autoCapatilize(newType->text().toStdString()));

    // row++;
*/
}


void MainWindow::setUpCIPPage(){
    setUpTableWidgetsCIP(laundry, tableWidgetLaundryCIP);
    setUpTableWidgetsCIP(dryClean, tableWidgetDryCleanCIP);
    setUpTableWidgetsCIP(alterations, tableWidgetAlterationsCIP);
}

void MainWindow::setUpTableWidgetsCIP(services::serviceList& prices, QTableWidget *tableWidget){
    size_t row = 0, i, j;
    QFont font;

    std::vector<pieces::pieceTypeList> typeList = prices.getServiceTypeList();
    std::vector<pieces::piece> pieceList, *pieceListP;
    pieces::piece piece, *pieceP;

    //If empty

    if(prices.getTypeListSize() == 0) //Might contain a bug
        tableWidget->setRowCount(1);
    else{
        for(i = 0; i < typeList.size(); i++){
            pieceList = typeList[i].getPieceList();
            pieceListP = &pieceList;
            for(j = 0; j < pieceList.size(); j++){
                if(j == 0){
                    // QLabel *label = new QLabel(QString::fromStdString(pieceList[j].getPieceName()));
                    QLabel *label = new QLabel(QString::fromStdString(typeList[i].getPieceTypeName()));
                    label->setAlignment(Qt::AlignCenter);
                    font = label->font();
                    font.setBold(true);
                    label->setFont(font);

                    label->setProperty("pieceListP", QVariant::fromValue(pieceListP));

                    tableWidget->insertRow(row);

                    tableWidget->setCellWidget(row, 0, label);
                    tableWidget->setCellWidget(row, 1, nullptr);
                    row++;
                }

                //If the type hasn't just been created so there arent any piece types
                if(pieceList[j].getPieceName() != "" && pieceList[j].getPiecePrice() != 0.00){
                    QLineEdit *piece = new QLineEdit(QString::fromStdString(pieceList[j].getPieceName()), nullptr);
                    piece->setAlignment(Qt::AlignCenter);

                    QDoubleSpinBox *price = new QDoubleSpinBox(tableWidget);
                    price->setMaximum(9999);
                    price->setDecimals(2);
                    price->setValue(pieceList[j].getPiecePrice());

                    pieceP = &pieceList[j];
                    piece->setProperty("pieceP", QVariant::fromValue(pieceP));

                    tableWidget->insertRow(row);

                    tableWidget->setCellWidget(row, 0, piece);
                    tableWidget->setCellWidget(row, 1, price);
                    row++;
                    continue;
                }

                //The last piece in the list
                if(typeList.size() - 1 == j || (pieceList[j].getPieceName() == "" && pieceList[j].getPiecePrice() != 0.00)){
                    QLineEdit *newPiece = new QLineEdit(tableWidget);
                    newPiece->setAlignment(Qt::AlignCenter);

                    QDoubleSpinBox *newPrice = new QDoubleSpinBox(tableWidget);
                    newPrice->setMaximum(9999);
                    newPrice->setDecimals(2);
                    newPrice->setValue(0.00);

                    tableWidget->insertRow(row);

                    tableWidget->setCellWidget(row, 0, newPiece);
                    tableWidget->setCellWidget(row, 1, newPrice);
                    row++;
                    continue;
                }
            }
        }
    }

    QLabel *newTypeLabel = new QLabel("New Type");
    newTypeLabel->setAlignment(Qt::AlignCenter);

    QLineEdit *newTypeLine = new QLineEdit(this);

    tableWidget->insertRow(row);

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
