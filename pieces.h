#ifndef PIECES_H
#define PIECES_H

#include "main.h"
namespace pieces{
    //Individual Piece
    class piece
    {
        public:
            piece();
            //piece(std::string pieceName, int pieceID, float piecePrice, int pieceCount) : _name(pieceName), _pieceID(pieceID), _price(piecePrice), _count(pieceCount) {};
            piece(std::string pieceName, int pieceID, int typeID, float piecePrice, int pieceCount) : _name(pieceName), _pieceID(pieceID), _typeID(typeID), _price(piecePrice), _count(pieceCount) {};

            //Getter functions
            std::string getPieceName(void) const {return _name;}
            int getPieceID(void) const {return _pieceID;}
            int getTypeID(void) const {return _typeID;}
            float getPiecePrice(void) const {return _price;}
            int getPieceCount(void) const {return _count;}

            //Setter functions
            void setPieceName(std::string pieceName) {_name = pieceName;}
            void setPieceID(int pieceID) {_pieceID = pieceID;}
            void setTypeID(int typeID) {_typeID = typeID;}
            void setPiecePrice(float piecePrice) {_price = piecePrice;}
            void setPieceCount(int pieceCount) {_count = pieceCount;}

            //Helper functions
            int updatePieceCount(void);
            piece(const piece &other) : _name(other._name), _pieceID(other._pieceID), _typeID(other._typeID), _price(other._price), _count(other._count) {};

        protected:
            std::string _name;
            int _pieceID;
            int _typeID;
            float _price;
            int _count; //So if a 2pc suit, this will be two, individual piece value
    };

    class pieceOrder : public piece{
        public:
            pieceOrder();
            pieceOrder(piece parent, int itemCount) : piece(parent), _itemCount(itemCount) {calculateCost();}
            pieceOrder(piece parent, float price, int itemCount);
            //pieceOrder(std::string pieceName, int pieceID, float piecePrice, int pieceCount, int itemCount, float cost); //Used to load from file at start up
            pieceOrder(std::string pieceName, int pieceID, int typeID, float piecePrice, int pieceCount, int itemCount, float cost); //Used to load from file at start up

            //Getter functions
            //int getPieceOrderNumber(void) const {return _number;}
            int getPieceOrderItemCount(void) const {return _itemCount;}
            float getPieceOrderCost(void) const {return _cost;}

            //Setter functions
            //void setPieceOrderNumber(int number) {_number = number;}
            void setPieceOrderItemCount(int count) {_itemCount = count;}
            void setPieceOrderCost(float cost) {_cost = cost;}

            //Helper functions
            float calculateCost(void);

            //Overloaded Operators
            //bool operator==(const pieceOrder& other) const;
            bool operator==(const piece&other) const;

        private:
            int _itemCount; //# of this type of piece
            float _cost; //Total cost
    };

    //Type of pieces combined as a vector
    class pieceType
    {
        public:
            pieceType();

            pieceType(std::string pieceTypeName) : _name(pieceTypeName) {}

            //Getter functions
            std::string getPieceTypeName() const {return _name;}
            int getTypeID() const {return _typeID;}

            //Setter functions
            void setPieceTypeName(std::string pieceTypeName) {_name = pieceTypeName;}
            void getTypeID(int typeID) {_typeID = typeID;}

        protected:
            std::string _name; //Should be given at the time of creation of the object
            int _typeID;
    };

    //To be used in the backend to display and select pieces
    class pieceTypeList : public pieceType{
    public:
        struct position{
            int first;
            int last;
        };

        pieceTypeList(std::string pieceTypeName, int typeID, std::vector<piece> pieceList);
        pieceTypeList(std::string pieceTypeName, std::vector<piece> pieceList, position positionInList);

        //Getter functions
        std::vector<piece> getPieceList() const {return _pieceList;}

        //Setter functions
        void setPositionInList(int first, int last) {_positionInList.first = first; _positionInList.last = last;}
        void setPieceList(std::vector<piece> pieceList) {_pieceList = pieceList;}

        //Helper functions
        int updatePositionInList(int first);

    private:
        position _positionInList;
        std::vector<piece> _pieceList;


    };

    //To be used in Orders
    class pieceTypeOrder : public pieceType{
        public:
            pieceTypeOrder();
            pieceTypeOrder(pieceType& parent, float cost) : pieceType(parent), _cost(cost){}
            pieceTypeOrder(pieceTypeList& fromList);


            pieceTypeOrder(std::string typeName, int typeID, pieces::piece piece, int pieceCount); //When creating a new type list given a type name, typeID, piece, and count
            pieceTypeOrder(std::string pieceTypeName, std::vector<pieceOrder> pieceList);
            pieceTypeOrder(std::string pieceTypeName, std::vector<pieceOrder> pieceList, float cost);
            pieceTypeOrder(std::string typeName, int typeID, float cost, std::vector<pieceOrder> pieceList, int pieceTotal);

            //Getter functions
            float getTypeCost(void) const {return _cost;}
            std::vector<pieceOrder> getPieceList(void) const {return _pieceList;}
            int getPieceTotal(void) const {return _pieceTotal;}
            int getPieceListSize(void) const {return _pieceList.size();}


            //Setter functions
            void setTypeCost(float );
            void setPieceList(std::vector<pieceOrder> pieceList) {_pieceList = pieceList;}

            //Helper functions
            float calculateTypeCost(void);
            int calculatePieceTotal(void);

            int addPiece(pieces::piece piece, int pieceCount);

        private:
            float _cost;
            std::vector<pieceOrder> _pieceList;
            int _pieceTotal;

    };


}
#endif // PIECES_H
