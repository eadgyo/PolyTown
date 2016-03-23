#include "Shop.h"

Shop::Shop(int x, int y) :
    QTEntity(SHOP_RECTANGLE(x, y)),
    Factory(SHOP_MAX_WORKERS, SHOP_INCOME_RATE),
    Energy(SHOP_ENERGY_NEEDS)
{
    setName(SHOP_NAME);
}