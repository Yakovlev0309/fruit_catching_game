#ifndef GAME_H
#define GAME_H

#include "footer.h"
#include "score.h"
#include "health.h"
#include "player.h"
#include "gameover.h"
#include "mainmenu.h"
#include "pause.h"
#include "pausemenu.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>
#include <QGraphicsProxyWidget>

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

private:
    void startFruitsGeneration(int ms);

private slots:
    void startClicked();
    void pauseClicked();
    void continueClicked();
    void mainMenuClicked();

    void generateFruit();
    void gameOver();

    void redFruitCathed();
    void greenFruitCathed();
    void wormAppleCatched();
    void appleCoreCatched();

    void focusChanged();

private:
    QGraphicsScene *scene;
    QGraphicsView *view;

    MainMenu *menu_widget;
    QGraphicsProxyWidget *menu;
    Pause *pause_widget;
    QGraphicsProxyWidget *pause;
    PauseMenu *pause_menu_widget;
    QGraphicsProxyWidget *pause_menu;

    Footer *footer;
    Score *score;
    Health *health;
    Player *player;
    GameOver *game_over;

    QSize window_size;
    QTimer *fruit_timer;
};

#endif // GAME_H
