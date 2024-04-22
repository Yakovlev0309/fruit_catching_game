#include "player.h"
#include <QKeyEvent>
#include <QGraphicsScene>

Player::Player(QGraphicsItem *parent) : QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/images/character.png").scaled(240, 120, Qt::KeepAspectRatio));
}

void Player::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Left:
        if (pos().x() > 0)
        {
            setPos(x() - 10, y());
            flipImage(-1);
        }
        break;
    case Qt::Key_Right:
        if (pos().x() + boundingRect().width() < scene()->width())
        {
            setPos(x() + 10, y());
            flipImage(1);
        }
        break;
    }
}

void Player::flipImage(int state)
{
    QTransform transform;
    transform.scale(state, 1);
    setTransformOriginPoint(0, 0);
    setTransform(transform);

    // TODO исправить отражение по вертикали (или вообще убрать)
}
