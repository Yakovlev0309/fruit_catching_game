#include "pause.h"
#include "ui_pause.h"

Pause::Pause(QWidget *parent)
    : Menu(parent)
    , ui(new Ui::Pause)
{
    ui->setupUi(this);
}

Pause::~Pause()
{
    delete ui;
}

void Pause::on_pause_button_clicked()
{
    emit pauseSignal();
}
