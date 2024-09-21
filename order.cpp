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
    this->pickUp = new date::Date(3);
    this->pieceTotal = 0;
    this->discountApplied = false;
    this->discount = 0.00;
    this->discountedCost = 0.00;
    this->deposit = 0.00;

    laundryO.resize(1);
    dryCleanO.resize(1);
    alterationsO.resize(1);
}

//Constructor used when loading in orders from orderFile into the program memory
order::order(int orderID, int customerID, double cost, int rack, bool pickedUp, bool paid, int pieceTotal, bool discountApplied, double discount, double discountedCost, double deposit, int dropOffDay, int dropOffMonth, int dropOffYear, int dropOffHour, int dropOffMin, std::string dropOffAm_Pm, int pickUpDay, int pickUpMonth, int pickUpYear, int pickUpHour, int pickUpMin, std::string pickUpAm_Pm, std::vector<std::vector<std::tuple<std::string, int, double>>> laundry, std::vector<std::vector<std::tuple<std::string, int, double>>> dryClean, std::vector<std::vector<std::tuple<std::string, int, double>>> alterations){
    this->orderID = orderID;
    this->customerID = customerID;
    this->cost = cost;
    this->rackNumber = rack;
    this->pickedUp = pickedUp;
    this->paid = paid;
    this->pieceTotal = pieceTotal;
    this->discountApplied = discountApplied;
    this->discount = discount;
    this->discountedCost = discountedCost;
    this->deposit = deposit;

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

std::vector<std::vector<std::tuple<std::string, int, double>>> order::getLaundry() const{
    return laundryO;
}

std::tuple<std::string, int, double>* order::getLaundryTup(int pos, std::string type){
    size_t i, j;

    for(i = 0; i < laundryO.size(); i++){
        for(j = 0; j < laundryO[i].size(); j++){
            if(std::get<0>(laundryO[i][j]) == type)
                return &laundryO[i][j];
        }
    }

    return nullptr;
}

std::vector<std::vector<std::tuple<std::string, int, double>>> order::getDryCleanO() const{
    return dryCleanO;
}

std::vector<std::vector<std::tuple<std::string, int, double>>> order::getAlterationsO() const{
    return alterationsO;
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

int order::getPieceTotal() const{
    return pieceTotal;
}

int order::getlaundryLength() const {
    return laundryO.size();
}

bool order::getDiscountApplied() const{
    return discountApplied;
}

double order::getDiscount() const{
    return discount;
}

double order::getDiscountedCost() const{
    return discountedCost;
}

double order::getDeposit() const{
    return deposit;
}

/*Set Functions*/
int order::setCustomerID(int id){
    this->customerID = id;
    return 0;
}

void order::setDetails(std::vector<std::vector<std::tuple<std::string, int, double>>> laundry){
    this->laundryO = laundry;
}

void order::setLaundryPiece(int pos, int n, double price, std::string article){
    size_t i;
    std::vector<std::tuple<std::string, int, double>>::iterator it = laundryO[pos].begin();
    std::tuple<std::string, int, double> tup = std::make_tuple(article, n, price);

    for(i = 0; i < laundryO[pos].size(); i++)
        if(article == std::get<0>(laundryO[pos][i]) && price == std::get<2>(laundryO[pos][i])){
            std::get<1>(laundryO[pos][i]) = n;
            return;
        }

    for(i = 0; i < laundryO[pos].size(); i++){
        if(article == std::get<0>(laundryO[pos][i]) && price != std::get<2>(laundryO[pos][i])){
            it++;
            laundryO[pos].insert(it, tup);
            return;
        }
    }

    laundryO[pos].push_back(tup);

    return;
}

void order::setDryClean(std::vector<std::vector<std::tuple<std::string, int, double>>> dryClean){
    this->dryCleanO = dryClean;
}

void order::setDryCleanPiece(int pos, int n, double price, std::string article){
    size_t i;
    std::vector<std::tuple<std::string, int, double>>::iterator it = dryCleanO[pos].begin();
    std::tuple<std::string, int, double> tup = std::make_tuple(article, n, price);

    for(i = 0; i < dryCleanO[pos].size(); i++)
        if(article == std::get<0>(dryCleanO[pos][i]) && price == std::get<2>(dryCleanO[pos][i])){
            std::get<1>(dryCleanO[pos][i]) = n;
            return;
        }

    for(i = 0; i < dryCleanO[pos].size(); i++){
        it++;
        if(article == std::get<0>(dryCleanO[pos][i]) && price != std::get<2>(dryCleanO[pos][i])){
            dryCleanO[pos].insert(it, tup);
            return;
        }
    }

    dryCleanO[pos].push_back(tup);

    return;
}

void order::setAlterations(std::vector<std::vector<std::tuple<std::string, int, double>>> alterations){
    this->alterationsO = alterations;
}

void order::setAlterationsPiece(int pos, int n, double price, std::string article){
    size_t i;
    std::vector<std::tuple<std::string, int, double>>::iterator it = alterationsO[pos].begin();
    std::tuple<std::string, int, double> tup = std::make_tuple(article, n, price);

    for(i = 0; i < alterationsO[pos].size(); i++)
        if(article == std::get<0>(alterationsO[pos][i]) && price == std::get<2>(alterationsO[pos][i])){
            std::get<1>(alterationsO[pos][i]) = n;
            return;
        }

    for(i = 0; i < alterationsO[pos].size(); i++){
        if(article == std::get<0>(alterationsO[pos][i]) && price != std::get<2>(alterationsO[pos][i])){
            it++;
            alterationsO[pos].insert(it, tup);
            return;
        }
    }

    alterationsO[pos].push_back(tup);

    return;
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

void order::setPieceTotal(int pieceTotal){
    this->pieceTotal = pieceTotal;
}

void order::setDiscountApplied(bool applied){
    this->discountApplied = applied;
}

void order::setDiscount(double disc){
    this->discount = disc;
}

void order::setDiscountedCost(double discCost){
    this->discountedCost = discCost;
}

void order::setDeposit(double dep){
    this->deposit = dep;
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

    return cost;
}

int order::calculatePieceTotal(){
    this-> pieceTotal = 0;

    size_t i, j;

    for(i = 0; i < this->laundryO.size(); i++)
        if(laundryO[i].empty() == false)
            for(j = 0; j < laundryO[i].size(); j++)
                pieceTotal = pieceTotal + (std::get<1>(laundryO[i][j]));

    for(i = 0; i < this->dryCleanO.size(); i++)
        if(dryCleanO[i].empty() == false)
            for(j = 0; j < dryCleanO[i].size(); j++)
                pieceTotal = pieceTotal + (std::get<1>(dryCleanO[i][j]));

    for(i = 0; i < this->alterationsO.size(); i++)
        if(alterationsO[i].empty() == false)
            for(j = 0; j < alterationsO[i].size(); j++)
                pieceTotal = pieceTotal + (std::get<1>(alterationsO[i][j]));

    return pieceTotal;
}

double order::applyDiscount(){
    if(discountApplied) // = true;
        discountedCost = cost - (cost * (discount/100.0));

    return discountedCost;
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

