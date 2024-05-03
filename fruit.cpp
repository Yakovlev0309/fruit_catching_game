#include "fruit.h"
#include "player.h"
#include <QGraphicsScene>

Fruit::Fruit(QGraphicsItem *parent) : QGraphicsPixmapItem(parent)
{
    move_timer = new QTimer(this);
    connect(move_timer, &QTimer::timeout, this, &Fruit::move);
    move_timer->start(50);
}

void Fruit::start()
{
    move_timer->start();
}

void Fruit::stop()
{
    move_timer->stop();
}

void Fruit::move()
{
    if (!move_timer->isActive())
        return;

    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (QGraphicsItem *item : colliding_items)
    {
        if (typeid(*(item)) == typeid(Player))
        {            
            scene()->removeItem(this);
            emit fruitCatchedSignal();
            delete this;

            return;
        }
    }

    setPos(x(), y() + 5);
    if (pos().y() > scene()->height())
    {
        scene()->removeItem(this);
        delete this;
    }
}
