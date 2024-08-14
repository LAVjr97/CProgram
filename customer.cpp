#include "customer.h"

/* TODO:

*/

using namespace cust;

//Constructors
//Used to load
customer::customer(int customerID, std::string firstName, std::string lastName, std::string phone, int visits, double total, std::vector<int> orders){
    this->customerID = customerID;
    this->firstName = firstName;
    this->lastName = lastName;
    this->phone = phone;
    this->visits = visits;
    this->total = total;
    this->orders = orders;
    return;
}

//first time customer
customer::customer(int customerID, std::string firstName, std::string lastName, std::string phone){
    this->customerID = customerID;
    this->firstName = firstName;
    this->lastName = lastName;
    this-> phone = this->createPhone(phone);
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

std::vector<int> customer::getOrders() const {
    return orders;
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

int customer::getOrderSize() const {
    return this->orders.size();
}

int customer::getOrderID(int i) const {
    return this->orders[i];
}

//Set functions
int customer::setCustomerID(int id) {
    this->customerID = id;
    return 0;
}

int customer::setFirstName(std::string firstName) {
    this->firstName = firstName;
    return 0;
}

int customer::setLastName(std::string lastName) {
    this->lastName = lastName;
    return 0;
}


int customer::setPhone(std::string phone) {
    this->phone = phone;
    return 0;
}

int customer::setOrders(std::vector<int> orders) {
    this->orders = orders;
    return 0;
}

int customer::setLatestOrder(int orderID) {
    this->orders.emplace_back(orderID);
    return 0;
}

int customer::updateLastVisit(std::string lastVisit) {
    this->lastVisit = lastVisit;
    return 0;
}

int customer::updateVisits(int visits) {
    this->visits = visits;
    return 0;
}

int customer::updateTotal(double total){
    this->total = total;
    return 0;
}


//Helper functions
std::string customer::createPhone(std::string phone) {
    int i, j = 1;
    std::string temp;

    for (i = 0; i < phone.size(); i++)
        if (phone[i] != '(' && phone[i] != ')' && phone[i] != '-' && phone[i] != ' ')
            temp += phone[i];

    return temp;
}

