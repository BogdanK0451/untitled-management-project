#include "addprojections.h"
#include "ui_addprojections.h"
#include "projection.h"
#include "film.h"
#include <QFile>
#include <QString>
#include <QVector>
#include <QDir>
#include <QRadioButton>
#include <QMessageBox>

AddProjections::AddProjections(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddProjections)
{
    ui->setupUi(this);

    loadTableData();
    fillTableWidgetH();
    fillTableWidgetF();

    QRegExp regexH = QRegExp("^spinBox_TerminH(.*)");
    QRegExp regexM = QRegExp("^spinBox_TerminM(.*)");

    checkBoxes = this->findChildren<QCheckBox*>();
    spinBoxesH = this->findChildren<QSpinBox*>(regexH);
    spinBoxesM = this->findChildren<QSpinBox*>(regexM);

}

AddProjections::~AddProjections()
{
    delete ui;
}

void AddProjections::on_pushButton_Back_clicked()
{
    QWidget::parentWidget()->QWidget::show();
    this->setAttribute(Qt::WA_DeleteOnClose,true);
    close();
}

void AddProjections::fillTableWidgetH()
{
    QStringList columnHeaders;
    columnHeaders << "Naziv sale" << "Broj redova" << "Broj kolona" << "Broj sedista";

    ui->tableWidget_Halls->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_Halls->QTableWidget::setColumnCount(4);
    ui->tableWidget_Halls->QTableWidget::setHorizontalHeaderLabels(columnHeaders);
    ui->tableWidget_Halls->QTableWidget::setEditTriggers(QAbstractItemView::NoEditTriggers);

    int i=0;
    int n=halls.count();

    ui->tableWidget_Halls->QTableWidget::setRowCount(halls.count());
    while (i<n)
    {
        ui->tableWidget_Halls->setItem(i,0,new QTableWidgetItem(halls.at(i).Hall::getHallName()));
        ui->tableWidget_Halls->setItem(i,1,new QTableWidgetItem(QString::number(halls.at(i).Hall::getRow())));
        ui->tableWidget_Halls->setItem(i,2,new QTableWidgetItem(QString::number(halls.at(i).Hall::getCol())));
        ui->tableWidget_Halls->setItem(i,3,new QTableWidgetItem(QString::number(halls.at(i).Hall::getRow()*halls.at(i).Hall::getCol())));
        i++;
     }
}

void AddProjections::fillTableWidgetF()
{
    QStringList columnHeaders;
    columnHeaders << "Naziv" << "ID" << "Duzina trajanja" << "Zanr" << "Pocetak prikazivanja" << "Kraj prikazivanja";

    ui->tableWidget_Films->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_Films->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget_Films->QTableWidget::setColumnCount(6);
    ui->tableWidget_Films->QTableWidget::setHorizontalHeaderLabels(columnHeaders);
    ui->tableWidget_Films->QTableWidget::setEditTriggers(QAbstractItemView::NoEditTriggers);

    int i=0;
    int n=films.count();
    ui->tableWidget_Films->QTableWidget::setRowCount(films.count());
    while (i<n)
    {
        ui->tableWidget_Films->setItem(i,0,new QTableWidgetItem(films.at(i).Film::getName()));
        ui->tableWidget_Films->setItem(i,1,new QTableWidgetItem(QString::number(films.at(i).Film::getId())));
        ui->tableWidget_Films->setItem(i,2,new QTableWidgetItem(QString::number(films.at(i).Film::getLength())));
        ui->tableWidget_Films->setItem(i,3,new QTableWidgetItem(films.at(i).Film::getGenre()));
        ui->tableWidget_Films->setItem(i,4,new QTableWidgetItem(films.at(i).Film::getProjectionsStart().toString("dd.MM.yyyy")));
        ui->tableWidget_Films->setItem(i,5,new QTableWidgetItem(films.at(i).Film::getProjectionsEnd().toString("dd.MM.yyyy")));
        i++;
     }
}
//dodavanje projekcija
void AddProjections::on_pushButton_AddProjections_clicked()
{
    QModelIndexList selectedHallIndexes=ui->tableWidget_Halls->selectionModel()->selectedRows();
    QModelIndexList selectedFilmIndex=ui->tableWidget_Films->selectionModel()->selectedRows();

    //ucitavanje termina
    QList<QCheckBox*>::const_iterator i1=checkBoxes.constBegin();
    QList<QCheckBox*>::const_iterator i2=checkBoxes.constEnd();

    int count =0;
        while(i1!=i2)
        {
            if((*i1)->isChecked())
                count++;
            i1++;
        }

    if(ui->tableWidget_Films->rowCount()>0 && selectedHallIndexes.size()>0 && selectedFilmIndex.size()>0 && count>0 )
    {
        QVector<QTime> schedule;

        i1=checkBoxes.constBegin();
        i2=checkBoxes.constEnd();
        QList<QSpinBox*>::const_iterator j1=spinBoxesH.constBegin();
        QList<QSpinBox*>::const_iterator j2=spinBoxesH.constEnd();
        QList<QSpinBox*>::const_iterator k1=spinBoxesM.constBegin();
        QList<QSpinBox*>::const_iterator k2=spinBoxesM.constEnd();

        while(i1!=i2 && j1!=j2 && k1!=k2)
        {
            if((*i1)->isChecked())
            {
                schedule.push_back(QTime((*j1)->value(),(*k1)->value()));
            }
            i1++;
            j1++;
            k1++;
        }
        //ucitavanje sala
        int n = selectedHallIndexes.size();
        QVector<Hall> hallsP;
        for (int i=0;i<n;i++)
            hallsP.push_back(halls.at(selectedHallIndexes.at(i).row()));
        int m = selectedFilmIndex.at(0).row();
        Hall hala = halls.at(0);
        Projection projection = Projection(films.at(m),hallsP,schedule);
        projection.createProjections();

    }
    else
    {
         QMessageBox::warning(this,"Dodavanje projekcija","Odaberite sve parametre");
    }
}

void AddProjections::loadTableData()
{
    Film film;
    QString fileName="Filmovi.txt";
    QFile fileF(fileName);
    if (fileF.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream stream(&fileF);
        while(!stream.QTextStream::atEnd())
        {
            stream >> film;
            films.push_back(film);
        }
    }
    fileF.close();

    Hall hall;
    fileName="Projekcije/Sale.txt";
    QFile fileH(fileName);
    if (fileH.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream stream(&fileH);
        while(!stream.QTextStream::atEnd())
        {
            stream >> hall;
            halls.push_back(hall);
        }
    }
    fileH.close();
}
