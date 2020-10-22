#include "addmovie.h"
#include "ui_addmovie.h"
#include "employeemenu.h"
#include "film.cpp"


AddMovie::AddMovie(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddMovie)
{
    ui->setupUi(this);

    ui->pushButton_Add->setEnabled(false);
    ui->label_ImageName->setVisible(false);

    setValidators();
    establishConnections();
}


AddMovie::~AddMovie()
{
    delete ui;
}

//dodavanja filma
void AddMovie::on_pushButton_Add_clicked()
{
    if(isExistingId())
    {
        QString filename="Filmovi.txt";
        QFile file(filename);

        if (file.open(QIODevice::ReadWrite | QIODevice::Append | QIODevice::Text))
        {
            QTextStream stream(&file);

            Film film = Film(ui->lineEdit_Name->text(),ui->lineEdit_ID->text().toInt(),ui->lineEdit_Hours->text().toInt()*60+ui->lineEdit_Minutes->text().toInt()
                       ,ui->lineEdit_Genre->text(),ui->dateEdit_ProjectionsStart->date(),ui->dateEdit_ProjectionsEnd->date(),ui->label_ImageName->text()
                       ,ui->lineEdit_Year->text(),ui->lineEdit_Actors->text(),ui->lineEdit_Director->text(),ui->lineEdit_Distributor->text(),ui->lineEdit_Country->text());
            stream << film;

            clearAll();
            QDir dir;
            if(!dir.exists("Projekcije/"+film.getName()))
                dir.mkdir("Projekcije/"+film.getName());
        }
        file.close();
        clearAll();
        QMessageBox::information(this,"Dodavanje filma","Uspeh");
    }
    else
    {
        QMessageBox::warning(this,"Greska","Postoji film sa ID-jem "+ui->lineEdit_ID->text());
    }
}


void AddMovie::on_pushButton_Back_clicked()
{
    QWidget::parentWidget()->QWidget::show();
    this->QWidget::hide();
}
//ucitavanje slike
void AddMovie::on_pushButton_Image_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, "Izaberi sliku","","Images (*.png *xpm *.jpg *jpeg *.bmp *.gif)");
    if(QString::compare(filename,QString()) !=0)
    {
        QImage image;
        bool valid = image.load(filename);
        if(valid)
        {
            image = image.scaledToWidth(ui->label_ImageFill->width(),Qt::SmoothTransformation);
            ui->label_ImageName->setText(filename);
            ui->label_ImageFill->setPixmap(QPixmap::fromImage(image));

        }
        else{
            QMessageBox errorBox;
            errorBox.critical(this,"Greska","Slika nije ucitana");
        }
    }
}

void AddMovie::textChanged()
{
    bool buttonState = !ui->lineEdit_Name->text().isEmpty() && !ui->lineEdit_ID->text().isEmpty() && !ui->lineEdit_Hours->text().isEmpty()
            && !ui->lineEdit_Minutes->text().isEmpty() && !ui->lineEdit_Genre->text().isEmpty() && !ui->label_ImageName->text().isEmpty();

    if(buttonState)
        ui->pushButton_Add->setEnabled(true);

    else if(!buttonState)
        ui->pushButton_Add->setEnabled(false);
}

void AddMovie::on_dateEdit_ProjectionsEnd_dateChanged()
{
        ui->dateEdit_ProjectionsEnd->setMinimumDate(ui->dateEdit_ProjectionsStart->date());
}

void AddMovie::clearAll()
{
    ui->pushButton_Add->setEnabled(false);
    ui->lineEdit_Name->clear();
    ui->lineEdit_ID->clear();
    ui->lineEdit_Hours->clear();
    ui->lineEdit_Minutes->clear();
    ui->lineEdit_Genre->clear();
    ui->label_ImageName->clear();
    ui->label_ImageFill->clear();
    ui->lineEdit_Year->clear();
    ui->lineEdit_Actors->clear();
    ui->lineEdit_Director->clear();
    ui->lineEdit_Distributor->clear();
    ui->lineEdit_Country->clear();
}

void AddMovie::establishConnections()
{
    QObject::connect(ui->lineEdit_Name,SIGNAL(textEdited(QString)),this,SLOT(textChanged()));
    QObject::connect(ui->lineEdit_ID,SIGNAL(textEdited(QString)),this,SLOT(textChanged()));
    QObject::connect(ui->lineEdit_Hours,SIGNAL(textEdited(QString)),this,SLOT(textChanged()));
    QObject::connect(ui->lineEdit_Minutes,SIGNAL(textEdited(QString)),this,SLOT(textChanged()));
    QObject::connect(ui->lineEdit_Genre,SIGNAL(textEdited(QString)),this,SLOT(textChanged()));
    QObject::connect(ui->pushButton_Image,SIGNAL(clicked(bool)),this,SLOT(textChanged()));
    QObject::connect(ui->dateEdit_ProjectionsEnd,SIGNAL(dateChanged(QDate)),this,SLOT(on_dateEdit_ProjectionsEnd_dateChanged()));
}

void AddMovie::setValidators()
{
    QRegExp regex("^[^;]*$");
    ui->label_ID->setToolTip("od 0 do 10000");
    QList<QLineEdit*> lineEdits = this->findChildren<QLineEdit*>(QString());
    QList<QLineEdit*>::const_iterator i=lineEdits.constBegin();
    QList<QLineEdit*>::const_iterator j=lineEdits.constEnd();
    while(i!=j)
    {
        (*i)->setValidator((new QRegExpValidator(regex)));
        i++;
    }
    ui->lineEdit_ID->setValidator(new QIntValidator(0,10000,this));
    ui->lineEdit_Hours->setValidator(new QIntValidator(0,5,this));
    ui->lineEdit_Minutes->setValidator(new QIntValidator(0,59,this));
    ui->dateEdit_ProjectionsStart->QDateEdit::setMinimumDate(QDate::currentDate());
    ui->dateEdit_ProjectionsEnd->QDateEdit::setMinimumDate(QDate::currentDate().addDays(1));
}
//provera da li postoji film sa unetim ID-om
bool AddMovie::isExistingId()
{
    Film film;
    QString filename="Filmovi.txt";
    QFile file( filename );
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        while(!stream.QTextStream::atEnd())
        {
            stream >> film;
            if(film.getId()==ui->lineEdit_ID->text().toInt())
                return false;
            else
                return true;
        }
    }
    return true;
}
