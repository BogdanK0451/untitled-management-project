#ifndef RESERVATION_H
#define RESERVATION_H

#include "film.h"
#include <QString>
#include <QDate>
#include <QTextStream>

class Reservation
{
public:

    Reservation(const QString &buyerName_, const QString &filmName_, const QString &hall_,
                int id_, int col_, int row_, QDate date_, QTime time_, float price_);
    Reservation();
    ~Reservation();

    void saveReservation() const;
    void deleteReservation();

    QString getHall() const;
    void setHall(const QString &value);

    int getID() const;
    void setID(int value);

    int getRow() const;
    void setRow(int value);

    int getCol() const;
    void setCol(int value);

    int getPrice() const;
    void setPrice(int value);

    QDate getDate() const;
    void setDate(const QDate &value);

    QTime getProjectionStart() const;
    void setProjectionStart(const QTime &value);

    QString getBuyerName() const;
    void setBuyerName(const QString &value);

    QString getFilmName() const;
    void setFilmName(const QString &value);

private:
    QString buyerName;
    QString filmName;
    QString hall;
    int ID;
    int row;
    int col;
    float price;
    QDate date;
    QTime projectionStart;
};

QTextStream &operator>>(QTextStream &strm, Reservation &reservation);

#endif // RESERVATION_H
