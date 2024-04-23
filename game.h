#ifndef GAME_H
#define GAME_H

#include "player.h"
#include <QGraphicsView>
#include <QGraphicsScene>

const int fruit_count = 6;

enum class FruitType
{
    APPLE_1 = 0,
    APPLE_2,
    WORM_APPLE,
    APPLE_CORE,
    PEAR_1,
    PEAR_2 = 5
};

class Game : public QObject
{
    Q_OBJECT
public:
    Game();
    ~Game();
    void start();

private:
    void startFruitsGeneration(int ms);

private slots:
    void generateFruit();

private:
    QGraphicsScene *scene;
    QGraphicsView *view;
    Player *player;

    QSize window_size;
};

#endif // GAME_H
