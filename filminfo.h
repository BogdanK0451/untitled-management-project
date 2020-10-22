#ifndef FILMINFO_H
#define FILMINFO_H

#include <QDialog>
#include "seatselection.h"
#include "film.h"

namespace Ui {
class FilmInfo;
}

class FilmInfo : public QDialog
{
    Q_OBJECT

public:
    explicit FilmInfo(int mode, const Film &film_, QWidget *parent = 0);
    ~FilmInfo();

private slots:
    void on_pushButton_Back_clicked();
    void openSeatSelection();

private:
    void listProjections();
    void uiSetup();
    void showFilmData();
    int mode;
    Ui::FilmInfo *ui;
    Film film;
    QGridLayout *gridLayout=NULL;
    SeatSelection *seatSelection=NULL;
};

#endif // FILMINFO_H
