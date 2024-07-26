#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "handle.h"
#include "laundry.h"
#include "customerselect.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnDropOff_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_btnLaundry_clicked()
{
    Laundry laundWindow; //creates object of the class
    laundWindow.setModal(true); //modal appraoch
    laundWindow.exec(); //executing object class, opens the window
}


void MainWindow::on_btnCustomer_clicked()
{
    CustomerSelect custWindow;
    custWindow.setModal(true);
    custWindow.exec();
}


void MainWindow::on_btnReturn_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

