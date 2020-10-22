#ifndef SEAT_H
#define SEAT_H
#include "buttonqlabel.h"


class Seat : public ButtonQLabel {
public:
    explicit Seat(QWidget* parent = 0, Qt::WindowFlags f = Qt::WindowFlags());
    ~Seat();

    int getState() const;
    void setState(int value);

private:
    int state;
};

#endif // SEAT_H
