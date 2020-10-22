#ifndef BUTTONQLABEL_H
#define BUTTONQLABEL_H

#include <QLabel>
#include <QWidget>
#include <Qt>
#include <QEvent>

class ButtonQLabel : public QLabel {
    Q_OBJECT

public:
    explicit ButtonQLabel(QWidget* parent = 0, Qt::WindowFlags f = Qt::WindowFlags());
    ~ButtonQLabel();


signals:
    void labelClicked();

protected:
    void mousePressEvent(QMouseEvent* event);
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;



};

#endif // BUTTONQLABEL_H
