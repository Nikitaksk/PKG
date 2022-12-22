#ifndef SEGMENT_H
#define SEGMENT_H

#include <QGraphicsItem>

#include "point.h"

class Segment : public QGraphicsItem
{
public:
    Point *p1, *p2;

    Segment();
    ~Segment();

    QRectF boundingRect() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
};

#endif // SEGMENT_H
