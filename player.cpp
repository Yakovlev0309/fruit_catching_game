#include "player.h"
#include <QKeyEvent>
#include <QGraphicsScene>

Player::Player(QGraphicsItem *parent) : QGraphicsPixmapItem(parent)
{
    step = 10;

    int divider = 35;
    right_pixmap = QPixmap(":/images/character.png");
    right_pixmap = right_pixmap.scaled(right_pixmap.size() / divider);
    setPixmap(right_pixmap);

    left_pixmap = QPixmap(":/images/character_flipped.png");
    left_pixmap = left_pixmap.scaled(right_pixmap.size());

    image_size = right_pixmap.size();
    current_direction = PlayerDirection::RIGHT;
}

void Player::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Left:
        if (pos().x() + image_size.width() / 2 > 0)
        {
            flipImage(PlayerDirection::LEFT);
            setPos(x() - step, y());
        }
        break;
    case Qt::Key_Right:
        if (pos().x() + image_size.width() / 2 < scene()->width())
        {
            flipImage(PlayerDirection::RIGHT);
            setPos(x() + step, y());
        }
        break;
    }
}

void Player::flipImage(const PlayerDirection &direction)
{
    if (current_direction != direction)
    {
        if (direction == PlayerDirection::LEFT)
        {
            setPixmap(left_pixmap);
        }
        else
        {
            setPixmap(right_pixmap);
        }
        current_direction = direction;
    }
}
