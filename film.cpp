#include "film.h"
#include <QDebug>

Film::Film()
{

}
Film::Film(const Film & film)
{
    name=film.getName();
    id=film.getId();
    length=film.getLength();
    genre=film.getGenre();
    projectionsStart=film.getProjectionsStart();
    projectionsEnd=film.getProjectionsEnd();
    imgPath=film.getImgPath();
    year=film.getYear();
    actors=film.getActors();
    director=film.getDirector();
    distributor=film.getDistributor();
    country=film.getCountry();
}

Film::Film(const QString &name_, int id_, int length_,const QString &genre_,const QDate &projectionsStart_,
           const QDate &projectionsEnd_,const QString &imgPath_,const QString &year_, const QString &actors_,
           const QString &director_, const QString &distributor_, const QString & country_ )
{
    name= name_;
    id=id_;
    length=length_;
    genre=genre_;
    projectionsStart=projectionsStart_;
    projectionsEnd=projectionsEnd_;
    timeOfAddition=QDateTime::currentDateTime();
    imgPath=imgPath_;
    year= Film::checkIfEmptyString(year_);
    actors= Film::checkIfEmptyString(actors_);
    director= Film::checkIfEmptyString(director_);
    distributor= Film::checkIfEmptyString(distributor_);
    country= Film::checkIfEmptyString(country_);
}
Film::~Film()
{

}
//provera da li ima teksta u line editu za pravljenje objekta
QString Film::checkIfEmptyString(const QString & string)
{
    if(!QString::compare(string,""))
        return "N/A";
    else
        return string;
}

//
int Film::getDaysBetween(const QDate &start, const QDate &end)
{
    int days;
    QDate today = QDate(QDate::currentDate());

    if (today>=start)
        days= today.daysTo(end);
    if (today<start)
        days= start.daysTo(end);

    return days;
}

QDate Film::startingDate(const QDate &start)
{
     QDate today = QDate(QDate::currentDate());
     if (today>=start)
         return today;
     else
         return start;
}

QString Film::getName() const
{
    return name;
}

void Film::setName(const QString &name_)
{
    name=name_;
}

int Film::getId() const
{
    return id;
}

void Film::setId(int id_)
{
    id=id_;
}

int Film::getLength() const
{
    return length;
}

void Film::setLength(int length_)
{
    length=length_;
}

QString Film::getGenre() const{
    return genre;
}

void Film::setGenre(const QString &genre_)
{
    genre=genre_;
}

QDate Film::getProjectionsStart() const
{
    return projectionsStart;
}

void Film::setProjectionsStart(const QDate &projectionsStart_)
{
    projectionsStart=projectionsStart_;
}

QDate Film::getProjectionsEnd() const{
    return projectionsEnd;
}

void Film::setProjectionsEnd(const QDate &projectionsEnd_)
{
    projectionsEnd=projectionsEnd_;
}

QString Film::getImgPath() const{
    return imgPath;
}

void Film::setImgPath(const QString &imgPath_){
    imgPath=imgPath_;
}

QString Film::getYear() const
{
    return year;
}

void Film::setYear(const QString &year_)
{
    year = year_;
}

QString Film::getActors() const
{
    return actors;
}

void Film::setActors(const QString &actors_)
{
    actors = actors_;
}

QString Film::getDirector() const
{
    return director;
}

void Film::setDirector(const QString &director_)
{
    director = director_;
}

QString Film::getCountry() const
{
    return country;
}

void Film::setCountry(const QString &country_)
{
    country = country_;
}

QString Film::getDistributor() const
{
    return distributor;
}

void Film::setDistributor(const QString &distributor_)
{
    distributor = distributor_;
}

QTextStream &operator<<(QTextStream &strm, const Film &film)
{
    return strm << film.getName() << ";" << film.getId() << ";" << film.getLength() << ";"  << film.getGenre() << ";"  << film.getProjectionsStart().toString("dd.MM.yyyy")
                << ";" << film.getProjectionsEnd().toString("dd.MM.yyyy") << ";" << film.getImgPath() << ";" << film.getYear() << ";" << film.getActors()
                << ";" << film.getDirector() << ";" << film.getCountry() << ";" << film.getDistributor() << endl  ;
}

QTextStream &operator>>(QTextStream &strm, Film &film)
{
    QString line;
    line = strm.readLine();
    QStringList strings = line.split(';'); // polja ne smeju imati karakter ;
    film.setName(strings.at(0));
    film.setId(strings.at(1).QString::toInt());
    film.setLength(strings.at(2).QString::toInt());
    film.setGenre(strings.at(3));
    film.setProjectionsStart(QDate::fromString(strings.at(4),"dd.MM.yyyy"));
    film.setProjectionsEnd(QDate::fromString(strings.at(5),"dd.MM.yyyy"));
    film.setImgPath(strings.at(6));
    film.setYear(strings.at(7));
    film.setActors(strings.at(8));
    film.setDirector(strings.at(9));
    film.setCountry(strings.at(10));
    film.setDistributor(strings.at(11));

    return strm;
}

