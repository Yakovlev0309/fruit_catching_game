#ifndef HEALTH_H
#define HEALTH_H

#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>

class Health : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Health(int health, QGraphicsItem *parent = nullptr);

    void decrease(int value);

    int get();
    void set(int health);

signals:
    void gameOverSignal();

private:
    QVector<QGraphicsPixmapItem*> hearts;
    int health;
};

#endif // HEALTH_H
