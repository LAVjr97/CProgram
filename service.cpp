#include "service.h"

using namespace services;

service::service(){
    _name = "";
}

serviceList::serviceList(){
    _name = "";
}

serviceList::serviceList(std::string serviceName, std::vector<pieces::pieceTypeList> typeList) : _typeList(typeList){
    _name = serviceName;
}

serviceOrder::serviceOrder(){
    _typeList.resize(1);
    _cost = 0;
}

serviceOrder::serviceOrder(std::string serviceName, float serviceCost, std::vector<pieces::pieceTypeOrder> typeList) : _cost(serviceCost), _typeList(typeList){
    _name = serviceName;
}

float serviceOrder::calculateTotalPrice(void){
    _cost = 0;

    for(size_t i = 0; i < _typeList.size(); i++){
        //_cost = _typeList[i].getTypeCost() + _cost;
        _cost = _typeList[i].calculateTypeCost() + _cost;
    }

    return _cost;
}

int serviceOrder::addPiece(std::string typeName, int typeID, pieces::piece piece, int pieceCount){
    bool pieceDupe = false, typeFound = false, typeInserted = false;

    for(size_t i = 0; i < _typeList.size(); i++){
        if(_typeList[i].getTypeID() > typeID){
            typeInserted = true;
            _typeList.emplace(_typeList.begin() + i, typeName, typeID, piece, pieceCount);
            break;
        }

        if(_typeList[i].getTypeID() == typeID){
            typeFound = true;
            pieceDupe = _typeList[i].addPiece(piece, pieceCount);
            break;
        }
    }

    if(!typeFound && !typeInserted){
        _typeList.emplace_back(typeName, typeID, piece, pieceCount);
    }

    calculateTotalPrice();
    calculatePieceTotal();

    return pieceDupe;
}

int serviceOrder::calculatePieceTotal(void){
    int pieceTotal = 0;

    for(size_t i = 0; i < _typeList.size(); i++){
        pieceTotal = _typeList[i].calculatePieceTotal() + pieceTotal;
        //pieceTotal = _typeList[i].getPieceTotal() + pieceTotal;
    }

    return pieceTotal;
}
