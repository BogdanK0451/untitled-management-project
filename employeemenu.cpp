#include "employeemenu.h"
#include "ui_employeemenu.h"


EmployeeMenu::EmployeeMenu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EmployeeMenu)
{
    ui->setupUi(this);
    setupTableWidget();

    Reservation reservation;
    QFile file("Rezervacije.txt");
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        while(!stream.QTextStream::atEnd())
        {
            stream>>reservation;
            reservations.push_back(reservation);
        }
            file.close();
    }
    fillTableWidget();
}

EmployeeMenu::~EmployeeMenu()
{
    delete ui;
}

void EmployeeMenu::on_pushButton_AddMovie_clicked()
{
    if(!addMovie)
    {
        addMovie = new AddMovie(this);
        this->QWidget::hide();
        addMovie->QWidget::show();
    }
    else
    {
        this->QWidget::hide();
        addMovie->QWidget::show();
    }
}

void EmployeeMenu::on_pushButton_Login_clicked()
{
    QWidget::parentWidget()->QWidget::show();
    this->setAttribute(Qt::WA_DeleteOnClose,true);
    close();

}

void EmployeeMenu::on_pushButton_DeleteMovie_clicked()
{
    if(!this->QObject::findChild<QDialog*>("DeleteMovie",Qt::FindDirectChildrenOnly))
    {
        deleteMovie = new DeleteMovie(this);
        this->QWidget::hide();
        deleteMovie->QWidget::show();
    }
    else
    {
        this->QWidget::hide();
        deleteMovie->QWidget::show();
    }
}

void EmployeeMenu::on_pushButton_AddHall_clicked()
{
    if(!this->QObject::findChild<QDialog*>("AddHall",Qt::FindDirectChildrenOnly))
    {
        addHall= new AddHall(this);
        this->QWidget::hide();
        addHall->QWidget::show();
    }
    else
    {
        this->QWidget::hide();
        addHall->QWidget::show();
    }

}

void EmployeeMenu::on_pushButton_AddProjections_clicked()
{
    if(!this->QObject::findChild<QDialog*>("addProjections",Qt::FindDirectChildrenOnly))
    {
        addProjections= new AddProjections(this);
        this->QWidget::hide();
        addProjections->QWidget::show();
    }
    else
    {
        this->QWidget::hide();
        deleteMovie->QWidget::show();
    }

}

void EmployeeMenu::on_pushButton_Repertoire_clicked()
{
    if(!this->QObject::findChild<QDialog*>("Repertoire",Qt::FindDirectChildrenOnly))
    {

        repertoire = new Repertoire(1,this);
        this->QWidget::hide();
        repertoire->QWidget::show();
    }
    else
    {
        this->QWidget::hide();
        repertoire->QWidget::show();
    }
}

void EmployeeMenu::setupTableWidget()
{
    QStringList columnHeaders;
    columnHeaders << "ID" << "Ime" << "Film" << "Cena";

    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->QTableWidget::setColumnCount(4);
    ui->tableWidget->QTableWidget::setHorizontalHeaderLabels(columnHeaders);
    ui->tableWidget->QTableWidget::setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void EmployeeMenu::fillTableWidget()
{
    {
        int i=0;
        int n= reservations.count();
        ui->tableWidget->QTableWidget::setRowCount(reservations.count());
        while (i<n)
        {
            ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString::number(reservations.at(i).getID())));
            ui->tableWidget->setItem(i,1,new QTableWidgetItem(reservations.at(i).getBuyerName()));
            ui->tableWidget->setItem(i,2,new QTableWidgetItem(reservations.at(i).getFilmName()));
            ui->tableWidget->setItem(i,3,new QTableWidgetItem(QString::number(reservations.at(i).getPrice())));

            i++;
        }
    }
}

//potvrda rezervacije
void EmployeeMenu::on_pushButton_Confirm_clicked()
{
    QModelIndexList selection =ui->tableWidget->selectionModel()->selectedRows();
    if(ui->tableWidget->rowCount()>0 && selection.size()>0)
    {
        int rowToDelete = selection.at(0).row();
        QString paymentSum =QString::number(reservations.at(rowToDelete).getPrice());
        reservations.erase(reservations.begin()+rowToDelete);

        fillTableWidget();

        QString filename="Rezervacije.txt";
        QFile file(filename);

        if (file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text))
        {
            QTextStream stream(&file);
            int i=0;
            int n=reservations.count();
            while (i<n)
            {
                reservations.at(i).saveReservation();
                i++;
            }
        }
        file.close();
        QMessageBox::information(this,"Uspeh","Za uplatu "+paymentSum+" din");
    }
    else
        QMessageBox::warning(this,"Greska","Morate odabrati  rezervaciju");
}
