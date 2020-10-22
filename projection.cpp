#include "projection.h"
#include <QDebug>
#include <QDir>

Projection::Projection(const Film &film_, const QVector<Hall> & halls_, const QVector<QTime> &schedule_)
{
    film=film_;
    halls=halls_;
    schedule=schedule_;
}

Projection::Projection()
{

}

Projection::~Projection()
{

}

void Projection::createProjections() const
{

    QString folderName="./Projekcije/"+film.getName();
    QDir dir= QDir();
    if(!dir.exists(folderName))
        dir.mkdir(folderName);

    int days = Film::getDaysBetween(film.getProjectionsStart(),film.getProjectionsEnd());
    QDate dayOne= Film::startingDate(film.getProjectionsStart());

    int n = halls.size();
    int m = schedule.size();

    for(int day=0;day<=days;day++)
    {
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<m;j++)
            {
                {
                    QString fileName= folderName+"/"+film.getName()+"_"+halls.at(i).getHallName()
                    +"_"+dayOne.addDays(day).toString("dd.MM.yyyy")+"_"+schedule.at(j).toString("hh:mm");
                    QFile fileP(fileName);
                    if (!fileP.exists())
                    {
                        if (fileP.open(QIODevice::ReadWrite | QIODevice::Append | QIODevice::Text))
                        {
                            QTextStream stream(&fileP);
                            QString seats= halls.at(i).generateSeats();
                            stream << seats;
                        }
                        fileP.close();
                    }
                }
            }
        }
    }
}

QVector<QTime> Projection::getSchedule() const
{
    return schedule;
}

void Projection::setSchedule(const QVector<QTime> &value)
{
    schedule = value;
}

QVector<Hall> Projection::getHalls() const
{
    return halls;
}

void Projection::setHalls(const QVector<Hall> &value)
{
    halls = value;
}

Film Projection::getFilm() const
{
    return film;
}

void Projection::setFilm(const Film &value)
{
    film = value;
}
