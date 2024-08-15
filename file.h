/*  file.h
    Used to save customer information to an unordered map and
 */

#ifndef FILE_H
#define FILE_H

#include "main.h"

#include "customer.h"
#include "order.h"

namespace fi{
class File{
public:
    //Constructor
    File(std::string customerFile, std::string orderFile, std::string tempFile, std::vector<cust::customer> &customers, std::vector<orderInfo::order> &orders);

    //Customers
    void saveCustomers(cust::customer &customer) const; //save 1 customer at a time;
    void loadCustomers(); //load all of the customers at a time

    //Orders
    void saveOrders(orderInfo::order &order) const; //save 1 order at a time
    void loadOrders();

    //Helper Functions;
    void updateCustomer(const int id);

    //Get Functions
    std::string getCustomerFile() const;
    std::string getOrderFile() const;
    std::string getTempFile() const;

    std::string customerFile;
    std::string orderFile;
    std::string tempFile;

    std::vector<cust::customer> &customers;
    std::vector<orderInfo::order> &orders;
};

}

#endif
