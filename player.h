#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>

enum class PlayerDirection
{
    LEFT = -1,
    RIGHT = 1
};

class Player : public QGraphicsPixmapItem
{
public:
    Player(QGraphicsItem *parent = nullptr);

private:
    void keyPressEvent(QKeyEvent *event) override;

    void flipImage(const PlayerDirection &direction);

private:
    QSize image_size;
    PlayerDirection current_direction;
};

#endif // PLAYER_H
