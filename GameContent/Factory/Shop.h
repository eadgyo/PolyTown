#ifndef SHOP_H
#define SHOP_H

#include "Factory.h"

#include "../Resources/Energy.h"

class Shop final : public virtual Factory, public virtual Energy
{
public:
    Shop(int x, int y);

    // ----- GETTER ----- //
    p_uint getEnergyNeeds() const;
    bool isWorking() const;

    // ----- SETTER ----- //
    void update();

private:

};

#endif // !SHOP_H