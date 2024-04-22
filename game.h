#ifndef GAME_H
#define GAME_H

#include "player.h"
#include <QGraphicsView>
#include <QGraphicsScene>

class Game
{
public:
    Game();
    void start();

private:
    QGraphicsScene *scene;
    QGraphicsView *view;
    Player *player;
};

#endif // GAME_H
