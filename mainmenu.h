#ifndef MAINMENU_H
#define MAINMENU_H

#include "menu.h"

namespace Ui {
class MainMenu;
}

class MainMenu : public Menu
{
    Q_OBJECT

public:
    MainMenu(QWidget *parent = nullptr);
    ~MainMenu();

private slots:
    void on_play_button_clicked();
    void on_results_button_clicked();
    void on_exit_button_clicked();

    void on_settings_button_clicked();

signals:
    void startSignal();
    void resultsSignal();
    void settingsSignal();

private:
    Ui::MainMenu *ui;
};

#endif // MAINMENU_H
