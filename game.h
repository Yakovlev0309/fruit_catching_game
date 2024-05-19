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
#include "results.h"
#include "settingsmenu.h"
#include "information.h"
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
    void waitEscKeyPress();
    void removeFruits();
    void freezeFruits();
    void unfreezeFruits();

    void writeResult();
    QStringList readResults();
    QString updateResults(const QStringList &results, const QString &result);

private slots:
    void startClicked();
    void returnClicked();
    void resultsClicked();
    void settingsClicked();
    void informationClicked();
    void pauseClicked();
    void continueClicked();
    void mainMenuClicked();

    void redFruitCathed();
    void greenFruitCathed();
    void wormAppleCatched();
    void appleCoreCatched();

    void resultsPathChanged(const QString &path);
    void fruitGenerationPeriodChanged(int period);
    void heartCountChanged(int count);

    void generateFruit();
    void gameOver();

    void focusChanged();

    bool eventFilter(QObject *object, QEvent *event);

signals:
    void escPressedSignal();

private:
    QGraphicsScene *scene;
    QGraphicsView *view;

    MainMenu *menu_widget;
    QGraphicsProxyWidget *menu;
    Pause *pause_widget;
    QGraphicsProxyWidget *pause_button;
    PauseMenu *pause_menu_widget;
    QGraphicsProxyWidget *pause_menu;
    Results *results_widget;
    QGraphicsProxyWidget *results;
    SettingsMenu *settings_menu_widget;
    QGraphicsProxyWidget *settings_menu;
    Information *information_widget;
    QGraphicsProxyWidget *information;

    Footer *footer;
    Score *score;
    Health *health;
    Player *player;
    GameOver *game_over;

    QSize window_size;
    QTimer *fruit_timer;

    QString results_path;
    int max_results_count;

    int start_health;
    int start_score;
    int fruit_generation_period;
};

#endif // GAME_H
