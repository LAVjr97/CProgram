#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "main.h"

namespace cust{
    class customer{
        public:
            //Constructors & Destructor
            customer(int customerID, std::string firstName, std::string lastName, std::string phone, int visits, double total, std::vector<int> orders);
            customer(int customerID, std::string firstName, std::string lastName, std::string phone);
            customer(std::string firstName, std::string lastName);


            //Get functions
            int getCustomerID() const;
            std::string getName() const; //full name
            std::string getFirstName() const;
            std::string getLastName() const;
            std::string getPhone() const;
            std::string getLastVisit() const;
            int getVisit() const;
            double getTotal() const;
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
            int updateTotal(double total);

            //Helper functions
            static std::string createPhone(std::string phone);

            //serialize functions

        private:
            int customerID;
            std::string firstName;
            std::string lastName;
            std::string phone;

            std::vector<int> orders;

            std::string lastVisit;
            int visits;
            double total;
    };
}
#endif
