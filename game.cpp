#include "game.h"
#include "fruit.h"
#include "apple.h"
#include "wormapple.h"
#include "applecore.h"
#include "pear.h"
#include <QTimer>

Game::Game()
{
    // Задание размеров окна
    window_size = QSize(800, 450);

    // Сцена
    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, window_size.width(), window_size.height());

    // Видимая область
    view = new QGraphicsView(scene);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setFixedSize(window_size);
    view->setBackgroundBrush(QBrush(QImage(":/images/background.png").scaled(window_size)));

    // Игрок
    player = new Player();
    player->setPos(view->width() / 2 - player->boundingRect().width() / 2, view->height() - player->boundingRect().height());
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    scene->addItem(player);

    // Очки
    // score = new Score();
    // scene->addItem(score);

    // Здоровье
    // health = new Health();
    // health->setPos(health->x(), health->y() + 25);
    // scene->addItem(health);

    // Фоновая музыка
    // QMediaPlayer *music = new QMediaPlayer();
    // music->setMedia(QUrl("qrc:/sounds/background.mp3"));
    // music->play();
}

Game::~Game()
{
    delete scene;
}

void Game::start()
{
    view->show();

    // Генерация фруктов
    startFruitsGeneration(2000);
}

void Game::startFruitsGeneration(int ms)
{
    // Генерация фруктов
    QTimer *timer = new QTimer();
    QObject::connect(timer, &QTimer::timeout, this, &Game::generateFruit);
    timer->start(ms);
}

void Game::generateFruit()
{
    Fruit *fruit;
    int fruit_number = rand() % fruit_count;
    int position = rand() % 700;
    switch (static_cast<FruitType>(fruit_number))
    {
    case FruitType::APPLE_1:
        fruit = new Apple(position, 1);
        break;
    case FruitType::APPLE_2:
        fruit = new Apple(position, 2);
        break;
    case FruitType::WORM_APPLE:
        fruit = new WormApple(position);
        break;
    case FruitType::APPLE_CORE:
        fruit = new AppleCore(position);
        break;
    case FruitType::PEAR_1:
        fruit = new Pear(position, 1);
        break;
    case FruitType::PEAR_2:
        fruit = new Pear(position, 2);
        break;
    }
    scene->addItem(fruit);
}
