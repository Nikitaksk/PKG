#include "paintingareawidget.h"
#include "ui_mainwindow.h"

PaintingAreaWidget::PaintingAreaWidget(QWidget *parent) : QWidget{parent} {
    repaint();
}

void PaintingAreaWidget::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    painter.setPen((QPen(Qt::black, 3)));

    if(this->currentImage.isNull()){
        painter.drawRect(0,0, size().width(), size().height());
        return;
    }

//    painter.drawRect(1,1, size().width() - 1, size().height() - 1);

    QRect target_rect;
    QImage image_to_draw;
    QRect image_widget_rect = QRect(0, 0, size().width(), size().height());

    float width_ratio  =  currentImage.width() / (float)this->width();
    float height_ratio = currentImage.height() / (float)this->height();

    if (width_ratio > height_ratio)
    {
        image_to_draw = this->currentImage.scaledToWidth(this->width());
        target_rect = QRect(
            image_widget_rect.x(), image_widget_rect.center().y() - image_to_draw.height() / 2,
            image_to_draw.width(), image_to_draw.height()
        );
    }
    else
    {
        image_to_draw = this->currentImage.scaledToHeight(this->height());
        target_rect = QRect(
            image_widget_rect.center().x() - image_to_draw.width() / 2, image_widget_rect.y(),
            image_to_draw.width(), image_to_draw.height()
        );
    }
    image_to_draw.convertTo(QImage::Format_Grayscale8);
    painter.drawImage(target_rect, image_to_draw);
}


void PaintingAreaWidget::setCurrentImage(QImage image){
    this->currentImage = image;
    repaint();

}
