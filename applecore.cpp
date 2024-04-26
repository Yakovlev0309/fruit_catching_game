#include "applecore.h"

AppleCore::AppleCore(int position, QGraphicsItem *parent) : Fruit(parent)
{
    int divider = 35;
    QPixmap pixmap = QPixmap(":/images/apple4.png");
    pixmap = pixmap.scaled(pixmap.size() / divider);
    setPixmap(pixmap);
    setPos(position, 0);
}
