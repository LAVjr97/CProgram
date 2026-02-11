#include "mainwindow.h"
#include "ui_mainwindow.h"

//
//***Page Movement***
//
void MainWindow::showMainPage(){
    recentStackedWidgetIndex = ui->stackedWidget->currentIndex();
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::showDropOffPage(){
    recentStackedWidgetIndex = ui->stackedWidget->currentIndex();
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::showSearchPage(){
    recentStackedWidgetIndex = ui->stackedWidget->currentIndex();
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::showCustomerSearchResultsPage(){
    recentStackedWidgetIndex = ui->stackedWidget->currentIndex();
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::showNewCustomerPage(){
    recentStackedWidgetIndex = ui->stackedWidget->currentIndex();
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::showOrderLaundryPage(){
    recentStackedWidgetIndex = ui->stackedWidget->currentIndex();
    ui->stackedWidget->setCurrentIndex(5);
}

void MainWindow::showOrderDryCleanPage(){
    recentStackedWidgetIndex = ui->stackedWidget->currentIndex();
    ui->stackedWidget->setCurrentIndex(6);
}

void MainWindow::showOrderAlterationsPage(){
    recentStackedWidgetIndex = ui->stackedWidget->currentIndex();
    ui->stackedWidget->setCurrentIndex(7);
}

void MainWindow::showPickUpPage(){
    recentStackedWidgetIndex = ui->stackedWidget->currentIndex();
    ui->stackedWidget->setCurrentIndex(8);
}

void MainWindow::showCustomerSearchPagePU(){
    recentStackedWidgetIndex = ui->stackedWidget->currentIndex();
    ui->stackedWidget->setCurrentIndex(9);
}

void MainWindow::showOrderSearchPagePU(){
    recentStackedWidgetIndex = ui->stackedWidget->currentIndex();
    ui->stackedWidget->setCurrentIndex(10);
}

void MainWindow::showCustomerSearchResultsPU(){
    recentStackedWidgetIndex = ui->stackedWidget->currentIndex();
    ui->stackedWidget->setCurrentIndex(11);
}

void MainWindow::showOrderSearchResultsPU(){
    recentStackedWidgetIndex = ui->stackedWidget->currentIndex();
    ui->stackedWidget->setCurrentIndex(12);
}

void MainWindow::showEditOrderPage(){
    recentStackedWidgetIndex = ui->stackedWidget->currentIndex();
    ui->stackedWidget->setCurrentIndex(13);
}

void MainWindow::showOrderSearchPageEO(){
    recentStackedWidgetIndex = ui->stackedWidget->currentIndex();
    ui->stackedWidget->setCurrentIndex(14);
}

void MainWindow::showCustomerSearchPageEO(){
    recentStackedWidgetIndex = ui->stackedWidget->currentIndex();
    ui->stackedWidget->setCurrentIndex(15);
}

void MainWindow::showCustomerSearchResultsEO(){
    recentStackedWidgetIndex = ui->stackedWidget->currentIndex();
    ui->stackedWidget->setCurrentIndex(16);
}

void MainWindow::showOrderSearchResultsEO(){
    recentStackedWidgetIndex = ui->stackedWidget->currentIndex();
    ui->stackedWidget->setCurrentIndex(17);
}

void MainWindow::showAdminPage(){
    recentStackedWidgetIndex = ui->stackedWidget->currentIndex();
    ui->stackedWidget->setCurrentIndex(18);
}

void MainWindow::showItemsAndPricePage(){
    recentStackedWidgetIndex = ui->stackedWidget->currentIndex();
    ui->stackedWidget->setCurrentIndex(19);
}

void MainWindow::showCustomerEditPage(){
    recentStackedWidgetIndex = ui->stackedWidget->currentIndex();
    ui->stackedWidget->setCurrentIndex(20);
}


void MainWindow::showOrderLaundryPageEO(){
    recentStackedWidgetIndex = ui->stackedWidget->currentIndex();
    ui->stackedWidget->setCurrentIndex(23);
}

void MainWindow::showOrderDryCleanPageEO(){
    recentStackedWidgetIndex = ui->stackedWidget->currentIndex();
    ui->stackedWidget->setCurrentIndex(22);
}

void MainWindow::showOrderAlterationsPageEO(){
    recentStackedWidgetIndex = ui->stackedWidget->currentIndex();
    ui->stackedWidget->setCurrentIndex(21);
}
