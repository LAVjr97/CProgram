#ifndef ORDER_H
#define ORDER_H

#include "main.h"
#include "date.h"

namespace orderInfo{
    class order{
        public:
            //Constructor
            order(int customerID, std::array<std::tuple<int, double>, 8> articles);
            order(int orderID, int customerID, std::array<std::tuple<int, double>, 8> articles, double cost);
            order(int orderID, int customerID, std::array<std::tuple<int, double>, 8> articles);

            //Loads orders at the start of program
            order(int orderID, int customerID, double cost, int rack, bool pickedUp, int dropOffDay, int dropOffMonth, int dropOffYear, int dropOffHour, int dropOffMin, std::string dropOffAm_Pm, int pickUpDay, int pickUpMonth, int pickUpYear, int pickUpHour, int pickUpMin, std::string pickUpAm_Pm, std::array<std::tuple<int, double>, 8> articles);

            //Get functions, set to const to insure that data isn't being changed
            int getCustomerID() const;
            int getOrderID() const;
            //std::string getDropOffDate() const;
            //std::string getPickUpDate() const;
            std::array<std::tuple<int, double>, 8> getDetails() const;
            double getCost() const;
            int getRack() const;
            bool getPickUp() const;
            int getArticlesLength() const;

            //Set functions
            int setCustomerID(int id);
            //int setDropOffDate(std::string date);
            //int setPickUpDate(std::string date);
            int setDetails(std::array<std::tuple<int, double>, 8> articles);
            int setCost(double cost);
            int setRack(int rack);
            int setPickUp(bool pickUp);

            //Helper functions
            void calculateCost();

            //order& operator=(const order& other);

            //Serialize
            void serialize(std::ofstream& ofs) const;
            static order deserialize(std::ifstream& ifs);
            date::Date* dropOff;
            date::Date* pickUp;

        private:
            int customerID;
            int orderID;

            //[0]: Shirts, [1]: Pants, [2]:Sweaters, [3]:Coats, [4]:Blouses, [5]:2pc Suit, [6]:Jacket, [7]:Vest
            std::array<std::tuple<int, double>, 8> articles;

            double cost;
            int rackNumber;
            bool pickedUp;


    };
}

#endif
