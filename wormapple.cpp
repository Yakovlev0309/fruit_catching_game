#include "wormapple.h"

WormApple::WormApple(QGraphicsItem *parent) : Fruit(parent)
{
    int divider = 35;
    QPixmap pixmap = QPixmap(":/images/apple3.png");
    pixmap = pixmap.scaled(pixmap.size() / divider, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    setPixmap(pixmap);
}
