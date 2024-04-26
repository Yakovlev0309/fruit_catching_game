#include "health.h"

Health::Health(int health, QGraphicsItem *parent) : QGraphicsRectItem(parent)
{
    this->health = health;
    hearts.reserve(health);
    for (int i = 0; i < health; ++i)
    {
        int divider = 40;
        QPixmap pixmap = QPixmap(":/images/heart.png");
        pixmap = pixmap.scaled(pixmap.size() / divider);
        hearts.push_back(new QGraphicsPixmapItem(pixmap, this));
        hearts[i]->setPos(i * 55, 0);
    }
}

void Health::decrease(int value)
{
    health -= value;
    hearts[health]->hide(); // FIXME index out of range
    if (health <= 0)
    {
        emit gameOverSignal();
    }
}

int Health::get()
{
    return health;
}

void Health::set(int health)
{
    this->health = health;
}
