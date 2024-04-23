#include "apple.h"

Apple::Apple(QGraphicsItem *parent) : Fruit(parent)
{
    int divider = 35;
    // TODO рандомный выбор картинки при создании яблока (передать из рандома в game.cpp)
    QPixmap pixmap = QPixmap(":/images/apple1.png");
    pixmap = pixmap.scaled(pixmap.size() / divider);
    setPixmap(pixmap);

    // image_size = pixmap.size();
}
