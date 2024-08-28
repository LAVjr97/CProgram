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
            order(int orderID, int customerID, double cost, int rack, bool pickedUp, bool paid, int dropOffDay, int dropOffMonth, int dropOffYear, int dropOffHour, int dropOffMin, std::string dropOffAm_Pm, int pickUpDay, int pickUpMonth, int pickUpYear, int pickUpHour, int pickUpMin, std::string pickUpAm_Pm, std::vector<std::vector<std::pair<int, double>>> laundry, std::vector<std::vector<std::pair<int, double>>> dryClean, std::vector<std::vector<std::pair<int, double>>> alterations);
            order(int orderID, int customerID, double cost, int rack, bool pickedUp, bool paid, int dropOffDay, int dropOffMonth, int dropOffYear, int dropOffHour, int dropOffMin, std::string dropOffAm_Pm, int pickUpDay, int pickUpMonth, int pickUpYear, int pickUpHour, int pickUpMin, std::string pickUpAm_Pm, std::vector<std::vector<std::tuple<std::string, int, double>>> laundry, std::vector<std::vector<std::tuple<std::string, int, double>>> dryClean, std::vector<std::vector<std::tuple<std::string, int, double>>> alterations);

            ~order();

            //Get functions, set to const to insure that data isn't being changed
            int getCustomerID() const;
            int getOrderID() const;
            //std::string getDropOffDate() const;
            //std::string getPickUpDate() const;
            std::vector<std::vector<std::pair<int, double>>> getDetails() const;
            std::vector<std::vector<std::tuple<std::string, int, double>>> getLaundry() const;
            std::tuple<std::string, int, double>* getLaundryTup(int pos, std::string);


            int getLaundryNumber(int pos, double price);
            int getLaundryNumberO(int pos, std::string article, double price);

            int getlaundryLength() const;
            std::vector<std::vector<std::pair<int, double>>> getDryClean() const;
            std::vector<std::vector<std::tuple<std::string, int, double>>> getDryCleanO() const;

            int getDryCleanLength() const;
            std::vector<std::vector<std::pair<int, double>>> getAlterations() const;
            std::vector<std::vector<std::tuple<std::string, int, double>>> getAlterationsO() const;
            int getAlterationsLength() const;

            double getCost() const;
            int getRack() const;
            bool getPickUp() const;
            bool getPaid() const;

            //Set functions
            int setCustomerID(int id);
            //int setDropOffDate(std::string date);
            //int setPickUpDate(std::string date);
            int setDetails(std::vector<std::vector<std::pair<int, double>>> laundry);
            void setDetails(std::vector<std::vector<std::tuple<std::string, int, double>>> laundry);
            bool setLaundryPiece(int pos, int n, double price);
            bool setLaundryPiece(int pos, int n, double price, std::string article);

            int setDryClean(std::vector<std::vector<std::pair<int, double>>> dryClean);
            void setDryClean(std::vector<std::vector<std::tuple<std::string, int, double>>> dryClean);
            bool setDryCleanPiece(int pos, int n, double price);

            int setAlterations(std::vector<std::vector<std::pair<int, double>>> alterations);            
            void setAlterations(std::vector<std::vector<std::tuple<std::string, int, double>>> alterations);
            bool setAlterationsPiece(int pos, int n, double price);


            int setCost(double cost);
            int setRack(int rack);
            int setPickUp(bool pickUp);
            int setPaid(bool paid);

            //Helper functions
            double calculateCost();
            double calculateCostO();

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
            std::vector<std::vector<std::tuple<std::string, int, double>>> laundryO;

            std::vector<std::vector<std::pair<int, double>>> dryClean;
            std::vector<std::vector<std::tuple<std::string, int, double>>> dryCleanO;

            std::vector<std::vector<std::pair<int, double>>> alterations;
            std::vector<std::vector<std::tuple<std::string, int, double>>> alterationsO;

            double cost;
            int rackNumber;
            bool pickedUp;
            bool paid;


    };
}

#endif
