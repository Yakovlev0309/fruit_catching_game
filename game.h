#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "score.h"
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
    void gameOver();

    void decreaseHealth();

    void updateHearts();

private slots:
    void generateFruit();
    void redFruitCathed();
    void greenFruitCathed();
    void wormAppleCatched();
    void appleCoreCatched();

private:
    QGraphicsScene *scene;
    QGraphicsView *view;

    QSize window_size;

    Player *player;
    Score *score;
    int health;
};

#endif // GAME_H
