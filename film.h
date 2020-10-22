#ifndef FILM_H
#define FILM_H

#include <QString>
#include <QtGlobal>
#include <QDate>
#include <QDateTime>
#include <QVector>
#include <QTime>
#include <iostream>
#include <QTextStream>
#include <QFile>
#include <QGridLayout>
#include <QFontMetrics>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QDebug>

class Film
{
public:
    Film();
    Film(const Film &film) ;
    Film(const QString &name_, int id_, int duration_, const QString &genre_, const QDate &projectionsStart_,
         const QDate &projectionsEnd_, const QString &imgPath_, const QString &year_, const QString &actors_,
         const QString &director_, const QString &distributor_, const QString &country_) ;
    ~Film();


    static int getDaysBetween(const QDate &start, const QDate &end);
    static QDate startingDate(const QDate &start);
    static QString checkIfEmptyString(const QString &string);

    QString getName() const;
    void setName(const QString &name_);

    int getId() const;
    void setId(int id_);

    int getLength() const;
    void setLength(int duration_);

    QString getGenre() const;
    void setGenre(const QString &genre_);

    QDate getProjectionsStart() const;
    void setProjectionsStart(const QDate &projectionsStart_);

    QDate getProjectionsEnd() const;
    void setProjectionsEnd(const QDate &projectionsEnd_);

    QString getImgPath() const;
    void setImgPath(const QString &imgPath_);

    QString getYear() const;
    void setYear(const QString &year_);

    QString getActors() const;
    void setActors(const QString &actors_);

    QString getDirector() const;
    void setDirector(const QString &director_);

    QString getCountry() const;
    void setCountry(const QString &country_);

    QString getDistributor() const;
    void setDistributor(const QString &distributor_);

private:
    QString name;
    int id;
    int length;
    QString genre;
    QDate projectionsStart;
    QDate projectionsEnd;
    QDateTime timeOfAddition;
    QString imgPath;
    QString year;
    QString actors;
    QString director;
    QString country;
    QString distributor;


};

QTextStream &operator<<(QTextStream &strm, const Film &film);
QTextStream &operator>>(QTextStream &strm, Film &film);
#endif // FILM_H
