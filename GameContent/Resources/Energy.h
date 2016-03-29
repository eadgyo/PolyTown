#ifndef ENERGY_H
#define ENERGY_H

#include "../../Constant.h"
class Energy;

#include "PowerPlant.h"

class Energy
{
public:
    Energy();
    Energy(p_uint energy_needs);

    // ----- GETTER ----- //
    virtual p_uint getEnergyNeeds() const = 0;
    bool hasEnergy() const;
	
	PowerPlant* getPowerPlant();
	void setPowerPlant(PowerPlant* power_plant);

protected:
    p_uint m_energy_needs;
    PowerPlant* m_power_plant;
};

#endif // !ENERGY_H