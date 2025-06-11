#include "mainwindow.h"
#include "./ui_mainwindow.h"



#include "gaugeclusterwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Cobra Dashboard");


    QPixmap bkgnd("..\\..\\data\\eagle_river_small.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    setPalette(palette);

    QWidget *mainWidget = new CGaugeClusterWidget();


    setCentralWidget(mainWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::setFuelQtyVal()
{
    //lbl->setText(QString::number(inputs->fuelqty));
}
