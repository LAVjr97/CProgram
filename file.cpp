#include "file.h"

using namespace fi;

//Constructors
File::File(std::string customerFile, std::string orderFile, std::string tempFile, std::vector<cust::customer>& customers, std::vector<orderInfo::order>& orders) : customerFile(customerFile), orderFile(orderFile), tempFile(tempFile), customers(customers), orders(orders)
{}

void File::saveCustomers(cust::customer& customer) const{
    std::ofstream ofs("/Users/luisvillalta/CProgram/customers.txt", std::ios::app);
    std::cout << std::endl << "In saveCustomers" << std::endl;

    if (!ofs) {
        std::cerr << "Error opening file to write to: " << this->customerFile << std::endl;
        return;
    }
    std::cout << std::endl << "before saving to customers.txt" << std::endl;

    ofs << customer.getCustomerID() << ","
        << customer.getFirstName() << ","
        << customer.getLastName() << ","
        << customer.getPhone() << ","
        << customer.getTotal() << ","
        << customer.getVisit() << std::endl;
    ofs.close();
    return;
}

void File::loadCustomers(){
    int id, visits, total;
    std::string line, firstName, lastName, phone, temp; //using a temp variable because not everything that is being read from the file will be a string.

    std::ifstream ifs("/Users/luisvillalta/CProgram/customers.txt");
    if (!ifs) {
        std::cerr << "Error opening file to write to: " << this->customerFile << std::endl;
        return;
    }
    //std::cout << std::endl << "Before while loop that reads file" << std::endl;

    while (std::getline(ifs, line)) {
        //std::cout << std::endl << "In while loop that reads file" << std::endl;
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
}

//Orders
void File::saveOrders(orderInfo::order &order) const{
    std::ofstream ofs("/Users/luisvillalta/CProgram/orders.txt", std::ios::app);
    std::cout << std::endl << "In saveOrders" << std::endl;

    if (!ofs) {
        std::cerr << "Error opening file to write to: " << this->orderFile << std::endl;
        return;
    }

    ofs << order.getOrderID() << ","
        << order.getCustomerID() << ","
        << order.getCost() << ","
        << order.getRack() << ","
        << order.getPickUp() << ",";
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
        << order.pickUp->getAm_Pm();
    for (const auto& i : order.getDetails()) {
        ofs << "," << std::get<0>(i);
        ofs << "," << std::get<1>(i);
    }
    ofs << std::endl;

    ofs.close();
    return;
}

void File::loadOrders() {
    //When .emplace_back is being used, the first and last name will be using the address of the variables from that customer's object in case any changes are made to the class, its reflected in the order class.
    int n, orderID, customerID, rack, dropOffDay, dropOffMonth, dropOffYear, dropOffHour, dropOffMin, pickUpDay, pickUpMonth, pickUpYear, pickUpHour, pickUpMin;
    double cost, price;
    bool pickedUp;
    std::string dropOffAm_Pm, pickUpAm_Pm, line, temp;
    std::array<std::tuple<int, double>, 8> articles;
    std::ifstream ifs("/Users/luisvillalta/CProgram/orders.txt");

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

        for (int i = 0; i < articles.size(); i++) {
            std::getline(ss, temp, ',');
            n = std::stoi(temp);
            std::getline(ss, temp, ',');
            price = std::stod(temp);
            articles[i] = std::make_tuple(n, price);
        }

        orders.emplace_back(orderID, customerID, cost, rack, pickedUp, dropOffDay, dropOffMonth, dropOffYear, dropOffHour, dropOffMin, dropOffAm_Pm, pickUpDay, pickUpMonth, pickUpYear, pickUpHour, pickUpMin, pickUpAm_Pm, articles);
    }

    ifs.close();

    return;
}

//random functions to go to certain customers to update.
void File::updateCustomer(const int id) {
    std::string current, line;
    bool found;

    std::ifstream ifs("/Users/luisvillalta/CProgram/customers.txt");
    std::ofstream tempF("/Users/luisvillalta/CProgram/temp.txt");

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
