#include "Shop.h"

Shop::Shop(int x, int y) :
    QTEntity(SHOP_RECTANGLE(x, y)),
    Factory(SHOP_MAX_WORKERS, SHOP_INCOME_RATE),
    Energy(SHOP_ENERGY_NEEDS)
{
    setName(SHOP_NAME);
}

// ----- GETTER ----- //
p_uint Shop::getEnergyNeeds() const
{
    return m_energy_needs;
}

bool Shop::isWorking() const
{
    return (m_power_plant != NULL);
}

// ----- SETTER ----- //
void Shop::update()
{
}