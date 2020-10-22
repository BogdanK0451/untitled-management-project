#include "addhall.h"
#include "ui_addhall.h"
#include "hall.h"
#include <QFile>
#include "price.h"
#include <QDebug>

AddHall::AddHall(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddHall)
{
    ui->setupUi(this);

    ui->pushButton_Add->setEnabled(false);

    ui->lineEdit_Row->setValidator(new QIntValidator(0,20,this));
    ui->lineEdit_Col->setValidator(new QIntValidator(0,50,this));

    price.loadPrices();
    setPriceLabels();

    loadHalls();

    QObject::connect(ui->lineEdit_HallName,SIGNAL(textEdited(QString)),this,SLOT(textChanged()));
    QObject::connect(ui->lineEdit_Row,SIGNAL(textEdited(QString)),this,SLOT(textChanged()));
    QObject::connect(ui->lineEdit_Col,SIGNAL(textEdited(QString)),this,SLOT(textChanged()));

    setupTableWidget();
    fillTableWidget();


}
void AddHall::loadHalls()
{
    Hall hall;
    QString filename="Projekcije/Sale.txt";
    QFile file( filename );
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        while(!stream.QTextStream::atEnd())
        {
            stream >> hall;
            halls.push_back(hall);
        }
    }
    file.close();
}

AddHall::~AddHall()
{
    delete ui;
}

void AddHall::on_pushButton_Back_clicked()
{
    QWidget::parentWidget()->QWidget::show();
    this->setAttribute(Qt::WA_DeleteOnClose,true);
    close();
}

//dodavanje sala
void AddHall::on_pushButton_Add_clicked()
{
    Hall hall;
    QString filename="Projekcije/Sale.txt";
    QFile file( filename );
    if (file.open(QIODevice::ReadWrite | QIODevice::Append | QIODevice::Text))
    {
        QTextStream stream(&file);
        hall.setHallName(ui->lineEdit_HallName->text());
        hall.setRow(ui->lineEdit_Row->text().toInt());
        hall.setCol(ui->lineEdit_Col->text().toInt());

        stream << hall;
        halls.push_back(hall);
        fillTableWidget();
    }
    file.close();

    ui->pushButton_Add->setEnabled(false);
    ui->lineEdit_HallName->clear();
    ui->lineEdit_Row->clear();
    ui->lineEdit_Col->clear();
}

void AddHall::textChanged()
{
    bool buttonState = !ui->lineEdit_HallName->text().isEmpty() && !ui->lineEdit_Row->text().isEmpty() && !ui->lineEdit_Col->text().isEmpty();

    if(buttonState)
        ui->pushButton_Add->setEnabled(true);

    if(!buttonState)
        ui->pushButton_Add->setEnabled(false);
}

void AddHall::setupTableWidget()
{
    QStringList columnHeaders;
    columnHeaders << "Naziv" << "Broj redova" << "Broj kolona" << "Broj sedista";

    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->QTableWidget::setColumnCount(4);
    ui->tableWidget->QTableWidget::setHorizontalHeaderLabels(columnHeaders);
    ui->tableWidget->QTableWidget::setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void AddHall::fillTableWidget()
{
    int i=0;
    int n=halls.count();
    ui->tableWidget->QTableWidget::setRowCount(halls.count());
    while (i<n)
    {
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(halls.at(i).Hall::getHallName()));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(QString::number(halls.at(i).Hall::getRow())));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(QString::number(halls.at(i).Hall::getCol())));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(QString::number(halls.at(i).Hall::getRow()*halls.at(i).Hall::getCol())));
        i++;
     }
}

void AddHall::setPriceLabels()
{
    ui->label_Standard->setText("Obicna cena\n"+QString::number(price.getStandardPrice()));
    ui->label_Saturday->setText("Cena subotom\n"+QString::number(price.getSaturdayPrice()));
    ui->label_Sunday->setText("Cena nedeljom\n"+QString::number(price.getSundayPrice()));
}
//izmena cene
void AddHall::on_pushButton_setPrice_clicked()
{
     price.savePrices(ui->lineEdit_Price->text());
     price.loadPrices();
     setPriceLabels();
}
