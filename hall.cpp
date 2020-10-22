#include "hall.h"
#include <QDebug>

Hall::Hall(int row_,int col_, const QString &hallName_)
{
    row=row_;
    col=col_;
    hallName=hallName_;
}


Hall::Hall()
{

}
Hall::~Hall()
{

}
QString Hall::generateSeats() const
{
    QString string;

    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
            string.append('0');
        string.append('\n');
    }
    return string;
}

int Hall::getCol() const
{
    return col;
}

void Hall::setCol(int value)
{
    col = value;
}

int Hall::getRow() const
{
    return row;
}

void Hall::setRow(int value)
{
    row = value;
}

QString Hall::getHallName() const
{
    return hallName;
}

void Hall::setHallName(const QString &value)
{
    hallName = value;
}

QTextStream &operator<<(QTextStream &strm, const Hall &sala)
{
    return strm << sala.getHallName() << ";" << sala.getCol() << ";" << sala.getRow() << endl  ;
}

QTextStream &operator>>(QTextStream &strm, Hall &sala)
{
    QString line;
    line = strm.readLine();
    QStringList strings = line.split(';'); // polja ne smeju imati karakter ;
    sala.setHallName(strings.at(0));
    sala.setRow(strings.at(1).QString::toInt());
    sala.setCol(strings.at(2).QString::toInt());
    return strm;
}
