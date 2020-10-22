#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDir>
#include <QDialog>
#include <QFileInfo>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit_Password->setEchoMode(QLineEdit::Password);

    createDirs();
    QDir dir("./Projekcije");
    cleanDirs(dir);
    cleanReservations();

}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_Login_clicked()
{
    QString username = ui->lineEdit_UserName->text();
    QString password = ui->lineEdit_Password->text();
    QDir dir("./Projekcije");
    cleanDirs(dir);
    cleanReservations();

    if(username == "" && password == "")
    {
        if(!this->QObject::findChild<QDialog*>("EmployeeMenu",Qt::FindDirectChildrenOnly))
        {
            employeeMenu = new EmployeeMenu(this);
            this->QWidget::hide();
            employeeMenu->QWidget::show();
        }
        else{
            this->QWidget::hide();
            employeeMenu->QWidget::show();
        }
    }
    else
    {
        QMessageBox::warning(this,"Authentication","Wrong password or username");
    }
}

void MainWindow::on_pushButton_clicked()
{
    QDir dir("./Projekcije");
    cleanDirs(dir);
    cleanReservations();

    if(!this->QObject::findChild<QDialog*>("Repertoire",Qt::FindDirectChildrenOnly))
    {

        repertoire = new Repertoire(0,this);
        this->QWidget::hide();
        repertoire->QWidget::show();
    }
    else
    {
        this->QWidget::hide();
        repertoire->QWidget::show();
    }
}
//pravi potrebne direktorijume pri prvom pokretanju programa
void MainWindow::createDirs()
{
    QDir dir;
    if(!dir.exists("Projekcije"))
        dir.mkdir("Projekcije");

    QDir dir2;
    if(!dir2.exists("Slike"))
        dir2.mkdir("Slike");


    if (!QFileInfo("Cene.txt").exists())
    {
        QFile file("Cene.txt");
        if (file.open(QIODevice::ReadWrite | QIODevice::Text))
        {
            QTextStream stream(&file);
            stream << "100";
        }
        file.close();
    }
    if (!QFileInfo("Rezervacije.txt").exists())
    {
        QFile file("Rezervacije.txt");
        file.open(QIODevice::ReadWrite | QIODevice::Text);
        file.close();
    }
}
//brise projekcije nakon prikaza
void MainWindow::cleanDirs(QDir dir)
{
    QRegExp regexpDate("[0-9]{2}\\.[0-9]{2}\\.[0-9]{4}");
    QRegExp regexpTime("([01][0-9]|2[0-3])\\:[0-5][0-9]");
    QStringList date,time;

    dir.setFilter(QDir::Files | QDir::NoDotAndDotDot | QDir::NoSymLinks);

    QStringList fileList = dir.entryList();

    if(!fileList.contains("Sale.txt"))
    {
    for (int i=0; i<fileList.count(); i++)
        {
            regexpDate.indexIn(fileList.at(i));
            regexpTime.indexIn(fileList.at(i));
            date=regexpDate.capturedTexts();
            time=regexpTime.capturedTexts();

            if(QDate::fromString(date.at(0),"dd.MM.yyyy")<=QDate::currentDate() &&
                     QTime::fromString(time.at(0),"hh:mm")<=QTime::currentTime())
            {
                QFile file(dir.absolutePath()+"/"+fileList.at(i));
                    file.remove();
            }
        }
    }

    dir.setFilter(QDir::AllDirs | QDir::NoDotAndDotDot | QDir::NoSymLinks);
    QStringList dirList = dir.entryList();
    for (int i=0; i<dirList.size(); ++i)
    {
        //%1/%2 argumenti, arg dir prvi arg dirList drugi arg
        QString newPath = QString("%1/%2").arg(dir.absolutePath()).arg(dirList.at(i));
        cleanDirs(QDir(newPath));
    }
}
// brise rezervacije koje nisu podignute 30 minuta do pocetka filma
void MainWindow::cleanReservations()
{
    Reservation reservation;
    QVector<Reservation> reservations;
    QFile file("Rezervacije.txt");
    if(file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        QTextStream stream(&file);
        while(!stream.QTextStream::atEnd())
        {
            stream>>reservation;
            if(reservation.getDate()<=QDate::currentDate() && reservation.getProjectionStart().addSecs(-1800)<=QTime::currentTime())
                reservation.deleteReservation();
            else
            {
                reservations.push_back(reservation);
            }
        }
            file.close();

        file.open(QIODevice::WriteOnly | QFile::Truncate);
        int i=0;
        while (i<reservations.count())
        {
            reservations.at(i).saveReservation();
            i++;
        }
    }
}
