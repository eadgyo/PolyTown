#ifndef WATER_H
#define WATER_H

#include "../../Constant.h"
#include "WaterTower.h"

class Water
{
public:
    Water();
    Water(p_uint water_needs);

protected:
    p_uint m_water_needs;
    WaterTower* m_water_tower;
};

#endif // !WATER_H