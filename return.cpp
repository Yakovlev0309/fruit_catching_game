#include "return.h"
#include "ui_return.h"

Return::Return(QWidget *parent)
    : Menu(parent)
    , ui(new Ui::Return)
{
    ui->setupUi(this);
}

Return::~Return()
{
    delete ui;
}

void Return::on_return_button_clicked()
{
    emit returnSignal();
}
