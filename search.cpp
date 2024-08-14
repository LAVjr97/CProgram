#include "order.h"
#include "customer.h"
#include "search.h"

using namespace search;

//Customer search functions
std::vector<cust::customer> Search::searchCustAlgo(const std::string& entry, std::vector<cust::customer>& customers){
    std::vector<cust::customer> customer;

    if (isName(entry))
        customer = searchCustLastName(entry, customers);

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

std::vector<cust::customer> Search::searchCustName(const std::string& entry, std::vector<cust::customer>& customers){
    std::vector<cust::customer> customer;
    int i = 0;

    for (i = 0; i < customers.size(); i++)
        if (entry == customers[i].getName())
            customer.emplace_back(customers[i].getCustomerID(), customers[i].getFirstName(), customers[i].getLastName(), customers[i].getPhone(), customers[i].getVisit(), customers[i].getTotal(), customers[i].getOrders());

    return customer;
}


std::vector<cust::customer> Search::searchCustLastName(const std::string& entry, std::vector<cust::customer>& customers){
    std::vector<cust::customer> customer;
    std::string phone;

    phone = cust::customer::createPhone(entry);

    int i = 0;

    for (i = 0; i < customers.size(); i++) {
        if (entry == customers[i].getLastName()) {
            customer.emplace_back(customers[i].getCustomerID(), customers[i].getFirstName(), customers[i].getLastName(), customers[i].getPhone(), customers[i].getVisit(), customers[i].getTotal(), customers[i].getOrders());
        }
    }
    return customer;
}
std::vector<cust::customer> Search::searchCustPhone(const std::string& entry, std::vector<cust::customer>& customers) {
    std::vector<cust::customer> customer;
    int i;

    for(i = 0; i < customers.size(); i++)
        if(entry == customers[i].getPhone())
            customer.emplace_back(customers[i].getCustomerID(), customers[i].getFirstName(), customers[i].getLastName(), customers[i].getPhone(), customers[i].getVisit(), customers[i].getTotal(), customers[i].getOrders());

    return customer;
}

std::vector<cust::customer> Search::searchCustID(const std::string& entry, std::vector<cust::customer>& customers) {
    std::vector<cust::customer> customer;
    int id = std::stoi(entry), i = 0;

    for (i = 0; i < customers.size(); i++)
        if (id == customers[i].getCustomerID()){
            customer.emplace_back(customers[i].getCustomerID(), customers[i].getFirstName(), customers[i].getLastName(), customers[i].getPhone(), customers[i].getVisit(), customers[i].getTotal(), customers[i].getOrders());
            break;
        }
    return customer;
}

//Order search functions
std::vector<orderInfo::order> Search::searchOrderAlgo(const std::string& entry, std::vector<orderInfo::order> &orders){
    std::vector<orderInfo::order> order;

    if (isID(entry))
        order = searchOrderID(entry, orders);

    return order;
}

std::vector<orderInfo::order> Search::searchOrderID(const std::string& entry, const std::vector<orderInfo::order> &orders){
    int id = stoi(entry), i, j = 0;
    std::vector<orderInfo::order> order;

    for(i = 0; i < orders.size(); i++){
        if(orders[i].getOrderID() == id){
            order.emplace_back(orders[i].getCustomerID(), orders[i].getCustomerID(), orders[i].getDetails(), orders[i].getCost());
            break;
        }
    }
    return order;
}

//Determining Functions
bool Search::isNameWithSpace(const std::string& entry){
    int i, j;
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



