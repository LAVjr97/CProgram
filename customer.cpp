#include "customer.h"

/* TODO:

*/

using namespace cust;

//Constructors
//Used to load
customer::customer(int customerID, std::string firstName, std::string lastName, std::string phone, int visits, float total, std::vector<int> orders){
    this->_customerID = customerID;
    this->_firstName = firstName;
    this->_lastName = lastName;
    this->_phone = phone;
    this->_visits = visits;
    this->_total = total;
    this->_orders = orders;
    return;
}

//first time customer
customer::customer(int customerID, std::string firstName, std::string lastName, std::string phone){
    this->_customerID = customerID;
    this->_firstName = firstName;
    this->_lastName = lastName;
    this->_phone = this->createPhone(phone);
    this->_visits = 0;
    this->_total = 0;
    return;
}

customer::customer(std::string firstName, std::string lastName){
    this->_firstName = firstName;
    this->_lastName = lastName;
}

//Get functions
int customer::getCustomerID() const{
    return _customerID;
}

std::string customer::getName() const{
    return _firstName + ' ' + _lastName;
}

std::string customer::getFirstName() const{
    return _firstName;
}
std::string customer::getLastName() const{
    return _lastName;
}

std::string customer::getPhone() const{
    return _phone;
}

std::string customer::getFormattedPhone() const{
    std::string fPhone;
    size_t i;

    for(i = 0; i < this->_phone.size(); i++){
        if(i == 0)
            fPhone = fPhone + "(";
        if(i == 3)
            fPhone = fPhone + ") ";
        if(i == 6)
            fPhone = fPhone + "-";
        fPhone += _phone[i];
    }

    return fPhone;
}

std::vector<int> customer::getOrders() const {
    return _orders;
}

std::string customer::getLastVisit() const{
    return _lastVisit;
}

int customer::getVisit() const{
    return _visits;
}
float customer::getTotal() const{
    return _total;
}

int customer::getOrderSize() const {
    return this->_orders.size();
}

int customer::getOrderID(int i) const {
    return this->_orders[i];
}

//Set functions
int customer::setCustomerID(int id) {
    this->_customerID = id;
    return 0;
}

int customer::setFirstName(std::string firstName) {
    this->_firstName = firstName;
    return 0;
}

int customer::setLastName(std::string lastName) {
    this->_lastName = lastName;
    return 0;
}


int customer::setPhone(std::string phone) {
    this->_phone = phone;
    return 0;
}

int customer::setOrders(std::vector<int> orders) {
    this->_orders = orders;
    return 0;
}

int customer::setLatestOrder(int orderID) {
    this->_orders.emplace_back(orderID);
    return 0;
}

int customer::updateLastVisit(std::string lastVisit) {
    this->_lastVisit = lastVisit;
    return 0;
}

int customer::updateVisits(int visits) {
    this->_visits = visits;
    return 0;
}

int customer::updateTotal(float total){
    this->_total = total;
    return 0;
}


//Helper functions
std::string customer::createPhone(std::string phone) {
    size_t i;
    std::string temp;

    for (i = 0; i < phone.size(); i++)
        if (phone[i] != '(' && phone[i] != ')' && phone[i] != '-' && phone[i] != ' ')
            temp += phone[i];

    return temp;
}

std::string customer::autoCapatilize(const std::string &string){
    size_t i;
    bool cNext = true;
    std::string result = string;

    for(i = 0; i < result.length(); i++){
        if(std::isspace(result[i]))
            cNext = true;
        else if (cNext && std::isalpha(result[i])){
            result[i] = std::toupper(result[i]);
            cNext = false;
        }
        else
            result[i] = std::tolower(result[i]);
    }
    return result;
}

