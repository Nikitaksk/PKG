#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButtonAddSegment, SIGNAL(clicked()), ui->graphicsView, SLOT(addSegmentSlot()));
    connect(ui->pushButtonDeleteSegment, SIGNAL(clicked()), ui->graphicsView, SLOT(deleteSegmentSlot()));

    connect(ui->pushButtonXSet, SIGNAL(clicked()), this, SLOT(setXSlot()));
    connect(ui->pushButtonYSet, SIGNAL(clicked()), this, SLOT(setYSlot()));

    connect(ui->graphicsView, SIGNAL(updateCoordSignal()), this, SLOT(updateCoordSlot()));

    /*
    connect(ui->graphicsView, SIGNAL(updateCoordSignal()), this, SLOT(updateCoordSlot()));

    connect(ui->pushButtonXSet, SIGNAL(clicked()), this, SLOT(setXSlot()));
    connect(ui->pushButtonYSet, SIGNAL(clicked()), this, SLOT(setYSlot()));*/
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateCoordSlot()
{
    if (!(ui->graphicsView->cutWin->p1->x == lastChangedX
          && ui->graphicsView->cutWin->p1->y == lastChangedY))
        ui->graphicsView->cutWin->p1->isPressed = false;

    if (!(ui->graphicsView->cutWin->p2->x == lastChangedX
          && ui->graphicsView->cutWin->p2->y == lastChangedY))
        ui->graphicsView->cutWin->p2->isPressed = false;

    for(auto& seg : ui->graphicsView->segments)
    {
        if (!(seg->p1->x == lastChangedX
              && seg->p1->y == lastChangedY))
            seg->p1->isPressed = false;

        if (!(seg->p2->x == lastChangedX
              && seg->p2->y == lastChangedY))
            seg->p2->isPressed = false;
    }

    ui->spinBoxXValue->setValue(lastChangedX);
    ui->spinBoxYValue->setValue(-lastChangedY);
}

void MainWindow::setXSlot()
{
    Point * point = ui->graphicsView->selectedPoint();

    if (point)
    {
        point->x = ui->spinBoxXSet->value();
        lastChangedX = point->x;
        updateCoordSlot();
    }
}

void MainWindow::setYSlot()
{
    Point * point = ui->graphicsView->selectedPoint();

    if (point)
    {
        point->y =  - ui->spinBoxYSet->value();
        lastChangedY = point->y;
        updateCoordSlot();
    }
}




void MainWindow::on_spinBoxYSet_valueChanged(int arg1)
{
    setYSlot();
}


void MainWindow::on_spinBoxXSet_valueChanged(int arg1)
{
    setXSlot();
}

