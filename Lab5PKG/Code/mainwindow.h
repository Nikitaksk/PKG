#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QDebug>

#include "mygraphicview.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

using namespace std;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

public slots:
    void updateCoordSlot();

    void setXSlot();
    void setYSlot();
private slots:
    void on_spinBoxYSet_valueChanged(int arg1);
    void on_spinBoxXSet_valueChanged(int arg1);
};
#endif // MAINWINDOW_H
