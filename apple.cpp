#include "apple.h"

Apple::Apple(int position, int apple_number, QGraphicsItem *parent) : Fruit(parent)
{
    int divider = 35;
    QPixmap pixmap = QPixmap(":/images/apple" + QString::number(apple_number) + ".png");
    pixmap = pixmap.scaled(pixmap.size() / divider);
    setPixmap(pixmap);
    setPos(position, 0);
}
