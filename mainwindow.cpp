#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "handle.h"
#include "laundry.h"
#include "customerselect.h"
#include "customersearchpage.h"

#include <QPushButton>
#include <QVBoxLayout>

//Constructor
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{   
    ui->setupUi(this);
    stackedWidget = new QStackedWidget(this);
    this->dropOffPage = new DropOffPage(this);
    this->dropOffPage->setDataStructures(&orders, &customers);

    stackedWidget->addWidget(this->dropOffPage);
    QPushButton *btnDropOff = new QPushButton("Drop Off", this);

    //connect buttons to slots
    connect(btnDropOff, &QPushButton::clicked, this, &MainWindow::showDropOffPage);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Main Home Page
void MainWindow::on_btnDropOff_clicked()
{
    MainWindow::showDropOffPage();
}


void MainWindow::on_btnLaundry_clicked()
{
    Laundry laundWindow; //creates object of the class
    laundWindow.setModal(true); //modal appraoch
    laundWindow.exec(); //executing object class, opens the window
}

//Drop Off Page
void MainWindow::on_btnCustomer_clicked()
{
    MainWindow::showSearchPage();

    //CustomerSelect custWindow;
    //custWindow.setModal(true);
    //custWindow.exec();
}


void MainWindow::on_btnReturn_clicked()
{
    MainWindow::showMainPage();
}

//Page Movement
void MainWindow::showMainPage(){
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::showDropOffPage(){
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::showSearchPage(){
    ui->stackedWidget->setCurrentIndex(2);
}

//Search Page
void MainWindow::on_btnReturn_2_clicked()
{
    MainWindow::showDropOffPage();
}

void MainWindow::on_btnNewCustomerPg_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

//New Customer Page
void MainWindow::on_btnReturn_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

//Get Functions
std::unordered_map<int, std::vector<orderInfo::order>>& MainWindow::getOrders() { //the variable that holds the address should be a pointer
    return this->orders;
}

std::vector<cust::customer>& MainWindow::getCustomers() {
    return this->customers;
}





