#ifndef GAME_H
#define GAME_H

#include "footer.h"
#include "score.h"
#include "health.h"
#include "player.h"
#include "gameover.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>

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
    void redFruitCathed();
    void greenFruitCathed();
    void wormAppleCatched();
    void appleCoreCatched();
    void gameOver();
    void focusChanged();

signals:
    void restartSignal();

private:
    QGraphicsScene *scene;
    QGraphicsView *view;

    Footer *footer;
    Score *score;
    Health *health;
    Player *player;
    GameOver *game_over;

    QSize window_size;
    QTimer *fruit_timer;
};

#endif // GAME_H
