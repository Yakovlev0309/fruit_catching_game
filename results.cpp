#include "results.h"
#include "ui_results.h"
#include <QSizePolicy>
#include <QScrollBar>>

Results::Results(const QSize &window_size, QWidget *parent)
    : Menu(parent)
    , ui(new Ui::Results)
{
    ui->setupUi(this);

    setFixedSize(window_size);

    ui->results_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->results_table->setSortingEnabled(true);
    ui->results_table->horizontalHeader()->setFixedHeight(70);
    ui->results_table->setFixedSize(width() - 200, height() - 100);
    ui->results_table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->results_table->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);

    // Кнопка возврата
    return_widget = new Return(this);
    return_widget->move(10, 10);
    return_widget->setFixedSize(100, 100);
    connect(return_widget, &Return::returnSignal, this, &Results::returnClicked);
}

Results::~Results()
{
    delete ui;
}

void Results::fillTable(const QStringList &results)
{
    int len = results.size();
    ui->results_table->setRowCount(len);
    for (int i = 0; i < len; ++i)
    {
        QStringList row = results[i].split(" | ");
        ui->results_table->setItem(i, 0, new QTableWidgetItem(row[0].remove("Количество очков: ").toStdString().c_str()));
        ui->results_table->setItem(i, 1, new QTableWidgetItem(row[1].remove("Дата: ").toStdString().c_str()));
        ui->results_table->setItem(i, 2, new QTableWidgetItem(row[2].remove("Время: ").toStdString().c_str()));
    }
}

void Results::returnClicked()
{
    emit returnSignal();
}
