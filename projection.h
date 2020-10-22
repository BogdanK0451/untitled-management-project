#ifndef PROJECTION_H
#define PROJECTION_H

#include<hall.h>
#include<film.h>

class Projection
{
public:
    Projection(const Film &film_, const QVector<Hall> &halls_, const QVector<QTime> &schedule_);
    Projection();
    ~Projection();

    void createProjections () const;

    Film getFilm() const;
    void setFilm(const Film &value);

    QVector<Hall> getHalls() const;
    void setHalls(const QVector<Hall> &value);

    QVector<QTime> getSchedule() const;
    void setSchedule(const QVector<QTime> &value);

private:
    Film film;
    QVector<Hall> halls;
    QVector<QTime> schedule;

};

#endif // PROJECTION_H
