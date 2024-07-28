#ifndef DROPOFFPAGE_H
#define DROPOFFPAGE_H
//Created using the QTWidgets form when creating a new source/header file

#include <QWidget>


#include "customer.h"
#include "order.h"
#include "qlineedit.h"
#include "qpushbutton.h"

namespace Ui {
class DropOffPage;
}

class DropOffPage : public QWidget
{
    Q_OBJECT

public:
    explicit DropOffPage(QWidget *parent = nullptr);
    ~DropOffPage();
    void setDataStructures(std::unordered_map<int, std::vector<orderInfo::order>> *orders, std::vector<cust::customer> *customers);


private slots:
    void on_btnCustomer_clicked();

private:
    Ui::DropOffPage *ui;

    QLineEdit *firstNameEdit;
    QLineEdit *lastNameEdit;
    QLineEdit *phoneEdit;
    QLineEdit *dropOffDateEdit;
    QLineEdit *pickUpDateEdit;
    QLineEdit *customerIdEdit;
    QLineEdit *orderIdEdit;
    QPushButton *clearButton;

    std::unordered_map<int, std::vector<orderInfo::order>> *orders;
    std::vector<cust::customer> *customers;
};

#endif // DROPOFFPAGE_H
