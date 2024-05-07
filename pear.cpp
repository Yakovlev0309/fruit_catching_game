#include "pear.h"

Pear::Pear(int pear_number, QGraphicsItem *parent) : Fruit(parent)
{
    int divider = 35;
    QPixmap pixmap = QPixmap(":/images/pear" + QString::number(pear_number) + ".png");
    pixmap = pixmap.scaled(pixmap.size() / divider, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    setPixmap(pixmap);
}
