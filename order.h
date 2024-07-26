#ifndef ORDER_H
#define ORDER_H

#include "main.h"

namespace orderInfo{
    class order{
        public:
            //Constructor
            order(std::string firstName, std::string lastName, int customerID, std::string dropOff, std::string pickUp, std::array<std::tuple<int, double>, 8> articles);
            order(int orderID, std::string firstName, std::string lastName, int customerID, std::string dropOff, std::string pickUp, std::array<std::tuple<int, double>, 8> articles);

            //Get functions, set to const to insure that data isn't being changed
            int getCustomerID() const;
            int getOrderID() const;
            std::string getName() const;
            std::string getFirstName() const;
            std::string getLastName() const;
            std::string getDropOffDate() const;
            std::string getPickUpDate() const;
            std::array<std::tuple<int, double>, 8> getDetails() const;
            double getCost() const;

            //Set functions
            int setCustomerID(int id);
            int setFirstName(std::string firstName);
            int setLastName(std::string lastName);
            int setDropOffDate(std::string date);
            int setPickUpDate(std::string date);
            int setDetails(std::array<std::tuple<int, double>, 8> articles);
            int setCost(double cost);

            //Helper functions
            double calculateCost(int* articles);
            int generateOrderID();

            //Serialize
            void serialize(std::ofstream& ofs) const;
            static order deserialize(std::ifstream& ifs) ;

        private:
            int customerID;
            int orderID;

            std::string firstName;
            std::string lastName;

            //Dates and time will be Chars to keep it simple
            //mm/dd/yy
            std::string dropOffDate;
            //hh:mm<pm/am>
            std::string pickUpDate;

            //[0]: Shirts, [1]: Pants, [2]:Sweaters, [3]:Coats, [4]:Blouses, [5]:2pc Suit, [6]:Jacket, [7]:Vest
            std::array<std::tuple<int, double>, 8> articles;

            double cost;
    };
}

#endif // ORDER_H
