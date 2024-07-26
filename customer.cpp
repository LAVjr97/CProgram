#include "customer.h"

/* TODO:

*/

using namespace cust;

//Constructors
customer::customer(int customerID, std::string firstName, std::string lastName, std::string phone, int visits, double total){
    this->customerID = customerID;
    this->firstName = firstName;
    this->lastName = lastName;
    this->phone = phone;
    this->visits = visits;
    this->total = total;
    return;
}

//first time customer
customer::customer(int customerID, std::string firstName, std::string lastName, std::string phone){
    this->customerID = customerID;
    this->firstName = firstName;
    this->lastName = lastName;
    this->phone = phone;
    this->visits = 1;
    this->total = 0;
    return;
}

customer::customer(std::string firstName, std::string lastName){
    this->firstName = firstName;
    this->lastName = lastName;
}

//Get functions
int customer::getCustomerID() const{
    return customerID;
}

std::string customer::getName() const{
    return firstName + ' ' + lastName;
}

std::string customer::getFirstName() const{
    return firstName;
}
std::string customer::getLastName() const{
    return lastName;
}

std::string customer::getPhone() const{
    return phone;
}

std::string customer::getLastVisit() const{
    return lastVisit;
}

int customer::getVisit() const{
    return visits;
}
double customer::getTotal() const{
    return total;
}

//Set functions
int customer::setCustomerID(int id) {
    this->customerID = id;
    return 0;
}
// int customer::setName(std::string name) {
// 	this->name = name;
// 	return 0;
// }

int customer::setFirstName(std::string firstName){
    this->firstName = firstName;
    return 0;
}

int customer::setLastName(std::string lastName){
    this->lastName = lastName;
    return 0;
}


int customer::setPhone(std::string phone){
    this->phone = phone;
    return 0;
}

int customer::updateLastVisit(std::string lastVisit){
    this->lastVisit = lastVisit;
    return 0;
}

int customer::updateVisits(int visits){
    this->visits = visits;
    return 0;
}

int customer::updateTotal(double total){
    this->total = total;
    return 0;
}


//Serialize functions
void customer::serialize(std::ofstream &ofs) const{
    //size_t = unsigned integer type of the result of sizeof

    ofs.write(reinterpret_cast<const char*>(&this->customerID), sizeof(this->customerID));

    size_t nameSize = firstName.size();
    ofs.write(reinterpret_cast<const char*>(&this->firstName), sizeof(nameSize));
    ofs.write(firstName.c_str(), nameSize);

    nameSize = lastName.size();
    ofs.write(reinterpret_cast<const char*>(&this->lastName), sizeof(nameSize));
    ofs.write(lastName.c_str(), nameSize);

    size_t phoneSize = phone.size();
    ofs.write(reinterpret_cast<const char*>(&this->phone), sizeof(phoneSize));
    ofs.write(phone.c_str(), phoneSize);

    ofs.write(reinterpret_cast<const char*>(&this->visits), sizeof(visits));
    ofs.write(reinterpret_cast<const char*>(&this->total), sizeof(total));

    return;
}

customer customer::deserialize(std::ifstream& ifs){
    int customerID = 0, visits = 0;
    double total = 0;
    size_t nameSize = 0, phoneSize = 0;

    ifs.read(reinterpret_cast<char*>(&customerID), sizeof(customerID));

    ifs.read(reinterpret_cast<char*>(&nameSize), sizeof(nameSize));
    std::string firstName(nameSize, ' ');
    ifs.read(&firstName[0], nameSize);

    ifs.read(reinterpret_cast<char*>(&nameSize), sizeof(nameSize));
    std::string lastName(nameSize, ' ');
    ifs.read(&lastName[0], nameSize);

    ifs.read(reinterpret_cast<char*>(&phoneSize), sizeof(phoneSize));
    std::string phone(phoneSize, ' ');
    ifs.read(&phone[0], phoneSize);

    ifs.read(reinterpret_cast<char*>(&visits), sizeof(visits));

    ifs.read(reinterpret_cast<char*>(&total), sizeof(total));

    return customer(customerID, firstName, lastName, phone, visits, total);
}
