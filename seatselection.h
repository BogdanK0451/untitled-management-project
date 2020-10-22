#ifndef SEATSELECTION_H
#define SEATSELECTION_H

#include "film.h"
#include "hall.h"
#include "seat.h"
#include "price.h"
#include <QChar>
#include <QList>
#include <QDialog>


namespace Ui {
class SeatSelection;
}

class SeatSelection : public QDialog
{
    Q_OBJECT

public:
    explicit SeatSelection(int mode, const Hall &hall_, const QString &string, const Film &film_, QWidget *parent = 0);
    ~SeatSelection();

private slots:
    void on_pushButton_Back_clicked();
    void selectSeat();
    void seatTaken();
    void on_pushButton_Buy_clicked();
    void textChanged();
    void on_pushButton_Reserve_clicked();
    void on_checkBox_Email_stateChanged(int arg1);

private:
    void loadImage(ButtonQLabel &label, const QChar &chr);
    void showSeats();
    void addTicketsAndPrice();
    void uiSetup();
    void sendEmail(const QString &name, const QString &email, int id);
    Film film;
    QString fileName;
    Ui::SeatSelection *ui;
    QString seats;
    Hall hall;
    QGridLayout *gridLayout=NULL;
    QList<Seat*> allSeats;
    Price price;
    QDate projectionDate;
    QTime projectionTime;
    int countSelectedSeats;
    int mode;
    bool allowReservations;
};

#endif // SEATSELECTION_H
