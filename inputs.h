#ifndef INPUTS_H
#define INPUTS_H

#include <QObject>

class CInputs : public QObject
{
    qreal dt;
    qreal current_time;
    bool  decr;


    Q_OBJECT
public:
    explicit CInputs(QObject *parent = nullptr);

    qreal fuelqty;
    qreal last_fuelqty;
    void timeIncrement();

signals:
    void fuelValueChanged();


public slots:
    void timerEvent();
};

#endif // INPUTS_H
