#ifndef HOUSING_H
#define HOUSING_H

#include "../Constant.h"

class Housing
{
public:
    Housing();
    Housing(p_uint inhabitants, p_uint max_inhabitants, p_uint food_needs, p_uint water_needs, p_uint energy_needs);

private:
    p_uint m_inhabitants;
    p_uint m_max_inhabitants;
    p_uint m_food_needs;
    p_uint m_water_needs;
    p_uint m_energy_needs;

    // social_score
    // eco_score
    // env_score
};

#endif // !HOUSING_H