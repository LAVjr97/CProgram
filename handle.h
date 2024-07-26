#ifndef HANDLE_H
#define HANDLE_H

#include "main.h"
#include "customer.h"
#include "order.h"

using namespace std;

namespace menu{
    class options{
        public:
            //Static functions, functions to be used through out run time.
            static int handleDropOff(std::unordered_map<int, orderInfo::order> &orders, std::vector<cust::customer> &customers);
            static int handlePickUp();
            static int handleLookUp();
            static int handleHistory();
            static std::array<std::tuple<int, double>, 8> handleArticles();

            static std::string getDate();

        private:

    };
}

#endif // HANDLE_H
