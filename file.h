/*  file.h
    Used to save customer information to an unordered map and
 */

#ifndef FILE_H
#define FILE_H

#include "main.h"

#include "logger.h"
#include "customer.h"
#include "order.h"

namespace fi{
    class File{
        public:
            //Constructor
            File(std::string customerFile, std::string orderFile, std::string priceFile, std::string tempOrderFile, std::string tempCustFile, std::vector<cust::customer>& customers, std::vector<orderInfo::order>& orders, std::vector<std::vector<std::pair<std::string, double>>> &laundryPrices, std::vector<std::vector<std::pair<std::string, double>>> &dryCleanPrices, std::vector<std::vector<std::pair<std::string, double>>> &alterationsPrices, std::vector<std::tuple<std::string, int, int>> &laundryPos, std::vector<std::tuple<std::string, int, int>> &dryCleanPos, std::vector<std::tuple<std::string, int, int>> &alterationsPos, std::string logFile);
            
            //Customers
            void saveCustomers(cust::customer &customer); //save 1 customer at a time;
            void loadCustomers(); //load all of the customers at a time

            //Orders
            void saveOrders(orderInfo::order &order); //save 1 order at a time
            void loadOrders();

            //Helper Functions;
            void updateCustomer(const int id);
            void updateOrder(const int id);

            //Prices
            void savePrices();
            void loadPrices();

            //Get Functions
            std::string getCustomerFile() const;
            std::string getOrderFile() const;
            std::string getTempFile() const;

            void checkAndCreateFile(const std::string& filename);

            int checkOrderIDs();

            std::string customerFile;
            std::string orderFile;
            std::string priceFile;
            std::string tempOrderFile;
            std::string tempCustFile;
            
            logger::Logger *logger;

            std::vector<cust::customer> &customers;
            std::vector<orderInfo::order> &orders;

            std::vector<std::vector<std::pair<std::string, double>>> &laundryPrices;
            std::vector<std::vector<std::pair<std::string, double>>> &dryCleanPrices;
            std::vector<std::vector<std::pair<std::string, double>>> &alterationsPrices;

            std::vector<std::tuple<std::string, int, int>> &laundryPos;
            std::vector<std::tuple<std::string, int, int>> &dryCleanPos;
            std::vector<std::tuple<std::string, int, int>> &alterationsPos;


    };

}

#endif
