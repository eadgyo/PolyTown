#ifndef WATER_H
#define WATER_H

class Water;
#include "../../Constant.h"

#include "WaterTower.h"

class Water
{
public:
    Water();
    Water(p_uint water_needs);

    // ----- GETTER ----- //
    virtual p_uint getWaterNeeds() const = 0;
    bool hasWater() const;

	WaterTower* getWaterTower();
	void setWaterTower(WaterTower* waterTower);

protected:
    p_uint m_water_needs;
    WaterTower* m_water_tower;
};

#endif // !WATER_H