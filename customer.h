#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "main.h"

namespace cust{
    class customer{
        public:
            //Constructors & Destructor
            customer(int customerID, std::string firstName, std::string lastName, std::string phone, int visits, double total);
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

            //Set functions
            int setCustomerID(int id);
            //int setName(std::string name); //full name
            int setFirstName(std::string firstName);
            int setLastName(std::string lastName);
            int setPhone(std::string phone);
            int updateLastVisit(std::string lastVisit);
            int updateVisits(int visits);
            int updateTotal(double total);

            //Helper functions

            //serialize functions
            void serialize(std::ofstream &ofs) const;
            static customer deserialize(std::ifstream& ifs);

        private:
            int customerID;
            std::string firstName;
            std::string lastName;
            std::string phone;
            std::string lastVisit;
            int visits;
            double total;
    };
}

#endif // CUSTOMER_H
