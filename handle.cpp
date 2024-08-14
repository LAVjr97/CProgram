#include "../include/handle.h"



//To clear the screen, windows uses "cls", mac/linux uses "clear"
#define screen "cls"

using namespace menu;

int options::handleDropOff(std::vector<orderInfo::order> &orders, std::vector<cust::customer> &customers, fi::File &manager) {
    system(screen);

    //Initialize variables
    std::string date, time, firstName, lastName, firstTime, number, choice;
    std::array<std::tuple<int, double>, 8> articles;
    double cost = 0.99;
    int customerID = 0, intChoice, orderID;
    search::Search search;
    std::vector<cust::customer> customer;

    //Customer Info
    cout << "\nIs this a first-time cusomter? <Yes/No>\n";
    cin >> firstTime;

    //Handle First time customer
    if(firstTime == "Yes" || firstTime == "yes" || firstTime == "y" || firstTime == "Y"){
        cout << "\nCustomer First Name:\n";
        cin >> firstName;
        cout << "\nCusotmer Last Name:\n";
        cin >> lastName;
        cout << "\nCustomer Phone Number?\n";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin ,number);

        customerID = customers.size();
        cout << customerID;

        //Create customer object, and save to database.
        customers.emplace_back(customerID, firstName, lastName, number);
        manager.saveCustomers(customers[customerID]);
    }

    //Already a pre-existing customer
    else {
        cout << "\nCusotmer Last Name:\n";
        cin >> lastName;
        customer = search.searchCustAlgo(lastName, customers);
        for (int i = 0; i < customer.size(); i++) {
            cout << std::to_string(i + 1) << ") " << customer[i].getName() << std::endl;
        }

        std::cout << std::endl << "Which Customer is the correct one?" << std::endl;
        cin >> choice;
        intChoice = std::stoi(choice) - 1;

        customerID = customer[intChoice].getCustomerID();
    }

    //Handle Orders
    articles = handleArticles();

    //Create Order Object
    orderID = orders.size();
    orders.emplace_back(orderID, customerID, articles);

    //Update customer Object
    customers[customerID].setLatestOrder(orderID);
    customers[customerID].updateVisits(customers[customerID].getVisit() + 1);

    //Save Order and update customers in the DataBase
    manager.saveOrders(orders[orderID]);
    manager.updateCustomer(customerID);

    /*
    std::thread threadOrder(&fi::File::saveOrders, &manager);
    std::thread threadCust(&fi::File::updateCustomer, &manager);



    threadOrder.join();
    threadCust.join();
    */

    return 0;
}

int options::handlePickUp(std::vector<orderInfo::order> &orders, std::vector<cust::customer> &customers, fi::File &manager) {
    std::string entry;
    int input;
    search::Search search;
    std::vector<cust::customer> customer;
    std::vector<orderInfo::order> order;
    int i;

    system(screen);

    while (true) {
        std::cout << "\nSearch by:\n1) Customer Name or Phone Number\n2) Order Number\n";
        cin >> input;

        if (input == 1) {
            system(screen);
            std::cout << "Customer Name or Phone Number?\n";
            std::cin >> entry;

            customer = search.searchCustAlgo(entry, customers);
            break;
        }
        else if (input == 2) {
            system(screen);
            std::cout << "Order Number?\n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline(std::cin, entry);

            order = search.searchOrderAlgo(entry, orders);
            break;
        }
        else
            std::cout << "Incorrect option, please only put 1 or 2";

    }

    //customer = search.searchCustAlgo(entry, customers);
    if (input == 1) {
        for (i = 0; i < customer.size(); i++) {
            std::cout << i + 1 << ") " << customer[i].getName() << "\n";
        }
        std::cout << "\nWhich customer's information would you like to see?\n";
        cin >> input;
        input--;

        int customerID = customer[input].getCustomerID();

        system(screen);
        std::cout << std::endl << customers[customerID].getCustomerID() << ", " << customers[customerID].getName() << ", " << customers[customerID].getPhone() << ", " << customers[customerID].getTotal() << ", " << customers[customerID].getVisit() << std::endl;

    }

    if (input == 2) {
        for (i = 0; i < order.size(); i++) {
            //    std::cout << i + 1 << ") " << order[i].get
        }
    }
    /*for (i = 0; i < customer.size(); i++) {
        //std::cout << "\n" << order[i].getCustomerID() << "\n";
        std::cout << std::endl << customer[i].getName() << std::endl;
        //std::cout << "\n" << order[i].getName() << "\n";

        //std::cout << std::endl << order[i].pickUp->getDate_Time() << std::endl;
    }
    */
    return 0;
}

int options::handleLookUp(std::vector<orderInfo::order> &orders, std::vector<cust::customer> &customers, fi::File &manager) {
    system(screen);
    cout << "\nhandleLookUp";
    return 0;
}

int options::handleHistory(std::vector<orderInfo::order> &orders, std::vector<cust::customer> &customers, fi::File &manager) {
    system(screen);
    cout << "\nhandleDropOff";
    return 0;
}

int options::handleRack(std::vector<orderInfo::order> &orders, std::vector<cust::customer> &customers, fi::File &manager){
    int id, rack;
    std::vector<orderInfo::order> order;
    system(screen);

    std::cout << "\nOrder Number:\n";
    std::cin >> id;

    std::cout << "\nRack Number:\n";
    std::cin >> rack;

    orders[id].setRack(rack);

    return 0;
}

//Creates a menu from where the user selects a piece of clothing and then inputs the number of pieces of that particular clothing
std::array<std::tuple<int, double>, 8> options::handleArticles() {
    //[0]: Shirts, [1]: Pants, [2]:Sweaters, [3]:Coats, [4]:Blouses, [5]:2pc Suit, [6]:Jacket, [7]:Vest
    std::array<std::tuple<int, double>, 8> articles;
    int article, n;

    while(true){
        //system(screen);
        cout << "\nEnter article number (or '0' to go save and return):\n1) Shirts\n2) Pants\n3) Sweaters\n4) Coats\n5) Blouses\n6) 2pc Suit\n7) Jackets\n7) Vest\n";
        cin >> article;

        switch(article){
        case 1:
            cout << "\nNumber of Shirt(s)?\n";
            cin >> n;
            articles[0] = std::make_tuple(n, 4.99);
            break;

        case 2:
            cout << "\nNumber of Pant(s)?\n";
            cin >> n;
            articles[1] = std::make_tuple(n, 4.99);
            break;

        case 3:
            cout << "\nNumber of Sweater(s)?\n";
            cin >> n;
            articles[2] = std::make_tuple(n, 5.99);
            break;

        case 4:
            cout << "\nNumber of Coat(s)?\n";
            cin >> n;
            articles[3] = std::make_tuple(n, 6.99);
            break;

        case 5:
            cout << "\nNumber of Blouse(s)?\n";
            cin >> n;
            articles[3] = std::make_tuple(n, 4.50);
            break;

        case 6:
            cout << "\nNumber of 2pc Suit(s)?\n";
            cin >> n;
            articles[4] = std::make_tuple(n, 12.99);
            break;

        case 7:
            cout << "\nNumber of Jacket(s)?\n";
            cin >> n;
            articles[4] = std::make_tuple(n, 6.99);
            break;

        case 8:
            cout << "\nNumber of Vest(s)?\n";
            cin >> n;
            articles[4] = std::make_tuple(n, 3.99);
            break;

        case 0:
            return articles;
        default:
            continue;
        }
    }
    return articles;
}

