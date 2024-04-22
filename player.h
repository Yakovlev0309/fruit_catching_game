#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>

class Player : public QGraphicsPixmapItem
{
public:
    Player(QGraphicsItem *parent = nullptr);

private:
    void keyPressEvent(QKeyEvent *event) override;

    void flipImage(int state);
};

#endif // PLAYER_H
