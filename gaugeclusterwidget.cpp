#include "gaugeclusterwidget.h"
#include <QGridLayout>

CGaugeClusterWidget::CGaugeClusterWidget(QWidget *parent)
    : QWidget{parent}
{
    dispfuelqty = 0.0;

    inputs = new CInputs();


    QGridLayout *layout = new QGridLayout;
    fuel_gauge = new CGaugeWidget(this);
    lbl = new QLabel(this);
    lbl->setText(QString("def"));

    //layout->addWidget(fuel_gauge, 0, 0, Qt::AlignLeft);
    //layout->addWidget(lbl, 1, 0, Qt::AlignLeft);

    setLayout(layout);
    QTimer *timer = new QTimer(this);

    connect(timer, &QTimer::timeout, inputs, &CInputs::timerEvent);
    connect(timer, &QTimer::timeout, fuel_gauge, &CGaugeWidget::animate);
    connect(inputs, &CInputs::fuelValueChanged, this, &CGaugeClusterWidget::updateFuelLevel);

    qDebug() << "starting up";

    //QObject::connect(ledit1, &QLineEdit::editingFinished, this, &MainWindow::updateElasticity);
    //connect(inputs, &CInputs::fuelValueChanged, this, &MainWindow::setFuelQtyVal);
    //connect(gaw1, &CGaugeWidget::paintEvent, inputs, &CInputs::fuelValueChanged);

    int frame_dt = 50; // milliseconds
    timer->start(frame_dt);



}


void CGaugeClusterWidget::updateFuelLevel()
{
    //qDebug() << "fuel value changed";
    fuel_gauge->commandNeedlePosition(inputs->fuelqty);
}
