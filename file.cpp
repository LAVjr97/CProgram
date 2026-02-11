#include "file.h"

using namespace fi;

//Mac: /Users/luisvillalta/CProgram
//Windows: C:/Code/repos/LAVjr97/CProgram/

//Constructors
File::File(std::string customerFile, std::string orderFile, std::string priceFile, std::string tempOrderFile, std::string tempCustFile, std::vector<cust::customer>& customers, std::vector<orderInfo::order>& orders, std::vector<std::vector<std::pair<std::string, double>>> &laundryPrices, std::vector<std::vector<std::pair<std::string, double>>> &dryCleanPrices, std::vector<std::vector<std::pair<std::string, double>>> &alterationsPrices, std::vector<std::tuple<std::string, int, int>> &laundryPos, std::vector<std::tuple<std::string, int, int>> &dryCleanPos, std::vector<std::tuple<std::string, int, int>> &alterationsPos, std::string logFile) : customerFile(customerFile), orderFile(orderFile), priceFile(priceFile), tempOrderFile(tempOrderFile), tempCustFile(tempCustFile), customers(customers), orders(orders), laundryPrices(laundryPrices), dryCleanPrices(dryCleanPrices), alterationsPrices(alterationsPrices), laundryPos(laundryPos), dryCleanPos(dryCleanPos), alterationsPos(alterationsPos){

    checkAndCreateFile(customerFile);
    checkAndCreateFile(orderFile);
    checkAndCreateFile(priceFile);
    checkAndCreateFile(tempOrderFile);
    checkAndCreateFile(tempCustFile);
    checkAndCreateFile(logFile);

    logger = new logger::Logger(logFile);
}

void File::saveCustomers(cust::customer& customer){
    std::ofstream ofs(this->customerFile.c_str(), std::ios::app);

    if (!ofs) {
        std::cerr << "Error opening file to write to: " << this->customerFile << "\n";
        logger->log("In saveCustomers(): Error opening file to write to: " + this->customerFile);
        logger->saveAsNewLog();

        return;
    }

    ofs << customer.getCustomerID() << ","
        << customer.getFirstName() << ","
        << customer.getLastName() << ","
        << customer.getPhone() << ","
        << customer.getTotal() << ","
        << customer.getVisit() << "\n";
    ofs.close();

    std::cout << "\n" << "Successfully saved customer data..." << "\n";
    logger->log("Successfully saved customer data...");

}

void File::loadCustomers(){
    int id, visits, total;
    std::string line, firstName, lastName, phone, temp; //using a temp variable because not everything that is being read from the file will be a string.

    std::ifstream ifs(this->customerFile.c_str());
    if (!ifs) {
        std::cerr << "Error opening file to write to: " << this->customerFile << "\n";
        logger->log("In loadCustomers(): Error opening file to write to: " + this->customerFile);
        logger->saveAsNewLog();

        return;
    }

    while (std::getline(ifs, line)) {
        std::stringstream ss(line);

        std::getline(ss, temp, ',');
        id = std::stoi(temp);
        std::cout << "\n" << id << "\n";
        std::getline(ss, firstName, ',');
        std::getline(ss, lastName, ',');
        std::getline(ss, phone, ',');
        std::getline(ss, temp, ',');
        total = std::stoi(temp);
        std::getline(ss, temp, ',');
        visits = std::stoi(temp);

        std::vector<int> orders;
        while (std::getline(ss, temp, ','))
            orders.emplace_back(std::stoi(temp));

        customers.emplace_back(id, firstName, lastName, phone, visits, total, orders);
    }

    ifs.close();
    std::cout << "\n" << "Successfully loaded customer data..." <<"\n";
    logger->log("Successfully loaded customer data...");


}

//Orders
void File::saveOrders(orderInfo::order &order){
    std::vector<std::vector<std::tuple<std::string, std::string, int, double>>> laundry = order.getLaundry();
    std::vector<std::vector<std::tuple<std::string, std::string, int, double>>> dryClean = order.getDryClean();
    std::vector<std::vector<std::tuple<std::string, std::string, int, double>>> alterations = order.getAlterations();


    size_t outerVectorSize = laundry.size(), innerVectorSize;
    std::ofstream ofs(this->orderFile.c_str(), std::ios::app);
    // int curOrderID = order.getOrderID();
    // if(order.getCustomerID() != customers[orders[curOrderID].getCustomerID()].getCustomerOrderID())

    if (!ofs) {
        std::cerr << "Error opening file to write to: " << this->orderFile << "\n";
        logger->log("In saveOrders(): Error opening file to write to: " + this->orderFile);
        return;
    }

    ofs << order.getOrderID().value_or(INVALID_ORDER_ID) << ","
        << order.getCustomerID() << ","
        << order.getCost() << ","
        << order.getRack() << ","
        << order.getPickUp() << ","
        << order.getPaid() << ","
        << order.getPieceTotal() << ","
        << order.getDiscountApplied() << ","
        << order.getDiscount() << ","
        << order.getTaxable() << ","
        << order.getTax() << ","
        << order.getFinalCost() << ","
        << order.getDeposit() << ",";

    ofs << order.dropOff->getDay() << ","
        << order.dropOff->getMonth() << ","
        << order.dropOff->getYear() << ","
        << order.dropOff->getHour() << ","
        << order.dropOff->getMin() << ","
        << order.dropOff->getAm_Pm() << ",";

    ofs << order.pickUp->getDay() << ","
        << order.pickUp->getMonth() << ","
        << order.pickUp->getYear() << ","
        << order.pickUp->getHour() << ","
        << order.pickUp->getMin() << ","
        << order.pickUp->getAm_Pm() << ",";


    //Laundry
    ofs << outerVectorSize;
    for (const auto& innerVector : laundry) {
        innerVectorSize = innerVector.size();
        ofs << "," << innerVectorSize;
        for (const auto& tuple : innerVector) {
            ofs << "," << std::get<0>(tuple);
            ofs << "," << std::get<1>(tuple);
            ofs << "," << std::get<2>(tuple);
            ofs << "," << std::get<3>(tuple);            //add this line
        }
    }
    ofs << "," << "DC" << ";";

    //Dry Clean
    outerVectorSize = dryClean.size();
    ofs << outerVectorSize;
    for (const auto& innerVector : dryClean) {
        innerVectorSize = innerVector.size();
        ofs << "," << innerVectorSize;
        for (const auto& tuple : innerVector) {
            ofs << "," << std::get<0>(tuple);
            ofs << "," << std::get<1>(tuple);
            ofs << "," << std::get<2>(tuple);
            ofs << "," << std::get<3>(tuple);            //add this line
        }
    }
    ofs << "," << "ALT" << ";";

    //Alterations
    outerVectorSize = alterations.size();
    ofs << outerVectorSize;
    for (const auto& innerVector : alterations) {
        innerVectorSize = innerVector.size();
        ofs << "," << innerVectorSize;
        for (const auto& tuple : innerVector) {
            ofs << "," << std::get<0>(tuple);
            ofs << "," << std::get<1>(tuple);
            ofs << "," << std::get<2>(tuple);
            ofs << "," << std::get<3>(tuple);            //add this line
        }
    }

    ofs << "\n";

    ofs.close();

    std::cout << "\n" << "Successfully saved order data..." << "\n";
    logger->log("Successfully saved order data...");
}

int File::checkOrderIDs(){
    int prevOrderID = 0, curOrderID = -1, prevCustomerID = 0, curCustomerID = -1;
    int errors = 0;
    std::string line, temp;

    std::ifstream ifs(this->orderFile.c_str());

    if (!ifs) {
        std::cerr << "Error opening file to write to: " << this->orderFile << "\n";
        logger->log("In loadOrders(): Error opening file to write to: " + this->orderFile);
        return -1;
    }

    while (std::getline(ifs, line)) {
        prevOrderID = curOrderID;
        prevCustomerID = curCustomerID;

        std::stringstream ss(line);
        std::getline(ss, temp, ',');
        curOrderID = std::stoi(temp);
        curCustomerID = std::stoi(temp);
        std::getline(ss, temp, ',');

        if(curOrderID == prevOrderID){
            errors++;
            std::string message = "Matching orderIDs found: " + std::to_string(curOrderID) + ", Current Customer ID: " + std::to_string(curCustomerID) + ", Previous Customer ID:" + std::to_string(prevCustomerID);
            logger->log(message);
        }
    }

    return errors;
}


void File::loadOrders() {
    int n, orderID, customerID, rack, pieceTotal, dropOffDay, dropOffMonth, dropOffYear, dropOffHour, dropOffMin, pickUpDay, pickUpMonth, pickUpYear, pickUpHour, pickUpMin;
    double cost, price, discount, tax, finalCost, deposit;
    size_t outersize, innersize, i, j;
    bool pickedUp, paid, discountApplied, taxable;
    std::string dropOffAm_Pm, pickUpAm_Pm, line, temp, article, articleType;
    std::vector<std::vector<std::tuple<std::string, std::string, int, double>>> laundry;
    std::vector<std::vector<std::tuple<std::string, std::string, int, double>>> dryClean;
    std::vector<std::vector<std::tuple<std::string, std::string, int, double>>> alterations;

    std::ifstream ifs(this->orderFile.c_str());

    if (!ifs) {
        std::cerr << "Error opening file to write to: " << this->orderFile << "\n";
        logger->log("In loadOrders(): Error opening file to write to: " + this->orderFile);
        return;
    }

    while (std::getline(ifs, line)) {
        std::stringstream ss(line);

        std::getline(ss, temp, ',');
        orderID = std::stoi(temp);
        std::getline(ss, temp, ',');
        customerID = std::stoi(temp);
        std::getline(ss, temp, ',');
        cost = std::stod(temp);
        std::getline(ss, temp, ',');
        rack = std::stoi(temp);
        std::getline(ss, temp, ',');
        pickedUp = std::stoi(temp);
        std::getline(ss, temp, ',');
        paid = std::stoi(temp);
        std::getline(ss, temp, ',');
        pieceTotal = std::stoi(temp);
        std::getline(ss, temp, ',');
        discountApplied = std::stoi(temp);
        std::getline(ss, temp, ',');
        discount = std::stod(temp);
        std::getline(ss, temp, ',');
        taxable = std::stoi(temp);
        std::getline(ss, temp, ',');
        tax = std::stod(temp);
        std::getline(ss, temp, ',');
        finalCost = std::stod(temp);
        std::getline(ss, temp, ',');
        deposit = std::stod(temp);

        std::getline(ss, temp, ',');
        dropOffDay = std::stoi(temp);
        std::getline(ss, temp, ',');
        dropOffMonth = std::stoi(temp);
        std::getline(ss, temp, ',');
        dropOffYear = std::stoi(temp);
        std::getline(ss, temp, ',');
        dropOffHour = std::stoi(temp);
        std::getline(ss, temp, ',');
        dropOffMin = std::stoi(temp);
        std::getline(ss, dropOffAm_Pm, ',');

        std::getline(ss, temp, ',');
        pickUpDay = std::stoi(temp);
        std::getline(ss, temp, ',');
        pickUpMonth = std::stoi(temp);
        std::getline(ss, temp, ',');
        pickUpYear = std::stoi(temp);
        std::getline(ss, temp, ',');
        pickUpHour = std::stoi(temp);
        std::getline(ss, temp, ',');
        pickUpMin = std::stoi(temp);
        std::getline(ss, pickUpAm_Pm, ',');

        std::getline(ss, temp, ',');
        outersize = std::stoi(temp);
        laundry.resize(outersize);

        for (i = 0; i < outersize; i++) {
            std::getline(ss, temp, ',');
            innersize = std::stoi(temp);
            laundry[i].resize(innersize);
            for (j = 0; j < innersize; j++) {
                std::getline(ss, articleType, ',');
                std::getline(ss, article, ',');
                std::getline(ss, temp, ',');
                n = std::stoi(temp);
                std::getline(ss, temp, ',');
                price = std::stod(temp);
                laundry[i][j] = std::make_tuple(articleType, article, n, price);
            }
        }

        std::getline(ss, temp, ';'); //DC part of order
        std::getline(ss, temp, ',');
        outersize = std::stoi(temp);
        dryClean.resize(outersize);

        for (i = 0; i < outersize; i++) {
            std::getline(ss, temp, ',');
            innersize = std::stoi(temp);
            dryClean[i].resize(innersize);
            for (j = 0; j < innersize; j++) {
                std::getline(ss, articleType, ',');
                std::getline(ss, article, ',');
                std::getline(ss, temp, ',');
                n = std::stoi(temp);
                std::getline(ss, temp, ',');
                price = std::stod(temp);
                dryClean[i][j] = std::make_tuple(articleType, article, n, price);
            }
        }

        std::getline(ss, temp, ';'); //ALT part of order
        std::getline(ss, temp, ',');
        outersize = std::stoi(temp);
        alterations.resize(outersize);

        for (i = 0; i < outersize; i++) {
            std::getline(ss, temp, ',');
            innersize = std::stoi(temp);
            alterations[i].resize(innersize);
            for (j = 0; j < innersize; j++) {
                std::getline(ss, articleType, ',');
                std::getline(ss, article, ',');
                std::getline(ss, temp, ',');
                n = std::stoi(temp);
                std::getline(ss, temp, ',');
                price = std::stod(temp);
                alterations[i][j] = std::make_tuple(articleType, article, n, price);
            }
        }

        orders.emplace_back(orderID, customerID, cost, rack, pickedUp, paid, pieceTotal, discountApplied, discount, taxable, tax, finalCost, deposit, dropOffDay, dropOffMonth, dropOffYear, dropOffHour, dropOffMin, dropOffAm_Pm, pickUpDay, pickUpMonth, pickUpYear, pickUpHour, pickUpMin, pickUpAm_Pm, laundry, dryClean, alterations);
    }

    ifs.close();

    std::cout << "\n" << "Successfully loaded order data..." << "\n";
    logger->log("Successfully loaded order data...");


}

//random functions to go to certain customers to update.
void File::updateOrder(const int id, const int customerID){
    std::string currentID, currentCustomerID, line;
    bool found = false;
    std::vector<std::vector<std::tuple<std::string, std::string, int, double>>> laundry = orders[id].getLaundry();
    std::vector<std::vector<std::tuple<std::string, std::string, int, double>>> dryClean = orders[id].getDryClean();
    std::vector<std::vector<std::tuple<std::string, std::string, int, double>>> alterations = orders[id].getAlterations();

    size_t outerVectorSize = laundry.size(), innerVectorSize;

    std::ifstream ifs(this->orderFile.c_str());
    std::ofstream tempF(this->tempOrderFile.c_str());

    if (!ifs) {
        std::cerr << "Error opening file to write to: " << this->orderFile << "\n";
        logger->log("In updateOrder(): Error opening file to write to: " + this->orderFile);
        return;
    }

    if (!tempF) {
        std::cerr << "Error opening file to write to: " << this->tempOrderFile << "\n";
        logger->log("In updateOrder(): Error opening file to write to: " + this->tempOrderFile);
        return;
    }

    while(std::getline(ifs, line)){
        std::stringstream ss(line);
        std::getline(ss, currentID, ',');
        std::getline(ss, currentCustomerID, ',');

        if(std::stoi(currentID) == id && std::stoi(currentCustomerID) == customerID && !found){
            found = true;

            tempF   << orders[id].getOrderID().value_or(INVALID_ORDER_ID) << ","
                    << orders[id].getCustomerID() << ","
                    << orders[id].getCost() << ","
                    << orders[id].getRack() << ","
                    << orders[id].getPickUp() << ","
                    << orders[id].getPaid() << ","
                    << orders[id].getPieceTotal() << ","
                    << orders[id].getDiscountApplied() << ","
                    << orders[id].getDiscount() << ","
                    << orders[id].getTaxable() << ","
                    << orders[id].getTax() << ","
                    << orders[id].getFinalCost() << ","
                    << orders[id].getDeposit() << ",";

            tempF   << orders[id].dropOff->getDay() << ","
                    << orders[id].dropOff->getMonth() << ","
                    << orders[id].dropOff->getYear() << ","
                    << orders[id].dropOff->getHour() << ","
                    << orders[id].dropOff->getMin() << ","
                    << orders[id].dropOff->getAm_Pm() << ",";

            tempF   << orders[id].pickUp->getDay() << ","
                    << orders[id].pickUp->getMonth() << ","
                    << orders[id].pickUp->getYear() << ","
                    << orders[id].pickUp->getHour() << ","
                    << orders[id].pickUp->getMin() << ","
                    << orders[id].pickUp->getAm_Pm() << ",";

            //Laundry
            tempF << outerVectorSize;
            for (const auto& innerVector : laundry) {
                innerVectorSize = innerVector.size();
                tempF << "," << innerVectorSize;
                for (const auto& tuple : innerVector) {
                    tempF << "," << std::get<0>(tuple);
                    tempF << "," << std::get<1>(tuple);
                    tempF << "," << std::get<2>(tuple);
                    tempF << "," << std::get<3>(tuple);
                }
            }
            tempF << "," << "DC" << ";";

            //Dry Clean
            outerVectorSize = dryClean.size();
            tempF << outerVectorSize;
            for (const auto& innerVector : dryClean) {
                innerVectorSize = innerVector.size();
                tempF << "," << innerVectorSize;
                for (const auto& tuple : innerVector) {
                    tempF << "," << std::get<0>(tuple);
                    tempF << "," << std::get<1>(tuple);
                    tempF << "," << std::get<2>(tuple);
                    tempF << "," << std::get<3>(tuple);
                }
            }
            tempF << "," << "ALT" << ";";

            //Alterations
            outerVectorSize = alterations.size();
            tempF << outerVectorSize;
            for (const auto& innerVector : alterations) {
                innerVectorSize = innerVector.size();
                tempF << "," << innerVectorSize;
                for (const auto& tuple : innerVector) {
                    tempF << "," << std::get<0>(tuple);
                    tempF << "," << std::get<1>(tuple);
                    tempF << "," << std::get<2>(tuple);
                    tempF << "," << std::get<3>(tuple);
                }
            }

            tempF << "\n";
        }
        else
            tempF << line << "\n";
    }

    ifs.close();
    tempF.close();

    std::filesystem::path from = std::filesystem::path(this->tempOrderFile);
    std::filesystem::path to = std::filesystem::path(this->getOrderFile());


    if (found) {
        std::remove(this->orderFile.c_str());
        std::filesystem::copy_file(from, to, std::filesystem::copy_options::overwrite_existing);
    }

    std::filesystem::resize_file(from, 0);
    std::string message = "Updated order file successfully, Order ID: " + std::to_string(id) + ", Customer ID: " + std::to_string(orders[id].getCustomerID()) + ", Customer Name: " + customers[orders[id].getCustomerID()].getName();
    logger->log(message);
}

void File::updateCustomer(const int id) {
    std::string current, line;
    bool found = false;

    std::ifstream ifs(this->customerFile.c_str());
    std::ofstream tempF(this->tempCustFile.c_str());

    if (!ifs) {
        std::cerr << "Error opening file to write to: " << this->customerFile << "\n";
        logger->log("In updateCustomer(): Error opening file to write to: " + this->customerFile);

        return;
    }
    if (!tempF) {
        std::cerr << "Error opening file to write to: " << this->tempCustFile << "\n";
        logger->log("In updateCustomer(): Error opening file to write to: " + this->tempCustFile);
        return;
    }


    while (std::getline(ifs, line)) {
        std::stringstream ss(line); //istringstream
        std::getline(ss, current, ',');

        if (std::stoi(current) == id && !found) {
            found = true;

            tempF << customers[id].getCustomerID() << ","
                  << customers[id].getFirstName() << ","
                  << customers[id].getLastName() << ","
                  << customers[id].getPhone() << ","
                  << customers[id].getTotal() << ","
                  << customers[id].getVisit();

            for (int i = 0; i < customers[id].getOrderSize(); i++)
                tempF << "," << customers[id].getOrderID(i);
            tempF << "\n";
        }
        else
            tempF << line << "\n";
    }

    ifs.close();
    tempF.close();

    std::filesystem::path from = std::filesystem::path(this->tempCustFile);
    std::filesystem::path to = std::filesystem::path(this->getCustomerFile());


    if (found) {
        std::remove(this->customerFile.c_str());

        std::filesystem::copy_file(from, to, std::filesystem::copy_options::overwrite_existing);

    }
    std::filesystem::resize_file(from, 0);

    std::string message = "Updated customer file successfully, Customer ID: " + std::to_string(id) + ", Customer Name: " + customers[id].getName();
    logger->log(message);
}


void File::savePrices(){
    std::ofstream ofs(this->priceFile.c_str());
    size_t outerVectorSize, innerVectorSize;
    if(!ofs){
        std::cerr << "Error opening file to write to: " << this->priceFile << "\n";
        logger->log("Error opening file to write to: " + this->priceFile);
        return;
    }

    outerVectorSize = laundryPrices.size();
    ofs << outerVectorSize;
    for(const auto &innerVector : laundryPrices){
        innerVectorSize = innerVector.size();
        ofs << "," << innerVectorSize;
        for(const auto& pair : innerVector){
            ofs << "," << pair.first
                << "," << pair.second;
        }
    }

    ofs << "," << "DC" << ";";

    outerVectorSize = dryCleanPrices.size();
    ofs << outerVectorSize;
    for(const auto &innerVector : dryCleanPrices){
        innerVectorSize = innerVector.size();
        ofs << "," << innerVectorSize;
        for(const auto& pair : innerVector){
            ofs << "," << pair.first
                << "," << pair.second;
        }
    }

    ofs << "," << "ALT" << ";";
    outerVectorSize = alterationsPrices.size();
    ofs << outerVectorSize;
    for(const auto &innerVector : alterationsPrices){
        innerVectorSize = innerVector.size();
        ofs << "," << innerVectorSize;
        for(const auto& pair : innerVector){
            ofs << "," << pair.first
                << "," << pair.second;
        }
    }
    
    ofs << "\n";

    
    outerVectorSize = laundryPos.size();
    ofs << outerVectorSize;
    for(const auto &tuple : laundryPos){
        ofs << "," << std::get<0>(tuple)
            << "," << std::get<1>(tuple)
            << "," << std::get<2>(tuple);
    }

    ofs << "," << "DC" << ";";
    outerVectorSize = dryCleanPos.size();
    ofs << outerVectorSize;
    for(const auto &tuple : dryCleanPos){
        ofs << "," << std::get<0>(tuple)
            << "," << std::get<1>(tuple)
            << "," << std::get<2>(tuple);
    }

    ofs << "," << "ALT" << ";";
    outerVectorSize = alterationsPos.size();
    ofs << outerVectorSize;
    for(const auto &tuple : alterationsPos){
        ofs << "," << std::get<0>(tuple)
            << "," << std::get<1>(tuple)
            << "," << std::get<2>(tuple);
    }

    ofs.close();

    std::cout << "\n" << "Successfully saved price data..." << "\n";
    logger->log("Successfully saved price data...");

}

void File::loadPrices(){
    int rPos, lPos, outerSize, innerSize, i, j;
    double price;
    std::string line, piece, temp;
    std::ifstream ifs(this->priceFile.c_str());

    if(!ifs){
        std::cerr << "Error opening file to write to: " << this->priceFile <<"\n";
        logger->log("Error opening file to write to: " + this->priceFile);

        return;
    }



    if(!std::getline(ifs, line)){
        laundryPrices.resize(1);
        laundryPrices[0].resize(1);
        laundryPos.resize(1);
        laundryPos[0] = std::make_tuple("", 0, 0);

        dryCleanPrices.resize(1);
        dryCleanPrices[0].resize(1);
        dryCleanPos.resize(1);
        dryCleanPos[0] = std::make_tuple("", 0, 0);

        alterationsPrices.resize(1);
        alterationsPrices[0].resize(1);
        alterationsPos.resize(1);
        alterationsPos[0] = std::make_tuple("", 0, 0);
        return;
    }

    std::stringstream ss(line);
    std::getline(ss, temp, ',');
    outerSize = std::stoi(temp);
    laundryPrices.resize(outerSize);
    for(i = 0; i < outerSize; i++){
        std::getline(ss, temp, ',');
        innerSize = std::stoi(temp);
        laundryPrices[i].resize(innerSize);
        for(j = 0; j < innerSize; j++){
            std::getline(ss, piece, ',');
            std::getline(ss, temp, ',');
            price = std::stod(temp);
            laundryPrices[i][j] = std::make_pair(piece, price);
        }
    }

    std::getline(ss, temp, ';');
    std::getline(ss, temp, ',');
    outerSize = std::stoi(temp);
    dryCleanPrices.resize(outerSize);
    for(i = 0; i < outerSize; i++){
        std::getline(ss, temp, ',');
        innerSize = std::stoi(temp);
        dryCleanPrices[i].resize(innerSize);
        for(j = 0; j < innerSize; j++){
            std::getline(ss, piece, ',');
            std::getline(ss, temp, ',');
            price = std::stod(temp);
            dryCleanPrices[i][j] = std::make_pair(piece, price);
        }
    }

    std::getline(ss, temp, ';');
    std::getline(ss, temp, ',');
    outerSize = std::stoi(temp);
    alterationsPrices.resize(outerSize);
    for(i = 0; i < outerSize; i++){
        std::getline(ss, temp, ',');
        innerSize = std::stoi(temp);
        alterationsPrices[i].resize(innerSize);
        for(j = 0; j < innerSize; j++){
            std::getline(ss, piece, ',');
            std::getline(ss, temp, ',');
            price = std::stod(temp);
            alterationsPrices[i][j] = std::make_pair(piece, price);
        }
    }

    std::getline(ifs, line);
    ss.clear();
    ss.str(line);

    std::getline(ss, temp, ',');
    outerSize = std::stoi(temp);
    laundryPos.resize(outerSize);
    for(i = 0; i < outerSize; i++){
        std::getline(ss, piece, ',');
        std::getline(ss, temp, ',');
        rPos = std::stoi(temp);
        std::getline(ss, temp, ',');
        lPos = std::stoi(temp);
        laundryPos[i] = std::make_tuple(piece, rPos, lPos);
    }

    std::getline(ss, temp, ';');
    std::getline(ss, temp, ',');
    outerSize = std::stoi(temp);
    dryCleanPos.resize(outerSize);
    for(i = 0; i < outerSize; i++){
        std::getline(ss, piece, ',');
        std::getline(ss, temp, ',');
        rPos = std::stoi(temp);
        std::getline(ss, temp, ',');
        lPos = std::stoi(temp);
        dryCleanPos[i] = std::make_tuple(piece, rPos, lPos);
    }

    std::getline(ss, temp, ';');
    std::getline(ss, temp, ',');
    outerSize = std::stoi(temp);
    alterationsPos.resize(outerSize);
    for(i = 0; i < outerSize; i++){
        std::getline(ss, piece, ',');
        std::getline(ss, temp, ',');
        rPos = std::stoi(temp);
        std::getline(ss, temp, ',');
        lPos = std::stoi(temp);
        alterationsPos[i] = std::make_tuple(piece, rPos, lPos);
    }
    
    ifs.close();

    std::cout << "\n" << "Successfully loaded price data..." << "\n";
    logger->log("Successfully loaded price data...");

}

void File::checkAndCreateFile(const std::string& filename){
    //std::ifstream fileCheck(filename);
    if(!std::filesystem::exists(filename)){
        std::ofstream file(filename.c_str());
        file.close();
    }
}

//Get functions
std::string File::getCustomerFile() const{
    return this->customerFile;
}

std::string File::getOrderFile() const{
    return this->orderFile;
}

std::string File::getTempFile() const{
    return this->tempOrderFile;
}
