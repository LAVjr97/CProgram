/**
 * @file customer.h
 * @brief <One-line description of file's purpose>
 * @author <Author Name>
 * @date <YYYY-MM-DD>
 * @copyright <Year> <Copyright Owner>
 * @license <Open Source License, if applicable>
 *
 * <More detailed description of the file's contents, module, or package.>
 */

#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "main.h"

namespace cust{
    class customer{
        public:
            //Constructors & Destructor
            customer(int customerID, std::string firstName, std::string lastName, std::string phone, int visits, float total, std::vector<int> orders);
            customer(int customerID, std::string firstName, std::string lastName, std::string phone);
            customer(std::string firstName, std::string lastName);


            //Get functions
            int getCustomerID() const;
            std::string getName() const; //full name
            std::string getFirstName() const;
            std::string getLastName() const;
            std::string getPhone() const;
            std::string getFormattedPhone() const;
            std::string getLastVisit() const;
            int getVisit() const;
            float getTotal() const;
            std::vector<int> getOrders() const;
            int getOrderSize() const;
            int getOrderID(int i) const; //used to get the specific order id of a customer, usefull in loops where i is used to traverse through the array

            //Set functions
            int setCustomerID(int id);
            int setFirstName(std::string firstName);
            int setLastName(std::string lastName);
            int setPhone(std::string phone);
            int setOrders(std::vector<int> orders);
            int setLatestOrder(int orderID);
            int updateLastVisit(std::string lastVisit);
            int updateVisits(int visits);
            int updateTotal(float total);

            //Helper functions
            static std::string createPhone(std::string phone);
            static std::string autoCapatilize(const std::string &string);


            //serialize functions

        private:
            int _customerID;
            std::string _firstName;
            std::string _lastName;
            std::string _phone;

            std::vector<int> _orders;

            std::string _lastVisit;
            int _visits;
            float _total;
    };
}
#endif
