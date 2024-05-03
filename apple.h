#ifndef APPLE_H
#define APPLE_H

#include "fruit.h"

class Apple : public Fruit
{
public:
    Apple(int apple_number, QGraphicsItem *parent = nullptr);
};

#endif // APPLE_H
