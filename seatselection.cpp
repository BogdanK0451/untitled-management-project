#include "seatselection.h"
#include "ui_seatselection.h"
#include "buttonqlabel.h"
#include "seat.h"
#include "reservation.h"
#include "./external_libs/SmtpMime" // old path "./src/SmtpMime"
#include <QChar>
#include <QMessageBox>
#include <QDebug>
#include <QtGlobal>
#include <cstdlib>

SeatSelection::SeatSelection(int mode_,const Hall &hall_, const QString &string, const Film &film_, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SeatSelection)
{
    ui->setupUi(this);
    mode=mode_;
    film=film_;
    hall=hall_;
    fileName=string;
    QStringList stringList= string.split('_');
    projectionDate =QDate::fromString(stringList.at(2),"dd.MM.yyyy");
    projectionTime =QTime::fromString(stringList.at(3),"hh:mm");
    ui->label_Info->hide();
    allowReservations=true;

    if(projectionTime.addSecs(-1800)<=QTime::currentTime() && projectionDate<=QDate::currentDate())
    {
        allowReservations=false;
        ui->label_Info->show();
    }
    ui->pushButton_Reserve->setEnabled(false);

    if (mode==0)
        ui->pushButton_Buy->setEnabled(false);
    else if(mode==1)
        ui->pushButton_Buy->setEnabled(true);

    QObject::connect(ui->lineEdit_Name,SIGNAL(textEdited(QString)),this,SLOT(textChanged()));

    countSelectedSeats=0;

    price.loadPrices();
    uiSetup();
    showSeats();

}

SeatSelection::~SeatSelection()
{
    delete ui;
}

void SeatSelection::uiSetup()
{
    ui->lineEdit_Email->hide();
    ui->label_Email->hide();
    ui->label_Seats->setText("Sedista: ");
    ui->label_Price->setText("Cena :");
    ui->label_Seats_2->setWordWrap(true);
    ui->label_Projection->setText(fileName);
    ui->label_Projection->setText(ui->label_Projection->text().replace('_','-'));

    gridLayout = new QGridLayout(ui->scrollAreaWidgetContents);
    gridLayout->setSizeConstraint(QLayout::SetFixedSize);
    gridLayout->setSpacing(5);
    ui->scrollArea->setAlignment(Qt::AlignCenter);
}

void SeatSelection::showSeats()
{
    QFile file("./Projekcije/"+film.getName()+"/"+fileName);

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        seats = stream.readAll();
    }
    int i=0;
    int j=0;
    int h=0;
    int n= seats.size();
    while(i<n)
    {

        if(seats.at(i) == '0')
        {
            Seat *seat= new Seat(this);
            loadImage(*seat,seats.at(i));
            gridLayout->addWidget(seat,j,h);
            seat->setObjectName(QString::number(h+1)+'_'+QString::number(j+1));
            seat->setState(0);
            QObject::connect(seat,SIGNAL(labelClicked()),this,SLOT(selectSeat()));
        }
        if(seats.at(i) == '1')
        {
            Seat *seat= new Seat(this);
            loadImage(*seat,seats.at(i));
            gridLayout->addWidget(seat,j,h);
            seat->setObjectName(QString::number(h+1)+'_'+QString::number(j+1));
            seat->setState(1);
            QObject::connect(seat,SIGNAL(labelClicked()),this,SLOT(seatTaken()));
        }
         h++;
        if(seats.at(i)=='\n')
        {
            j++;
            h=0;
        }
        i++;
    }
    allSeats= this->findChildren<Seat*>(QString());
}

void SeatSelection::on_pushButton_Back_clicked()
{
    QWidget::parentWidget()->QWidget::show();
    this->setAttribute(Qt::WA_DeleteOnClose,true);
    close();
}

void SeatSelection::addTicketsAndPrice()
{
    QString labelSeats;
    QList<Seat*>::const_iterator i=allSeats.constBegin();
    QList<Seat*>::const_iterator j=allSeats.constEnd();
    while(i!=j)
    {
        if ((*i)->getState()==2)
        {
            QStringList string = (*i)->objectName().split('_');
            labelSeats.append("Kolona "+string.at(0)+' '+string.at(1)+" Red\n");
        }
        i++;
    }
    ui->label_Seats_2->setText(labelSeats);
    ui->label_Price_2->setText(QString::number(countSelectedSeats)+" x "+QString::number(price.calcPrice(projectionDate))+" din");
}

void SeatSelection::seatTaken()
{
    QObject *senderObj =sender();
    QStringList string = senderObj->objectName().split('_');
    QMessageBox::information(this ,"Rezervacija karata","Sediste - Kolona "+string.at(0)+" Red "+string.at(1)+" je zauzeto");
}

void SeatSelection::selectSeat()
{
    Seat *senderObj =(Seat*) sender();
    QImage image;

    if (senderObj->getState()==0)
    {
        if (countSelectedSeats<6)
        {
            image.load("Slike/2.png");
            image = image.scaledToWidth(senderObj->width(),Qt::SmoothTransformation);
            senderObj->setPixmap(QPixmap::fromImage(image));
            senderObj->setState(2);
            countSelectedSeats++;
        }
        else
            QMessageBox::information(this,"Rezervacija","Ne moze se rezervisati vise od 6 mesta");
    }
    else if (senderObj->getState()==2)
    {
        image.load("Slike/1.png");
        image = image.scaledToWidth(senderObj->width(),Qt::SmoothTransformation);
        senderObj->setPixmap(QPixmap::fromImage(image));
        senderObj->setState(0);
        countSelectedSeats--;
    }
    addTicketsAndPrice();
}

void SeatSelection::loadImage(ButtonQLabel &seat, const QChar &chr)
{
    QImage image;
    if (chr=='0')
        image.load("Slike/1.png");
    else
        image.load("Slike/3.png");
    seat.setFixedSize(30,30);
    image = image.scaledToWidth(seat.width(),Qt::SmoothTransformation);
    seat.setPixmap(QPixmap::fromImage(image));
}

void SeatSelection::on_pushButton_Buy_clicked()
{
    if(countSelectedSeats>0)
    {
        QFile file("./Projekcije/"+film.getName()+"/"+fileName);

        if (file.open(QIODevice::ReadWrite | QIODevice::Text))
        {
            QTextStream stream(&file);

            QList<Seat*>::const_iterator i=allSeats.constBegin();
            QList<Seat*>::const_iterator j=allSeats.constEnd();
            int c=0;
            while(i!=j)
            {
                c++;
                if ((*i)->getState()==2 || (*i)->getState()==1)
                {
                    stream << "1";
                }
                else if ((*i)->getState()==0)
                {
                    stream << "0";
                }
                i++;
                if(c==hall.getCol())
                {
                    stream<<"\n";
                    c=0;
                }
            }
        }
        QMessageBox::information(this,"Uspeh","Uspesno kupljeno "+QString::number(countSelectedSeats)+" karata");
        QWidget::parentWidget()->QWidget::show();
        this->setAttribute(Qt::WA_DeleteOnClose,true);
        close();
    }
    else
        QMessageBox::information(this,"Neuspeh","Izaberite sedista");
}

void SeatSelection::on_pushButton_Reserve_clicked()
{
    if(countSelectedSeats>0)
    {
        Reservation reservation;
        srand(QTime::currentTime().msec());
        int id= rand()%10000;
        QFile file("./Projekcije/"+film.getName()+"/"+fileName);

        if (file.open(QIODevice::ReadWrite | QIODevice::Text))
        {
            QTextStream stream(&file);

            QList<Seat*>::const_iterator i=allSeats.constBegin();
            QList<Seat*>::const_iterator j=allSeats.constEnd();
            int c=0;
            int r=1;
            while(i!=j)
            {
                c++;
                if ((*i)->getState()==1)
                {
                    stream << "1";
                }
                else if ((*i)->getState()==2)
                {
                    reservation = Reservation(ui->lineEdit_Name->text(),film.getName(),hall.getHallName(),id,c,r,
                                              projectionDate,projectionTime,price.calcPrice(QDate::currentDate()));
                    reservation.saveReservation();
                    stream << "1";
                }
                else if ((*i)->getState()==0)
                {
                    stream << "0";
                }
                if(c==hall.getCol())
                {
                    r++;
                    stream<<"\n";
                    c=0;
                }
                i++;
            }
        }
        if(ui->checkBox_Email->isChecked())
            sendEmail(ui->lineEdit_Name->text(),ui->lineEdit_Email->text(),id);

        QMessageBox::information(this,"Uspeh","Uspesno rezervisano "+QString::number(countSelectedSeats)+" karata.\nVasa sifra je\n"+QString::number(id));

        QWidget::parentWidget()->QWidget::show();
        this->setAttribute(Qt::WA_DeleteOnClose,true);
        close();
    }
    else
        QMessageBox::information(this,"Neuspeh","Izaberite sedista");
}

void SeatSelection::sendEmail(const QString &name, const QString &email, int id)
{
        SmtpClient smtp("smtp.gmail.com", 465, SmtpClient::SslConnection);

        smtp.setUser("projectsendemail@gmail.com");
        smtp.setPassword("emailsender123");

        MimeMessage message;

        message.setSender(new EmailAddress("projectsendemail@gmail.com", "Bioskop"));
        message.addRecipient(new EmailAddress(email, name));
        message.setSubject("Rezervacija");

        MimeText text;

        text.setText(name+", broj vase rezervacije je,\n"+QString::number(id)+".");

        message.addPart(&text);

        smtp.connectToHost();
        smtp.login();
        smtp.sendMail(message);
        smtp.quit();
}

void SeatSelection::textChanged()
{
    bool buttonState = !ui->lineEdit_Name->text().isEmpty();

    if(buttonState && allowReservations)
        ui->pushButton_Reserve->setEnabled(true);

    else if(!buttonState)
        ui->pushButton_Reserve->setEnabled(false);
}

void SeatSelection::on_checkBox_Email_stateChanged(int arg1)
{
    if(ui->checkBox_Email->isChecked())
    {
         ui->lineEdit_Email->show();
         ui->label_Email->show();
    }
    else
    {
        ui->lineEdit_Email->hide();
        ui->label_Email->hide();
    }
}
