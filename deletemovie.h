#ifndef DELETEMOVIE_H
#define DELETEMOVIE_H

#include <QDialog>
#include <QTableWidget>
#include <QStringList>
#include "film.h"

namespace Ui {
class DeleteMovie;
}

class DeleteMovie : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteMovie(QWidget *parent = 0);
    ~DeleteMovie();
    void fillTableWidget();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_Delete_clicked();

private:
    void setupTableWidget();
    Ui::DeleteMovie *ui;
    QVector<Film> films;
};

#endif // DELETEMOVIE_H
