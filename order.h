#ifndef ORDER_H
#define ORDER_H

#include "main.h"
#include "date.h"

namespace orderInfo{
    class order{
        public:
            //Constructor
            order(int customerID, int orderID);
            order(int customerID, std::vector<std::vector<std::pair<int, double>>> laundry);
            order(int orderID, int customerID, std::vector<std::vector<std::pair<int, double>>> laundry, double cost);
            order(int orderID, int customerID, std::vector<std::vector<std::pair<int, double>>> laundry);

            //Loads orders at the start of program
            order(int orderID, int customerID, double cost, int rack, bool pickedUp, int dropOffDay, int dropOffMonth, int dropOffYear, int dropOffHour, int dropOffMin, std::string dropOffAm_Pm, int pickUpDay, int pickUpMonth, int pickUpYear, int pickUpHour, int pickUpMin, std::string pickUpAm_Pm, std::vector<std::vector<std::pair<int, double>>> laundry, std::vector<std::vector<std::pair<int, double>>> dryClean, std::vector<std::vector<std::pair<int, double>>> alterations);

            ~order();

            //Get functions, set to const to insure that data isn't being changed
            int getCustomerID() const;
            int getOrderID() const;
            //std::string getDropOffDate() const;
            //std::string getPickUpDate() const;
            std::vector<std::vector<std::pair<int, double>>> getDetails() const;
            int getLaundryNumber(int pos, double price);
            int getlaundryLength() const;
            std::vector<std::vector<std::pair<int, double>>> getDryClean() const;
            int getDryCleanLength() const;
            std::vector<std::vector<std::pair<int, double>>> getAlterations() const;
            int getAlterationsLength() const;

            double getCost() const;
            int getRack() const;
            bool getPickUp() const;

            //Set functions
            int setCustomerID(int id);
            //int setDropOffDate(std::string date);
            //int setPickUpDate(std::string date);
            int setDetails(std::vector<std::vector<std::pair<int, double>>> laundry);
            bool setLaundryPiece(int pos, int n, double price);
            int setDryClean(std::vector<std::vector<std::pair<int, double>>> dryClean);
            bool setDryCleanPiece(int pos, int n, double price);
            int setAlterations(std::vector<std::vector<std::pair<int, double>>> alterations);
            bool setAlterationsPiece(int pos, int n, double price);


            int setCost(double cost);
            int setRack(int rack);
            int setPickUp(bool pickUp);

            //Helper functions
            double calculateCost();

            //order& operator=(const order& other);

            //Serialize
            void serialize(std::ofstream& ofs) const;
            static order deserialize(std::ifstream& ifs);

            //Dates
            date::Date* dropOff;
            date::Date* pickUp;

        private:
            int customerID;
            int orderID;

            //[0]: Shirts, [1]: Pants, [2]:Sweaters, [3]:Coats, [4]:Blouses, [5]:2pc Suit, [6]:Jacket, [7]:Vest
            std::vector<std::vector<std::pair<int, double>>> laundry;
            //
            std::vector<std::vector<std::pair<int, double>>> dryClean;
            //
            std::vector<std::vector<std::pair<int, double>>> alterations;
            double cost;
            int rackNumber;
            bool pickedUp;


    };
}

#endif
