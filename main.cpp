#include "mainwindow.h"
#include <QApplication>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    //stylesheet ucitavanje
    QFile f(":qdarkstyle/style.qss");
    if (!f.exists())
    {
        printf("Unable to set stylesheet, file not found\n");
    }
    else
    {
        f.open(QFile::ReadOnly | QFile::Text);
        QTextStream ts(&f);
        qApp->setStyleSheet(ts.readAll());
    }

    //dimenzije prozora
    int width = w.frameGeometry().width();
    int height = w.frameGeometry().height();

    QDesktopWidget display;

    //dimenzije ekrana
    int screenWidth = display.screen()->width();
    int screenHeight = display.screen()->height();
    w.setGeometry((screenWidth/2)-(width/2),(screenHeight/2)-(height/2),width,height);

    w.show();



    return a.exec();
}
