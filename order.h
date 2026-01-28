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
            order(int orderID, int customerID, double cost, int rack, bool pickedUp, bool paid, int pieceTotal, bool discountApplied, double discount, bool taxable, double tax, double finalCost, double deposit, int dropOffDay, int dropOffMonth, int dropOffYear, int dropOffHour, int dropOffMin, std::string dropOffAm_Pm, int pickUpDay, int pickUpMonth, int pickUpYear, int pickUpHour, int pickUpMin, std::string pickUpAm_Pm, std::vector<std::vector<std::tuple<std::string, int, double>>> laundry, std::vector<std::vector<std::tuple<std::string, int, double>>> dryClean, std::vector<std::vector<std::tuple<std::string, int, double>>> alterations);
            order(int orderID, int customerID, double cost, int rack, bool pickedUp, bool paid, int pieceTotal, bool discountApplied, double discount, bool taxable, double tax, double finalCost, double deposit, int dropOffDay, int dropOffMonth, int dropOffYear, int dropOffHour, int dropOffMin, std::string dropOffAm_Pm, int pickUpDay, int pickUpMonth, int pickUpYear, int pickUpHour, int pickUpMin, std::string pickUpAm_Pm, std::vector<std::vector<std::tuple<std::string, std::string, int, double>>> laundry, std::vector<std::vector<std::tuple<std::string, std::string, int, double>>> dryClean, std::vector<std::vector<std::tuple<std::string, std::string, int, double>>> alterations);

            ~order();

            //Get functions, set to const to insure that data isn't being changed
            int getCustomerID() const;
            int getOrderID() const;

            std::vector<std::vector<std::tuple<std::string, std::string, int, double>>> getLaundry() const;
            int getLaundryNumber(std::string articleType, std::string article, double price);
            int getlaundryLength() const;

            std::vector<std::vector<std::tuple<std::string, std::string, int, double>>> getDryClean() const;
            int getDryCleanNumber(std::string articleType, std::string article, double price);
            int getDryCleanLength() const;

            std::vector<std::vector<std::tuple<std::string, std::string, int, double>>> getAlterations() const;
            int getAlterationsNumber(std::string articleType, std::string article, double price);
            int getAlterationsLength() const;

            double getCost() const;
            int getRack() const;
            bool getPickUp() const;
            bool getPaid() const;
            int getPieceTotal() const;
            bool getDiscountApplied() const;
            double getDiscount() const;

            bool getTaxable() const {return taxable;}
            double getTax() const {return tax;}

            double getFinalCost() const {return finalCost;}
            double getDeposit() const;

            //Set functions
            int setCustomerID(int id);
            void setLaundry(std::vector<std::vector<std::tuple<std::string, std::string, int, double>>> laundry);
            void setLaundryPiece(std::string articleType, int n, double price, std::string article);

            void setDryClean(std::vector<std::vector<std::tuple<std::string, std::string, int, double>>> laundry);
            void setDryCleanPiece(std::string articleType, int n, double price, std::string article);

            void setAlterations(std::vector<std::vector<std::tuple<std::string, std::string, int, double>>> alterations);
            void setAlterationsPiece(std::string articleType, int n, double price, std::string article);

            int setCost(double cost);
            int setRack(int rack);
            int setPickUp(bool pickUp);
            int setPaid(bool paid);
            void setPieceTotal(int pieceTotal);
            void setDiscountApplied(bool applied);
            void setDiscount(double disc);
            void setTaxable(bool taxable) {this->taxable = taxable;}
            void setTax(double tax) {this->tax = tax;}
            void setfinalCost(double finalCost) {this->finalCost = finalCost;}

            void setDeposit(double dep);

            //Helper functions
            double calculateCostO();
            int calculatePieceTotal();
            bool verifyOrderIDs();
            double calculateFinalCost();
            void set_calculateTax(){tax = (cost * .09375);}
            void taxReset(){dryClean.clear(); dryClean.resize(1); laundry.clear(); laundry.shrink_to_fit();}

            //order& operator=(const order& other);

            //Dates
            date::Date* dropOff;
            date::Date* pickUp;

        private:
            int  customerID;
            int orderID;

            //[0]: Shirts, [1]: Pants, [2]:Sweaters, [3]:Coats, [4]:Blouses, [5]:2pc Suit, [6]:Jacket, [7]:Vest
            std::vector<std::vector<std::tuple<std::string, int, double>>> laundryO;
            std::vector<std::vector<std::tuple<std::string, std::string, int, double>>> laundry;

            std::vector<std::vector<std::tuple<std::string, int, double>>> dryCleanO;
            std::vector<std::vector<std::tuple<std::string, std::string, int, double>>> dryClean;

            std::vector<std::vector<std::tuple<std::string, int, double>>> alterationsO;
            std::vector<std::vector<std::tuple<std::string, std::string, int, double>>> alterations;

            double cost;
            int rackNumber;
            bool pickedUp;
            bool paid;
            int pieceTotal;

            bool discountApplied;
            double discount;

            bool taxable;
            double tax;

            double finalCost;

            double deposit;
    };
}

#endif
