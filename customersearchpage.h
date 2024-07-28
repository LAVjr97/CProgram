#ifndef CUSTOMERSEARCHPAGE_H
#define CUSTOMERSEARCHPAGE_H

#include <QWidget>

namespace Ui {
class CustomerSearchPage;
}

class CustomerSearchPage : public QWidget
{
    Q_OBJECT

public:
    explicit CustomerSearchPage(QWidget *parent = nullptr);
    ~CustomerSearchPage();

private:
    Ui::CustomerSearchPage *ui;
};

#endif // CUSTOMERSEARCHPAGE_H
