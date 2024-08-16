#ifndef SEARCH_H
#define SEARCH_H

#include "main.h"
#include "customer.h"
#include "order.h"



namespace search{
class Search{
public:
    Search(){
        this->lastAccessedCustoemr = 0;
        this->lastAccessedOrder = 0;
    }

    //search customer
    //search order
    //search by phone
    std::vector<cust::customer*> searchCustAlgo(const std::string& entry, std::vector<cust::customer>& customers);
    std::vector<cust::customer*> searchCustName(const std::string& entry, std::vector<cust::customer>& customers);
    std::vector<cust::customer*> searchCustLastName(const std::string& entry, std::vector<cust::customer>& customers);
    std::vector<cust::customer*> searchCustPhone(const std::string& entry, std::vector<cust::customer>& customers);
    std::vector<cust::customer*> searchCustID(const std::string& entry, std::vector<cust::customer>& customers);



    std::vector<orderInfo::order*> searchOrderAlgo(const std::string& entry, std::vector<orderInfo::order> &orders);
    std::vector<orderInfo::order*> searchOrderID(const std::string& entry, std::vector<orderInfo::order> &orders);
    std::vector<orderInfo::order*> searchOrderCustomerID(const std::string& entry, std::vector<orderInfo::order> &orders);


    //Determining Functions
    bool isNameWithSpace(const std::string& entry);
    static bool isName(const std::string& entry);
    static bool isPhoneNumber(const std::string& entry);
    static bool isID(const std::string& entry);

private:
    //last accessed
    int lastAccessedOrder;
    int lastAccessedCustoemr;

};

}

#endif
