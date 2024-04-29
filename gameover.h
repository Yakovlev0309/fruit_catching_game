#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <QGraphicsPixmapItem>

class GameOver : public QGraphicsPixmapItem
{
public:
    GameOver(const QSize &size, QGraphicsItem *parent = nullptr);
};

#endif // GAMEOVER_H
