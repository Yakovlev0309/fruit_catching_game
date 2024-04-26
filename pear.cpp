#include "pear.h"

Pear::Pear(int position, int pear_number, QGraphicsItem *parent) : Fruit(parent)
{
    int divider = 35;
    QPixmap pixmap = QPixmap(":/images/pear" + QString::number(pear_number) + ".png");
    pixmap = pixmap.scaled(pixmap.size() / divider);
    setPixmap(pixmap);
    setPos(position, 0);
}