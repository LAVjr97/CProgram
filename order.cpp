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

    //laundry.resize(8);
    //dryClean.resize(8);
    //alterations.resize(8);
    laundryO.resize(8);
    dryCleanO.resize(8);
    alterationsO.resize(8);
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

//Constructor used when loading in orders from orderFile into the program memory
order::order(int orderID, int customerID, double cost, int rack, bool pickedUp, bool paid, int dropOffDay, int dropOffMonth, int dropOffYear, int dropOffHour, int dropOffMin, std::string dropOffAm_Pm, int pickUpDay, int pickUpMonth, int pickUpYear, int pickUpHour, int pickUpMin, std::string pickUpAm_Pm, std::vector<std::vector<std::tuple<std::string, int, double>>> laundry, std::vector<std::vector<std::tuple<std::string, int, double>>> dryClean, std::vector<std::vector<std::tuple<std::string, int, double>>> alterations){
    this->orderID = orderID;
    this->customerID = customerID;
    this->cost = cost;
    this->rackNumber = rack;
    this->pickedUp = pickedUp;
    this->paid = paid;
    this->dropOff = new date::Date(dropOffDay, dropOffMonth, dropOffYear, dropOffHour, dropOffMin, dropOffAm_Pm);
    this->pickUp = new date::Date(pickUpDay, pickUpMonth, pickUpYear, pickUpHour, pickUpMin, pickUpAm_Pm);
    this->laundryO = laundry;
    this->dryCleanO = dryClean;
    this->alterationsO = alterations;
}

order::~order() {
    //delete this->dropOff;
    dropOff = nullptr;

    //delete this->pickUp;
    pickUp = nullptr;
}


/*Get Functions*/
int order::getCustomerID() const{
    return this->customerID;
}

int order::getOrderID() const{
    return orderID;
}

std::vector<std::vector<std::pair<int, double>>> order::getDetails() const{
    return laundry;
}

std::vector<std::vector<std::tuple<std::string, int, double>>> order::getLaundry() const{
    return laundryO;
}

std::tuple<std::string, int, double>* order::getLaundryTup(int pos, std::string type){
    size_t i, j;

    for(i = 0; i < laundryO.size(); i++){
        for(j = 0; j < laundry[i].size(); j++){
            if(std::get<0>(laundryO[i][j]) == type)
                return &laundryO[i][j];
        }
    }

    return nullptr;
}


std::vector<std::vector<std::pair<int, double>>> order::getDryClean() const{
    return dryClean;
}

std::vector<std::vector<std::tuple<std::string, int, double>>> order::getDryCleanO() const{
    return dryCleanO;
}

std::vector<std::vector<std::pair<int, double>>> order::getAlterations() const{
    return alterations;
}

std::vector<std::vector<std::tuple<std::string, int, double>>> order::getAlterationsO() const{
    return alterationsO;
}


int order::getLaundryNumber(int pos, double price){
    size_t i;

    for(i = 0; i < laundry[pos].size(); i++){
        if(price == laundry[pos][i].second)
            return laundry[pos][i].first;
    }

    return -1;
}

//Return the number of pieces of a give article
int order::getLaundryNumberO(int pos, std::string article, double price){
    size_t i;

    for(i = 0; i < laundryO[pos].size(); i++)
        if(article == std::get<0>(laundryO[pos][i]) && price == std::get<2>(laundryO[pos][i]))
            return std::get<1>(laundryO[pos][i]);

    return NULL;
}

int order::getDryCleanNumberO(int pos, std::string article, double price){
    size_t i;

    for(i = 0; i < dryCleanO[pos].size(); i++)
        if(article == std::get<0>(dryCleanO[pos][i]) && price == std::get<2>(dryCleanO[pos][i]))
            return std::get<1>(dryCleanO[pos][i]);

    return NULL;
}

int order::getAlterationsNumberO(int pos, std::string article, double price){
    size_t i;

    for(i = 0; i < alterationsO[pos].size(); i++)
        if(article == std::get<0>(alterationsO[pos][i]) && price == std::get<2>(alterationsO[pos][i]))
            return std::get<1>(alterationsO[pos][i]);

    return NULL;
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

void order::setDetails(std::vector<std::vector<std::tuple<std::string, int, double>>> laundry){
    this->laundryO = laundry;
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

bool order::setLaundryPiece(int pos, int n, double price, std::string article){
    size_t i;
    std::vector<std::tuple<std::string, int, double>>::iterator it = laundryO[pos].begin();
    bool foundPrice = false;
    std::tuple<std::string, int, double> tup = std::make_tuple(article, n, price);

    for(i = 0; i < laundryO[pos].size(); i++)
        if(article == std::get<0>(laundryO[pos][i]) && price == std::get<2>(laundryO[pos][i])){
            std::get<1>(laundryO[pos][i]) = n;
            return true;
        }

    for(i = 0; i < laundryO[pos].size(); i++){
        if(article == std::get<0>(laundryO[pos][i]) && price != std::get<2>(laundryO[pos][i])){
            it++;
            laundryO[pos].insert(it, tup);
            return foundPrice;
        }
    }

    if(foundPrice == false)
        laundryO[pos].push_back(tup);

    return foundPrice;
}


int order::setDryClean(std::vector<std::vector<std::pair<int, double>>> dryClean){
    this->dryClean = dryClean;
    return 0;
}

void order::setDryClean(std::vector<std::vector<std::tuple<std::string, int, double>>> dryClean){
    this->dryCleanO = dryClean;
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

bool order::setDryCleanPiece(int pos, int n, double price, std::string article){
    size_t i;
    std::vector<std::tuple<std::string, int, double>>::iterator it = dryCleanO[pos].begin();
    bool foundPrice = false;
    std::tuple<std::string, int, double> tup = std::make_tuple(article, n, price);

    for(i = 0; i < dryCleanO[pos].size(); i++)
        if(article == std::get<0>(dryCleanO[pos][i]) && price == std::get<2>(dryCleanO[pos][i])){
            std::get<1>(dryCleanO[pos][i]) = n;
            return true;
        }

    for(i = 0; i < dryCleanO[pos].size(); i++){
        it++;
        if(article == std::get<0>(dryCleanO[pos][i]) && price != std::get<2>(dryCleanO[pos][i])){
            dryCleanO[pos].insert(it, tup);
            return foundPrice;
        }
    }

    if(foundPrice == false)
        dryCleanO[pos].push_back(tup);

    return foundPrice;
}


int order::setAlterations(std::vector<std::vector<std::pair<int, double>>> alterations){
    this->alterations = alterations;
    return 0;
}

void order::setAlterations(std::vector<std::vector<std::tuple<std::string, int, double>>> alterations){
    this->alterationsO = alterations;
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

bool order::setAlterationsPiece(int pos, int n, double price, std::string article){
    size_t i;
    std::vector<std::tuple<std::string, int, double>>::iterator it = alterationsO[pos].begin();
    bool foundPrice = false;
    std::tuple<std::string, int, double> tup = std::make_tuple(article, n, price);

    for(i = 0; i < alterationsO[pos].size(); i++)
        if(article == std::get<0>(alterationsO[pos][i]) && price == std::get<2>(alterationsO[pos][i])){
            std::get<1>(alterationsO[pos][i]) = n;
            return true;
        }

    for(i = 0; i < alterationsO[pos].size(); i++){
        if(article == std::get<0>(alterationsO[pos][i]) && price != std::get<2>(alterationsO[pos][i])){
            it++;
            alterationsO[pos].insert(it, tup);
            return foundPrice;
        }
    }

    if(foundPrice == false)
        alterationsO[pos].push_back(tup);

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

double order::calculateCostO(){
    this->cost = 0;

    size_t i, j;

    for (i = 0; i < this->laundryO.size(); i++)
        if(laundryO[i].empty() == false)
            for (j = 0; j < this->laundryO[i].size(); j++)
                this->cost = this-> cost + ((std::get<1>(this->laundryO[i][j]) * std::get<2>(this->laundryO[i][j])));

    for (i = 0; i < this->dryCleanO.size(); i++)
        if(dryCleanO[i].empty() == false)
            for (j = 0; j < this->dryCleanO[i].size(); j++)
                this->cost = cost + (std::get<1>(this->dryCleanO[i][j]) * std::get<2>(this->dryCleanO[i][j]));

    for (i = 0; i < this->alterationsO.size(); i++)
        if(alterationsO[i].empty() == false)
            for (j = 0; j < this->alterationsO[i].size(); j++)
                this->cost = cost + (std::get<1>(this->alterationsO[i][j]) * std::get<2>(this->alterationsO[i][j]));

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

