#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSlider>
#include <QPainter>
#include <QPaintEvent>
#include <QPaintEngine>
#include <QTextEdit>
#include <QAbstractSpinBox>
#include <iostream>
#include <cmath>
#include <QGridLayout>

using namespace std;

#define RED_SLIDER_STYLE   "QSlider::groove:horizontal {"                                                          \
                           "height: 10px;"                                                                         \
                           "background-color: qlineargradient(x1: 0, x2: 1, stop: 0 black, stop: 1 red);"          \
                           "border-radius: 4px;"                                                                   \
                           "}"                                                                                     \
                           "QSlider::handle:horizontal {"                                                          \
                           "background-color:#f3f3f3;"                                                             \
                           "border: 1px solid #5c5c5c;"                                                            \
                           "width: 18px;"                                                                          \
                           "margin: -2px 0;"                                                                       \
                           "border-radius: 3px;"                                                                   \
                           "};"

#define GREEN_SLIDER_STYLE "QSlider::groove:horizontal {"                                                          \
                           "height: 10px;"                                                                         \
                           "background-color: qlineargradient(x1: 0, x2: 1, stop: 0 black, stop: 1 chartreuse);"   \
                           "border-radius: 4px;"                                                                   \
                           "}"                                                                                     \
                           "QSlider::handle:horizontal {"                                                          \
                           "background-color: #f3f3f3;"                                                            \
                           "border: 1px solid #5c5c5c;"                                                            \
                           "width: 18px;"                                                                          \
                           "margin: -2px 0;"                                                                       \
                           "border-radius: 3px;"                                                                   \
                           "};"


#define BLUE_SLIDER_STYLE  "QSlider::groove:horizontal {"                                                          \
                           "height: 10px;"                                                                         \
                           "background-color:qlineargradient(x1:0, x2: 1, stop: 0 black,stop: 1 blue);"            \
                           "border-radius:4px;"                                                                    \
                           "}"                                                                                     \
                           "QSlider::handle:horizontal {"                                                          \
                            "background-color:#f3f3f3;"                                                            \
                            "border: 1px solid #5c5c5c;"                                                           \
                            "width: 18px;"                                                                         \
                            "margin: -2px 0;"                                                                      \
                            "border-radius: 3px;"                                                                  \
                           "};"


#define ALPHA_SLIDER_STYLE "QSlider::groove:horizontal {"                                                          \
                           "height: 10px;"                                                                         \
                           "background-color: qlineargradient(x1: 0, x2: 1, stop: 0 white, stop: 1 black);"        \
                           "border-radius: 4px;"                                                                   \
                           "}"                                                                                     \
                           "QSlider::handle:horizontal {"                                                          \
                           "background-color: #f3f3f3;"                                                            \
                           "border: 1px solid #5c5c5c;"                                                            \
                           "width: 18px;"                                                                          \
                           "margin: -2px 0;"                                                                       \
                           "border-radius: 3px;"                                                                   \
                           "};"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    MainWindow::setWindowTitle("Color Picker");

    this->setMinimumSize(700, 385);
    this->resize(700, 385);

    QGridLayout *mainLayout = new QGridLayout();

    colorOutput = new QLabel(this);
    red_slider   = new QSlider(this);
    green_slider = new QSlider(this);
    blue_slider  = new QSlider(this);
    alpha_slider = new QSlider(this);

    colorOutput->setMinimumSize(400, 250);


    red_slider   -> setOrientation(Qt::Horizontal);
    green_slider -> setOrientation(Qt::Horizontal);
    blue_slider  -> setOrientation(Qt::Horizontal);
    alpha_slider -> setOrientation(Qt::Horizontal);



    red_slider   -> setRange(0, 255);
    green_slider -> setRange(0, 255);
    blue_slider  -> setRange(0, 255);
    alpha_slider -> setRange(0, 100);

    red_slider   -> move(10, colorOutput->y() + colorOutput->height()      +  4);
    green_slider -> move(10, red_slider->y() + red_slider->height()   + 10);
    blue_slider  -> move(10, green_slider->y() + green_slider->height() + 10);
    alpha_slider -> move(10, blue_slider->y() + blue_slider->height()  + 10);



    rSpinBox = new QSpinBox(this);
    rSpinBox->setFixedSize(40,20);
    rSpinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);
    rSpinBox->setMaximum(255);
    rSpinBox->setMinimum(0);
    rSpinBox->setAlignment(Qt::AlignCenter);
    rSpinBox->setValue(blue_slider->value());
    rSpinBox->move(10+red_slider->width()+10,colorOutput->height()+16);
    rSpinBox->setStyleSheet("QLabel{border:2px solid ""red;""border-radius:2px;};");

    gSpinBox = new QSpinBox(this);
    gSpinBox->setFixedSize(40,20);
    gSpinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);
    gSpinBox->setMaximum(255);
    gSpinBox->setMinimum(0);
    gSpinBox->setAlignment(Qt::AlignCenter);
    gSpinBox->setValue(blue_slider->value());
    gSpinBox->move(10+red_slider->width()+10,rSpinBox->y()+rSpinBox->height()+10);
    gSpinBox->setStyleSheet("QLabel{border:2px solid ""chartreuse;""border-radius:2px;};");

    bSpinBox = new QSpinBox(this);
    bSpinBox->setFixedSize(40,20);
    bSpinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);
    bSpinBox->setMaximum(255);
    bSpinBox->setMinimum(0);
    bSpinBox->setAlignment(Qt::AlignCenter);
    bSpinBox->setValue(blue_slider->value());
    bSpinBox->move(10+red_slider->width()+10,gSpinBox->y()+gSpinBox->height()+10);
    bSpinBox->setStyleSheet("QLabel{border:2px solid ""blue;""border-radius:2px;};");

    aSpinBox = new QSpinBox(this);
    aSpinBox->setFixedSize(40,20);
    aSpinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);
    aSpinBox->setMaximum(255);
    aSpinBox->setMinimum(0);
    aSpinBox->setAlignment(Qt::AlignCenter);
    aSpinBox->setValue(blue_slider->value());
    aSpinBox->setGeometry(370,355, 50,50);
    aSpinBox->setStyleSheet("QLabel{border:2px solid "
                            "qlineargradient(x1:0, x2: 1, stop: 0 black,stop: 1 gray);"
                            "border-radius:2px;"
                            "font-size:16px;};");
    alpha_slider->setValue(100);
    aSpinBox->setValue(100);





    red_slider->setValue(0);
    green_slider->setValue(0);
    blue_slider->setValue(0);

    connect(red_slider, SIGNAL(valueChanged(int)),this, SLOT(setValueColor()));
    connect(green_slider, SIGNAL(valueChanged(int)),this, SLOT(setValueColor()));
    connect(blue_slider, SIGNAL(valueChanged(int)),this, SLOT(setValueColor()));
    connect(alpha_slider, SIGNAL(valueChanged(int)),this, SLOT(setAlpha(int)));




    red_slider->setStyleSheet(RED_SLIDER_STYLE);
    green_slider->setStyleSheet(GREEN_SLIDER_STYLE);
    blue_slider->setStyleSheet(BLUE_SLIDER_STYLE);
    alpha_slider->setStyleSheet(ALPHA_SLIDER_STYLE);




    connect(rSpinBox,SIGNAL(valueChanged(int)),this, SLOT(setSliderPos()));
    connect(gSpinBox,SIGNAL(valueChanged(int)),this, SLOT(setSliderPos()));
    connect(bSpinBox,SIGNAL(valueChanged(int)),this, SLOT(setSliderPos()));
    connect(aSpinBox,SIGNAL(valueChanged(int)),this, SLOT(setSliderPos()));






    xyzBG = new QLabel(this);
    xyzBG->setStyleSheet("QLabel{"
                         "border-style: solid;"
                         "border-width: 3px;"
                         "border-color: black;} "
                       );


    xSpinBox = new QDoubleSpinBox(this);
    ySpinBox = new QDoubleSpinBox(this);
    zSpinBox = new QDoubleSpinBox(this);

    xSpinBox->setDecimals(2);
    ySpinBox->setDecimals(2);
    zSpinBox->setDecimals(2);

    xSpinBox->setValue(0.001);
    xSpinBox->setGeometry(452,20,50,25);
    ySpinBox->setGeometry(452,50,50,25);
    zSpinBox->setGeometry(452,80,50,25);

    xSpinBox->setMaximum(120);
    ySpinBox->setMaximum(120);
    zSpinBox->setMaximum(120);

    zSpinBox->setMinimum(0.0);
    ySpinBox->setMinimum(0.0);
    xSpinBox->setMinimum(0.0);



    xSpinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ySpinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);
    zSpinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);

    connect(xSpinBox,SIGNAL(valueChanged(double)),this, SLOT(xyzChanged()));
    connect(ySpinBox,SIGNAL(valueChanged(double)),this, SLOT(xyzChanged()));
    connect(zSpinBox,SIGNAL(valueChanged(double)),this, SLOT(xyzChanged()));

    XLabel = new QLabel("X : ",this);
    YLabel = new QLabel("Y : ",this);
    ZLabel = new QLabel("Z : ",this);

    QFont font = XLabel->font();
    font.setPointSize(16);
    XLabel->setGeometry(430,20,70,25);
    XLabel->setFont(font);
    YLabel->setGeometry(430,50,70,25);
    YLabel->setFont(font);
    ZLabel->setGeometry(430,80,70,25);
    ZLabel->setFont(font);




    HLabel = new QLabel("H: ",this);
    SLabel = new QLabel("S : ",this);
    VLabel = new QLabel("V : ",this);


    font.setPointSize(16);
    HLabel->setGeometry(430,125,70,25);
    HLabel->setFont(font);
    SLabel->setGeometry(430,155,70,25);
    SLabel->setFont(font);
    VLabel->setGeometry(430,185,70,25);
    VLabel->setFont(font);

    hSpinBox = new QDoubleSpinBox(this);
    sSpinBox = new QDoubleSpinBox(this);
    vSpinBox = new QDoubleSpinBox(this);

    hSpinBox->setDecimals(2);
    sSpinBox->setDecimals(2);
    vSpinBox->setDecimals(2);

    hSpinBox->setGeometry(452,125,50,25);
    sSpinBox->setGeometry(452,155,50,25);
    vSpinBox->setGeometry(452,185,50,25);

    hSpinBox->setMinimum(0.0);
    sSpinBox->setMinimum(0.0);
    vSpinBox->setMinimum(0.0);


    hSpinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);
    sSpinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);
    vSpinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);

    hSpinBox->setMaximum(360.0);
    sSpinBox->setMaximum(100);
    vSpinBox->setMaximum(100);

    hsvBG = new QLabel(this);
    hsvBG->setStyleSheet("QLabel{"
                          "border-style: solid;"
                          "border-width: 3px;"
                          "border-color: black;} "
                           );
    hsvBG->setGeometry(420,120,110,100);

    HLabelHSL = new QLabel("H: ",this);
    SLabelHSL = new QLabel("S : ",this);
    lLabelHSL = new QLabel("L : ",this);



    hexValueLabel = new QLabel(this);
    hexValueLabel->setFixedSize(110,30);
    hexValueLabel->setAlignment(Qt::AlignCenter);
    hexValueLabel->move(420, 225);
    hexValueLabel->setStyleSheet("QLabel{border:2px solid "
                                "black;"
                                "border-radius:4px;font-size:20px;};");

    mainLayout->addWidget(hexValueLabel, 6, 2, 1, 2);

    font.setPointSize(16);

    HLabelHSL->setGeometry(545,20,70,25);
    HLabelHSL->setFont(font);
    SLabelHSL->setGeometry(545,50,70,25);
    SLabelHSL->setFont(font);
    lLabelHSL->setGeometry(545,80,70,25);
    lLabelHSL->setFont(font);

    hSpinBoxHSL = new QDoubleSpinBox(this);
    sSpinBoxHSL = new QDoubleSpinBox(this);
    lSpinBoxHSL = new QDoubleSpinBox(this);

    hSpinBoxHSL->setDecimals(2);
    sSpinBoxHSL->setDecimals(2);
    lSpinBoxHSL->setDecimals(2);

    hSpinBoxHSL->setGeometry(567,20,50,25);
    sSpinBoxHSL->setGeometry(567,50,50,25);
    lSpinBoxHSL->setGeometry(567,80,50,25);

    hSpinBoxHSL->setMinimum(0.0);
    sSpinBoxHSL->setMinimum(0.0);
    lSpinBoxHSL->setMinimum(0.0);


    hSpinBoxHSL->setButtonSymbols(QAbstractSpinBox::NoButtons);
    sSpinBoxHSL->setButtonSymbols(QAbstractSpinBox::NoButtons);
    lSpinBoxHSL->setButtonSymbols(QAbstractSpinBox::NoButtons);

    hSpinBoxHSL->setMaximum(360.0);
    sSpinBoxHSL->setMaximum(100);
    lSpinBoxHSL->setMaximum(100);

    hslBG = new QLabel(this);
    hslBG->setStyleSheet("QLabel{"
                          "border-style: solid;"
                          "border-width: 3px;"
                          "border-color: black;} "
                           );
    hslBG->setGeometry(535,15,110,100);


    cLabel = new QLabel("C: ",this);
    mLabel = new QLabel("M : ",this);
    yLabel = new QLabel("Y : ",this);
    kLabel = new QLabel("K : ",this);


    font.setPointSize(16);
    cLabel->setGeometry(545,130,70,25);
    cLabel->setFont(font);
    mLabel->setGeometry(545,160,70,25);
    mLabel->setFont(font);
    yLabel->setGeometry(545,190,70,25);
    yLabel->setFont(font);
    kLabel->setGeometry(545,220,70,25);
    kLabel->setFont(font);

    cSpinBox = new QDoubleSpinBox(this);
    mSpinBox = new QDoubleSpinBox(this);
    ySpinBoxCMYK = new QDoubleSpinBox(this);
    kSpinBox = new QDoubleSpinBox(this);

    cSpinBox->setDecimals(2);
    mSpinBox->setDecimals(2);
    ySpinBoxCMYK->setDecimals(2);
    kSpinBox->setDecimals(2);

    cSpinBox->setGeometry(567,130,50,25);
    mSpinBox->setGeometry(567,160,50,25);
    ySpinBoxCMYK->setGeometry(567,190,50,25);
    kSpinBox->setGeometry(567,220,50,25);

    cSpinBox->setMinimum(0.0);
    mSpinBox->setMinimum(0.0);
    ySpinBoxCMYK->setMinimum(0.0);
    kSpinBox->setMinimum(0.0);

    cSpinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);
    mSpinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ySpinBoxCMYK->setButtonSymbols(QAbstractSpinBox::NoButtons);
    kSpinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);

    cSpinBox->setMaximum(100);
    mSpinBox->setMaximum(100);
    ySpinBoxCMYK->setMaximum(100);
    kSpinBox->setMaximum(100);


    cmykBG = new QLabel(this);
    cmykBG->setStyleSheet("QLabel{"
                          "border-style: solid;"
                          "border-width: 3px;"
                          "border-color: black;} "
                           );
    cmykBG->setGeometry(535,120,110,135);



    QGridLayout * palette = new QGridLayout;
    for(int i = 0; i < 6; i++){
        setColorButtons[i] = new QPushButton(this);
        setColorButtons[i]->setGeometry(420 + 40*i, 265, 25, 25);
        setColorButtons[i]->setStyleSheet("QPushButton {"
                                          "background-color:"
                                          "rgb(" + QString::number(100 + 25 * i) + "," + QString::number(30 + i) + "," + QString::number(255 - 42.5 * i) + ");"
                                          "border-radius: 2px;"
                                          "}");
        setColorButtons[i]->setObjectName(QString::number(i));
        connect(setColorButtons[i],SIGNAL(clicked()),this, SLOT(paletteButtonsFuns()));

        palette->addWidget(setColorButtons[i], 0, i);

        setColorButtons[i+6] = new QPushButton(this);
        setColorButtons[i+6]->setGeometry(420 + 40*i, 305, 25, 25);
        setColorButtons[i+6]->setStyleSheet("QPushButton {"
                                          "background-color:"
                                          "rgb(" + QString::number(255 - 42.5 * i) + "," + QString::number(100 + 25 * i) + "," + QString::number(30+i) + ");"
                                          "border-radius: 2px;"
                                          "}");
        setColorButtons[i+6]->setObjectName(QString::number(i + 6));
        connect(setColorButtons[i+6],SIGNAL(clicked()),this, SLOT(paletteButtonsFuns()));
        palette->addWidget(setColorButtons[i + 6], 1, i);

        setColorButtons[i+12] = new QPushButton(this);
        setColorButtons[i+12]->setGeometry(420 + 40*i, 350, 25, 25);
        setColorButtons[i+12]->setStyleSheet("QPushButton {"
                                          "background-color:"
                                          "rgb(" + QString::number(42.5*i) + "," + QString::number(255) + "," + QString::number(255 - 42.5 * i) + ");"
                                          "border-radius: 2px;"
                                          "}");
        setColorButtons[i+12]->setObjectName(QString::number(i + 12));
        connect(setColorButtons[i+12],SIGNAL(clicked()),this, SLOT(paletteButtonsFuns()));
        palette->addWidget(setColorButtons[i + 12], 2, i);

        setColorButtons[i+18] = new QPushButton(this);
        setColorButtons[i+18]->setGeometry(420 + 40*i, 350, 25, 25);
        setColorButtons[i+18]->setStyleSheet("QPushButton {"
                                          "background-color:"
                                          "rgb(" + QString::number(42.5*i) + "," + QString::number(125) + "," + QString::number(42.5 * i) + ");"
                                          "border-radius: 2px;"
                                          "}");
        setColorButtons[i+18]->setObjectName(QString::number(i + 18));
        connect(setColorButtons[i+18],SIGNAL(clicked()),this, SLOT(paletteButtonsFuns()));
        palette->addWidget(setColorButtons[i + 18], 3, i);
    }

    mainLayout->addWidget(colorOutput,0, 0, 7 , 2);
    mainLayout->setContentsMargins(10, 10, 10, 10);
    mainLayout->setSpacing(10);

    mainLayout->addWidget(red_slider, 8, 0);
    mainLayout->addWidget(green_slider, 9, 0);
    mainLayout->addWidget(blue_slider, 10, 0);
    mainLayout->addWidget(alpha_slider, 11, 0);

    mainLayout->addWidget(rSpinBox, 8, 1);
    mainLayout->addWidget(gSpinBox, 9, 1);
    mainLayout->addWidget(bSpinBox, 10, 1);
    mainLayout->addWidget(aSpinBox, 11, 1);

    mainLayout->addWidget(xyzBG, 0, 2 , 3, 2);
    mainLayout->addWidget(XLabel, 0, 2 ,  {Qt::AlignRight, Qt::AlignVCenter});
    mainLayout->addWidget(xSpinBox, 0, 3, {Qt::AlignLeft, Qt::AlignVCenter});
    mainLayout->addWidget(YLabel, 1, 2  , {Qt::AlignRight, Qt::AlignVCenter});
    mainLayout->addWidget(ySpinBox, 1, 3, {Qt::AlignLeft, Qt::AlignVCenter});
    mainLayout->addWidget(ZLabel, 2, 2  , {Qt::AlignRight, Qt::AlignVCenter});
    mainLayout->addWidget(zSpinBox, 2, 3, {Qt::AlignLeft, Qt::AlignVCenter});

    mainLayout->addWidget(hsvBG, 3, 2 , 3, 2);
    mainLayout->addWidget(HLabel, 3, 2  ,Qt::AlignRight);
    mainLayout->addWidget(hSpinBox, 3, 3,Qt::AlignLeft);
    mainLayout->addWidget(SLabel, 4, 2  ,Qt::AlignRight);
    mainLayout->addWidget(sSpinBox, 4, 3,Qt::AlignLeft);
    mainLayout->addWidget(VLabel, 5, 2  ,Qt::AlignRight);
    mainLayout->addWidget(vSpinBox, 5, 3,Qt::AlignLeft);

    mainLayout->addWidget(hslBG, 0, 4 , 3, 2);
    mainLayout->addWidget(HLabelHSL, 0, 4  , Qt::AlignRight);
    mainLayout->addWidget(hSpinBoxHSL, 0, 5, Qt::AlignLeft);
    mainLayout->addWidget(SLabelHSL, 1, 4  , Qt::AlignRight);
    mainLayout->addWidget(sSpinBoxHSL, 1, 5, Qt::AlignLeft);
    mainLayout->addWidget(lLabelHSL, 2, 4  , Qt::AlignRight);
    mainLayout->addWidget(lSpinBoxHSL, 2, 5, Qt::AlignLeft);

    mainLayout->addWidget(cmykBG, 3, 4 , 4, 2);
    mainLayout->addWidget(cLabel, 3, 4      , Qt::AlignRight);
    mainLayout->addWidget(cSpinBox, 3, 5    , Qt::AlignLeft);
    mainLayout->addWidget(mLabel, 4, 4      , Qt::AlignRight);
    mainLayout->addWidget(mSpinBox, 4, 5    , Qt::AlignLeft);
    mainLayout->addWidget(yLabel, 5, 4      , Qt::AlignRight);
    mainLayout->addWidget(ySpinBoxCMYK, 5, 5, Qt::AlignLeft);
    mainLayout->addWidget(kLabel, 6, 4      , Qt::AlignRight);
    mainLayout->addWidget(kSpinBox, 6, 5    , Qt::AlignLeft);

    mainLayout->addLayout(palette, 8, 2, 4, 4);

    setValueColor();

    centralWidget()->setLayout(mainLayout);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::setSliderPos(){
    red_slider->setValue(rSpinBox->value());
    blue_slider->setValue(bSpinBox->value());
    green_slider->setValue(gSpinBox->value());
    alpha_slider->setValue(aSpinBox->value());
}




void MainWindow::setValueColor()
{
    int r, g, b, a;
    r = red_slider->value();
    g = green_slider->value();
    b = blue_slider->value();
    a = alpha_slider->value();

    rSpinBox->setValue(r);
    gSpinBox->setValue(g);
    bSpinBox->setValue(b);
    aSpinBox->setValue(a);

    vector<double> tempV;
    tempV = rgbToXYZ(r, g, b);

    xSpinBox->setValue(rgbToXYZ(r, g, b)[0]);
    ySpinBox->setValue(rgbToXYZ(r, g, b)[1]);
    zSpinBox->setValue(rgbToXYZ(r, g, b)[2]);

    hSpinBox->setValue(rgbToHSV(r, g, b)[0]);
    sSpinBox->setValue(rgbToHSV(r, g, b)[1]);
    vSpinBox->setValue(rgbToHSV(r, g, b)[2]);

    hSpinBoxHSL->setValue(rgbToHSL(r, g, b)[0]);
    sSpinBoxHSL->setValue(rgbToHSL(r, g, b)[1]);
    lSpinBoxHSL->setValue(rgbToHSL(r, g, b)[2]);

    cSpinBox->setValue(rgbToCMYK(r, g, b)[0]);
    mSpinBox->setValue(rgbToCMYK(r, g, b)[1]);
    ySpinBoxCMYK->setValue(rgbToCMYK(r, g, b)[2]);
    kSpinBox->setValue(rgbToCMYK(r, g, b)[3]);


    colorOutput->setStyleSheet("QLabel {"
                           "background-color:"
                           "rgb(" + QString::number(r) + "," + QString::number(g) + "," + QString::number(b) + ");"
                           "border-radius: 5px;"
                           "}");

    alpha_slider->setStyleSheet("QSlider::groove:horizontal{"
                           "height: 10px;"
                           "background-color: qlineargradient(x1: 0, x2: 1, stop: 0 white, stop: 1 rgb(" + QString::number(r) + "," + QString::number(g) + "," + QString::number(b) + "));"
                           "border-radius: 4px;"
                           "}"
                           "QSlider::handle:horizontal {"
                           "background-color: #f3f3f3;"
                           "border: 1px solid #5c5c5c;"
                           "width: 18px;"
                           "margin: -2px 0;"
                           "border-radius: 3px;"
                           "};");

    xyzBG->setStyleSheet("QLabel{"
                         "border-style: solid;"
                         "border-width: 3px;"
                         "border-radius:4px;"
                         "border-color: rgb(" + QString::number(r) + "," + QString::number(g) + "," + QString::number(b) + ");"
                         "};" );

    hsvBG->setStyleSheet("QLabel{"
                         "border-style: solid;"
                         "border-width: 3px;"
                         "border-radius:4px;"
                         "border-color: rgb(" + QString::number(r) + "," + QString::number(g) + "," + QString::number(b) + ");"
                         "};" );

    hslBG->setStyleSheet("QLabel{"
                         "border-style: solid;"
                         "border-width: 3px;"
                         "border-radius:4px;"
                         "border-color: rgb(" + QString::number(r) + "," + QString::number(g) + "," + QString::number(b) + ");"
                         "};" );

    cmykBG->setStyleSheet("QLabel{"
                         "border-style: solid;"
                         "border-width: 3px;"
                         "border-radius:4px;"
                         "border-color: rgb(" + QString::number(r) + "," + QString::number(g) + "," + QString::number(b) + ");"
                         "};" );

    QString r1 = QString::number(r, 16);
    QString g1 = QString::number(g, 16);
    QString b1 = QString::number(b, 16);

    if (r <= 15) {
        r1 = "0" + r1;
    }
    if (g <= 15) {
        g1 = "0" + g1;
    }
    if (b <= 15) {
        b1 = "0" + b1;
    }

    r1 = r1.toUpper();
    g1 = g1.toUpper();
    b1 = b1.toUpper();

    hexValueLabel->setText("#" + r1 + g1 + b1);
    hexValueLabel->setStyleSheet("QLabel{border:3px solid "
                                 "black;"
                                 "border-radius:4px;font-size:20px;"
                                 "border-color: rgb(" + QString::number(r) + "," + QString::number(g) + "," + QString::number(b) + ");"
                                 "};");


}

void MainWindow::setAlpha(int a)
{
    int r, g, b;
    float f = 0.0f;
    r = red_slider->value();
    g = green_slider->value();
    b = blue_slider->value();

    a = alpha_slider->value();
    aSpinBox->setValue(a);

    f = (float)a / 100;

    QString tempAlphaValue;
    tempAlphaValue.setNum(f);


    colorOutput->setStyleSheet("QLabel {"
                           "background-color:"
                           "rgba(" + QString::number(r) + "," + QString::number(g) + "," + QString::number(b) + ", " + QString::number(f) + ");"
                           "border-radius: 5px;"
                           "}");
}


vector<double> MainWindow::rgbToXYZ(double r, double g, double b) {
    vector<double> tempV(3);
    tempV.clear();

    double tempR = (r / 255.0);
    double tempG = (g / 255.0);
    double tempB = (b / 255.0);

    if (tempR > 0.04045) {
        tempR = (tempR + 0.055) / 1.055;
        tempR = pow(tempR, 2.4);
    } else {
        tempR = tempR / 12.92;
    }

    if (tempG > 0.04045) {
        tempG = (tempG + 0.055) / 1.055;
        tempG = pow(tempG, 2.4);
    } else {
        tempG = tempG / 12.92;
    }

    if (tempB > 0.04045) {
        tempB = (tempB + 0.055) / 1.055;
        tempB = pow(tempB, 2.4);
    } else {
        tempB = tempB / 12.92;
    }

    double X = (tempR * 0.4124 + tempG * 0.3576 + tempB * 0.1805) * 100;
    double Y = (tempR * 0.2126 + tempG * 0.7152 + tempB * 0.0722) * 100;
    double Z = (tempR * 0.0193 + tempG * 0.1192 + tempB * 0.9505) * 100;

    tempV.push_back(X);
    tempV.push_back(Y);
    tempV.push_back(Z);

    return tempV;
}

vector<double> MainWindow::rgbToHSV(double r, double g, double b) {
    double hue = 0.0, saturation = 0.0, value = 0.0;

    double maximum = max(max(r, g), b);
    double minimum = min(min(r, g), b);
    double delta = maximum - minimum;

    vector<double> tempV;
    if(delta > 0) {
        if(maximum == r) {
            hue = 60 * (fmod(((g - b) / delta), 6));
        } else if(maximum == g) {
            hue = 60 * (((b - r) / delta) + 2);
        } else if(maximum == b) {
            hue = 60 * (((r - g) / delta) + 4);
        }
        if(maximum > 0) {
            saturation = delta / maximum;
        } else {
            saturation = 0;
        } value = maximum;

    } else {
        hue = 0;
        saturation = 0;
        value = maximum;
    }
    if(hue < 0) {
        hue = 360 + hue;
    }
    value = value/2.55;

    tempV.push_back(hue);
    tempV.push_back(saturation*100);
    tempV.push_back(value);

    return tempV;
}
vector<double> MainWindow::rgbToHSL(double r, double g, double b) {
    double hue = 0.0, saturation = 0.0, lightness= 0.0;
    vector<double> tempV;

        r = r / 255.0;
        g = g / 255.0;
        b = b / 255.0;


        float minimum = min(min(r, g), b);
        float maximum = max(max(r, g), b);
        float delta = maximum - minimum;

        lightness = (maximum + minimum) / 2;

        if (delta == 0) {
            hue = 0;
            saturation = 0.0;
        } else {
            saturation = (lightness <= 0.5) ? (delta / (maximum + minimum)) : (delta / (2 - maximum - minimum));

            if (r == maximum)
            {
                hue = ((g - b) / 6) / delta;
            }
            else if (g == maximum)
            {
                hue = (1.0 / 3) + ((b - r) / 6) / delta;
            }
            else
            {
                hue = (2.0f/ 3) + ((r - g) / 6) / delta;
            }

            if (hue < 0)
                hue += 1;
            if (hue > 1)
                hue -= 1;

           hue = (int)(hue * 360);
        }
        tempV.push_back(hue);
        tempV.push_back(saturation * 100);
        tempV.push_back(lightness * 100);

    return tempV;
}
vector<double> MainWindow::rgbToCMYK(double r, double g, double b) {
    vector<double> tempV;

    r = r / 255.0;
    g = g / 255.0;
    b = b / 255.0;

    if  (r == 0 & g == 0 & b == 0){
        tempV = {0.0,0.0,0.0,1.0};
        return tempV;
    }

    double k = 1 - max(max(r, g), b);
    double c = (1 - r - k) / (1 - k);
    double m = (1 - g - k) / (1 - k);
    double y = (1 - b - k) / (1 - k);

    tempV.push_back(c);
    tempV.push_back(m);
    tempV.push_back(y);
    tempV.push_back(k);

    return tempV;
}

constexpr array<array<long double, 3>, 3> xyz_to_rgb_matrix = {{
    {  3.2406, -1.5372, -0.4986 },
    { -0.9689,  1.8758,  0.0415 },
    {  0.0557, -0.2040,  1.0570 },
}};

long double xyz_to_rgb_function(long double x) {
    if (x >= 0.0031308) {
        return 1.055 * pow(x, 1 / 2.4) - 0.055;
    } else {
        return 12.92 * x;
    }
}
array<long double, 3> xyz_to_rgb(array<long double, 3> xyz) {

    array<long double, 3> result = {0, 0, 0};

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            result[i] += xyz_to_rgb_matrix[i][j] * xyz[j] / 100;
        }
        result[i] = xyz_to_rgb_function(result[i]) * 255;
    }

    return result;

}
void MainWindow::xyzChanged(){
    array<long double, 3> xyz = {xSpinBox->value(), ySpinBox->value(), zSpinBox->value()};
    array<long double, 3> currentRGB = xyz_to_rgb(xyz);


//    rSpinBox->setValue((int) currentRGB[0]);
//    bSpinBox->setValue((int) currentRGB[1]);
//    gSpinBox->setValue((int) currentRGB[2]);

}

void MainWindow::paletteButtonsFuns(){
    int buttonNumber = stoi(((QAbstractButton * ) sender()) -> objectName().toStdString());
    if  (buttonNumber <= 5){
        red_slider->setValue(100 + 25 * buttonNumber);
        blue_slider->setValue(255 - 42.5 * buttonNumber);
        green_slider->setValue(30 + buttonNumber);
    }
    if (buttonNumber > 5 && buttonNumber <= 11){
        buttonNumber-=6;
        red_slider->setValue(255 - 42.5 * buttonNumber);
        blue_slider->setValue(30 + buttonNumber);
        green_slider->setValue(100 + 25 * buttonNumber);
    }
    if (buttonNumber > 11 && buttonNumber <= 17){
        buttonNumber-=12;
        red_slider->setValue(42.5 * buttonNumber);
        blue_slider->setValue(255 - 42.5 * buttonNumber);
        green_slider->setValue(255 );
    }
    if(buttonNumber > 17){
        buttonNumber-=18;
        red_slider->setValue(42.5 * buttonNumber);
        blue_slider->setValue(42.5 * buttonNumber);
        green_slider->setValue(125);
    }

}
