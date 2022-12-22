#include "cutwin.h"

CutWin::CutWin()
{
    p1 = new Point();
    p2 = new Point();

    p1->x = -100;
    p1->y = -100;
    p2->x = 100;
    p2->y = 100;
}

CutWin::~CutWin()
{
    delete p1;
    delete p2;
}

QRectF CutWin::boundingRect() const
{
    int width = abs(p1->x - p2->x);
    int height = abs(p1->y - p2->y);

    return QRectF(p1->x, p1->y,
                  width, height);
}

void CutWin::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing);


    QFont font("Courier New");

    font.setStyleHint(QFont::Monospace);
    font.setPixelSize(10);
    painter->setFont(font);
    painter->setBrush(QBrush(Qt::black, Qt::BDiagPattern));

    painter->drawText(3, 12, QString::number(0));
    painter->drawText(23, 12, QString::number(20));
    painter->drawText(-27, 12, QString::number(-20));



    painter->drawText(2, 33, QString::number(-20));
    painter->drawText(5, -13, QString::number(20));

    font.setPixelSize(16);
    font.setStyleHint(QFont::AnyStyle);
    painter->setFont(font);
    painter->drawText(280, -13, "X");
    painter->drawText(15, -310, "Y");



//    int counter = -13;
//    for (int i = 2 - 270; i < 270; i+=20.3) {
//        if(i > 0){
//            painter->drawText(i + 1, 14, QString::number(counter));
//            counter ++;
//        } else if (counter < -9){
//            painter->drawText(i + 5, 14, QString::number(counter));
//            counter ++;
//        } else {
//            painter->drawText(i + 1, 14, QString::number(counter));
//            counter ++;
//        }
//    }
//    counter = 15;
//    for (int i = -290; i < 330; i+=20) {
//        if(counter == 0){
//            counter--;
//        } else  if (counter < 0){
//            painter->drawText(2, i + 2, QString::number(counter));
//            counter--;
//        } else {
//            painter->drawText(5, i + 2, QString::number(counter));
//            counter--;
//        }

//    }

    QPen pen(Qt::black, SEGMENT_WIDTH);
    if (p1->isPressed || p2->isPressed)
        pen.setColor(Qt::red);
    painter->setPen(pen);

    if (p1->x > p2->x)
        p1->x = p2->x;

    if (p1->y > p2->y)
        p1->y = p2->y;

    int width = p2->x - p1->x;
    int height = p2->y - p1->y;

    painter->drawRect(p1->x, p1->y, width, height);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}
