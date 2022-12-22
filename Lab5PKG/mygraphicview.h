#ifndef MYGRAPHICVIEW_H
#define MYGRAPHICVIEW_H

#define LEFT  1  // 0001
#define RIGHT 2  // 0010
#define BOT   4  // 0100
#define TOP   8  // 1000

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItemGroup>
#include <QTimer>
#include <cmath>
#include <QVector>

#include "point.h"
#include "segment.h"
#include "cutwin.h"

using namespace std;

class MyGraphicView : public QGraphicsView
{
    Q_OBJECT

public:
    QVector<Segment*> segments;
    CutWin *cutWin;

    Point *selectedPoint();

    explicit MyGraphicView(QWidget *parent = 0);
    ~MyGraphicView();

signals:
    void updateCoordSignal();

private slots:
    void slotAlarmTimer();

public slots:
    void addSegmentSlot();
    void deleteSegmentSlot();

private:
    QGraphicsScene* scene;
    QTimer* timer;

    QGraphicsItemGroup* grid;
    QGraphicsItemGroup* lines;

    void createGrid();

    void resizeEvent(QResizeEvent *event);
    void deleteItemsFromGroup(QGraphicsItemGroup *group_1);

    int getCode(Point *);
    void cohenSutherland (Point *a, Point *b);
};

#endif // MYGRAPHICVIEW_H
