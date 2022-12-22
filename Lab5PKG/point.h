#ifndef POINT_H
#define POINT_H

#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

#include <constants.h>

extern qreal lastChangedX;
extern qreal lastChangedY;

class Point : public QGraphicsItem
{
public:
    bool isPressed = false;
    bool isMoved = false;

    Point();
    ~Point();
    Point(qreal, qreal, qreal);
    Point(qreal, qreal);

    qreal x = 0, y = 0, r = POINT_RADIUS;

    QRectF boundingRect() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // POINT_H
