#ifndef ADD_H
#define ADD_H

#include "hall.h"
#include <QDialog>
#include <QVector>
#include "price.h"

namespace Ui {
class AddHall;
}

class AddHall : public QDialog
{
    Q_OBJECT

public:
    explicit AddHall(QWidget *parent = 0);
    ~AddHall();
    void setupTableWidget();
    void fillTableWidget();
    void loadHalls();
    void setPriceLabels();


private slots:
    void on_pushButton_Back_clicked();
    void on_pushButton_Add_clicked();
    void textChanged();

    void on_pushButton_setPrice_clicked();

private:
    Ui::AddHall *ui;
    QVector<Hall> halls;
    Price price;
};

#endif // ADD_H
