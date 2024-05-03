#ifndef SETTINGSMENU_H
#define SETTINGSMENU_H

#include "menu.h"

namespace Ui {
class SettingsMenu;
}

const int fruit_generation_period_delta = 500;
const int health_delta = 1;

class SettingsMenu : public Menu
{
    Q_OBJECT

public:
    SettingsMenu(QWidget *parent = nullptr);
    ~SettingsMenu();

    void setResultsPathSetting(const QString &path);
    void setFruitGenerationPeriodSettings(int min_period, int max_period, int current_period);
    void setHealthSettings(int min_health, int max_health, int heart_count);

private slots:
    void on_fruit_generation_period_up_button_clicked();
    void on_fruit_generation_period_down_button_clicked();
    void on_heart_count_up_button_clicked();
    void on_heart_count_down_button_clicked();
    void on_results_path_edit_textChanged(const QString &path);
    void on_choose_path_button_clicked();

private:
    void setFruitGenerationPeriod(int fruit_generation_period);
    void setHeartCount(int heart_count);

signals:
    void resultsPathChangedSignal(const QString &path);
    void fruitGenerationPeriodChangedSignal(int period);
    void heartCountChangedSignal(int count);

private:
    Ui::SettingsMenu *ui;

    QString results_path;

    int min_period;
    int max_period;
    int fruit_generation_period;

    int min_health;
    int max_health;
    int heart_count;
};

#endif // SETTINGSMENU_H
