#include "point.h"

qreal lastChangedX = 0;
qreal lastChangedY = 0;

Point::Point() {
}

Point::~Point() {

}

Point::Point(qreal X, qreal Y, qreal R = POINT_RADIUS) {
    x = X;
    y = Y;
    r = R;
}

Point::Point(qreal X, qreal Y) {
    x = X;
    y = Y;
    r = POINT_RADIUS;
}

QRectF Point::boundingRect() const {
    return QRectF(x - r, y - r,
                  2 * r, 2 * r);
}

void Point::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    prepareGeometryChange();

    QPainterPath path;
    path.addEllipse(x - r, y - r, 1.5 * r,  1.5 *r);

    painter->setRenderHint(QPainter::Antialiasing);

    QPen pen(Qt::black, 1);
    painter->setPen(pen);
    if (isPressed)
        painter->fillPath(path, Qt::red);
    else
        painter->fillPath(path, Qt::black);
    painter->drawPath(path);

    painter->drawPath(path);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Point::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    isPressed = !isPressed;

    lastChangedX = x;
    lastChangedY = y;
}

void Point::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    if (isMoved)
        isPressed = false;

    isMoved = false;
}

void Point::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    if (event->pos().x() == x && event->pos().y() == y)
        isMoved = false;
    else
    {
        isMoved = true;
        x = event->pos().x();
        y = event->pos().y();

        lastChangedX = x;
        lastChangedY = y;
    }
}
