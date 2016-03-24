#ifndef HOUSING_H
#define HOUSING_H

#include "../Quadtree/QTEntity.h"

#include "../Resources/Energy.h"
#include "../Resources/Water.h"

class Housing : public virtual QTEntity, public virtual Energy, public virtual Water
{
public:
    // ----- GETTER ----- //
    p_uint getInhabitants() const;
    p_uint getFoodNeeds() const;
    p_uint getWaterNeeds() const;
    p_uint getEnergyNeeds() const;

    bool isFull() const;
    bool hasFood() const;

    // ----- SETTER ----- //
    p_uint addInhabitants(p_uint n);
    p_uint delInhabitants(p_uint n);

    void upgrade(p_uint water_needs, p_uint energy_needs);

protected:
    Housing();
    Housing(p_uint max_inhabitants);

    p_uint m_inhabitants;
    p_uint m_max_inhabitants;
    static const p_uint m_food_needs;

    bool m_hasFood;

    // social_score
    // eco_score
    // env_score
};

#endif // !HOUSING_H