#include "game.h"
#include "fruit.h"
#include "apple.h"
#include "wormapple.h"
#include "applecore.h"
#include "pear.h"

Game::Game()
{
    // Задание размеров окна
    window_size = QSize(800, 450);

    // Сцена
    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, window_size.width(), window_size.height());
    connect(scene, &QGraphicsScene::focusItemChanged, this, &Game::focusChanged);

    // Видимая область
    view = new QGraphicsView(scene);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setFixedSize(window_size);
    view->setBackgroundBrush(QBrush(QImage(":/images/background.png").scaled(window_size)));

    // Меню
    menu_widget = new MainMenu();
    menu = scene->addWidget(menu_widget);
    menu->setPos(view->width() / 2 - menu->boundingRect().width() / 2, view->height() / 2 - menu->boundingRect().height() / 2);
    menu->setZValue(1);
    connect(menu_widget, &MainMenu::startSignal, this, &Game::startClicked);

    // Кнопка паузы
    pause_widget = new Pause();
    pause = scene->addWidget(pause_widget);
    pause->setPos(10, 10);
    pause->setZValue(1);
    pause->setVisible(false);
    connect(pause_widget, &Pause::pauseSignal, this, &Game::pauseClicked);

    // Меню паузы
    pause_menu_widget = new PauseMenu();
    pause_menu = scene->addWidget(pause_menu_widget);
    pause_menu->setPos(view->width() / 2 - pause_menu->boundingRect().width() / 2, view->height() / 2 - pause_menu->boundingRect().height() / 2);
    pause_menu->setZValue(1);
    pause_menu->setVisible(false);
    connect(pause_menu_widget, &PauseMenu::continueSignal, this, &Game::continueClicked);
    connect(pause_menu_widget, &PauseMenu::mainMenuSignal, this, &Game::mainMenuClicked);

    // Нижняя часть сцены
    footer = new Footer();
    footer->setPos(0, window_size.height() - 70);
    footer->setVisible(false);
    scene->addItem(footer);

    // Очки
    score = new Score(0, footer);
    score->setPos(580, 0);

    // Здоровье
    health = new Health(5, footer);
    connect(health, &Health::gameOverSignal, this, &Game::gameOver);

    // Игрок
    player = new Player();
    player->setPos(view->width() / 2 - player->boundingRect().width() / 2, view->height() - player->boundingRect().height() - 50);
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    player->setVisible(false);
    scene->addItem(player);

    // Конец игры
    game_over = new GameOver(window_size);
    game_over->setVisible(false);
    game_over->setZValue(1);
    scene->addItem(game_over);

    view->show();
}

Game::~Game()
{
    delete scene;
}

void Game::startClicked()
{
    menu->setVisible(false);
    game_over->setVisible(false);
    footer->setVisible(true);
    pause->setVisible(true);

    player->setPos(view->width() / 2 - player->boundingRect().width() / 2, view->height() - player->boundingRect().height() - 50);
    player->setVisible(true);

    // Генерация фруктов
    startFruitsGeneration(1000);
}

void Game::pauseClicked()
{
    pause->setVisible(false);

    pause_menu->setVisible(true);
}

void Game::continueClicked()
{
    pause_menu->setVisible(false);

    pause->setVisible(true);
}

void Game::mainMenuClicked()
{
    pause->setVisible(false);
    pause_menu->setVisible(false);
    footer->setVisible(false);
    player->setVisible(false);

    menu->setVisible(true);

    fruit_timer->stop();
}

void Game::startFruitsGeneration(int ms)
{
    // Генерация фруктов
    fruit_timer = new QTimer(this);
    connect(fruit_timer, &QTimer::timeout, this, &Game::generateFruit);
    fruit_timer->start(ms);
}

void Game::generateFruit()
{
    Fruit *fruit;
    int fruit_number = rand() % fruit_count;
    int position = rand() % (window_size.width() - 100);
    void (Game::*fruitCatchedFunction)();
    switch (static_cast<FruitType>(fruit_number))
    {
    case FruitType::APPLE_1:
        fruit = new Apple(position, 1);
        fruitCatchedFunction = &Game::greenFruitCathed;
        break;
    case FruitType::APPLE_2:
        fruit = new Apple(position, 2);
        fruitCatchedFunction = &Game::redFruitCathed;
        break;
    case FruitType::WORM_APPLE:
        fruit = new WormApple(position);
        fruitCatchedFunction = &Game::wormAppleCatched;
        break;
    case FruitType::APPLE_CORE:
        fruit = new AppleCore(position);
        fruitCatchedFunction = &Game::appleCoreCatched;
        break;
    case FruitType::PEAR_1:
        fruit = new Pear(position, 1);
        fruitCatchedFunction = &Game::greenFruitCathed;
        break;
    case FruitType::PEAR_2:
        fruit = new Pear(position, 2);
        fruitCatchedFunction = &Game::redFruitCathed;
        break;
    }
    connect(fruit, &Apple::fruitCatchedSignal, this, fruitCatchedFunction);
    scene->addItem(fruit);
}

void Game::redFruitCathed()
{
    score->increase(2);
}

void Game::greenFruitCathed()
{
    score->increase(1);
}

void Game::wormAppleCatched()
{
    score->increase(-1);
}

void Game::appleCoreCatched()
{
    health->decrease(1);
}

void Game::gameOver()
{
    game_over->setVisible(true);
    fruit_timer->stop();
    scene->removeItem(player);
    // TODO ожидание нажатия любой кнопки
}

void Game::focusChanged()
{
    if (player->isVisible()) // FIXME заменить на if (started)
    {
        player->setFocus();
    }
}
