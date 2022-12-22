#include "mygraphicview.h"

MyGraphicView::MyGraphicView(QWidget *parent)
    : QGraphicsView(parent)
{

    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setAlignment(Qt::AlignCenter);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setRenderHints(QPainter::Antialiasing);

    this->setMinimumHeight(500);
    this->setMinimumWidth(500);

    scene = new QGraphicsScene();
    this->setScene(scene);

    grid = new QGraphicsItemGroup;
    scene->addItem(grid);
    createGrid();

    lines = new QGraphicsItemGroup;
    scene->addItem(lines);

    cutWin = new CutWin();
    scene->addItem(cutWin);
    scene->addItem(cutWin->p1);
    scene->addItem(cutWin->p2);

    int width = this->width();
    int height = this->height();
    scene->setSceneRect(-width / 2,-height/2,width,height);

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(slotAlarmTimer()));
    timer->start(50);
}

MyGraphicView::~MyGraphicView()
{

}


Point *MyGraphicView::selectedPoint()
{
    if (cutWin->p1->isPressed)
        return cutWin->p1;

    if (cutWin->p2->isPressed)
        return cutWin->p2;

    if (segments.size() > 0)
        for (auto& seg : segments)
        {
            if (seg->p1->isPressed)
                return seg->p1;

            if (seg->p2->isPressed)
                return seg->p2;
        }

    return nullptr;
}

void MyGraphicView::slotAlarmTimer() {
    int width = this->width();
    int height = this->height();

    deleteItemsFromGroup(lines);

    for (auto& seg : segments)
        cohenSutherland(seg->p1, seg->p2);

    scene->setSceneRect(-width / 2,-height/2,width,height);
    scene->update(-width / 2,-height/2,width,height);

    emit updateCoordSignal();
}

void MyGraphicView::addSegmentSlot() {
    Segment *newSegment = new Segment();

    segments.push_back(newSegment);
    scene->addItem(newSegment);
    scene->addItem(newSegment->p1);
    scene->addItem(newSegment->p2);
}

void MyGraphicView::deleteSegmentSlot() {
    Point *point = selectedPoint();

    if (point)
    {
        for (int i = 0; i < segments.size(); ++i)
            if (segments.at(i)->p1 == point
                    || segments.at(i)->p2 == point)
            {
                delete segments.at(i);
                segments.erase(segments.begin() + i);
                return;
            }
    }
}

void MyGraphicView::createGrid() {
    QPen penGrid(Qt::lightGray, 1);
    QPen penAxis(Qt::black, 3);




    int width = this->width();
    int height = this->height();

    int step = 20;


    for (int i = 0; i < width; i += step)
        grid->addToGroup(scene->addLine(i, -height / 2, i, height, penGrid));
    for (int i = -step; i > -width / 2; i -= step)
        grid->addToGroup(scene->addLine(i, -height / 2, i, height, penGrid));

    for (int i = 0; i < height; i += step)
        grid->addToGroup(scene->addLine(-width / 2, i, width, i, penGrid));
    for (int i = -step; i > -height / 2; i -= step)
        grid->addToGroup(scene->addLine(-width / 2, i, width, i, penGrid));




    grid->addToGroup(scene->addLine(0, -height / 2, 0, height, penAxis));
    grid->addToGroup(scene->addLine(-width / 2, 0, width, 0, penAxis));

    grid->addToGroup(scene->addLine(0, -height / 2 +   step/3 + -3, step / 2, -height / 2 + step, penAxis));
    grid->addToGroup(scene->addLine(0, -height / 2 +   step/3 + -3, -step / 2, -height / 2 + step, penAxis));

    grid->addToGroup(scene->addLine(width / 2 - step / 2 - 3, -step / 2, width / 2, 0, penAxis));
    grid->addToGroup(scene->addLine(width / 2 - step / 2 - 3, step / 2, width / 2, 0, penAxis));
}


void MyGraphicView::resizeEvent(QResizeEvent *event) {
    deleteItemsFromGroup(grid);
    createGrid();
    timer->start(50);
    QGraphicsView::resizeEvent(event);
}

void MyGraphicView::deleteItemsFromGroup(QGraphicsItemGroup *group) {
    foreach( QGraphicsItem *item, scene->items(group->boundingRect())) {
       if(item->group() == group )
          delete item;
    }
}

int MyGraphicView::getCode(Point * p) {
    return (((p->x < (cutWin->p1->x)) ? LEFT : 0) +
     ((p->x > cutWin->p2->x) ? RIGHT : 0) +
     ((p->y < cutWin->p1->y) ? BOT : 0) +
            ((p->y > cutWin->p2->y) ? TOP : 0));
}

void MyGraphicView::cohenSutherland(Point *A, Point *B) {
    int codeA, codeB, code;

    Point *a = new Point(A->x, A->y);
    Point *b = new Point(B->x, B->y);
    Point *c;

    codeA = getCode(a);
    codeB = getCode(b);

    QPen penBlack(Qt::black, SEGMENT_WIDTH);
    QPen penGreen(Qt::green, SEGMENT_WIDTH);
    QPen penRed(Qt::red, SEGMENT_WIDTH);

    lines->addToGroup(scene->addLine(a->x, a->y, b->x, b->y, penRed));

    while (codeA | codeB) {

        if (codeA & codeB)
        {
            lines->addToGroup(scene->addLine(a->x, a->y, b->x, b->y, penBlack));
            return;
        }

        if (codeA) {
            code = codeA;
            c = a;
        } else {
            code = codeB;
            c = b;
        }

        if (code & LEFT) {
            c->y += (a->y - b->y) * (cutWin->p1->x - c->x) / (a->x - b->x);
            c->x = cutWin->p1->x;
        } else if (code & RIGHT) {
            c->y += (a->y - b->y) * (cutWin->p2->x - c->x) / (a->x - b->x);
            c->x = cutWin->p2->x;
        }

        else if (code & BOT) {
            c->x += (a->x - b->x) * (cutWin->p1->y - c->y) / (a->y - b->y);
            c->y = cutWin->p1->y;
        } else if (code & TOP) {
            c->x += (a->x - b->x) * (cutWin->p2->y - c->y) / (a->y - b->y);
            c->y = cutWin->p2->y;
        }

        if (code == codeA)
        {
            a = c;
            codeA = getCode(a);
        } else
        {
            b = c;
            codeB = getCode(b);
        }
    }

    lines->addToGroup(scene->addLine(a->x, a->y, b->x, b->y, penGreen));
}
