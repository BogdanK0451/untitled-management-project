#include "seat.h"
#include "buttonqlabel.h"

Seat::Seat(QWidget* parent, Qt::WindowFlags f)
    : ButtonQLabel(parent) {

}

Seat::~Seat()
{

}

int Seat::getState() const
{
    return state;
}

void Seat::setState(int value)
{
    state = value;
}
