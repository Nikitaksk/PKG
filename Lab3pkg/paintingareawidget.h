#ifndef PAINTINGAREAWIDGET_H
#define PAINTINGAREAWIDGET_H

#include <QWidget>
#include <QMainWindow>
#include <QDir>
#include <vector>
#include <QPaintEvent>
#include <QPainter>
#include <transformation.h>
#include <filter_kernel.h>

class PaintingAreaWidget : public QWidget
{
    Q_OBJECT
public:
    PaintingAreaWidget(QWidget *parent = nullptr);

//    QDir currentDirectory;
//    QString currentFilePath;
    QImage currentImage;


    void setCurrentImage(QImage image);

protected:
    void paintEvent(QPaintEvent*) override;


signals:



};

#endif // PAINTINGAREAWIDGET_H
