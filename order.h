#ifndef ORDER_H
#define ORDER_H

#include "main.h"
#include "date.h"

namespace orderInfo{
    class order{
        public:
            //Constructor
            order(int customerID, int orderID);

            //Loads orders at the start of program
            order(int orderID, int customerID, double cost, int rack, bool pickedUp, bool paid, int pieceTotal, int dropOffDay, int dropOffMonth, int dropOffYear, int dropOffHour, int dropOffMin, std::string dropOffAm_Pm, int pickUpDay, int pickUpMonth, int pickUpYear, int pickUpHour, int pickUpMin, std::string pickUpAm_Pm, std::vector<std::vector<std::pair<int, double>>> laundry, std::vector<std::vector<std::pair<int, double>>> dryClean, std::vector<std::vector<std::pair<int, double>>> alterations);
            order(int orderID, int customerID, double cost, int rack, bool pickedUp, bool paid, int pieceTotal, int dropOffDay, int dropOffMonth, int dropOffYear, int dropOffHour, int dropOffMin, std::string dropOffAm_Pm, int pickUpDay, int pickUpMonth, int pickUpYear, int pickUpHour, int pickUpMin, std::string pickUpAm_Pm, std::vector<std::vector<std::tuple<std::string, int, double>>> laundry, std::vector<std::vector<std::tuple<std::string, int, double>>> dryClean, std::vector<std::vector<std::tuple<std::string, int, double>>> alterations);

            ~order();

            //Get functions, set to const to insure that data isn't being changed
            int getCustomerID() const;
            int getOrderID() const;
            std::vector<std::vector<std::pair<int, double>>> getDetails() const;
            std::vector<std::vector<std::tuple<std::string, int, double>>> getLaundry() const;
            std::tuple<std::string, int, double>* getLaundryTup(int pos, std::string);

            int getLaundryNumberO(int pos, std::string article, double price);
            int getlaundryLength() const;
            //int calcLaundryLength();

            std::vector<std::vector<std::tuple<std::string, int, double>>> getDryCleanO() const;
            int getDryCleanNumberO(int pos, std::string article, double price);
            int getDryCleanLength() const;
            //int calcDryCleanLength();

            std::vector<std::vector<std::tuple<std::string, int, double>>> getAlterationsO() const;
            int getAlterationsNumberO(int pos, std::string article, double price);
            int getAlterationsLength() const;
            //int calcAlterationsLength();

            double getCost() const;
            int getRack() const;
            bool getPickUp() const;
            bool getPaid() const;
            int getPieceTotal() const;

            //Set functions
            int setCustomerID(int id);
            void setDetails(std::vector<std::vector<std::tuple<std::string, int, double>>> laundry);
            void setLaundryPiece(int pos, int n, double price, std::string article);

            void setDryClean(std::vector<std::vector<std::tuple<std::string, int, double>>> dryClean);
            void setDryCleanPiece(int pos, int n, double price, std::string article);

            void setAlterations(std::vector<std::vector<std::tuple<std::string, int, double>>> alterations);
            void setAlterationsPiece(int pos, int n, double price, std::string article);


            int setCost(double cost);
            int setRack(int rack);
            int setPickUp(bool pickUp);
            int setPaid(bool paid);
            void setPieceTotal(int pieceTotal);

            //Helper functions
            double calculateCostO();
            int calculatePieceTotal();


            //order& operator=(const order& other);

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
            int pieceTotal;
    };
}

#endif
