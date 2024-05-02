#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>

class GameOver : public QGraphicsPixmapItem
{
public:
    GameOver(const QSize &size, QGraphicsItem *parent = nullptr);

private:
    QGraphicsTextItem *text;
};

#endif // GAMEOVER_H
