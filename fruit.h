#ifndef FRUIT_H
#define FRUIT_H

#include <QGraphicsPixmapItem>

class Fruit : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Fruit(QGraphicsItem *parent = nullptr);

private:
    void move();
};

#endif // FRUIT_H
