#ifndef PAUSE_H
#define PAUSE_H

#include "menu.h"

namespace Ui {
class Pause;
}

class Pause : public Menu
{
    Q_OBJECT

public:
    explicit Pause(QWidget *parent = nullptr);
    ~Pause();

private slots:
    void on_pause_button_clicked();

signals:
    void pauseSignal();

private:
    Ui::Pause *ui;
};

#endif // PAUSE_H
