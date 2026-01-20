#include "pieces.h"
#include <regex>

using namespace pieces;


//Piece Class
piece::piece() {}

int piece::updatePieceCount(void){
    std::regex pattern("(?<!\\d)\\d{1,2}(?!\\d)");
    std::smatch match;

    std::string::const_iterator searchStart(_name.cbegin());
    while (std::regex_search(searchStart, _name.cend(), match, pattern)) {
        _count = std::stoi(match.str());
        searchStart = match.suffix().first;
    }

    return _count;
}


//Piece Order Class
pieceOrder::pieceOrder(piece parent, float price, int itemCount) : piece(parent), _itemCount(itemCount){
    _price = price;
    calculateCost();
}


pieceOrder::pieceOrder(std::string pieceName, int pieceID, int typeID, float piecePrice, int pieceCount, int itemCount, float cost) : _itemCount(itemCount), _cost(cost){
    _name = pieceName;
    _pieceID = pieceID;
    _typeID = typeID;
    _price = piecePrice;
    _count = pieceCount;
}


float pieceOrder::calculateCost(void){
    _cost = _itemCount * _price;

    return _cost;
}

bool pieceOrder::operator==(const piece& other) const{
    return other.getPieceName() == this->_name && other.getPiecePrice() == this->_price && other.getPieceID() == this->_pieceID;
}

pieceType::pieceType(){
    _name = "";
    _typeID = -1;
}

pieceTypeList::pieceTypeList(std::string pieceTypeName, int typeID, std::vector<piece> pieceList) : _pieceList(pieceList){
    _name = pieceTypeName;
    _typeID = typeID;
}

pieceTypeList::pieceTypeList(std::string pieceTypeName, std::vector<piece> pieceList, position positionInList) : _positionInList(positionInList){
    _name = pieceTypeName;
    _pieceList = pieceList;
}


int pieceTypeList::updatePositionInList(int first){
    _positionInList.first = first;

    _positionInList.last = first + _pieceList.size();

    return _positionInList.last;
}

pieceTypeOrder::pieceTypeOrder(){
    _pieceList.resize(1);
    _cost = 0;
}

pieceTypeOrder::pieceTypeOrder(std::string typeName, int typeID, pieces::piece piece, int pieceCount){
    _name = typeName;
    _typeID = typeID;
    addPiece(piece, pieceCount);
}

pieceTypeOrder::pieceTypeOrder(std::string pieceTypeName, std::vector<pieceOrder> pieceList){
    _name = pieceTypeName;
    _pieceList = pieceList;
    _cost = 0;
}

pieceTypeOrder::pieceTypeOrder(std::string pieceTypeName, std::vector<pieceOrder> pieceList, float cost) : _cost(cost){
    _name = pieceTypeName;
    _pieceList = pieceList;
}

pieceTypeOrder::pieceTypeOrder(std::string typeName, int typeID, float cost, std::vector<pieceOrder> pieceList, int pieceTotal) : _cost(cost), _pieceList(pieceList), _pieceTotal(pieceTotal){
    _name = typeName;
    _typeID = typeID;
}

float pieceTypeOrder::calculateTypeCost(void){
    _cost = 0;

    for(size_t i = 0; i < _pieceList.size(); i++){
        _cost = _pieceList[i].getPieceOrderCost() + _cost;
    }

    return _cost;
}

int pieceTypeOrder::calculatePieceTotal(void){
    _pieceTotal = 0;

    for(size_t i = 0; i < _pieceList.size(); i++){
        _pieceTotal = _pieceList[i].getPieceCount() * _pieceList[i].getPieceOrderItemCount();
    }

    return _pieceTotal;
}

int pieceTypeOrder::addPiece(piece piece, int pieceCount){
bool dupe = false, pieceInserted = false;

    for(size_t i = 0; i < _pieceList.size(); i++){
        if(_pieceList[i].getPieceID() > piece.getPieceID()){
            pieceInserted = true;
            _pieceList.emplace(_pieceList.begin() + i, piece, pieceCount);
            break;
        }

        if(_pieceList[i] == piece){ //Piece exists, just update pieceCount
            dupe = true;
            _pieceList[i].setPieceOrderItemCount(pieceCount);
            break;
        }
    }

    if(!dupe && !pieceInserted){
            _pieceList.emplace_back(piece, pieceCount);
    }

    return dupe;
}

