#ifndef EMPLOYEEMENU_H
#define EMPLOYEEMENU_H

#include <QDialog>
#include "addmovie.h"
#include "deletemovie.h"
#include "addhall.h"
#include "addprojections.h"
#include "repertoire.h"
#include <Qt>
#include <QWidget>


namespace Ui {
class EmployeeMenu;
}

class EmployeeMenu : public QDialog
{
    Q_OBJECT

public:
    explicit EmployeeMenu(QWidget *parent = 0);
    ~EmployeeMenu();

private slots:
    void on_pushButton_AddMovie_clicked();

    void on_pushButton_Login_clicked();

    void on_pushButton_DeleteMovie_clicked();

    void on_pushButton_AddHall_clicked();

    void on_pushButton_AddProjections_clicked();

    void on_pushButton_Repertoire_clicked();

    void on_pushButton_Confirm_clicked();

private:
    void setupTableWidget();
    void fillTableWidget();
    Ui::EmployeeMenu *ui;
    AddMovie * addMovie = NULL;
    DeleteMovie * deleteMovie = NULL;
    AddHall * addHall = NULL;
    AddProjections * addProjections = NULL;
    Repertoire * repertoire = NULL;
    QVector<Reservation> reservations;
};

#endif // EMPLOYEEMENU_H
