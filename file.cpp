#include "file.h"

using namespace fi;

//Mac: /Users/luisvillalta/CProgram
//Windows: C:/Code/repos/LAVjr97/CProgram/

//Constructors
// File::File(std::string customerFile, std::string orderFile, std::string priceFile, std::string tempOrderFile, std::string tempCustFile, std::vector<cust::customer>& customers, std::vector<orderInfo::order>& orders, std::vector<std::vector<std::pair<std::string, float>>> &laundryPrices, std::vector<std::vector<std::pair<std::string, float>>> &dryCleanPrices, std::vector<std::vector<std::pair<std::string, float>>> &alterationsPrices, std::vector<std::tuple<std::string, int, int>> &laundryPos, std::vector<std::tuple<std::string, int, int>> &dryCleanPos, std::vector<std::tuple<std::string, int, int>> &alterationsPos, std::string logFile) : customerFile(customerFile), orderFile(orderFile), priceFile(priceFile), tempOrderFile(tempOrderFile), tempCustFile(tempCustFile), customers(customers), orders(orders), laundryPrices(laundryPrices), dryCleanPrices(dryCleanPrices), alterationsPrices(alterationsPrices), laundryPos(laundryPos), dryCleanPos(dryCleanPos), alterationsPos(alterationsPos){

//     checkAndCreateFile(customerFile);
//     checkAndCreateFile(orderFile);
//     checkAndCreateFile(priceFile);
//     checkAndCreateFile(tempOrderFile);
//     checkAndCreateFile(tempCustFile);
//     checkAndCreateFile(logFile);

//     logger = new logger::Logger(logFile);
// }

File::File(const Params& params) :
    customerFile(params.customerFile),
    orderFile(params.orderFile),
    priceFile(params.priceFile),
    tempOrderFile(params.tempOrderFile),
    tempCustFile(params.tempCustFile),
    logger(params.logFile),
    customers(params.customers),
    orders(params.orders),
    laundry(params.laundry),
    dryClean(params.dryClean),
    alterations(params.alterations)
{
}


void File::saveCustomers(cust::customer& customer){
    std::ofstream ofs(this->customerFile.c_str(), std::ios::app);

    if (!ofs) {
        std::cerr << "Error opening file to write to: " << this->customerFile << "\n";
        logger.log("In saveCustomers(): Error opening file to write to: " + this->customerFile);
        logger.saveAsNewLog();

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
    logger.log("Successfully saved customer data...");

}

void File::loadCustomers(){
    int id, visits, total;
    std::string line, firstName, lastName, phone, temp; //using a temp variable because not everything that is being read from the file will be a string.

    std::ifstream ifs(this->customerFile.c_str());
    if (!ifs) {
        std::cerr << "Error opening file to write to: " << this->customerFile << "\n";
        logger.log("In loadCustomers(): Error opening file to write to: " + this->customerFile);
        logger.saveAsNewLog();

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
    logger.log("Successfully loaded customer data...");
}

void File::saveOrders(orderInfo::order &order){
    services::serviceOrder laundry;
    services::serviceOrder dryClean;
    services::serviceOrder alterations;

    std::vector<pieces::pieceOrder> pieceList; //Vector contained by type class, meant to store pieces
    std::vector<pieces::pieceTypeOrder> typeList; //Vector contained by Service class, meant to store types


    size_t outerVectorSize = laundry.getTypeListSize(), innerVectorSize;

    std::ofstream ofs(this->orderFile.c_str(), std::ios::app);
    // int curOrderID = order.getOrderID();
    // if(order.getCustomerID() != customers[orders[curOrderID].getCustomerID()].getCustomerOrderID())

    if (!ofs) {
        std::cerr << "Error opening file to write to: " << this->orderFile << "\n";
        logger.log("In saveOrders(): Error opening file to write to: " + this->orderFile);
        return;
    }

    ofs << order.getOrderID() << ","
        << order.getCustomerID() << ","
        << order.getCost() << ","
        << order.getRack() << ","
        << order.getPickUp() << ","
        << order.getPaid() << ","
        << order.getPieceTotal() << ","
        << order.getDiscountApplied() << ","
        << order.getDiscount() << ","
        << order.getDiscountedCost() << ","
        << order.getDeposit() << ","
        << order.getVoidOrder() << ",";

    ofs << order.dropOff.getDay() << ","
        << order.dropOff.getMonth() << ","
        << order.dropOff.getYear() << ","
        << order.dropOff.getHour() << ","
        << order.dropOff.getMin() << ","
        << order.dropOff.getAm_Pm() << ",";

    ofs << order.pickUp.getDay() << ","
        << order.pickUp.getMonth() << ","
        << order.pickUp.getYear() << ","
        << order.pickUp.getHour() << ","
        << order.pickUp.getMin() << ","
        << order.pickUp.getAm_Pm() << ",";

    //Laundry
    ofs << laundry.getServiceName() << ","
        << laundry.getServiceTotal() << ","
        << outerVectorSize;

    typeList = laundry.getServiceTypeList();
    for(const auto& innerVector : typeList) {
        ofs << "," << innerVector.getPieceTypeName()
            << "," << innerVector.getTypeID()
            << "," << innerVector.getTypeCost()
            << "," << innerVector.getPieceTotal();

        innerVectorSize = innerVector.getPieceListSize();
        ofs << "," << innerVectorSize;

        pieceList = innerVector.getPieceList();
        for(const auto& pieceOrder : pieceList){
            ofs << "," << pieceOrder.getPieceName()
                << "," << pieceOrder.getPieceID()
                << "," << pieceOrder.getTypeID()
                << "," << pieceOrder.getPiecePrice()
                << "," << pieceOrder.getPieceCount()
                << "," << pieceOrder.getPieceOrderItemCount()
                << "," << pieceOrder.getPieceOrderCost();
        }
    }

    ofs << "," << "DC" << ";";
    outerVectorSize = dryClean.getTypeListSize();
    ofs << dryClean.getServiceName() << ","
        << dryClean.getServiceTotal() << ","
        << outerVectorSize;

    typeList = dryClean.getServiceTypeList();
    for(const auto& innerVector : typeList) {
        ofs << "," << innerVector.getPieceTypeName()
            << "," << innerVector.getTypeID()
            << "," << innerVector.getTypeCost()
            << "," << innerVector.getPieceTotal();

        innerVectorSize = innerVector.getPieceListSize();
        ofs << "," << innerVectorSize;

        pieceList = innerVector.getPieceList();
        for(const auto& pieceOrder : pieceList){
            ofs << "," << pieceOrder.getPieceName()
            << "," << pieceOrder.getPieceID()
            << "," << pieceOrder.getPiecePrice()
            << "," << pieceOrder.getPieceCount()
            << "," << pieceOrder.getPieceOrderItemCount()
            << "," << pieceOrder.getPieceOrderCost();
        }
    }

    ofs << "," << "ALT" << ";";
    outerVectorSize = alterations.getTypeListSize();
    ofs << alterations.getServiceName() << ","
        << alterations.getServiceTotal() << ","
        << outerVectorSize;

    typeList = alterations.getServiceTypeList();
    for(const auto& innerVector : typeList) {
        ofs << "," << innerVector.getPieceTypeName()
            << "," << innerVector.getTypeID()
            << "," << innerVector.getTypeCost()
            << "," << innerVector.getPieceTotal();

        innerVectorSize = innerVector.getPieceListSize();
        ofs << "," << innerVectorSize;

        pieceList = innerVector.getPieceList();
        for(const auto& pieceOrder : pieceList){
            ofs << "," << pieceOrder.getPieceName()
            << "," << pieceOrder.getPieceID()
            << "," << pieceOrder.getPiecePrice()
            << "," << pieceOrder.getPieceCount()
            << "," << pieceOrder.getPieceOrderItemCount()
            << "," << pieceOrder.getPieceOrderCost();
        }
    }

    ofs << "\n";

    ofs.close();

    std::cout << "\n" << "Successfully saved order data..." << "\n";
    logger.log("Successfully saved order data...");
}


int File::checkOrderIDs(){
    int prevOrderID = 0, curOrderID = -1, prevCustomerID = 0, curCustomerID = -1;
    int errors = 0;
    std::string line, temp;

    std::ifstream ifs(this->orderFile.c_str());

    if (!ifs) {
        std::cerr << "Error opening file to write to: " << this->orderFile << "\n";
        logger.log("In loadOrders(): Error opening file to write to: " + this->orderFile);
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
            logger.log(message);
        }
    }

    return errors;
}


void File::loadOrders() {
    int orderID, customerID, rack, pieceTotal, dropOffDay, dropOffMonth, dropOffYear, dropOffHour, dropOffMin, pickUpDay, pickUpMonth, pickUpYear, pickUpHour, pickUpMin, typeID, pieceTypeTotal, pieceID, pieceTypeID, pieceCount, pieceOrderItemCount;
    float total, discount, discountedCost, deposit, typeCost, piecePrice, pieceOrderCost, serviceTotal;
    size_t outersize, innersize, i, j;
    bool pickedUp, paid, discountApplied, voidOrder;
    std::string dropOffAm_Pm, pickUpAm_Pm, line, temp, article, articleType, pieceTypeName, pieceName, serviceName;

    //pieces::pieceOrder piece;
    pieces::pieceTypeOrder type;

    std::vector<pieces::pieceOrder> pieceList; //Vector contained by type class, meant to store pieces
    std::vector<pieces::pieceTypeOrder> typeList; //Vector contained by Service class, meant to store types

    services::serviceOrder laundry;
    services::serviceOrder dryClean;
    services::serviceOrder alterations;

    std::ifstream ifs(this->orderFile.c_str());

    if (!ifs) {
        std::cerr << "Error opening file to write to: " << this->orderFile << "\n";
        logger.log("In loadOrders(): Error opening file to write to: " + this->orderFile);
        return;
    }

    while (std::getline(ifs, line)) {
        std::stringstream ss(line);

        std::getline(ss, temp, ',');
        orderID = std::stoi(temp);
        std::getline(ss, temp, ',');
        customerID = std::stoi(temp);
        std::getline(ss, temp, ',');
        total = std::stof(temp);
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
        discountedCost = std::stod(temp);
        std::getline(ss, temp, ',');
        deposit = std::stod(temp);
        std::getline(ss,temp, ',');
        voidOrder = std::stof(temp);

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

        std::getline(ss, serviceName, ',');
        std::getline(ss, temp, ',');
        serviceTotal = std::stof(temp);

        std::getline(ss, temp, ',');
        outersize = std::stoi(temp);

        typeList.resize(outersize);

        for (i = 0; i < outersize; i++) {
            std::getline(ss, pieceTypeName, ',');
            std::getline(ss, temp, ',');
            typeID = std::stoi(temp);
            std::getline(ss, temp, ',');
            typeCost = std::stof(temp);
            std::getline(ss, temp, ',');
            pieceTypeTotal = std::stoi(temp);

            std::getline(ss, temp, ',');
            innersize = std::stoi(temp);
            pieceList.resize(innersize);

            for (j = 0; j < innersize; j++) {
                std::getline(ss, pieceName, ',');
                std::getline(ss, temp, ',');
                pieceID = std::stoi(temp);
                std::getline(ss, temp, ',');
                pieceTypeID = std::stoi(temp);
                std::getline(ss, temp, ',');
                piecePrice = std::stof(temp);
                std::getline(ss, temp, ',');
                pieceCount = std::stoi(temp);
                std::getline(ss, temp, ',');
                pieceOrderItemCount = std::stoi(temp);
                std::getline(ss, temp, ',');
                pieceOrderCost = std::stof(temp);

                pieceList[j] = pieces::pieceOrder(pieceName, pieceID, pieceTypeID, piecePrice, pieceCount, pieceOrderItemCount, pieceOrderCost);;
            }

            type = pieces::pieceTypeOrder(pieceTypeName, typeID, typeCost, pieceList, pieceTypeTotal);
            typeList[i] = type;
        }

        laundry = services::serviceOrder(serviceName, serviceTotal, typeList);
        pieceList.clear();
        typeList.clear();

        //Finish below this

        std::getline(ss, temp, ';'); //DC part of order

        std::getline(ss, serviceName, ',');
        std::getline(ss, temp, ',');
        serviceTotal = std::stof(temp);

        std::getline(ss, temp, ',');
        outersize = std::stoi(temp);

        typeList.resize(outersize);

        for (i = 0; i < outersize; i++) {
            std::getline(ss, pieceTypeName, ',');
            std::getline(ss, temp, ',');
            typeID = std::stoi(temp);
            std::getline(ss, temp, ',');
            typeCost = std::stof(temp);
            std::getline(ss, temp, ',');
            pieceTypeTotal = std::stoi(temp);

            std::getline(ss, temp, ',');
            innersize = std::stoi(temp);
            pieceList.resize(innersize);

            for (j = 0; j < innersize; j++) {
                std::getline(ss, pieceName, ',');
                std::getline(ss, temp, ',');
                pieceID = std::stoi(temp);
                std::getline(ss, temp, ',');
                pieceTypeID = std::stoi(temp);
                std::getline(ss, temp, ',');
                piecePrice = std::stof(temp);
                std::getline(ss, temp, ',');
                pieceCount = std::stoi(temp);
                std::getline(ss, temp, ',');
                pieceOrderItemCount = std::stoi(temp);
                std::getline(ss, temp, ',');
                pieceOrderCost = std::stof(temp);

                pieceList[j] = pieces::pieceOrder(pieceName, pieceID, pieceTypeID, piecePrice, pieceCount, pieceOrderItemCount, pieceOrderCost);
            }

            type = pieces::pieceTypeOrder(pieceTypeName, typeID, typeCost, pieceList, pieceTypeTotal);
            typeList[i] = type;
        }

        dryClean = services::serviceOrder(serviceName, serviceTotal, typeList);
        pieceList.clear();
        typeList.clear();

        std::getline(ss, temp, ';'); //ALT part of order

        std::getline(ss, serviceName, ',');
        std::getline(ss, temp, ',');
        serviceTotal = std::stof(temp);

        std::getline(ss, temp, ',');
        outersize = std::stoi(temp);

        typeList.resize(outersize);

        for (i = 0; i < outersize; i++) {
            std::getline(ss, pieceTypeName, ',');
            std::getline(ss, temp, ',');
            typeID = std::stoi(temp);
            std::getline(ss, temp, ',');
            typeCost = std::stof(temp);
            std::getline(ss, temp, ',');
            pieceTypeTotal = std::stoi(temp);

            std::getline(ss, temp, ',');
            innersize = std::stoi(temp);
            pieceList.resize(innersize);

            for (j = 0; j < innersize; j++) {
                std::getline(ss, pieceName, ',');
                std::getline(ss, temp, ',');
                pieceID = std::stoi(temp);
                std::getline(ss, temp, ',');
                pieceTypeID = std::stoi(temp);
                std::getline(ss, temp, ',');
                piecePrice = std::stof(temp);
                std::getline(ss, temp, ',');
                pieceCount = std::stoi(temp);
                std::getline(ss, temp, ',');
                pieceOrderItemCount = std::stoi(temp);
                std::getline(ss, temp, ',');
                pieceOrderCost = std::stof(temp);

                pieceList[j] = pieces::pieceOrder(pieceName, pieceID, pieceTypeID, piecePrice, pieceCount, pieceOrderItemCount, pieceOrderCost);
            }

            type = pieces::pieceTypeOrder(pieceTypeName, typeID, typeCost, pieceList, pieceTypeTotal);
            typeList[i] = type;
        }

        alterations = services::serviceOrder(serviceName, serviceTotal, typeList);
        pieceList.clear();
        typeList.clear();

        orderInfo::order::Params params {
            .orderID = orderID,
            .customerID = customerID,
            .laundry = laundry,
            .dryClean = dryClean,
            .alterations = alterations,

            .total = total,
            .rack = rack,
            .pickedUp = pickedUp,
            .paid = paid,
            .pieceTotal = pieceTotal,
            .discountApplied = discountApplied,
            .discount = discount,
            .discountedCost = discountedCost,
            .deposit = deposit,
            .voidOrder = voidOrder,

            .dropOff = date::Date(dropOffDay, dropOffMonth, dropOffYear, dropOffHour, dropOffMin, dropOffAm_Pm),
            .pickUp = date::Date(pickUpDay, pickUpMonth, pickUpYear, pickUpHour, pickUpMin, pickUpAm_Pm)
        };

        orders.emplace_back(params);

    }

    ifs.close();

    std::cout << "\n" << "Successfully loaded order data..." << "\n";
    logger.log("Successfully loaded order data...");


}

//random functions to go to certain customers to update.
void File::updateOrder(const int id){
    std::string currentID, currentCustomerID, line;
    bool found = false;
    services::serviceOrder laundry = orders[id].getLaundry();
    services::serviceOrder dryClean = orders[id].getDryClean();
    services::serviceOrder alterations = orders[id].getAlterations();

    std::vector<pieces::pieceOrder> pieceList; //Vector contained by type class, meant to store pieces
    std::vector<pieces::pieceTypeOrder> typeList; //Vector contained by Service class, meant to store types

    size_t outerVectorSize = laundry.getTypeListSize(), innerVectorSize;

    std::ifstream ifs(this->orderFile.c_str());
    std::ofstream tempF(this->tempOrderFile.c_str());
    int customerID = orders[id].getCustomerID();

    if (!ifs) {
        std::cerr << "Error opening file to write to: " << this->orderFile << "\n";
        logger.log("In updateOrder(): Error opening file to write to: " + this->orderFile);
        return;
    }

    if (!tempF) {
        std::cerr << "Error opening file to write to: " << this->tempOrderFile << "\n";
        logger.log("In updateOrder(): Error opening file to write to: " + this->tempOrderFile);
        return;
    }

    while(std::getline(ifs, line)){
        std::stringstream ss(line);
        std::getline(ss, currentID, ',');
        std::getline(ss, currentCustomerID, ',');

        if(std::stoi(currentID) == id && std::stoi(currentCustomerID) == customerID && !found){
            found = true;

            orderInfo::order &order = orders[id];


            tempF << order.getOrderID() << ","
                << order.getCustomerID() << ","
                << order.getCost() << ","
                << order.getRack() << ","
                << order.getPickUp() << ","
                << order.getPaid() << ","
                << order.getPieceTotal() << ","
                << order.getDiscountApplied() << ","
                << order.getDiscount() << ","
                << order.getDiscountedCost() << ","
                << order.getDeposit() << ","
                << order.getVoidOrder() << ",";

            tempF << order.dropOff.getDay() << ","
                << order.dropOff.getMonth() << ","
                << order.dropOff.getYear() << ","
                << order.dropOff.getHour() << ","
                << order.dropOff.getMin() << ","
                << order.dropOff.getAm_Pm() << ",";

            tempF << order.pickUp.getDay() << ","
                << order.pickUp.getMonth() << ","
                << order.pickUp.getYear() << ","
                << order.pickUp.getHour() << ","
                << order.pickUp.getMin() << ","
                << order.pickUp.getAm_Pm() << ",";

            //Laundry
            tempF << laundry.getServiceName() << ","
                << laundry.getServiceTotal() << ","
                << outerVectorSize;

            typeList = laundry.getServiceTypeList();
            for(const auto& innerVector : typeList) {
                tempF << "," << innerVector.getPieceTypeName()
                    << "," << innerVector.getTypeID()
                    << "," << innerVector.getTypeCost()
                    << "," << innerVector.getPieceTotal();

                innerVectorSize = innerVector.getPieceListSize();
                tempF << "," << innerVectorSize;

                pieceList = innerVector.getPieceList();
                for(const auto& pieceOrder : pieceList){
                    tempF << "," << pieceOrder.getPieceName()
                            << "," << pieceOrder.getPieceID()
                            << "," << pieceOrder.getPiecePrice()
                            << "," << pieceOrder.getPieceCount()
                            << "," << pieceOrder.getPieceOrderItemCount()
                            << "," << pieceOrder.getPieceOrderCost();
                }
            }

            tempF << "," << "DC" << ";";
            outerVectorSize = dryClean.getTypeListSize();
            tempF << dryClean.getServiceName() << ","
                  << dryClean.getServiceTotal() << ","
                  << outerVectorSize;

            typeList = dryClean.getServiceTypeList();
            for(const auto& innerVector : typeList) {
                tempF << "," << innerVector.getPieceTypeName()
                    << "," << innerVector.getTypeID()
                    << "," << innerVector.getTypeCost()
                    << "," << innerVector.getPieceTotal();

                innerVectorSize = innerVector.getPieceListSize();
                tempF << "," << innerVectorSize;

                pieceList = innerVector.getPieceList();
                for(const auto& pieceOrder : pieceList){
                    tempF << "," << pieceOrder.getPieceName()
                        << "," << pieceOrder.getPieceID()
                        << "," << pieceOrder.getPiecePrice()
                        << "," << pieceOrder.getPieceCount()
                        << "," << pieceOrder.getPieceOrderItemCount()
                        << "," << pieceOrder.getPieceOrderCost();
                }
            }

            tempF << "," << "ALT" << ";";
            outerVectorSize = alterations.getTypeListSize();
            tempF << alterations.getServiceName() << ","
                    << alterations.getServiceTotal() << ","
                    << outerVectorSize;

            typeList = alterations.getServiceTypeList();
            for(const auto& innerVector : typeList) {
                tempF << "," << innerVector.getPieceTypeName()
                    << "," << innerVector.getTypeID()
                    << "," << innerVector.getTypeCost()
                    << "," << innerVector.getPieceTotal();

                innerVectorSize = innerVector.getPieceListSize();
                tempF << "," << innerVectorSize;

                pieceList = innerVector.getPieceList();
                for(const auto& pieceOrder : pieceList){
                    tempF << "," << pieceOrder.getPieceName()
                        << "," << pieceOrder.getPieceID()
                        << "," << pieceOrder.getPiecePrice()
                        << "," << pieceOrder.getPieceCount()
                        << "," << pieceOrder.getPieceOrderItemCount()
                        << "," << pieceOrder.getPieceOrderCost();
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
    logger.log(message);
}

void File::updateCustomer(const int id) {
    std::string current, line;
    bool found = false;

    std::ifstream ifs(this->customerFile.c_str());
    std::ofstream tempF(this->tempCustFile.c_str());

    if (!ifs) {
        std::cerr << "Error opening file to write to: " << this->customerFile << "\n";
        logger.log("In updateCustomer(): Error opening file to write to: " + this->customerFile);

        return;
    }
    if (!tempF) {
        std::cerr << "Error opening file to write to: " << this->tempCustFile << "\n";
        logger.log("In updateCustomer(): Error opening file to write to: " + this->tempCustFile);
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
    logger.log(message);
}


void File::savePrices(){
    std::ofstream ofs(this->priceFile.c_str());

    std::vector<pieces::pieceTypeList> typeList;
    std::vector<pieces::piece> pieceList;


    if(!ofs){
        std::cerr << "Error opening file to write to: " << this->priceFile << "\n";
        logger.log("Error opening file to write to: " + this->priceFile);
        return;
    }



    ofs << laundry.getServiceName()
        << "," << laundry.getTypeListSize();

    typeList = laundry.getServiceTypeList();

    for(const auto &type : typeList){
        pieceList = type.getPieceList();

        ofs << "," << type.getPieceTypeName()
            << "," << type.getTypeID()
            << "," << pieceList.size();

        for(const auto& piece : pieceList){
            ofs << "," << piece.getPieceName()
                << "," << piece.getPieceID()
                << "," << piece.getTypeID()
                << "," << piece.getPiecePrice()
                << "," << piece.getPieceCount();
        }
    }

    ofs << "," << "DC" << ";";

    ofs << dryClean.getServiceName()
        << "," << dryClean.getTypeListSize();

    typeList = dryClean.getServiceTypeList();

    for(const auto &type : typeList){
        pieceList = type.getPieceList();

        ofs << "," << type.getPieceTypeName()
            << "," << type.getTypeID()
            << "," << pieceList.size();

        for(const auto& piece : pieceList){
            ofs << "," << piece.getPieceName()
            << "," << piece.getPieceID()
            << "," << piece.getPiecePrice()
            << "," << piece.getPieceCount();
        }
    }


    ofs << alterations.getServiceName()
        << "," << alterations.getTypeListSize();

    typeList = alterations.getServiceTypeList();

    for(const auto &type : typeList){
        pieceList = type.getPieceList();

        ofs << "," << type.getPieceTypeName()
            << "," << type.getTypeID()
            << "," << pieceList.size();

        for(const auto& piece : pieceList){
            ofs << "," << piece.getPieceName()
            << "," << piece.getPieceID()
            << "," << piece.getPiecePrice()
            << "," << piece.getPieceCount();
        }
    }
    
    ofs << "\n";

    ofs.close();

    std::cout << "\n" << "Successfully saved price data..." << "\n";
    logger.log("Successfully saved price data...");

}

void File::loadPrices(){
    int typeListSize, pieceListSize, i, j, typeID, pieceID, pieceTypeID, pieceCount;
    float piecePrice;
    std::string line, piece, temp, service, type;
    std::ifstream ifs(this->priceFile.c_str());

    std::vector<pieces::pieceTypeList> typeList;
    std::vector<pieces::piece> pieceList;

    if(!ifs){
        std::cerr << "Error opening file to write to: " << this->priceFile <<"\n";
        logger.log("Error opening file to write to: " + this->priceFile);

        return;
    }

    /*if(!std::getline(ifs, line)){
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
    } */

    std::stringstream ss(line);
    std::getline(ss, service, ',');
    std::getline(ss, temp, ',');
    typeListSize = std::stoi(temp);

    typeList.reserve(typeListSize);

    for(i = 0; i < typeListSize; i++){
        std::getline(ss, type, ',');
        std::getline(ss, temp, ',');
        typeID = std::stoi(temp);

        std::getline(ss, temp, ',');
        pieceListSize = std::stoi(temp);
        pieceList.reserve(pieceListSize);

        for(j = 0; j < pieceListSize; j++){
            std::getline(ss, piece, ',');
            std::getline(ss, temp, ',');
            pieceID = std::stoi(temp);
            std::getline(ss, temp, ',');
            pieceTypeID = std::stoi(temp);
            std::getline(ss, temp, ',');
            piecePrice = std::stof(temp);
            std::getline(ss, temp, ',');
            pieceCount = std::stoi(temp);

            pieceList[j] = pieces::piece(piece, pieceID, pieceTypeID, piecePrice, pieceCount);
        }
        typeList[i] = pieces::pieceTypeList(type, typeID, pieceList);
    }
    laundry = services::serviceList(service, typeList);

    std::getline(ss, temp, ';');
    std::getline(ss, service, ',');
    std::getline(ss, temp, ',');
    typeListSize = std::stoi(temp);

    typeList.reserve(typeListSize);

    for(i = 0; i < typeListSize; i++){
        std::getline(ss, type, ',');
        std::getline(ss, temp, ',');
        typeID = std::stoi(temp);

        std::getline(ss, temp, ',');
        pieceListSize = std::stoi(temp);
        pieceList.reserve(pieceListSize);

        for(j = 0; j < pieceListSize; j++){
            std::getline(ss, piece, ',');
            std::getline(ss, temp, ',');
            pieceID = std::stoi(temp);
            std::getline(ss, temp, ',');
            pieceTypeID = std::stoi(temp);
            std::getline(ss, temp, ',');
            piecePrice = std::stof(temp);
            std::getline(ss, temp, ',');
            pieceCount = std::stoi(temp);

            pieceList[j] = pieces::piece(piece, pieceID, pieceTypeID, piecePrice, pieceCount);
        }
        typeList[i] = pieces::pieceTypeList(type, typeID, pieceList);
    }
    dryClean = services::serviceList(service, typeList);

    std::getline(ss, temp, ';');
    std::getline(ss, service, ',');
    std::getline(ss, temp, ',');
    typeListSize = std::stoi(temp);

    typeList.reserve(typeListSize);

    for(i = 0; i < typeListSize; i++){
        std::getline(ss, type, ',');
        std::getline(ss, temp, ',');
        typeID = std::stoi(temp);

        std::getline(ss, temp, ',');
        pieceListSize = std::stoi(temp);
        pieceList.reserve(pieceListSize);

        for(j = 0; j < pieceListSize; j++){
            std::getline(ss, piece, ',');
            std::getline(ss, temp, ',');
            pieceID = std::stoi(temp);
            std::getline(ss, temp, ',');
            pieceTypeID = std::stoi(temp);
            std::getline(ss, temp, ',');
            piecePrice = std::stof(temp);
            std::getline(ss, temp, ',');
            pieceCount = std::stoi(temp);

            pieceList[j] = pieces::piece(piece, pieceID, pieceTypeID, piecePrice, pieceCount);
        }
        typeList[i] = pieces::pieceTypeList(type, typeID, pieceList);
    }
    alterations = services::serviceList(service, typeList);

    ifs.close();

    std::cout << "\n" << "Successfully loaded price data..." << "\n";
    logger.log("Successfully loaded price data...");

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
