//Notes: To clear screen on Unix based os', use "clear", windows, "cls"
#ifndef HANDLE_H
#define HANDLE_H

#include "main.h"
#include "order.h"
#include "customer.h"
#include "search.h"
#include "file.h"

namespace menu{
class options{
public:
    //Static functions, functions to be used through out run time.
    static int handleDropOff(std::vector<orderInfo::order> &orders, std::vector<cust::customer> &customers, fi::File &manager);
    static int handlePickUp(std::vector<orderInfo::order> &orders, std::vector<cust::customer> &customers, fi::File &manager);
    static int handleLookUp(std::vector<orderInfo::order> &orders, std::vector<cust::customer> &customers, fi::File &manager);
    static int handleHistory(std::vector<orderInfo::order> &orders, std::vector<cust::customer> &customers, fi::File &manager);
    static int handleRack(std::vector<orderInfo::order> &orders, std::vector<cust::customer> &customers, fi::File &manager);

    static std::vector<std::vector<std::pair<int, double>>> handleArticles();

private:

};


}

#endif // !MENU_HEADER_H
