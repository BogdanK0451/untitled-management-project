#include "deletemovie.h"
#include "ui_deletemovie.h"
#include "employeemenu.h"
#include "film.h"
#include <QDebug>

DeleteMovie::DeleteMovie(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeleteMovie)
{
    ui->setupUi(this);

    Film film;
    QString filename="Filmovi.txt";
    QFile file( filename );
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        while(!stream.QTextStream::atEnd())
        {
            stream >> film;
            films.push_back(film);
        }
    }
    file.close();
    setupTableWidget();
    fillTableWidget();
}
DeleteMovie::~DeleteMovie()
{
    delete ui;
}

void DeleteMovie::on_pushButton_clicked()
{

    QWidget::parentWidget()->QWidget::show();
    this->setAttribute(Qt::WA_DeleteOnClose,true);
    close();
}

//brise film iz datoteke
void DeleteMovie::on_pushButton_Delete_clicked()
{
    QModelIndexList selection =ui->tableWidget->selectionModel()->selectedRows();
    if(ui->tableWidget->rowCount()>0 && selection.size()>0)
    {
        int rowToDelete = selection.at(0).row();
        QDir dir = QDir("Projekcije/"+films.at(rowToDelete).getName());
        if(dir.exists())
            dir.removeRecursively();
        films.erase(films.begin()+rowToDelete);

        fillTableWidget();

        QString filename="Filmovi.txt";
        QFile file( filename );

        if (file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text))
        {
            QTextStream stream(&file);
            int i=0;
            while (i<films.count())
            {
                stream << films.at(i);
                i++;
            }
        }
    }
    else
        QMessageBox::warning(this,"Greska","Morate odabrati film");
}

void DeleteMovie::setupTableWidget()
{
    QStringList columnHeaders;
    columnHeaders << "Naziv" << "ID" << "Duzina trajanja" << "Zanr" << "Pocetak prikazivanja" << "Kraj prikazivanja";

    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->QTableWidget::setColumnCount(6);
    ui->tableWidget->QTableWidget::setHorizontalHeaderLabels(columnHeaders);
    ui->tableWidget->QTableWidget::setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void DeleteMovie::fillTableWidget()
{
    int i=0;
    int n= films.count();
    ui->tableWidget->QTableWidget::setRowCount(films.count());
    while (i<n)
    {
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(films.at(i).getName()));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(QString::number(films.at(i).getId())));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(QString::number(films.at(i).getLength())));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(films.at(i).getGenre()));
        ui->tableWidget->setItem(i,4,new QTableWidgetItem(films.at(i).getProjectionsStart().toString("dd.MM.yyyy")));
        ui->tableWidget->setItem(i,5,new QTableWidgetItem(films.at(i).getProjectionsEnd().toString("dd.MM.yyyy")));
        i++;
    }
}
