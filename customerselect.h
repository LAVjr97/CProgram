#ifndef CUSTOMERSELECT_H
#define CUSTOMERSELECT_H

#include <QDialog>

namespace Ui {
class CustomerSelect;
}

class CustomerSelect : public QDialog
{
    Q_OBJECT

public:
    explicit CustomerSelect(QWidget *parent = nullptr);
    ~CustomerSelect();

private:
    Ui::CustomerSelect *ui;
};

#endif // CUSTOMERSELECT_H
