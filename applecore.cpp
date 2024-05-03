#include "applecore.h"

AppleCore::AppleCore(QGraphicsItem *parent) : Fruit(parent)
{
    int divider = 35;
    QPixmap pixmap = QPixmap(":/images/apple4.png");
    pixmap = pixmap.scaled(pixmap.size() / divider);
    setPixmap(pixmap);
}
