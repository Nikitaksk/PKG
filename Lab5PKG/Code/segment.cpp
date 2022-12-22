#include "segment.h"

Segment::Segment()
{
    p1 = new Point();
    p2 = new Point();
}

Segment::~Segment()
{
    delete p1;
    delete p2;
}

QRectF Segment::boundingRect() const
{
    return QRectF(p1->x, p1->y,
                  p2->x, p2->y);
}

void Segment::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
