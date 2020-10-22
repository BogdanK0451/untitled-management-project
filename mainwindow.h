#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "employeemenu.h"
#include "repertoire.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_Login_clicked();
    void on_pushButton_clicked();

private:
    void createDirs();
    void deleteOldProjections();
    void cleanDirs(QDir dir);
    void cleanReservations();
    Ui::MainWindow *ui;
    EmployeeMenu * employeeMenu = NULL;
    Repertoire * repertoire = NULL;
};

#endif // MAINWINDOW_H
