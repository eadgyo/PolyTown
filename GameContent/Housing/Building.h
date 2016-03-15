#ifndef BUILDING_H
#define BUILDING_H

#include "../Housing.h"

class Building : public Housing
{
public:
    Building();
    Building(p_uint water_needs, p_uint energy_needs);
    Building(p_uint water_needs, p_uint energy_needs, p_uint floor);

    // ----- GETTER ----- //
    p_uint getFloors() const;

    // ----- SETTER ----- //
    p_uint addFloors(p_uint n);

private:
    p_uint m_floor;
    p_uint m_max_floor;
    p_uint m_max_inhabitants_per_floor;
};

#endif // !BUILDING_H