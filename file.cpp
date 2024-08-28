#include "file.h"

using namespace fi;

//Mac: /Users/luisvillalta/CProgram
//Windows: C:/Code/repos/LAVjr97/CProgram/

//Constructors
File::File(std::string customerFile, std::string orderFile, std::string tempFile, std::vector<cust::customer>& customers, std::vector<orderInfo::order>& orders) : customerFile(customerFile), orderFile(orderFile), tempFile(tempFile), customers(customers), orders(orders)
{}

void File::saveCustomers(cust::customer& customer) const{
    std::ofstream ofs("C:/Code/repos/LAVjr97/CProgram/customers.txt", std::ios::app);

    if (!ofs) {
        std::cerr << "Error opening file to write to: " << this->customerFile << std::endl;
        return;
    }

    ofs << customer.getCustomerID() << ","
        << customer.getFirstName() << ","
        << customer.getLastName() << ","
        << customer.getPhone() << ","
        << customer.getTotal() << ","
        << customer.getVisit() << std::endl;
    ofs.close();

    std::cout << std::endl << "Successfully saved customer data..." << std::endl;
}

void File::loadCustomers(){
    int id, visits, total;
    std::string line, firstName, lastName, phone, temp; //using a temp variable because not everything that is being read from the file will be a string.

    std::ifstream ifs("C:/Code/repos/LAVjr97/CProgram/customers.txt");
    if (!ifs) {
        std::cerr << "Error opening file to write to: " << this->customerFile << std::endl;
        return;
    }

    while (std::getline(ifs, line)) {
        std::stringstream ss(line);

        std::getline(ss, temp, ',');
        id = std::stoi(temp);
        std::cout << std::endl << id << std::endl;
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
    std::cout << std::endl << "Successfully loaded customer data..." <<std::endl;

}

//Orders
void File::saveOrders(orderInfo::order &order) const{
    std::vector<std::vector<std::tuple<std::string, int, double>>> laundry = order.getLaundry();
    std::vector<std::vector<std::tuple<std::string, int, double>>> dryClean = order.getDryCleanO();
    std::vector<std::vector<std::tuple<std::string, int, double>>> alterations = order.getAlterationsO();


    size_t outerVectorSize = laundry.size(), innerVectorSize;
    std::ofstream ofs("C:/Code/repos/LAVjr97/CProgram/orders.txt", std::ios::app);

    if (!ofs) {
        std::cerr << "Error opening file to write to: " << this->orderFile << std::endl;
        return;
    }

    ofs << order.getOrderID() << ","
        << order.getCustomerID() << ","
        << order.getCost() << ","
        << order.getRack() << ","
        << order.getPickUp() << ","
        << order.getPaid() << ",";

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


    //Check chatgpt to see how delimiter works, fix delimiter and how data is being stored and how to read the ";"

    //Laundry
    ofs << outerVectorSize;
    for (const auto& innerVector : laundry) {
        innerVectorSize = innerVector.size();
        ofs << "," << innerVectorSize;
        for (const auto& tuple : innerVector) {
            ofs << "," << std::get<0>(tuple);
            ofs << "," << std::get<1>(tuple);
            ofs << "," << std::get<2>(tuple); //add this line
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
        }
    }

    ofs << std::endl;

    ofs.close();

    std::cout << std::endl << "Successfully saved order data..." << std::endl;

}

void File::loadOrders() {
    int n, orderID, customerID, rack, dropOffDay, dropOffMonth, dropOffYear, dropOffHour, dropOffMin, pickUpDay, pickUpMonth, pickUpYear, pickUpHour, pickUpMin;
    double cost, price;
    size_t outersize, innersize, i, j;
    bool pickedUp, paid;
    std::string dropOffAm_Pm, pickUpAm_Pm, line, temp, article;
    std::vector<std::vector<std::tuple<std::string, int, double>>> laundry;
    std::vector<std::vector<std::tuple<std::string, int, double>>> dryClean;
    std::vector<std::vector<std::tuple<std::string, int, double>>> alterations;

    std::ifstream ifs("C:/Code/repos/LAVjr97/CProgram/orders.txt");

    if (!ifs) {
        std::cerr << "Error opening file to write to: " << this->orderFile << std::endl;
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
                std::getline(ss, article, ',');
                std::getline(ss, temp, ',');
                n = std::stoi(temp);
                std::getline(ss, temp, ',');
                price = std::stod(temp);
                laundry[i][j] = std::make_tuple(article, n, price);
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
                std::getline(ss, article, ',');
                std::getline(ss, temp, ',');
                n = std::stoi(temp);
                std::getline(ss, temp, ',');
                price = std::stod(temp);
                dryClean[i][j] = std::make_tuple(article, n, price);
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
                std::getline(ss, article, ',');
                std::getline(ss, temp, ',');
                n = std::stoi(temp);
                std::getline(ss, temp, ',');
                price = std::stod(temp);
                alterations[i][j] = std::make_tuple(article, n, price);
            }
        }

        orders.emplace_back(orderID, customerID, cost, rack, pickedUp, paid, dropOffDay, dropOffMonth, dropOffYear, dropOffHour, dropOffMin, dropOffAm_Pm, pickUpDay, pickUpMonth, pickUpYear, pickUpHour, pickUpMin, pickUpAm_Pm, laundry, dryClean, alterations);
    }

    ifs.close();

    std::cout << std::endl << "Successfully loaded order data..." << std::endl;

}

//random functions to go to certain customers to update.
void File::updateOrder(const int id){
    std::string current, line;
    bool found;
    std::vector<std::vector<std::tuple<std::string, int, double>>> laundry = orders[id].getLaundry();
    std::vector<std::vector<std::tuple<std::string, int, double>>> dryClean = orders[id].getDryCleanO();
    std::vector<std::vector<std::tuple<std::string, int, double>>> alterations = orders[id].getAlterationsO();

    size_t outerVectorSize = laundry.size(), innerVectorSize;

    std::ifstream ifs("C:/Code/repos/LAVjr97/CProgram/orders.txt");
    std::ofstream tempF("C:/Code/repos/LAVjr97/CProgram/temp.txt");

    if (!ifs) {
        std::cerr << "Error opening file to write to: " << this->customerFile << std::endl;
        return;
    }

    if (!tempF) {
        std::cerr << "Error opening file to write to: " << this->tempFile << std::endl;
        return;
    }

    while(std::getline(ifs, line)){
        std::stringstream ss(line);
        std::getline(ss, current, ',');

        if(std::stoi(current) == id){
            found = true;

            tempF   << orders[id].getOrderID() << ","
                    << orders[id].getCustomerID() << ","
                    << orders[id].getCost() << ","
                    << orders[id].getRack() << ","
                    << orders[id].getPickUp() << ","
                    << orders[id].getPaid() << ",";

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
                }
            }

            tempF << std::endl;
        }
        else
            tempF << line << std::endl;
    }

    ifs.close();
    tempF.close();

    if(found){
        std::remove(this->orderFile.c_str());
        std::rename(this->tempFile.c_str(), this->customerFile.c_str());
    }
    else
        std::remove(this->tempFile.c_str());
    return;

}

void File::updateCustomer(const int id) {
    std::string current, line;
    bool found;

    std::ifstream ifs("C:/Code/repos/LAVjr97/CProgram/customers.txt");
    std::ofstream tempF("C:/Code/repos/LAVjr97/CProgram/temp.txt");

    if (!ifs) {
        std::cerr << "Error opening file to write to: " << this->customerFile << std::endl;
        return;
    }
    if (!tempF) {
        std::cerr << "Error opening file to write to: " << this->tempFile << std::endl;
        return;
    }


    while (std::getline(ifs, line)) {
        std::stringstream ss(line); //istringstream
        std::getline(ss, current, ',');

        if (std::stoi(current) == id) {
            found = true;

            tempF << customers[id].getCustomerID() << ","
                  << customers[id].getFirstName() << ","
                  << customers[id].getLastName() << ","
                  << customers[id].getPhone() << ","
                  << customers[id].getTotal() << ","
                  << customers[id].getVisit();

            for (int i = 0; i < customers[id].getOrderSize(); i++)
                tempF << "," << customers[id].getOrderID(i);
            tempF << std::endl;
        }
        else
            tempF << line << std::endl;
    }

    ifs.close();
    tempF.close();

    if (found) {
        std::remove(this->customerFile.c_str());
        std::rename(this->tempFile.c_str(), this->customerFile.c_str());
    }
    else
        std::remove(this->tempFile.c_str());

    return;
}



//Get functions

std::string File::getCustomerFile() const{
    return this->customerFile;
}

std::string File::getOrderFile() const{
    return this->orderFile;
}

std::string File::getTempFile() const{
    return this->tempFile;
}
