#ifndef LAUNDRY_H
#define LAUNDRY_H

#include <QDialog>

namespace Ui {
class Laundry;
}

class Laundry : public QDialog
{
    Q_OBJECT

public:
    explicit Laundry(QWidget *parent = nullptr);
    ~Laundry();

private:
    Ui::Laundry *ui;
};

#endif // LAUNDRY_H
