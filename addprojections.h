#ifndef ADDPROJECTIONS_H
#define ADDPROJECTIONS_H

#include <QDialog>
#include "film.h"
#include "hall.h"
#include <QSpinBox>
#include <QCheckBox>

namespace Ui {
class AddProjections;
}

class AddProjections : public QDialog
{
    Q_OBJECT

public:
    explicit AddProjections(QWidget *parent = 0);
    ~AddProjections();
    void loadTableData();
    void fillTableWidgetF();
    void fillTableWidgetH();

private slots:
    void on_pushButton_Back_clicked();

    void on_pushButton_AddProjections_clicked();

private:
    Ui::AddProjections *ui;
    QVector<Film> films;
    QVector<Hall> halls;
    QList<QCheckBox*> checkBoxes;
    QList<QSpinBox*> spinBoxesH;
    QList<QSpinBox*> spinBoxesM;
};

#endif // ADDPROJECTIONS_H
