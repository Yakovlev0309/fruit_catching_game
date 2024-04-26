#ifndef WORMAPPLE_H
#define WORMAPPLE_H

#include "fruit.h"

class WormApple : public Fruit
{
public:
    WormApple(int position, QGraphicsItem *parent = nullptr);
};

#endif // WORMAPPLE_H
