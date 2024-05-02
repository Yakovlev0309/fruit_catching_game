#include "results.h"
#include "ui_results.h"
#include <QSizePolicy>

Results::Results(QWidget *parent)
    : Menu(parent)
    , ui(new Ui::Results)
{
    ui->setupUi(this);

    setFixedSize(600, 350);

    ui->results_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->results_table->setSortingEnabled(true);
    ui->results_table->horizontalHeader()->setFixedHeight(70);
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
    ui->results_table->resizeColumnsToContents();
    ui->results_table->resizeRowsToContents();
}
