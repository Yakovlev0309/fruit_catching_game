#ifndef RESULTS_H
#define RESULTS_H

#include "menu.h"
#include "return.h"

namespace Ui {
class Results;
}

class Results : public Menu
{
    Q_OBJECT

public:
    Results(const QSize &window_size, QWidget *parent = nullptr);
    ~Results();

    void fillTable(const QStringList &results);

private slots:
    void returnClicked();

signals:
    void returnSignal();

private:
    Ui::Results *ui;

    Return *return_widget;
};

#endif // RESULTS_H
