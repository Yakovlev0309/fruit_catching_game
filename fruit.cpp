#include "fruit.h"
#include "player.h"
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
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (QGraphicsItem *item : colliding_items)
    {
        if (typeid(*(item)) == typeid(Player))
        {
            // game->score->increase();
            emit fruitCatchedSignal();

            scene()->removeItem(this);
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
