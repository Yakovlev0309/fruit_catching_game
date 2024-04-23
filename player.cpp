#include "player.h"
#include <QKeyEvent>
#include <QGraphicsScene>

Player::Player(QGraphicsItem *parent) : QGraphicsPixmapItem(parent)
{
    int divider = 35;
    QPixmap pixmap = QPixmap(":/images/character.png");
    pixmap = pixmap.scaled(pixmap.size() / divider);
    setPixmap(pixmap);

    image_size = pixmap.size();
    current_direction = PlayerDirection::RIGHT;
}

void Player::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Left:
        if (pos().x() + image_size.width() / 2 - image_size.width() / 2 > 0)
        {
            setPos(x() - 10, y());
            flipImage(PlayerDirection::LEFT);
        }
        break;
    case Qt::Key_Right:
        if (pos().x() + image_size.width() / 2 + image_size.width() / 2 < scene()->width())
        {
            setPos(x() + 10, y());
            flipImage(PlayerDirection::RIGHT);
        }
        break;
    }
}

void Player::flipImage(const PlayerDirection &direction)
{
    if (direction != current_direction)
    {
        // QTransform transform;
        // transform.scale((int)direction, 1);
        // setTransformOriginPoint(0, 0);
        // setTransform(transform);
        // setPos(QPointF(pos().x() + image_size.width() * - (int)direction, pos().y()));
        current_direction = direction;
    }
}
