#ifndef SETTINGSMENU_H
#define SETTINGSMENU_H

#include "menu.h"

namespace Ui {
class SettingsMenu;
}

const int fruit_generation_period_delta = 500;

class SettingsMenu : public Menu
{
    Q_OBJECT

public:
    SettingsMenu(QWidget *parent = nullptr);
    ~SettingsMenu();

    void setFruitGenerationPeriodSettings(int min_period, int max_period, int current_period);

private slots:
    void on_fruit_generation_period_up_button_clicked();
    void on_fruit_generation_period_down_button_clicked();

private:
    void setFruitGenerationPeriod(int fruit_generation_period);

signals:
    void fruitGenerationPeriodChangedSignal(int period);

private:
    Ui::SettingsMenu *ui;

    int min_period;
    int max_period;
    int fruit_generation_period;
};

#endif // SETTINGSMENU_H
