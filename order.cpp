#include "../include/order.h"

using namespace orderInfo;

//Constructor
order::order(int customerID, std::array<std::tuple<int, double>, 8> articles){
    this->articles = articles;
    this->customerID = customerID;
    this->rackNumber = -1;
    this->pickedUp = false;
    this->calculateCost();
}

order::order(int orderID, int customerID, std::array<std::tuple<int, double>, 8> articles, double cost){
    this->orderID = orderID;
    this->customerID = customerID;
    this->articles = articles;
    this->cost = cost;
    this->rackNumber = -1;
    this->pickedUp = false;
    this->dropOff = new date::Date();
    this->pickUp = new date::Date(2);
}

//Used in handle.cpp
order::order(int orderID, int customerID, std::array<std::tuple<int, double>, 8> articles){
    this->orderID = orderID;
    this->customerID = customerID;
    this->articles = articles;
    this->calculateCost();
    this->rackNumber = -1;
    this->pickedUp = false;
    this->dropOff = new date::Date();
    this->pickUp = new date::Date(2);
}

//Constructor used when loading in orders from orderFile into the program memory
order::order(int orderID, int customerID, double cost, int rack, bool pickedUp, int dropOffDay, int dropOffMonth, int dropOffYear, int dropOffHour, int dropOffMin, std::string dropOffAm_Pm, int pickUpDay, int pickUpMonth, int pickUpYear, int pickUpHour, int pickUpMin, std::string pickUpAm_Pm, std::array<std::tuple<int, double>, 8> articles){
    this->orderID = orderID;
    this->customerID = customerID;
    this->cost = cost;
    this->rackNumber = rack;
    this->pickedUp = pickedUp;
    this->dropOff = new date::Date(dropOffDay, dropOffMonth, dropOffYear, dropOffHour, dropOffMin, dropOffAm_Pm);
    this->pickUp = new date::Date(pickUpDay, pickUpMonth, pickUpYear, pickUpHour, pickUpMin, pickUpAm_Pm);
    this->articles = articles;
}

/*order::~order() {
    delete this->dropOff;
    delete this->pickUp;
}*/


/*Get Functions*/
int order::getCustomerID() const{
    //std::cout << "\n" << this->customerID;
    return this->customerID;
}

int order::getOrderID() const{
    return orderID;
}

/*
std::string order::getDropOffDate() const{
    return dropOffDate;
}

std::string order::getPickUpDate() const{
    return pickUpDate;
}*/

std::array<std::tuple<int, double>, 8> order::getDetails() const{
    return articles;
}

double order::getCost() const{
    return cost;
}

int order::getRack() const{
    return rackNumber;
}

bool order::getPickUp() const{
    return pickedUp;
}

int order::getArticlesLength() const {
    return std::tuple_size<decltype(articles)>::value;
}

/*Set Functions*/
int order::setCustomerID(int id){
    this->customerID = id;
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

int order::setRack(int rack){
    this->rackNumber = rack;
    return 0;
}

int order::setPickUp(bool pickUp){
    this->pickedUp = pickUp;
    return 0;
}

void order::calculateCost() {
    this->cost = 0;

    for (const auto& i : articles)
        this->cost = this->cost + (std::get<0>(i) * std::get<1>(i));

    return;
}

/*
order& order::operator=(const order& other){
    this->customerID = other.getCustomerID();
    this->orderID = other.getOrderID();
    this->firstName = other.getFirstName();
    this->lastName = other.getLastName();
    this->dropOffDate = other.getFirstName();
    this->pickUpDate = other.getPickUpDate();
    this->articles = other.getDetails();
    this->cost = other.getCost();

    return *this;
}
*/

