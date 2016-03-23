#ifndef BUILDING_H
#define BUILDING_H

#include "Housing.h"

class Building final : public Housing
{
public:
    Building(int x, int y);
    Building(int x, int y, p_uint floor);
    Building(int x, int y, p_uint water_needs, p_uint energy_needs);
    Building(int x, int y, p_uint floor, p_uint water_needs, p_uint energy_needs);

    // ----- GETTER ----- //
    p_uint getFloors() const;

    // ----- SETTER ----- //
    p_uint addFloors(p_uint n);

private:
    p_uint m_floor;
};

#endif // !BUILDING_H