#include "filminfo.h"
#include "ui_filminfo.h"
#include <buttonqlabel.h>
#include <QDir>
#include <QFont>
#include <QScrollArea>
#include <QGridLayout>

FilmInfo::FilmInfo(int mode_,const Film &film_, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FilmInfo)
{
    mode=mode_;
    ui->setupUi(this);
    film=film_;
    uiSetup();
    showFilmData();
    listProjections();

}

FilmInfo::~FilmInfo()
{
    delete ui;
}

void FilmInfo::on_pushButton_Back_clicked()
{
    QWidget::parentWidget()->QWidget::show();
    this->setAttribute(Qt::WA_DeleteOnClose,true);
    close();
}

void FilmInfo::openSeatSelection()
{
    if(!this->QObject::findChild<QDialog*>("SeatSelection",Qt::FindDirectChildrenOnly))
    {
        QObject *senderObj = sender();
        Hall hall;
        QStringList stringList= senderObj->objectName().split('_');
        QString fileName ="./Projekcije/Sale.txt";
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream stream(&file);
            while(!stream.QTextStream::atEnd())
            {
                stream >> hall;
                if(!QString::compare(hall.getHallName(),stringList.at(1)))
                        break;
            }
        }
        file.close();

        seatSelection = new SeatSelection(mode,hall,senderObj->objectName(),film,this);
        this->QWidget::hide();
        seatSelection->QWidget::show();
    }
    else
    {
        this->QWidget::hide();
        seatSelection->QWidget::show();
    }


}

void FilmInfo::uiSetup()
{
    gridLayout = new QGridLayout(ui->scrollAreaWidgetContents_2);
    gridLayout->setSizeConstraint(QLayout::SetFixedSize);
    gridLayout->setSpacing(15);
}

void FilmInfo::showFilmData()
{
    QImage image;

    image.load(film.getImgPath());
    ui->labelImage->setFixedSize(350,250);
    image = image.scaledToWidth(ui->labelImage->width(),Qt::SmoothTransformation);
    ui->labelImage->setPixmap(QPixmap::fromImage(image));

    ui->label_Name_2->setText(film.getName());
    ui->label_ProjectionsStart_2->setText(film.getProjectionsStart().toString("dd.MM.yyyy"));
    ui->label_Length_2->setText(QString::number(film.getLength())+" min");
    ui->label_Genre_2->setText(film.getGenre());
    ui->label_Year_2->setText(film.getYear());
    ui->label_Actors_2->setText(film.getActors());
    ui->label_Director_2->setText(film.getDirector());
    ui->label_Distributor_2->setText(film.getDistributor());
    ui->label_Country_2->setText(film.getCountry());
}
//prikaz projekcija u narednih 5 dana
void FilmInfo::listProjections()
{
    QDir dir = QDir("./Projekcije/"+film.getName());
    QStringList directories = dir.entryList(QDir::NoDotAndDotDot | QDir::AllEntries);

    int projectionCount = 0;
    int i =0;
    QFont f("Arial",32, QFont::Bold);
    QDate today = QDate::currentDate();
    QRegExp regex = QRegExp("^"+film.getName());

        foreach( const QString &string , directories)
        {
            if((string.contains(regex)) && (string.contains(today.toString("dd.MM.yyyy"))
            || string.contains(today.addDays(1).toString("dd.MM.yyyy")) || string.contains(today.addDays(2).toString("dd.MM.yyyy"))
            || string.contains(today.addDays(3).toString("dd.MM.yyyy")) || string.contains(today.addDays(4).toString("dd.MM.yyyy"))))
            {
                QStringList fileInfo = string.split('_');
                ButtonQLabel *labelFilm = new ButtonQLabel(this);

                labelFilm->setObjectName(string);
                labelFilm->setText(fileInfo.at(2)+" "+fileInfo.at(1)+" "+fileInfo.at(3));

                gridLayout->addWidget(labelFilm,i / 3,i % 3);

                projectionCount++;
                i++;
            QObject::connect(labelFilm,SIGNAL(labelClicked()),this,SLOT(openSeatSelection()));
            }

        }
        if(projectionCount==0)
        {
            QLabel *labelNoProjections = new QLabel(this);
            labelNoProjections->setText("NEMA PROJEKCIJA");
            ui->scrollArea->setAlignment(Qt::AlignCenter);
            gridLayout->addWidget(labelNoProjections);
            labelNoProjections->setFont(f);
        }
}
