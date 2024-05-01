#include "pausemenu.h"
#include "ui_pausemenu.h"

PauseMenu::PauseMenu(QWidget *parent)
    : Menu(parent)
    , ui(new Ui::PauseMenu)
{
    ui->setupUi(this);
}

PauseMenu::~PauseMenu()
{
    delete ui;
}

void PauseMenu::on_continue_button_clicked()
{
    emit continueSignal();
}

void PauseMenu::on_main_menu_button_clicked()
{
    emit mainMenuSignal();
}
