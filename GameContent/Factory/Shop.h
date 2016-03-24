#ifndef SHOP_H
#define SHOP_H

#include "Factory.h"

#include "../Resources/Energy.h"

class Shop final : public virtual Factory, public virtual Energy
{
public:
    Shop(int x, int y);

    // ----- GETTER ----- //
    bool isWorking() const;

private:

};

#endif // !SHOP_H