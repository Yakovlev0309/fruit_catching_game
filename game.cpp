#include "game.h"
#include "fruit.h"
#include "apple.h"
#include "wormapple.h"
#include "applecore.h"
#include "pear.h"
#include <QEventLoop>
#include <QDate>
#include <QTime>
#include <QIcon>
#include <QFile>

Game::Game()
{
    max_results_count = 10;
    results_path = "results.txt";
    start_health = 5;
    start_score = 0;
    fruit_generation_period = 1000;

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
    view->setBackgroundBrush(QBrush(QImage(":/images/background.png").scaled(window_size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
    view->setWindowIcon(QIcon(":/images/apple2.png"));
    view->setWindowTitle("Ловля фруктов");

    // Меню
    menu_widget = new MainMenu();
    menu = scene->addWidget(menu_widget);
    menu->setPos(view->width() / 2 - menu->boundingRect().width() / 2, view->height() / 2 - menu->boundingRect().height() / 2);
    menu->setZValue(1);
    connect(menu_widget, &MainMenu::startSignal, this, &Game::startClicked);
    connect(menu_widget, &MainMenu::resultsSignal, this, &Game::resultsClicked);
    connect(menu_widget, &MainMenu::settingsSignal, this, &Game::settingsClicked);
    connect(menu_widget, &MainMenu::informationSignal, this, &Game::informationClicked);

    // Список результатов
    results_widget = new Results(window_size);
    results = scene->addWidget(results_widget);
    // results->setPos(view->width() / 2 - results->boundingRect().width() / 2, view->height() / 2 - results->boundingRect().height() / 2);
    results->setPos(0, 0);
    results->setZValue(1);
    results->setVisible(false);
    connect(results_widget, &Results::returnSignal, this, &Game::returnClicked);

    // Меню настроек
    settings_menu_widget = new SettingsMenu(window_size);
    settings_menu = scene->addWidget(settings_menu_widget);
    settings_menu->setPos(view->width() / 2 - settings_menu->boundingRect().width() / 2, view->height() / 2 - settings_menu->boundingRect().height() / 2);
    settings_menu->setZValue(1);
    settings_menu->setVisible(false);
    connect(settings_menu_widget, &SettingsMenu::returnSignal, this, &Game::returnClicked);
    connect(settings_menu_widget, &SettingsMenu::resultsPathChangedSignal, this, &Game::resultsPathChanged);
    settings_menu_widget->setResultsPathSetting(results_path);
    connect(settings_menu_widget, &SettingsMenu::fruitGenerationPeriodChangedSignal, this, &Game::fruitGenerationPeriodChanged);
    settings_menu_widget->setFruitGenerationPeriodSettings(500, 3000, fruit_generation_period);
    connect(settings_menu_widget, &SettingsMenu::heartCountChangedSignal, this, &Game::heartCountChanged);
    settings_menu_widget->setHealthSettings(1, 5, start_health);

    // Информация об игре
    information_widget = new Information(window_size);
    information = scene->addWidget(information_widget);
    information->setPos(view->width() / 2 - information->boundingRect().width() / 2, view->height() / 2 - information->boundingRect().height() / 2);
    information->setZValue(1);
    information->setVisible(false);
    connect(information_widget, &Information::returnSignal, this, &Game::returnClicked);

    // Кнопка паузы
    pause_widget = new Pause();
    pause_button = scene->addWidget(pause_widget);
    pause_button->setZValue(1);
    pause_button->setGeometry(QRect(10, 10, 100, 100));
    pause_button->setVisible(false);
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
    player->setPos(view->width() / 2 - player->boundingRect().width() / 2, view->height() - player->boundingRect().height());
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
    pause_button->setVisible(true);

    health->set(start_health);
    score->set(start_score);

    player->setPos(view->width() / 2 - player->boundingRect().width() / 2, view->height() - player->boundingRect().height() - 50);
    player->setVisible(true);
    player->setFocus();

    // Генерация фруктов
    startFruitsGeneration(fruit_generation_period);
}

void Game::returnClicked()
{
    if (settings_menu->isVisible()) // Открыто меню настроек
    {
        settings_menu->setVisible(false);
    }
    else if (results->isVisible()) // Открыт список результатов
    {
        results->setVisible(false);
    }
    else // Открыта информация об игре
    {
        information->setVisible(false);
    }

    menu->setVisible(true);
}

void Game::resultsClicked()
{
    menu->setVisible(false);

    results_widget->fillTable(readResults());

    results->setVisible(true);
}

void Game::settingsClicked()
{
    menu->setVisible(false);

    settings_menu->setVisible(true);
}

void Game::informationClicked()
{
    menu->setVisible(false);

    information->setVisible(true);
}

void Game::pauseClicked()
{
    pause_button->setVisible(false);

    fruit_timer->stop();
    freezeFruits();

    pause_menu->setVisible(true);
}

void Game::continueClicked()
{
    pause_menu->setVisible(false);

    fruit_timer->start();
    unfreezeFruits();

    pause_button->setVisible(true);
}

void Game::mainMenuClicked()
{
    pause_button->setVisible(false);
    pause_menu->setVisible(false);
    footer->setVisible(false);
    player->setVisible(false);

    menu->setVisible(true);

    fruit_timer->stop();
    removeFruits();
}

void Game::startFruitsGeneration(int ms)
{
    // Генерация фруктов
    fruit_timer = new QTimer(this);
    connect(fruit_timer, &QTimer::timeout, this, &Game::generateFruit);
    fruit_timer->start(ms);
}

void Game::waitEscKeyPress()
{
    view->installEventFilter(this);
    QEventLoop loop;
    connect(this, &Game::escPressedSignal, [&]() {
        loop.quit();
    });
    loop.exec();
    view->removeEventFilter(this);
}

void Game::removeFruits()
{
    QList<QGraphicsItem *> items = scene->items();
    for (auto item : items)
    {
        if (dynamic_cast<const Fruit *>(item) != nullptr)
        {
            scene->removeItem(item);
            delete item;
        }
    }
}

void Game::freezeFruits()
{
    QList<QGraphicsItem *> items = scene->items();
    for (auto item : items)
    {
        if (dynamic_cast<const Fruit *>(item) != nullptr)
        {
            dynamic_cast<Fruit *>(item)->stop();
        }
    }
}

void Game::unfreezeFruits()
{
    QList<QGraphicsItem *> items = scene->items();
    for (auto item : items)
    {
        if (dynamic_cast<const Fruit *>(item) != nullptr)
        {
            dynamic_cast<Fruit *>(item)->start();
        }
    }
}

void Game::generateFruit()
{
    Fruit *fruit;
    void (Game::*fruitCatchedFunction)();

    int fruit_number = rand() % fruit_count;
    switch (static_cast<FruitType>(fruit_number))
    {
    case FruitType::APPLE_1:
        fruit = new Apple(1);
        fruitCatchedFunction = &Game::greenFruitCathed;
        break;
    case FruitType::APPLE_2:
        fruit = new Apple(2);
        fruitCatchedFunction = &Game::redFruitCathed;
        break;
    case FruitType::WORM_APPLE:
        fruit = new WormApple();
        fruitCatchedFunction = &Game::wormAppleCatched;
        break;
    case FruitType::APPLE_CORE:
        fruit = new AppleCore();
        fruitCatchedFunction = &Game::appleCoreCatched;
        break;
    case FruitType::PEAR_1:
        fruit = new Pear(1);
        fruitCatchedFunction = &Game::greenFruitCathed;
        break;
    case FruitType::PEAR_2:
        fruit = new Pear(2);
        fruitCatchedFunction = &Game::redFruitCathed;
        break;
    }

    int position = rand() % (window_size.width() - (int)fruit->boundingRect().width());
    fruit->setPos(position, 0);

    scene->addItem(fruit);
    connect(fruit, &Apple::fruitCatchedSignal, this, fruitCatchedFunction);
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

void Game::resultsPathChanged(const QString &path)
{
    results_path = path;
}

void Game::fruitGenerationPeriodChanged(int period)
{
    fruit_generation_period = period;
}

void Game::heartCountChanged(int count)
{
    start_health = count;
}

void Game::gameOver()
{
    pause_button->setVisible(false);

    game_over->setVisible(true);

    fruit_timer->stop();
    removeFruits();
    player->setVisible(false);

    writeResult();

    waitEscKeyPress();

    game_over->setVisible(false);
    footer->setVisible(false);

    menu->setVisible(true);
}

void Game::focusChanged()
{
    if (player->isVisible())
    {
        player->setFocus();
    }
}

bool Game::eventFilter(QObject *object, QEvent *event)
{
    if (event->type() == QEvent::KeyPress)
    {
        if (static_cast<QKeyEvent*>(event)->key() == Qt::Key_Escape)
        {
            emit escPressedSignal();
        }
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
    QStringList new_results(results);
    if (new_results.count() < max_results_count)
    {
        new_results.append(result);
    }
    else
    {
        int min_index = 0;
        int min_score = -1;
        int current_score;
        for (int i = 0; i < results.size(); ++i)
        {
            current_score = new_results[i].split(" | ")[0].remove("Количество очков: ").toInt();
            if (min_score == -1)
            {
                min_score = current_score;
            }
            if (current_score < min_score)
            {
                min_index = i;
                min_score = current_score;
            }
        }
        int new_score = result.split(" | ")[0].remove("Количество очков: ").toInt();
        if (new_score > min_score)
        {
            new_results[min_index] = result;
        }
    }
    return new_results.join("\n");
}
