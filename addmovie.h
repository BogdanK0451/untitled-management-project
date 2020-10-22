#ifndef ADDMOVIE_H
#define ADDMOVIE_H

#include <QDialog>
#include <QFile>
#include <QImage>
#include <iostream>
#include <QString>
#include <QList>
#include <QTextStream>
#include <QVector>
#include <QFileDialog>
#include <QMessageBox>
#include <QLocale>
#include <QLineEdit>

namespace Ui {
class AddMovie;
}

class AddMovie : public QDialog
{
    Q_OBJECT

public:
    explicit AddMovie(QWidget *parent = 0);
    ~AddMovie();

private slots:
    void on_pushButton_Add_clicked();
    void on_pushButton_Image_clicked();
    void on_pushButton_Back_clicked();
    void textChanged();
    void on_dateEdit_ProjectionsEnd_dateChanged();

private:
    bool isExistingId();
    void setValidators();
    void establishConnections();
    void clearAll();
    Ui::AddMovie *ui;
};

#endif // ADDMOVIE_H
