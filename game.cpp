#include "game.h"

Game::Game()
{
    // Сцена
    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, 800, 450);

    // Видимая область
    view = new QGraphicsView(scene);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setFixedSize(800, 450);
    view->setBackgroundBrush(QBrush(QImage(":/images/background.png").scaled(800, 450)));

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

    // Генерация фруктов
    // QTimer *timer = new QTimer();
    // QObject::connect(timer, &QTimer::timeout, player, &Player::spawn);
    // timer->start(2000);

    // Фоновая музыка
    // QMediaPlayer *music = new QMediaPlayer();
    // music->setMedia(QUrl("qrc:/sounds/background.mp3"));
    // music->play();
}

void Game::start()
{
    view->show();
}
