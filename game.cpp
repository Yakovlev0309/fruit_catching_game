#include "game.h"
#include "fruit.h"
#include "apple.h"
#include "wormapple.h"
#include "applecore.h"
#include "pear.h"
#include <QEventLoop>
#include <QDate>
#include <QTime>

Game::Game()
{
    results_path = "results.txt";
    start_health = 1;
    start_score = 0;
    fruit_generation_period = 1000; // мс

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
    footer->setZValue(1);
    scene->addItem(footer);

    // Очки
    score = new Score(start_score, footer);
    score->setPos(580, 0);

    // Здоровье
    health = new Health(start_health, footer);
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

    health->set(start_health);
    score->set(start_score);

    player->setPos(view->width() / 2 - player->boundingRect().width() / 2, view->height() - player->boundingRect().height() - 50);
    player->setVisible(true);
    player->setFocus();

    // Генерация фруктов
    startFruitsGeneration(fruit_generation_period);
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

void Game::waitAnyKeyPress()
{
    view->installEventFilter(this);
    QEventLoop loop;
    connect(this, &Game::keyPressedSignal, [&]() {
        loop.quit();
    });
    loop.exec();
    view->removeEventFilter(this);
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
    pause->setVisible(false);

    game_over->setVisible(true);

    fruit_timer->stop();
    player->setVisible(false);

    writeResult();

    waitAnyKeyPress();

    game_over->setVisible(false);
    footer->setVisible(false);

    menu->setVisible(true);
}

void Game::focusChanged()
{
    if (player->isVisible()) // FIXME заменить на if (started)
    {
        player->setFocus();
    }
}

bool Game::eventFilter(QObject *object, QEvent *event)
{
    if (event->type() == QEvent::KeyPress)
    {
        emit keyPressedSignal();
    }
    return QObject::eventFilter(object, event);
}

void Game::writeResult()
{
    QFile file(results_path);
    QStringList results = readResults();
    QString result = "Количество очков: ";
    result += QString::number(score->get());
    result += " | Дата: ";
    result += QDate::currentDate().toString();
    result += " | Время: ";
    result += QTime::currentTime().toString();
    QString text = updateResults(results, result);
    if (file.open(QIODevice::WriteOnly))
    {
        file.write(text.toStdString().c_str());
    }
    file.close();
}

QStringList Game::readResults()
{
    QStringList result;
    QFile file(results_path);
    if (file.open(QIODevice::ReadOnly))
    {
        QByteArray data = file.readAll();
        QString text = QString::fromUtf8(data);
        result = text.split('\n');
    }
    file.close();
    return result;
}

QString Game::updateResults(const QStringList &results, const QString &result)
{
    QStringList new_results = results;
    if (results.size() < max_results_count)
    {
        new_results.append(result);
    }
    else
    {
        QStringList str = result.split(" | ");
        int score = str[2].remove("Количество очков: ").toInt();

        new_results.sort();
        for (int i = 0; i < max_results_count; ++i)
        {
            QStringList str = new_results[i].split(" | ");
            if (score > str[0].remove("Количество очков: ").toInt())
            {
                new_results.insert(i, result);
                new_results.pop_back();
                break;
            }
        }
    }
    return new_results.join("\n");
}
