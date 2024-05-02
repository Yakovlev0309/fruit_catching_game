#ifndef RESULTS_H
#define RESULTS_H

#include "menu.h"

namespace Ui {
class Results;
}

class Results : public Menu
{
    Q_OBJECT

public:
    Results(QWidget *parent = nullptr);
    ~Results();

    void fillTable(const QStringList &results);

private:
    Ui::Results *ui;
};

#endif // RESULTS_H
