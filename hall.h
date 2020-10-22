#ifndef HALL_H
#define HALL_H

#include <QVector>
#include <QString>
#include <QTextStream>

class Hall
{
public:
    Hall(int row,int col,const QString &hallName_);
    Hall();
    ~Hall();

    QString generateSeats() const;

    int getCol() const;
    void setCol(int value);

    int getRow() const;
    void setRow(int value);

    QString getHallName() const;
    void setHallName(const QString &value);

private:

    int row;
    int col;
    int **seats;
    QString hallName;
};

QTextStream &operator<<(QTextStream &strm, const Hall &sala);
QTextStream &operator>>(QTextStream &strm, Hall &sala);

#endif // HALL_H
