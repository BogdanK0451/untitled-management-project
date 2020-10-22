#include "price.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

Price::Price()
{

}

Price::~Price()
{

}

float Price::calcPrice(const QDate &date)
{
    if(date.dayOfWeek()==7)
        return sundayPrice;
    else if (date.dayOfWeek()==6)
       return saturdayPrice;
    else
       return standardPrice;
}

void Price::loadPrices()
{
    QString price;
    QString filename="Cene.txt";
    QFile file(filename);

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        stream >> price;
    }
    standardPrice= price.toFloat();
    saturdayPrice= standardPrice+standardPrice*25/100;
    sundayPrice= standardPrice+standardPrice*35/100;
}
void Price::savePrices(const QString &price)
{
    QString filename="Cene.txt";
    QFile file(filename);

    if (file.open(QIODevice::ReadWrite| QIODevice::Text))
    {
        QTextStream stream(&file);
        file.resize(0);
        stream << price;
    }
}

float Price::getStandardPrice() const
{
    return standardPrice;
}

void Price::setStandardPrice(float value)
{
    standardPrice = value;
}

float Price::getSaturdayPrice() const
{
    return saturdayPrice;
}

void Price::setSaturdayPrice(float value)
{
    saturdayPrice = value;
}

float Price::getSundayPrice() const
{
    return sundayPrice;
}

void Price::setSundayPrice(float value)
{
    sundayPrice = value;
}
