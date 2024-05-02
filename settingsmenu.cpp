#include "settingsmenu.h"
#include "ui_settingsmenu.h"

SettingsMenu::SettingsMenu(QWidget *parent)
    : Menu(parent)
    , ui(new Ui::SettingsMenu)
{
    ui->setupUi(this);

    fruit_generation_period = 1000;
    heart_count = 5;
}

SettingsMenu::~SettingsMenu()
{
    delete ui;
}

void SettingsMenu::setFruitGenerationPeriodSettings(int min_period, int max_period, int current_period)
{
    setFruitGenerationPeriod(current_period);
    this->min_period = min_period;
    this->max_period = max_period;
}

void SettingsMenu::setHealthSettings(int min_health, int max_health, int heart_count)
{
    setHeartCount(heart_count);
    this->min_health = min_health;
    this->max_health = max_health;
}

void SettingsMenu::setFruitGenerationPeriod(int fruit_generation_period)
{
    ui->fruit_generation_period_label->setText(QString::number(fruit_generation_period));
    this->fruit_generation_period = fruit_generation_period;
}

void SettingsMenu::setHeartCount(int heart_count)
{
    ui->heart_count_label->setText(QString::number(heart_count));
    this->heart_count = heart_count;
}

void SettingsMenu::on_fruit_generation_period_up_button_clicked()
{
    if (fruit_generation_period + fruit_generation_period_delta <= max_period)
    {
        setFruitGenerationPeriod(fruit_generation_period + fruit_generation_period_delta);
        emit fruitGenerationPeriodChangedSignal(fruit_generation_period);
    }
}

void SettingsMenu::on_fruit_generation_period_down_button_clicked()
{
    if (fruit_generation_period - fruit_generation_period_delta >= min_period)
    {
        setFruitGenerationPeriod(fruit_generation_period - fruit_generation_period_delta);
        emit fruitGenerationPeriodChangedSignal(fruit_generation_period);
    }
}

void SettingsMenu::on_heart_count_up_button_clicked()
{
    if (heart_count + health_delta <= max_health)
    {
        setHeartCount(heart_count + health_delta);
        emit heartCountChangedSignal(heart_count);
    }
}

void SettingsMenu::on_heart_count_down_button_clicked()
{
    if (heart_count - health_delta >= min_health)
    {
        setHeartCount(heart_count - health_delta);
        emit heartCountChangedSignal(heart_count);
    }
}

// TODO изменение пути
