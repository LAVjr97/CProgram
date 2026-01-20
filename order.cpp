 #include "order.h"

using namespace orderInfo;

//Constructor
order::order(int customerID, int orderID) : dropOff(), pickUp(3), _laundry(),  _dryClean(), _alterations() {
    _customerID = customerID;
    _orderID = orderID;
    _total = 0;
    _rackNumber = -1;
    _pickedUp = false;
    _pieceTotal = 0;
    _discountApplied = false;
    _discount = 0.00;
    _discountedCost = 0.00;
    _deposit = 0.00;
    _voidOrder = false;
}

//Constructor used when loading in orders from orderFile into the program memory
order::order(const Params& params) :
    _customerID(params.customerID),
    _orderID(params.orderID),
    _laundry(params.laundry),
    _dryClean(params.dryClean),
    _alterations(params.alterations),
    _total(params.total),
    _rackNumber(params.rack),
    _pickedUp(params.pickedUp),
    _paid(params.paid),
    _pieceTotal(params.pieceTotal),
    _discountApplied(params.discountApplied),
    _discount(params.discount),
    _discountedCost(params.discountedCost),
    _deposit(params.deposit),
    _voidOrder(params.voidOrder)
{
}



/*Set Functions*/
int order::setCustomerID(int id){
    this->_customerID = id;
    return 0;
}

float order::calculateSubTotal(void){
    _total = 0;

    _total += _laundry.calculateTotalPrice();
    _total += _dryClean.calculateTotalPrice();
    _total += _alterations.calculateTotalPrice();

    return _total;
}

int order::calculatePieceTotal(){
    _pieceTotal = 0;

    _pieceTotal += _laundry.calculatePieceTotal();
    _pieceTotal += _dryClean.calculatePieceTotal();
    _pieceTotal += _alterations.calculatePieceTotal();

    return _pieceTotal;
}

float order::applyDiscount(){
    if(_discountApplied) // = true;
        _discountedCost = _total - (_total * (_discount/100.0));
    else
        _discountedCost = _total;
    return _discountedCost;
}

void order::voidOrder(){
    _voidOrder = true;
    _laundry.voidOrder();
    _dryClean.voidOrder();
    _alterations.voidOrder();

    _customerID = -1;
    _total = -1;
    _rackNumber = -1;
    _paid = false;
    _pieceTotal = -1;

    _discountApplied = false;
    _discount = -1;
    _discountedCost = -1;
    _deposit = -1;
}
