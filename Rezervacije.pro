#-------------------------------------------------
#
# Project created by QtCreator 2018-05-24T15:21:11
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Rezervacije
TEMPLATE = app

RESOURCES += qdarkstyle/style.qrc
# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    employeemenu.cpp \
    addmovie.cpp \
    deletemovie.cpp \
    film.cpp \
    repertoire.cpp \
    filminfo.cpp \
    buttonqlabel.cpp \
    reservation.cpp \
    hall.cpp \
    addprojections.cpp \
    addhall.cpp \
    projection.cpp \
    seatselection.cpp \
    seat.cpp \
    price.cpp \
    src/emailaddress.cpp \
    src/mimeattachment.cpp \
    src/mimecontentformatter.cpp \
    src/mimefile.cpp \
    src/mimehtml.cpp \
    src/mimeinlinefile.cpp \
    src/mimemessage.cpp \
    src/mimemultipart.cpp \
    src/mimepart.cpp \
    src/mimetext.cpp \
    src/quotedprintable.cpp \
    src/smtpclient.cpp



HEADERS += \
        mainwindow.h \
    employeemenu.h \
    addmovie.h \
    deletemovie.h \
    film.h \
    repertoire.h \
    filminfo.h \
    buttonqlabel.h \
    reservation.h \
    hall.h \
    addprojections.h \
    addhall.h \
    projection.h \
    seatselection.h \
    seat.h \
    price.h \
    src/emailaddress.h \
    src/mimeattachment.h \
    src/mimecontentformatter.h \
    src/mimefile.h \
    src/mimehtml.h \
    src/mimeinlinefile.h \
    src/mimemessage.h \
    src/mimemultipart.h \
    src/mimepart.h \
    src/mimetext.h \
    src/quotedprintable.h \
    src/smtpclient.h \
    src/smtpexports.h \
    src/SmtpMime


FORMS += \
        mainwindow.ui \
    employeemenu.ui \
    addmovie.ui \
    deletemovie.ui \
    repertoire.ui \
    filminfo.ui \
    addprojections.ui \
    addhall.ui \
    seatselection.ui
