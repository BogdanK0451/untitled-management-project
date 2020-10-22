#ifndef PRICE_H
#define PRICE_H
#include <QString>
#include <QDate>

class Price
{
public:
    Price();
    ~Price();

    float calcPrice(const QDate &date);

    void savePrices(const QString &price);
    void loadPrices();

    float getStandardPrice() const;
    void setStandardPrice(float value);

    float getSaturdayPrice() const;
    void setSaturdayPrice(float value);

    float getSundayPrice() const;
    void setSundayPrice(float value);

private:
    float standardPrice;
    float saturdayPrice;
    float sundayPrice;
};

#endif // PRICE_H
