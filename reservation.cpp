#include "reservation.h"
#include <QFile>
#include <QTextStream>

Reservation::Reservation(const QString &buyerName_, const QString &filmName_, const QString &hall_, int id_,
                         int col_, int row_, QDate date_, QTime time_,float price_)
{
    buyerName=buyerName_;
    filmName=filmName_;
    hall=hall_;
    ID= id_;
    row=id_;
    col=col_;
    row=row_;
    price=price_;
    date=date_;
    projectionStart=time_;
}

Reservation::Reservation()
{

}
Reservation::~Reservation()
{

}

void Reservation::saveReservation() const
{
    QFile file("./Rezervacije.txt");

    if (file.open(QIODevice::ReadWrite | QIODevice::Append | QIODevice::Text))
    {
        QTextStream stream(&file);

        stream << ID << ";" << buyerName << ";" << filmName << ";" << date.toString("dd.MM.yyyy") << ";" <<
                  projectionStart.toString("hh:mm") << ";" << hall << ";" << col << ";" << row << ";" << price <<  endl;
    }
    file.close();
}
//oslobadjanje zauzetih sedista
void Reservation::deleteReservation()
{
    QFile file("./Projekcije/"+filmName+"/"+filmName+"_"+hall+"_"+date.toString("dd.MM.yyyy")+"_"+projectionStart.toString("hh:mm"));

    if (file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        QString string;
        QString fileText;
        QTextStream stream(&file);
        int i=1;
        while(!stream.QTextStream::atEnd())
        {
            string=stream.readLine();
            if(i==row)
            {
                string.replace(col-1,1,"0");
            }
            i++;
            fileText.append(string+'\n');
        }
        file.resize(0);
        stream << fileText;
    }
    file.close();
}

QString Reservation::getHall() const
{
    return hall;
}

void Reservation::setHall(const QString &value)
{
    hall = value;
}

int Reservation::getID() const
{
    return ID;
}

void Reservation::setID(int value)
{
    ID = value;
}

int Reservation::getRow() const
{
    return row;
}

void Reservation::setRow(int value)
{
    row = value;
}

QDate Reservation::getDate() const
{
    return date;
}

void Reservation::setDate(const QDate &value)
{
    date = value;
}

QTime Reservation::getProjectionStart() const
{
    return projectionStart;
}

void Reservation::setProjectionStart(const QTime &value)
{
    projectionStart = value;
}

QString Reservation::getBuyerName() const
{
    return buyerName;
}

void Reservation::setBuyerName(const QString &value)
{
    buyerName = value;
}

QString Reservation::getFilmName() const
{
    return filmName;
}

void Reservation::setFilmName(const QString &value)
{
    filmName = value;
}

int Reservation::getCol() const
{
    return col;
}

void Reservation::setCol(int value)
{
    col = value;
}

int Reservation::getPrice() const
{
    return price;
}

void Reservation::setPrice(int value)
{
    price = value;
}

QTextStream &operator>>(QTextStream &strm, Reservation &reservation)
{
    QString line;
    line = strm.readLine();
    QStringList strings = line.split(';'); // polja ne smeju imati karakter ;
    reservation.setID(strings.at(0).QString::toInt());
    reservation.setBuyerName(strings.at(1));
    reservation.setFilmName(strings.at(2));
    reservation.setDate(QDate::fromString(strings.at(3),"dd.MM.yyyy"));
    reservation.setProjectionStart(QTime::fromString(strings.at(4),"hh:mm"));
    reservation.setHall(strings.at(5));
    reservation.setCol(strings.at(6).QString::toInt());
    reservation.setRow(strings.at(7).QString::toInt());
    reservation.setPrice(strings.at(8).QString::toFloat());

    return strm;
}
