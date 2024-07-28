#include "customersearchpage.h"
#include "ui_customersearchpage.h"

CustomerSearchPage::CustomerSearchPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CustomerSearchPage)
{
    ui->setupUi(this);
}

CustomerSearchPage::~CustomerSearchPage()
{
    delete ui;
}
