#ifndef FRUIT_H
#define FRUIT_H

#include <QGraphicsPixmapItem>
#include <QTimer>

class Fruit : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Fruit(QGraphicsItem *parent = nullptr);

    void start();
    void stop();

private:
    void move();

signals:
    void fruitCatchedSignal();

private:
    QTimer *move_timer;

    int step;
    int move_period;
};

#endif // FRUIT_H
