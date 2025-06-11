#ifndef GAUGECLUSTERWIDGET_H
#define GAUGECLUSTERWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QLabel>
#include "gaugewidget.h"
#include "inputs.h"

class CGaugeClusterWidget : public QWidget
{
    Q_OBJECT

    CGaugeWidget *fuel_gauge;
    CInputs *inputs;
    QLabel *lbl;

    qreal dispfuelqty;

public:
    explicit CGaugeClusterWidget(QWidget *parent = nullptr);

signals:

public slots:
    void updateFuelLevel();
};

#endif // GAUGECLUSTERWIDGET_H
