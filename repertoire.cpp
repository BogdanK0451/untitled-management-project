#include "repertoire.h"
#include "ui_repertoire.h"
#include "film.h"
#include "buttonqlabel.h"
#include <QRadioButton>
#include <QSet>
#include <QMessageBox>

#define HEIGHT 162
#define WIDTH 288

Repertoire::Repertoire(int mode_,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Repertoire)
{
    ui->setupUi(this);

    mode=mode_;
    uiSetup();

    ui->lineEdit_Cancel->setValidator(new QIntValidator(0,99999,this));

    QObject::connect(ui->pushButton_Soon,SIGNAL(clicked(bool)),this,SLOT(filterSoon()));
    QObject::connect(ui->pushButton_All,SIGNAL(clicked(bool)),this,SLOT(filterAll()));

    // ucitavanje filmova
    loadFilms();

    displayRepertoire();
    generateGenres();

    fadeIn();

    radioButtons = this->findChildren<QRadioButton*>(QString());
    buttonLabels = this->findChildren<ButtonQLabel*>(QString());

}

Repertoire::~Repertoire()
{
    delete ui;
}

void Repertoire::on_pushButton_Back_clicked()
{
    QWidget::parentWidget()->QWidget::show();
    this->setAttribute(Qt::WA_DeleteOnClose,true);
    close();
}
void Repertoire::uiSetup()
{
    ui->pushButton_All->setCheckable(true);
    ui->pushButton_Soon->setCheckable(true);
    gridLayout = new QGridLayout(ui->scrollAreaWidgetContents);
    gridLayout->setSizeConstraint(QLayout::SetFixedSize);
    gridLayout->setSpacing(15);
}

void Repertoire::displayRepertoire()
{
    QImage image;
    QStringList objectNames = { "labelImage_", "labelName_","labelProjectionStart_"};

    int i=0;
    int n=films.count();


    while(i<n)
    {
        ButtonQLabel *labelImage = new ButtonQLabel(this);
        ButtonQLabel *labelName = new ButtonQLabel(this);
        ButtonQLabel *labelProjectionStart = new ButtonQLabel(this);
        QVBoxLayout *verticalLayout = new QVBoxLayout();

        labelImage->setObjectName(objectNames.at(0)+QString::number(i));
        labelName->setObjectName(objectNames.at(1)+QString::number(i));
        labelProjectionStart->setObjectName(objectNames.at(2)+QString::number(i));

        verticalLayout->setSpacing(0);
        verticalLayout->setSizeConstraint((QLayout::SetFixedSize));

        image.load(films.at(i).getImgPath());
        labelImage->setFixedSize(WIDTH,HEIGHT);
        image = image.scaledToWidth(labelImage->width(),Qt::SmoothTransformation);
        labelImage->setPixmap(QPixmap::fromImage(image));

        labelName->setText(films.at(i).getName().toUpper());
        labelProjectionStart->setText("Pocetak prikazivanja: "+films.at(i).getProjectionsStart().toString("dd.MM.yyyy"));

        verticalLayout->addWidget(labelImage);
        verticalLayout->addWidget(labelProjectionStart);
        verticalLayout->addWidget(labelName);
        gridLayout->addLayout(verticalLayout,i / 3,i % 3);

        QObject::connect(labelImage,SIGNAL(labelClicked()),this,SLOT(openFilmInfo()));
        QObject::connect(labelName,SIGNAL(labelClicked()),this,SLOT(openFilmInfo()));
        QObject::connect(labelProjectionStart,SIGNAL(labelClicked()),this,SLOT(openFilmInfo()));


        genres.insert(films.at(i).getGenre());

        i++;
    }
}
void Repertoire::generateGenres()
{
    QVBoxLayout *verticalLayout_2 = new QVBoxLayout(ui->groupBox);
    QSet<QString>::const_iterator j=genres.constBegin();
    int h=0;
    while(j!=genres.constEnd())
    {

        QRadioButton *radioButton = new QRadioButton();

        radioButton->setText(*j);
        radioButton->setObjectName("radioButton_"+QString::number(h++));
        verticalLayout_2->addWidget(radioButton);
        j++;

        QObject::connect(radioButton,SIGNAL(clicked(bool)),this,SLOT(on_textEdit_Filter_textChanged()));
    }
}

void Repertoire::openFilmInfo()
{
    if(!this->QObject::findChild<QDialog*>("FilmInfo",Qt::FindDirectChildrenOnly))
    {
        QObject *senderObj = sender();
        QString senderObjName = senderObj->objectName();
        QStringList senderObjNames= senderObjName.split('_');
        filmInfo = new FilmInfo(mode,films.at(senderObjNames.at(1).toInt()),this);


        this->QWidget::hide();
        filmInfo->QWidget::show();
    }
    else
    {
        this->QWidget::hide();
        filmInfo->QWidget::show();
    }
}

void Repertoire::fadeIn()
{
    QGraphicsOpacityEffect *eff = new QGraphicsOpacityEffect(this);
    QPropertyAnimation *a = new QPropertyAnimation(eff,"opacity");
    a->setDuration(2000);
    a->setStartValue(0);
    a->setEndValue(1);
    a->setEasingCurve(QEasingCurve::Linear);
    a->start(QPropertyAnimation::DeleteWhenStopped);
    ui->scrollArea->setGraphicsEffect(eff);

}

void Repertoire::on_textEdit_Filter_textChanged()
{

    QString regexPlaceholder = "(.*)";
    QList<QRadioButton*>::const_iterator j=radioButtons.constBegin();
    QList<QRadioButton*>::const_iterator k=radioButtons.constEnd();

    while(j!=k)
    {
        if((*j)->isChecked())
            regexPlaceholder =(*j)->text();
        j++;
    }

    QDate today;

    if(ui->pushButton_Soon->isChecked())
        today = QDate(QDate::currentDate());
    if(ui->pushButton_All->isChecked())
        today = QDate(1,1,9999);

    QRegExp regexGenre = QRegExp(regexPlaceholder);
    QRegExp regexName = QRegExp("^"+ui->textEdit_Filter->toPlainText()+"(.*)",Qt::CaseInsensitive);

    int i=0;
    int n=films.count();
    while(i<n)
    {
        if (!(films.at(i).getName().contains(regexName) && films.at(i).getGenre().contains(regexGenre) && films.at(i).getProjectionsStart()>today))
        {
            buttonLabels.at(i*3)->hide();
            buttonLabels.at(i*3+1)->hide();
            buttonLabels.at(i*3+2)->hide();
        }
        else
        {
            buttonLabels.at(i*3)->show();
            buttonLabels.at(i*3+1)->show();
            buttonLabels.at(i*3+2)->show();
        }
         i++;
    }
}

void Repertoire::filterAll()
{
    ui->pushButton_All->setChecked(true);
    ui->pushButton_Soon->setChecked(false);
    on_textEdit_Filter_textChanged();

}
void Repertoire::filterSoon()
{
    ui->pushButton_Soon->setChecked(true);
    ui->pushButton_All->setChecked(false);
    on_textEdit_Filter_textChanged();
}

void Repertoire::on_pushButton_Cancel_clicked()
{
    int successFlag=0;
    Reservation reservation;

    QString fileName="Rezervacije.txt";
    QFile fileF(fileName);
    if (fileF.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream stream(&fileF);
        while(!stream.QTextStream::atEnd())
        {
            stream >> reservation;
            if(reservation.getID()!=ui->lineEdit_Cancel->text().toInt())
                reservations.push_back(reservation);
            else
            {
                successFlag=1;
                reservation.deleteReservation();
            }
        }
            fileF.close();


        fileF.open(QIODevice::WriteOnly | QFile::Truncate);
        fileF.close();
        int i=0;
        while (i<reservations.count())
        {
            reservations.at(i).saveReservation();
            i++;
        }
        reservations.clear();
    }
    if(successFlag==1)
    {
        QMessageBox::information(this,"Otkaz rezervacije broj ","Uspeh"+ui->lineEdit_Cancel->text());
        ui->lineEdit_Cancel->clear();
    }

}
void Repertoire::loadFilms()
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
            films.push_back(film);
        }
    }
    file.close();
}
