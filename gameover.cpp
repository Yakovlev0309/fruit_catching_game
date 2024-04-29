#include "gameover.h"

GameOver::GameOver(const QSize &size, QGraphicsItem *parent) : QGraphicsPixmapItem(parent)
{
    QPixmap pixmap = QPixmap(":/images/end.png");
    pixmap = pixmap.scaled(size);
    setPixmap(pixmap);
}
