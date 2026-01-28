#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>

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
//***Customer Data Page ()***
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
        lineOrderDiscountDP->clear();
    else
        lineOrderDiscountDP->setText(QString::number(order[0]->getDiscount()) + "%");

    if(checkBoxTaxDP->isChecked())
        widgetTaxDP->setVisible(true);
    else
        widgetTaxDP->setVisible(false);

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

    if(order[0]->getDiscountApplied()){
        widgetDiscountPU->setVisible(true);
        lineOrderDiscountPU->setText(QString::number(order[0]->getDiscount()) + "%");
    }else{
        widgetDiscountPU->setVisible(false);
        lineOrderDiscountPU->clear();
    }

    if(order[0]->getTaxable()){
        widgetTaxPU->setVisible(true);
        lineOrderTaxPU->setText(QString::number(order[0]->getTax(), 'f', 2));
        checkBoxTaxPU->setCheckState(Qt::Checked);
    }else{
        widgetTaxPU->setVisible(false);
        lineOrderTaxPU->clear();
        checkBoxTaxPU->setCheckState(Qt::Unchecked);
    }

    lineOrderSubTotalPU->setText(QString::number(order[0]->getCost(), 'f', 2));
    lineOrderTotalPU->setText(QString::number(order[0]->getFinalCost(), 'f', 2));


    //Set Date
    setDate(dateDTDropOffPU, dateDPickUpPU);
    dateDTDropOffPU->show();
    dateDPickUpPU->show();

    if(order[0]->getPaid())
        checkBoxPaidPU->setCheckState(Qt::Checked);
    if(order[0]->getPickUp())
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

    if(order[0]->getDiscountApplied()){
        widgetDiscountEO->setVisible(true);
        lineOrderDiscountEO->setText(QString::number(order[0]->getDiscount()) + "%");
    }else{
        widgetDiscountEO->setVisible(false);
        lineOrderDiscountEO->clear();
    }

    if(order[0]->getTaxable()){
        widgetTaxEO->setVisible(true);
        lineOrderTaxEO->setText(QString::number(order[0]->getTax(), 'f', 2));
        checkBoxTaxEO->setCheckState(Qt::Checked);

    }else{
        widgetTaxEO->setVisible(false);
        lineOrderTaxEO->clear();
        checkBoxTaxEO->setCheckState(Qt::Unchecked);

    }

    lineOrderSubTotalEO->setText(QString::number(order[0]->getCost(), 'f', 2));
    lineOrderTotalEO->setText(QString::number(order[0]->getFinalCost(), 'f', 2));

    //Set Date
    setDate(dateDTDropOffEO, dateDPickUpEO);
    dateDTDropOffEO->show();
    dateDPickUpEO->show();

    if(order[0]->getPaid())
        checkBoxPaidEO->setCheckState(Qt::Checked);
    if(order[0]->getPickUp())
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
    lineOrderTaxDP->clear();
    widgetTaxDP->setVisible(false);    
    lineOrderDiscountDP->clear();

    checkBoxPaidDP->setCheckState(Qt::Unchecked);
    checkBoxPaidDP->setCheckable(false);

    checkBoxTaxDP->setCheckState(Qt::Unchecked);
    checkBoxTaxDP->setCheckable(false);
    checkBoxTaxDP->setEnabled(false);

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
    lineOrderTaxPU->clear();
    widgetTaxPU->setVisible(false);
    lineOrderDiscountPU->clear();
    widgetDiscountPU->setVisible(false);

    checkBoxPaidPU->setCheckState(Qt::Unchecked);
    checkBoxTaxPU->setCheckState(Qt::Unchecked);
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
    lineOrderTaxEO->clear();
    widgetTaxEO->setVisible(false);
    lineOrderDiscountEO->clear();
    widgetDiscountEO->setVisible(false);

    checkBoxPaidEO->setCheckState(Qt::Unchecked);
    checkBoxTaxEO->setCheckState(Qt::Unchecked);
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
    customer.clear();
    model -> removeRows(0, model -> rowCount());

    QString entryQ = lineSearch->text();
    if(entryQ.isEmpty())
        return;

    std::string entry = entryQ.toStdString();

    if(search::Search::isPhoneNumber(entry) || search::Search::isName(entry))
        customer = search::Search::searchCustAlgo(entry, this->customers);

    if(customer.empty())
        return;

    for(size_t i = 0; i < customer.size(); i++){
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
    order[0]->calculateFinalCost();
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
    std::string typeName;
    typeName.clear();

    for(size_t i = 0; i < articlePos.size(); i++)
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
        if(order[0]->getTaxable()){
            painter.drawText(QRect(x, y, width, metrics.height() + 5), Qt::AlignRight, "Subtotal: $" + QString::number(order[0]->getCost(), 'f', 2));
            painter.drawText(QRect(x, y, width, metrics.height() + 5), Qt::AlignRight, "Tax: $" + QString::number(order[0]->getTax(), 'f', 2));
        }
        painter.drawText(QRect(x, y, width, metrics.height() + 5), Qt::AlignRight, "Total: $" + QString::number(order[0]->getFinalCost(), 'f', 2));
    }
    else{
        painter.drawText(QRect(x, y, width, metrics.height() + 5), Qt::AlignLeft, QString::number(order[0]->getPieceTotal()) + " Pieces");
        painter.drawText(QRect(x, y, width, metrics.height() + 5), Qt::AlignRight, "Subtotal: $" + QString::number(order[0]->getCost(), 'f', 2));
        y+=yInc;
        painter.drawText(QRect(x, y, width, metrics.height() + 5), Qt::AlignLeft, "Discount: " + QString::number(order[0]->getDiscount()) + "%");

        if(order[0]->getTaxable()){
            painter.drawText(QRect(x, y, width, metrics.height() + 5), Qt::AlignRight, "Tax: $" + QString::number(order[0]->getTax(), 'f', 2));
        }

        painter.drawText(QRect(x, y, width, metrics.height() + 5), Qt::AlignRight, "Total: $" + QString::number(order[0]->getFinalCost(), 'f', 2));
        if(order[0]->getPaid()){
            y += yInc;
            painter.drawText(QRect(x, y, width, metrics.height() + 5), Qt::AlignCenter, "Paid");
        }
    }

    y += 75;
    painter.drawText(QRect(x, y, width, metrics.height() + 50), Qt::AlignCenter, "Thank You Very Much");//QString::number(curOrderID));

    painter.end();
}

float MainWindow::calculateTax(float subTotal){
    if(checkBoxTaxDP->isChecked())
        return subTotal * .09375;
    else
        return 0;
}



