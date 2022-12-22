#ifndef CUTWIN_H
#define CUTWIN_H

#include <QGraphicsItem>

#include "point.h"

class CutWin : public QGraphicsItem
{
public:
    Point *p1, *p2;

    CutWin();
    ~CutWin();

    QRectF boundingRect() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
};

#endif // CUTWIN_H
