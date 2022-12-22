#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <vector>
#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QProgressBar>
#include <QSlider>
#include <QDebug>
#include <QTextEdit>
#include <QLineEdit>
#include <QSpinBox>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

using namespace std;
class MainWindow : public QMainWindow
{
    Q_OBJECT
    QLabel *colorOutput;

    double xGlobalXYZ, yGlobalXYZ, zGlobalXYZ;

    double lGlobalLAB, aGlobalLAB, bGlobalLAB;

    double rGlobal, gGlobal, bGlobal;


    QLabel *XLabel;
    QLabel *YLabel;
    QLabel *ZLabel;
    QLabel *xyzBG;

    QLabel *HLabel;
    QLabel *SLabel;
    QLabel *VLabel;
    QLabel *hsvBG;

    QLabel *HLabelHSL;
    QLabel *SLabelHSL;
    QLabel *lLabelHSL;
    QLabel *hslBG;

    QLabel *cLabel;
    QLabel *mLabel;
    QLabel *yLabel;
    QLabel *kLabel;
    QLabel *cmykBG;

    QSlider *red_slider;
    QSlider *green_slider;
    QSlider *blue_slider;
    QSlider *alpha_slider;

    QSpinBox *gSpinBox;
    QSpinBox *bSpinBox;
    QSpinBox *rSpinBox;
    QLabel *hexValueLabel;
    QSpinBox *aSpinBox;

    QDoubleSpinBox *xSpinBox;
    QDoubleSpinBox *ySpinBox;
    QDoubleSpinBox *zSpinBox;

    QDoubleSpinBox *hSpinBox;
    QDoubleSpinBox *sSpinBox;
    QDoubleSpinBox *vSpinBox;

    QDoubleSpinBox *hSpinBoxHSL;
    QDoubleSpinBox *sSpinBoxHSL;
    QDoubleSpinBox *lSpinBoxHSL;

    QDoubleSpinBox *cSpinBox;
    QDoubleSpinBox *mSpinBox;
    QDoubleSpinBox *ySpinBoxCMYK;
    QDoubleSpinBox *kSpinBox;


    QPushButton* setColorButtons[24];


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    vector<double> rgbToXYZ(double r, double g, double b);
    vector<double> xyzToRGB(double x, double y, double z);
    vector<double> rgbToHSV(double r, double g, double b);
    vector<double> rgbToHSL(double r, double g, double b);
    vector<double> rgbToCMYK(double r, double g, double b);



private slots:
    void setValueColor();
    void setSliderPos();
    void setAlpha(int);

    void paletteButtonsFuns();
    void xyzChanged();

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
