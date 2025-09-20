#include "search.h"
#include "levenshtein.h"
#include <QElapsedTimer>

using namespace search;

//Customer search functions
std::vector<cust::customer*> Search::searchCustAlgo(const std::string& entry, std::vector<cust::customer>& customers){
    std::vector<cust::customer*> customer;

    if (isName(entry))
        customer = searchCustLastName(cust::customer::autoCapatilize(entry), customers);

    else if (isID(entry))
        customer = searchCustID(entry, customers);

    else if (isPhoneNumber(entry)) {
        std::string temp = cust::customer::createPhone(entry);
        customer = searchCustPhone(temp, customers);
    }

    else if (isNameWithSpace(entry))
        customer = searchCustName(entry, customers);

    return customer;
}

std::vector<cust::customer*> Search::searchCustName(const std::string& entry, std::vector<cust::customer>& customers){
    std::vector<cust::customer*> customer;
    size_t i;

    for (i = 0; i < customers.size(); i++)
        if (entry == customers[i].getName())
            customer.push_back(&customers[i]);
    return customer;
}


std::vector<cust::customer*> Search::searchCustLastName(const std::string& entry, std::vector<cust::customer>& customers){
    std::vector<cust::customer*> customer;
    size_t i;

    // for (i = 0; i < customers.size(); i++) {
    //     if (entry == customers[i].getLastName())
    //         customer.push_back(&customers[i]);

    // }
    // return customer;

    QElapsedTimer timer;
    timer.start();

    for (i = 0; i < customers.size(); i++)
        if (levenshteinDist(entry, customers[i].getLastName()) < 4)
            customer.push_back(&customers[i]);

    return customer;
}
std::vector<cust::customer*> Search::searchCustPhone(const std::string& entry, std::vector<cust::customer>& customers) {
    std::vector<cust::customer*> customer;
    size_t i;

    for (i = 0; i < customers.size(); i++)
        if (entry == customers[i].getPhone())
            customer.push_back(&customers[i]);

    return customer;
}

std::vector<cust::customer*> Search::searchCustID(const std::string& entry, std::vector<cust::customer>& customers) {
    std::vector<cust::customer*> customer;
    int id = std::stoi(entry);
    size_t i;

    for (i = 0; i < customers.size(); i++)
        if (id == customers[i].getCustomerID()){
            customer.push_back(&customers[i]);
            break;
        }
    return customer;
}

//Order search functions
std::vector<orderInfo::order*> Search::searchOrderAlgo(const std::string& entry, std::vector<orderInfo::order> &orders){
    std::vector<orderInfo::order*> order;

    if (isID(entry))
        order = searchOrderCustomerID(entry, orders);

    return order;
}

std::vector<orderInfo::order*> Search::searchOrderID(const std::string& entry, std::vector<orderInfo::order>& orders) {
    int id = stoi(entry);
    size_t i;
    std::vector<orderInfo::order*> order;

    for(i = 0; i < orders.size(); i++){
        if(orders[i].getOrderID() == id){
            order.push_back(&orders[i]);
            break;
        }
    }
    return order;
}

std::vector<orderInfo::order*> Search::searchOrderCustomerID(const std::string& entry, std::vector<orderInfo::order>& orders) {
    std::vector<orderInfo::order*> order;
    int id = stoi(entry);
    size_t i;

    for (i = 0; i < orders.size(); i++) {
        if (orders[i].getCustomerID() == id) {
            order.push_back(&orders[i]);
        }
    }

    return order;
}

std::vector<cust::customer*> Search::copyVector(std::vector<cust::customer>& customers){
    size_t i, end = customers.size();
    std::vector<cust::customer*> customerCopy;

    for(i = 0; i < end; i++)
        customerCopy.push_back(&customers[i]);
    
    return customerCopy;
}

/*
bool Search::comp(std::string a, std::string b) {
    return a > b;
}

std::vector<cust::customer*> Search::sortByLastName(std::vector<cust::customer>& customers){
    std::vector<cust::customer*> customer;





    return customer;
}*/


//Determining Functions
bool Search::isNameWithSpace(const std::string& entry){
    size_t i;
    std::string temp;
    bool found = false;

    for (i = 0; i < entry.size(); i++) {
        if (entry[i] == ' ')
            found = true;
    }

    return found;
}

bool Search::isName(const std::string& entry){
    return std::all_of(entry.begin(), entry.end(), ::isalpha);
}

bool Search::isPhoneNumber(const std::string& entry){
    std::string temp = cust::customer::createPhone(entry);
    bool found = false;

    if (std::all_of(temp.begin(), temp.end(), ::isdigit) && temp.length() == 10)
        found = true;

    return found;
}

bool Search::isID(const std::string& entry){
    return std::all_of(entry.begin(), entry.end(), ::isdigit) && entry.length() <= 7;
}





