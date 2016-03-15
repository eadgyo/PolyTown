#ifndef HOUSING_H
#define HOUSING_H

#include "../Constant.h"

class Housing
{
public:
    Housing(p_uint max_inhabitants, p_uint water_needs, p_uint energy_needs);

    p_uint getInhabitants();
    p_uint getFoodNeeds();
    p_uint getWaterNeeds();
    p_uint getEnergyNeeds();

    bool isFull();
    bool hasFood();
    bool hasWater();
    bool hasEnergy();

protected:
    p_uint m_inhabitants;
    const p_uint m_max_inhabitants;
    static const p_uint m_food_needs;
    const p_uint m_water_needs;
    const p_uint m_energy_needs;

    bool m_hasFood;
    bool m_hasWater; // pointeur
    bool m_hasEnergy; // pointeur

    // social_score
    // eco_score
    // env_score
};

#endif // !HOUSING_H