#include "order.h"

using namespace orderInfo;

//Constructor
order::order(std::string firstName, std::string lastName, int customerID, std::string dropOff, std::string pickUp, std::array<std::tuple<int, double>, 8> articles){
    this->orderID = order::generateOrderID();
    this->firstName = firstName;
    this->lastName = lastName;
    this->dropOffDate = dropOff;
    this->pickUpDate = pickUp;
    this->articles = articles;
    this->cost = 0;
    // generate cost;

}

order::order(int orderID, std::string firstName, std::string lastName, int customerID, std::string dropOff, std::string pickUp, std::array<std::tuple<int, double>, 8> articles){
    this->orderID = orderID;
    this->firstName = firstName;
    this->lastName = lastName;
    this->dropOffDate = dropOff;
    this->pickUpDate = pickUp;
    this->articles = articles;
    this->cost = 0;
}

/*Get Functions*/
int order::getCustomerID() const{
    std::cout << "\n" << this->customerID;
    return this->customerID;
}

int order::getOrderID() const{
    return orderID;
}

std::string order::getName() const{
    return firstName + " " + lastName;
}

std::string order::getFirstName() const{
    return firstName;
}

std::string order::getLastName() const{
    return lastName;
}

std::string order::getDropOffDate() const{
    return dropOffDate;
}

std::string order::getPickUpDate() const{
    return pickUpDate;
}

std::array<std::tuple<int, double>, 8> order::getDetails() const{
    return articles;
}

double order::getCost() const{
    return cost;
}

/*Set Functions*/
int order::setCustomerID(int id){
    this->customerID = id;
    return 0;
}

// int order::setName(std::string name){
//     this->name = name;
//     return 0;
// }

int order::setFirstName(std::string firstName){
    this->firstName = firstName;
    return 0;
}

int order::setLastName(std::string lastName){
    this->lastName = lastName;
    return 0;
}

int order::setDropOffDate(std::string date){
    this->dropOffDate = date;
    return 0;
}

int order::setPickUpDate(std::string date){
    this->pickUpDate = date;
    return 0;
}

int order::setDetails(std::array<std::tuple<int, double>, 8> articles){
    this->articles = articles;
    return 0;
}

int order::setCost(double cost){
    this->cost = cost;
    return 0;
}

double order::calculateCost(int* articles) {
    return 0;
}

int order::generateOrderID(){
    int id = 0;
    //pull up latest id used, "++"" it, update and save the latest ID

    return id;
}

//Serialize functions
void order::serialize(std::ofstream& ofs) const{
    //size_t = unsigned integer type of the result of sizeof, ofs = filename
    size_t nameSize = firstName.size();

    ofs.write(reinterpret_cast<const char*>(&this->orderID), sizeof(this->orderID));

    ofs.write(reinterpret_cast<const char*>(&this->firstName), sizeof(nameSize));
    ofs.write(firstName.c_str(), nameSize);

    nameSize = lastName.size();
    ofs.write(reinterpret_cast<const char*>(&this->lastName), sizeof(nameSize));

    /*


    DO THE REST HERE


*/

}
orderInfo::order order::deserialize(std::ifstream& ifs){
    int orderId = 0;
    ifs.read(reinterpret_cast<char*>(&orderId), sizeof(orderId));

    int customerId = 0;
    ifs.read(reinterpret_cast<char*>(&customerId), sizeof(customerId));

    size_t customerNameSize = 0;
    ifs.read(reinterpret_cast<char*>(&customerNameSize), sizeof(customerNameSize));
    std::string firstName(customerNameSize, ' ');
    ifs.read(&firstName[0], customerNameSize);

    ifs.read(reinterpret_cast<char*>(&customerNameSize), sizeof(customerNameSize));
    std::string lastName(customerNameSize, ' ');
    ifs.read(&lastName[0], customerNameSize);

    size_t dropOffDateSize = 0;
    ifs.read(reinterpret_cast<char*>(&dropOffDateSize), sizeof(dropOffDateSize));
    std::string dropOffDate(dropOffDateSize, ' ');
    ifs.read(&dropOffDate[0], dropOffDateSize);

    size_t pickUpDateSize = 0;
    ifs.read(reinterpret_cast<char*>(&pickUpDateSize), sizeof(pickUpDateSize));
    std::string pickUpDate(pickUpDateSize, ' ');
    ifs.read(&pickUpDate[0], pickUpDateSize);

    //adress to tup, tup iterates over articles, so any change done to tup is a change to articles because of the "&" in "auto&"

    std::array<std::tuple<int, double>, 8> articles;
    for(auto& tup: articles){
        int i = 0;
        double d = 0;

        ifs.read(reinterpret_cast<char*>(&i), sizeof(i));
        ifs.read(reinterpret_cast<char*>(&d), sizeof(d));

        tup = std::make_tuple(i, d);
    }

    double cost = 0;
    ifs.read(reinterpret_cast<char*>(&cost), sizeof(cost));

    //std::string name, int customerID, std::string dropOff, std::string pickUp, std::array<std::tuple<int, double>, 8> description, double cost

    return orderInfo::order(orderId, firstName, lastName, customerId, dropOffDate, pickUpDate, articles);

}
