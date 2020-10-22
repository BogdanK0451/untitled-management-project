#include "buttonqlabel.h"


ButtonQLabel::ButtonQLabel(QWidget* parent, Qt::WindowFlags f)
    : QLabel(parent) {

}

ButtonQLabel::~ButtonQLabel()
{

}

void ButtonQLabel::mousePressEvent(QMouseEvent* event) {
    emit labelClicked();
}

void ButtonQLabel::enterEvent(QEvent *event)
{
   setStyleSheet("QLabel { background-color : #01B9CB; }");
}

void ButtonQLabel::leaveEvent(QEvent *event)
{
   setStyleSheet("QLabel { background-color : #31363A; }");
}


