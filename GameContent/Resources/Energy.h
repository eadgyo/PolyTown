#ifndef ENERGY_H
#define ENERGY_H

#include "../../Constant.h"
#include "PowerPlant.h"

class Energy
{
public:
    Energy();
    Energy(p_uint energy_needs);

    // ----- GETTER ----- //
    bool hasEnergy() const;

protected:
    p_uint m_energy_needs;
    PowerPlant* m_power_plant;
};

#endif // !ENERGY_H