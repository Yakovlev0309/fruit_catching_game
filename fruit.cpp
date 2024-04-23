#include "fruit.h"
#include <QTimer>
#include <QGraphicsScene>

Fruit::Fruit(QGraphicsItem *parent) : QGraphicsPixmapItem(parent)
{
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Fruit::move);

    timer->start(50);
}

void Fruit::move()
{
    setPos(x(), y() + 5);
    if (pos().y() > scene()->height())
    {
        scene()->removeItem(this);
        delete this;
    }
}
