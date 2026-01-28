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
    taxable = false;
    tax = 0.00;
    finalCost = 0.00;
    this->deposit = 0.00;

    laundry.resize(1);
    dryClean.resize(1);
    alterations.resize(1);
}

//Constructor used when loading in orders from orderFile into the program memory
order::order(int orderID, int customerID, double cost, int rack, bool pickedUp, bool paid, int pieceTotal, bool discountApplied, double discount, bool taxable, double tax, double finalCost, double deposit, int dropOffDay, int dropOffMonth, int dropOffYear, int dropOffHour, int dropOffMin, std::string dropOffAm_Pm, int pickUpDay, int pickUpMonth, int pickUpYear, int pickUpHour, int pickUpMin, std::string pickUpAm_Pm, std::vector<std::vector<std::tuple<std::string, int, double>>> laundry, std::vector<std::vector<std::tuple<std::string, int, double>>> dryClean, std::vector<std::vector<std::tuple<std::string, int, double>>> alterations){
    this->orderID = orderID;
    this->customerID = customerID;
    this->cost = cost;
    this->rackNumber = rack;
    this->pickedUp = pickedUp;
    this->paid = paid;
    this->pieceTotal = pieceTotal;
    this->discountApplied = discountApplied;
    this->discount = discount;
    this->taxable = taxable;
    this->tax = tax;
    this->finalCost = finalCost;
    this->deposit = deposit;

    this->dropOff = new date::Date(dropOffDay, dropOffMonth, dropOffYear, dropOffHour, dropOffMin, dropOffAm_Pm);
    this->pickUp = new date::Date(pickUpDay, pickUpMonth, pickUpYear, pickUpHour, pickUpMin, pickUpAm_Pm);
    this->laundryO = laundry;
    this->dryCleanO = dryClean;
    this->alterationsO = alterations;
}

order::order(int orderID, int customerID, double cost, int rack, bool pickedUp, bool paid, int pieceTotal, bool discountApplied, double discount, bool taxable, double tax, double finalCost, double deposit, int dropOffDay, int dropOffMonth, int dropOffYear, int dropOffHour, int dropOffMin, std::string dropOffAm_Pm, int pickUpDay, int pickUpMonth, int pickUpYear, int pickUpHour, int pickUpMin, std::string pickUpAm_Pm, std::vector<std::vector<std::tuple<std::string, std::string, int, double>>> laundry, std::vector<std::vector<std::tuple<std::string, std::string, int, double>>> dryClean, std::vector<std::vector<std::tuple<std::string, std::string, int, double>>> alterations){
    this->orderID = orderID;
    this->customerID = customerID;
    this->cost = cost;
    this->rackNumber = rack;
    this->pickedUp = pickedUp;
    this->paid = paid;
    this->pieceTotal = pieceTotal;
    this->discountApplied = discountApplied;
    this->discount = discount;
    this->taxable = taxable;
    this->tax = tax;
    this->finalCost = finalCost;
    this->deposit = deposit;

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
    return this->customerID;
}

int order::getOrderID() const{
    return orderID;
}

std::vector<std::vector<std::tuple<std::string, std::string, int, double>>> order::getLaundry() const{
    return laundry;
}

std::vector<std::vector<std::tuple<std::string, std::string, int, double>>> order::getDryClean() const{
    return dryClean;
}

std::vector<std::vector<std::tuple<std::string, std::string, int, double>>> order::getAlterations() const{
    return alterations;
}

int order::getLaundryNumber(std::string articleType, std::string article, double price){
    size_t i, j;

    for(i = 0; i < laundry.size(); i++){
        if(articleType == std::get<0>(laundry[i][0]))
            for(j = 0; j < laundry[i].size(); j++)
                if(article == std::get<1>(laundry[i][j]) && price == std::get<3>(laundry[i][j]))
                    return std::get<2>(laundry[i][j]);
    }

    return NULL;
}

int order::getDryCleanNumber(std::string articleType, std::string article, double price){
    size_t i, j;

    for(i = 0; i < dryClean.size(); i++){
        if(articleType == std::get<0>(dryClean[i][0]))
            for(j = 0; j < dryClean[i].size(); j++)
                if(article == std::get<1>(dryClean[i][j]) && price == std::get<3>(dryClean[i][j]))
                    return std::get<2>(dryClean[i][j]);
    }

    return NULL;
}

int order::getAlterationsNumber(std::string articleType, std::string article, double price){
    size_t i, j;

    for(i = 0; i < alterations.size(); i++){
        if(articleType == std::get<0>(alterations[i][0]))
            for(j = 0; j < alterations[i].size(); j++)
                if(article == std::get<1>(alterations[i][j]) && price == std::get<3>(alterations[i][j]))
                    return std::get<2>(alterations[i][j]);
    }

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

double order::getDeposit() const{
    return deposit;
}

/*Set Functions*/
int order::setCustomerID(int id){
    this->customerID = id;
    return 0;
}

void order::setLaundry(std::vector<std::vector<std::tuple<std::string, std::string, int, double>>> laundry){
    this->laundry = laundry;
}

void order::setLaundryPiece(std::string articleType, int n, double price, std::string article){
    size_t i, j;
    std::tuple<std::string, std::string, int, double> tup = std::make_tuple(articleType, article, n, price);

    if(laundry[0].empty()){
        laundry[0].push_back(tup);
        return;
    }

    for(i = 0; i< laundry.size(); i++)
        if(articleType == std::get<0>(laundry[i][0])){
            std::vector<std::tuple<std::string, std::string, int, double>>::iterator it = laundry[i].begin();
            for(j = 0; j < laundry[i].size(); j++){
                if(article == std::get<1>(laundry[i][j]) && price == std::get<3>(laundry[i][j])){
                    std::get<2>(laundry[i][j]) = n;
                    return;
                }

                if(article == std::get<1>(laundry[i][j]) && price != std::get<2>(laundry[i][j])){
                    it++;
                    laundry[i].insert(it, tup);
                    return;
                }
            }
        }

    std::vector<std::tuple<std::string, std::string, int, double>> articleVec;
    articleVec.push_back(tup);
    laundry.push_back(articleVec);

    return;
}

void order::setDryClean(std::vector<std::vector<std::tuple<std::string, std::string, int, double>>> dryClean){
    this->dryClean = dryClean;
}

void order::setDryCleanPiece(std::string articleType, int n, double price, std::string article){
    size_t i, j;
    std::tuple<std::string, std::string, int, double> tup = std::make_tuple(articleType, article, n, price);

    if(dryClean[0].empty()){
        dryClean[0].push_back(tup);
        return;
    }

    for(i = 0; i< dryClean.size(); i++)
        if(articleType == std::get<0>(dryClean[i][0])){
            std::vector<std::tuple<std::string, std::string, int, double>>::iterator it = dryClean[i].begin();
            for(j = 0; j < dryClean[i].size(); j++){
                if(article == std::get<1>(dryClean[i][j]) && price == std::get<3>(dryClean[i][j])){
                    std::get<2>(dryClean[i][j]) = n;
                    return;
                }

                if(article == std::get<1>(dryClean[i][j]) && price != std::get<3>(dryClean[i][j])){
                    it++;
                    dryClean[i].insert(it, tup);
                    return;
                }
            }
        }

    std::vector<std::tuple<std::string, std::string, int, double>> articleVec;
    articleVec.push_back(tup);
    dryClean.push_back(articleVec);

    return;
}


void order::setAlterations(std::vector<std::vector<std::tuple<std::string, std::string, int, double>>> alterations){
    this->alterations = alterations;
}

void order::setAlterationsPiece(std::string articleType, int n, double price, std::string article){
    size_t i, j;
    std::tuple<std::string, std::string, int, double> tup = std::make_tuple(articleType, article, n, price);

    if(alterations[0].empty()){
        alterations[0].push_back(tup);
        return;
    }

    for(i = 0; i< alterations.size(); i++)
        if(articleType == std::get<0>(alterations[i][0])){
            std::vector<std::tuple<std::string, std::string, int, double>>::iterator it = alterations[i].begin();
            for(j = 0; j < alterations[i].size(); j++){
                if(article == std::get<1>(alterations[i][j]) && price == std::get<3>(alterations[i][j])){
                    std::get<2>(alterations[i][j]) = n;
                    return;
                }

                if(article == std::get<1>(alterations[i][j]) && price != std::get<2>(alterations[i][j])){
                    it++;
                    alterations[i].insert(it, tup);
                    return;
                }
            }
        }

    std::vector<std::tuple<std::string, std::string, int, double>> articleVec;
    articleVec.push_back(tup);
    alterations.push_back(articleVec);

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

void order::setDeposit(double dep){
    this->deposit = dep;
}

double order::calculateCostO(){
    this->cost = 0;

    size_t i, j;

    for (i = 0; i < this->laundry.size(); i++)
        //if(laundry[i].empty() == false)
        for (j = 0; j < this->laundry[i].size(); j++)
            this->cost = this-> cost + ((std::get<2>(this->laundry[i][j]) * std::get<3>(this->laundry[i][j])));

    for (i = 0; i < this->dryClean.size(); i++)
        //if(dryCleanO[i].empty() == false)
        for (j = 0; j < this->dryClean[i].size(); j++)
            this->cost = cost + (std::get<2>(this->dryClean[i][j]) * std::get<3>(this->dryClean[i][j]));

    for (i = 0; i < this->alterations.size(); i++)
        //if(alterationsO[i].empty() == false)
        for (j = 0; j < this->alterations[i].size(); j++)
            this->cost = cost + (std::get<2>(this->alterations[i][j]) * std::get<3>(this->alterations[i][j]));

    return cost;
}

int order::calculatePieceTotal(){
    this-> pieceTotal = 0;

    size_t i, j;

    for(i = 0; i < this->laundry.size(); i++)
        //if(laundryO[i].empty() == false)
        for(j = 0; j < laundry[i].size(); j++)
            pieceTotal = pieceTotal + (std::get<2>(laundry[i][j]));

    for(i = 0; i < this->dryClean.size(); i++)
        //if(dryCleanO[i].empty() == false)
        for(j = 0; j < dryClean[i].size(); j++)
            pieceTotal = pieceTotal + (std::get<2>(dryClean[i][j]));

    for(i = 0; i < this->alterations.size(); i++)
        //if(alterationsO[i].empty() == false)
        for(j = 0; j < alterations[i].size(); j++)
            pieceTotal = pieceTotal + (std::get<2>(alterations[i][j]));

    return pieceTotal;
}

double order::calculateFinalCost(){
    double tempCost;

    if(discountApplied)
        finalCost = cost - (cost * (discount/100.0));
    else
        finalCost = cost;

    tempCost = finalCost;

    if(taxable)
        finalCost = tempCost + (tempCost * .09375);
    else
        finalCost = tempCost;

    return finalCost;
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

