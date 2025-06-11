#include "inputs.h"
#include <QtDebug>



CInputs::CInputs(QObject *parent)
    : QObject{parent}
{
    fuelqty = 0.0;
    last_fuelqty = 0.0;
    dt = 0.2;
    current_time = 0.0;
    decr = false;
}



void CInputs::timeIncrement()
{
    //simulate changing fuel level
    current_time += dt;

    if(current_time >= 5.0) {
        fuelqty = 1.0;
    }

    if(current_time >= 20.0) {
        fuelqty = 0.0;
        //current_time = 0.0;
    }

    if(last_fuelqty != fuelqty)
    {
        emit fuelValueChanged();
    }

    last_fuelqty = fuelqty;
}



void CInputs::timerEvent()
{
    timeIncrement();
}
