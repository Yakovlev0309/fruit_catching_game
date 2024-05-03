#ifndef PEAR_H
#define PEAR_H

#include "fruit.h"

class Pear : public Fruit
{
public:
    Pear(int pear_number, QGraphicsItem *parent = nullptr);
};

#endif // PEAR_H
