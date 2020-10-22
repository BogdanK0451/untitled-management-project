#ifndef REPERTOIRE_H
#define REPERTOIRE_H

#include <QDialog>
#include "filminfo.h"
#include "buttonqlabel.h"
#include "reservation.h"
#include <QGridLayout>
#include <QList>
#include <QRadioButton>



namespace Ui {
class Repertoire;
}

class Repertoire : public QDialog
{
    Q_OBJECT
//moc
public:
    explicit Repertoire(int mode_, QWidget *parent = 0);
    ~Repertoire();

signals:

private slots:
    void on_pushButton_Back_clicked();
    void openFilmInfo();
    void on_textEdit_Filter_textChanged();
    void filterAll();
    void filterSoon();

    void on_pushButton_Cancel_clicked();

private:
    void fadeIn();
    void loadFilms();
    void displayRepertoire();
    void generateGenres();
    void uiSetup();
    Ui::Repertoire *ui;
    QVector<Reservation> reservations;
    FilmInfo *filmInfo = NULL;
    QGridLayout *gridLayout= NULL;
    QVBoxLayout *verticalLayout_2 = NULL;
    QList<QRadioButton*> radioButtons;
    QList<ButtonQLabel*> buttonLabels;
    QVector<Film> films;
    QSet<QString> genres;
    int mode;
};

#endif // REPERTOIRE_H
