#include "apple.h"

Apple::Apple(int apple_number, QGraphicsItem *parent) : Fruit(parent)
{
    int divider = 35;
    QPixmap pixmap = QPixmap(":/images/apple" + QString::number(apple_number) + ".png");
    pixmap = pixmap.scaled(pixmap.size() / divider, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    setPixmap(pixmap);
}
