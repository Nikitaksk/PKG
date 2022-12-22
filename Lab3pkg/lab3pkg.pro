QT       += core gui

INCLUDEPATH += /opt/homebrew/Cellar/opencv/4.6.0_1/include/opencv4

LIBS += -L/opt/homebrew/Cellar/opencv/4.6.0_1/lib -lopencv_core -lopencv_imgproc -lopencv_imgcodecs

#LIBS += -L/opt/homebrew/Cellar/opencv/4.6.0_1/lib -lopencv_core -lsometypeofheader
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    filter_kernel.cpp\
    main.cpp \
    mainwindow.cpp \
    paintingareawidget.cpp

HEADERS += \
    filter_kernel.h\
    mainwindow.h \
    paintingareawidget.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
