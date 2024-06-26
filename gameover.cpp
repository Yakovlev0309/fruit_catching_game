#include "gameover.h"
#include <QFont>

GameOver::GameOver(const QSize &size, QGraphicsItem *parent) : QGraphicsPixmapItem(parent)
{
    QPixmap pixmap = QPixmap(":/images/end.png");
    pixmap = pixmap.scaled(size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    setPixmap(pixmap);

    text = new QGraphicsTextItem(this);
    text->setPlainText("Для продолжения нажмите Esc");
    text->setDefaultTextColor(Qt::white);
    text->setFont(QFont("Comic Sans MS", 12));
    text->setPos(pixmap.width() / 2 - text->boundingRect().width() / 2, pixmap.height() - text->boundingRect().height() * 2);
}
