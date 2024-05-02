#include "health.h"

Health::Health(int health, QGraphicsItem *parent) : QGraphicsRectItem(parent)
{
    set(health);
}

void Health::decrease(int value)
{
    health -= value;
    if (health >= 0)
    {
        hearts[health]->setVisible(false);
    }
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
    if (health != this->health)
    {
        for (int i = 0; i < hearts.size(); ++i)
        {
            delete hearts[i];
        }
        hearts.resize(health);
        for (int i = 0; i < health; ++i)
        {
            int divider = 40;
            QPixmap pixmap = QPixmap(":/images/heart.png");
            pixmap = pixmap.scaled(pixmap.size() / divider);
            hearts[i] = new QGraphicsPixmapItem(pixmap, this);
            hearts[i]->setPos(i * 55, 0);
        }
    }
    else
    {
        for (auto heart : hearts)
        {
            heart->setVisible(true);
        }
    }
    this->health = health;
}
