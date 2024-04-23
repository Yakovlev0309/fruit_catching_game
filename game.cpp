#include "game.h"
#include "fruit.h"
#include "apple.h"
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
#include <QDebug>
void Game::generateFruit()
{
    Fruit *fruit;
    int fruit_number = rand() % fruit_count;
    switch (static_cast<FruitType>(fruit_number))
    {
    case FruitType::APPLE_1:
        fruit = new Apple();
        scene->addItem(fruit);
        break;
    case FruitType::APPLE_2:
        fruit = new Apple();
        scene->addItem(fruit);
        break;
    case FruitType::WORM_APPLE:
        // fruit = new WormApple();
        qDebug() << "WORM_APPLE";
        break;
    case FruitType::APPLE_CORE:
        // fruit = new AppleCore();
        qDebug() << "APPLE_CORE";
        break;
    case FruitType::PEAR_1:
        // fruit = new Pear();
        qDebug() << "PEAR_1";
        break;
    case FruitType::PEAR_2:
        // fruit = new Pear();
        qDebug() << "PEAR_2";
        break;
    }

    // scene->addItem(fruit);
}
