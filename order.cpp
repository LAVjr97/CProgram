#include "order.h"

using namespace orderInfo;

//Constructor
order::order(int customerID, int orderID){ //used when creating order in the dropoff page
    this->customerID = customerID;
    this->orderID = orderID;
    this->cost = 0;
    this->rackNumber = -1;
    this->pickedUp = false;
    this->dropOff = new date::Date();
    this->pickUp = new date::Date(2);

    laundry.resize(8);
    dryClean.resize(8);
    alterations.resize(8);
}

order::order(int customerID, std::vector<std::vector<std::pair<int, double>>> laundry){
    this->laundry = laundry;
    this->customerID = customerID;
    this->rackNumber = -1;
    this->pickedUp = false;
    this->calculateCost();
}

order::order(int orderID, int customerID, std::vector<std::vector<std::pair<int, double>>> laundry, double cost){
    this->orderID = orderID;
    this->customerID = customerID;
    this->laundry = laundry;
    this->cost = cost;
    this->rackNumber = -1;
    this->pickedUp = false;
    this->dropOff = new date::Date();
    this->pickUp = new date::Date(2);
}

//Used in handle.cpp
order::order(int orderID, int customerID, std::vector<std::vector<std::pair<int, double>>> laundry){
    this->orderID = orderID;
    this->customerID = customerID;
    this->laundry = laundry;
    this->calculateCost();
    this->rackNumber = -1;
    this->pickedUp = false;
    this->dropOff = new date::Date();
    this->pickUp = new date::Date(2);
}

//Constructor used when loading in orders from orderFile into the program memory
order::order(int orderID, int customerID, double cost, int rack, bool pickedUp, bool paid, int dropOffDay, int dropOffMonth, int dropOffYear, int dropOffHour, int dropOffMin, std::string dropOffAm_Pm, int pickUpDay, int pickUpMonth, int pickUpYear, int pickUpHour, int pickUpMin, std::string pickUpAm_Pm, std::vector<std::vector<std::pair<int, double>>> laundry, std::vector<std::vector<std::pair<int, double>>> dryClean, std::vector<std::vector<std::pair<int, double>>> alterations){
    this->orderID = orderID;
    this->customerID = customerID;
    this->cost = cost;
    this->rackNumber = rack;
    this->pickedUp = pickedUp;
    this->paid = paid;
    this->dropOff = new date::Date(dropOffDay, dropOffMonth, dropOffYear, dropOffHour, dropOffMin, dropOffAm_Pm);
    this->pickUp = new date::Date(pickUpDay, pickUpMonth, pickUpYear, pickUpHour, pickUpMin, pickUpAm_Pm);
    this->laundry = laundry;
    this->dryClean = dryClean;
    this->alterations = alterations;
}

order::~order() {
    //delete this->dropOff;
    dropOff = nullptr;

    //delete this->pickUp;
    pickUp = nullptr;
}


/*Get Functions*/
int order::getCustomerID() const{
    //std::cout << "\n" << this->customerID;
    return this->customerID;
}

int order::getOrderID() const{
    return orderID;
}

std::vector<std::vector<std::pair<int, double>>> order::getDetails() const{
    return laundry;
}

std::vector<std::vector<std::pair<int, double>>> order::getDryClean() const{
    return dryClean;
}

std::vector<std::vector<std::pair<int, double>>> order::getAlterations() const{
    return alterations;
}

int order::getLaundryNumber(int pos, double price){
    size_t i;

    for(i = 0; i < laundry[pos].size(); i++){
        if(price == laundry[pos][i].second)
            return laundry[pos][i].first;
    }

    return 0;
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

bool order::getPaid() const{
    return paid;
}

int order::getlaundryLength() const {
    return laundry.size();
}

/*Set Functions*/
int order::setCustomerID(int id){
    this->customerID = id;
    return 0;
}

int order::setDetails(std::vector<std::vector<std::pair<int, double>>> laundry){
    this->laundry = laundry;
    return 0;
}

bool order::setLaundryPiece(int pos, int n, double price){
    //this->laundry[pos].push_back(std::make_pair(n, price));
    size_t i;
    bool foundPrice = false;

    for(i = 0; i < laundry[pos].size(); i++)
        if(price == laundry[pos][i].second){
            laundry[pos][i].first = laundry[pos][i].first + n;
            foundPrice = true;
            break;
        }

    if(foundPrice == false)
        laundry[pos].push_back(std::make_pair(n, price));

    return foundPrice;
}

int order::setDryClean(std::vector<std::vector<std::pair<int, double>>> dryClean){
    this->dryClean = dryClean;
    return 0;
}

bool order::setDryCleanPiece(int pos, int n, double price){
    size_t i;
    bool foundPrice = false;

    for(i = 0; i < dryClean[pos].size(); i++)
        if(price == dryClean[pos][i].second){
            dryClean[pos][i].first = dryClean[pos][i].first + n;
            foundPrice = true;
        }

    if(foundPrice == false)
        dryClean[pos].push_back(std::make_pair(n, price));

    return foundPrice;
}

int order::setAlterations(std::vector<std::vector<std::pair<int, double>>> alterations){
    this->alterations = alterations;
    return 0;
}

bool order::setAlterationsPiece(int pos, int n, double price){
    size_t i;
    bool foundPrice = false;

    for(i = 0; i < alterations[pos].size(); i++)
        if(price == alterations[pos][i].second){
            alterations[pos][i].first = alterations[pos][i].first + n;
            foundPrice = true;
        }

    if(foundPrice == false)
        alterations[pos].push_back(std::make_pair(n, price));

    return foundPrice;
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

int order::setPaid(bool paid){
    this->paid = paid;
    return 0;
}

double order::calculateCost() {
    this->cost = 0;

    size_t i, j;

    for (i = 0; i < this->laundry.size(); i++)
        if(laundry[i].empty() == false)
            for (j = 0; j < this->laundry[i].size(); i++)
                this->cost = cost + (this->laundry[i][j].first * this->laundry[i][j].second);

    for (i = 0; i < this->dryClean.size(); i++)
        if(dryClean[i].empty() == false)
            for (j = 0; j < this->dryClean[i].size(); i++)
                this->cost = cost + (this->dryClean[i][j].first * this->dryClean[i][j].second);

    for (i = 0; i < this->alterations.size(); i++)
        if(alterations[i].empty() == false)
            for (j = 0; j < this->alterations[i].size(); i++)
                this->cost = cost + (this->alterations[i][j].first * this->alterations[i][j].second);

    //for (const auto& i : laundry)

    //this->cost = this->cost + (std::get<0>(i) * std::get<1>(i));

    return this->cost;
}

/*
order& order::operator=(const order& other){
    this->customerID = other.getCustomerID();
    this->orderID = other.getOrderID();
    this->firstName = other.getFirstName();
    this->lastName = other.getLastName();
    this->dropOffDate = other.getFirstName();
    this->pickUpDate = other.getPickUpDate();
    this->laundry = other.getDetails();
    this->cost = other.getCost();

    return *this;
}
*/

