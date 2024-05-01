#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include "menu.h"

namespace Ui {
class PauseMenu;
}

class PauseMenu : public Menu
{
    Q_OBJECT

public:
    PauseMenu(QWidget *parent = nullptr);
    ~PauseMenu();

private slots:
    void on_continue_button_clicked();
    void on_main_menu_button_clicked();

signals:
    void continueSignal();
    void mainMenuSignal();

private:
    Ui::PauseMenu *ui;
};

#endif // PAUSEMENU_H
