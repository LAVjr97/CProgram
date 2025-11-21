#ifndef SERVICE_H
#define SERVICE_H

#include "pieces.h"

namespace services
{
    
    // namespace services

    class service
    {
        public:
            service();
            service(std::string serviceName) : _name(serviceName) {}
            //Getter functions
            std::string getServiceName(void) const {return _name;}

            //Setter functions
            void setServiceName(std::string serviceName) {_name = serviceName;}

        protected:
            std::string _name;

    };

    class serviceList : public service{
        public:
            //Getter functions
            std::vector<pieces::pieceType> getServiceTypeList(void) const {return _typeList;}
            int getTypeListSize() const {return _typeList.size();}

            //Setter functions
            void setServiceTypeList(std::vector<pieces::pieceType> typeList) {_typeList = typeList;}

        private:
            std::vector<pieces::pieceType> _typeList;
    };

    class serviceOrder : public service
    {
        public:
            serviceOrder();
            serviceOrder(float serviceCost) : _cost(serviceCost){}

            //Getter functions
            float getServiceTotal(void) const {return _cost;}
            std::vector<pieces::pieceTypeOrder> getServiceTypeList(void) const {return _typeList;}
            pieces::pieceTypeOrder getTypeList(std::string typeName);
            int getTypeListSize() const {return _typeList.size();}

            //Setter functions
            void setServiceTotal(float cost) {_cost = cost;}
            void setServiceTypeList(std::vector<pieces::pieceTypeOrder> typeList) {_typeList = typeList;}

            //Helper functions
            float calculateTotalPrice(void);
            int addPiece(std::string typeName, int typeID, pieces::piece piece, int pieceCount);
            void voidOrder() {_typeList = {}; _name.clear();}
            int calculatePieceTotal(void);

        private:
            float _cost;
            std::vector<pieces::pieceTypeOrder> _typeList;

    };
}
    
#endif // SERVICE_H
\
