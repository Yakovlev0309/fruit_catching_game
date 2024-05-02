#ifndef RETURN_H
#define RETURN_H

#include "menu.h"

namespace Ui {
class Return;
}

class Return : public Menu
{
    Q_OBJECT

public:
    Return(QWidget *parent = nullptr);
    ~Return();

private slots:
    void on_return_button_clicked();

signals:
    void returnSignal();

private:
    Ui::Return *ui;
};

#endif // RETURN_H
