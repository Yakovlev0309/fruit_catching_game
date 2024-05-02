#include "mainmenu.h"
#include "ui_mainmenu.h"
#include <QMessageBox>

MainMenu::MainMenu(QWidget *parent)
    : Menu(parent)
    , ui(new Ui::MainMenu)
{
    ui->setupUi(this);
}

MainMenu::~MainMenu()
{
    delete ui;
}

void MainMenu::on_play_button_clicked()
{
    emit startSignal();
}

void MainMenu::on_results_button_clicked()
{
    emit resultsSignal();
}

void MainMenu::on_settings_button_clicked()
{
    emit settingsSignal();
}

void MainMenu::on_exit_button_clicked()
{
    QMessageBox msg;
    msg.setWindowTitle("Выход из игры");
    msg.setText("Вы уверены, что хотите выйти из игры?");
    QPushButton *okButton = msg.addButton("Да", QMessageBox::AcceptRole);
    msg.addButton("Нет", QMessageBox::RejectRole);
    msg.exec();
    if (msg.clickedButton() == okButton)
    {
        QApplication::quit();
    }
}
