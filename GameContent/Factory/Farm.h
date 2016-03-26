#ifndef FARM_H
#define FARM_H

#include "Factory.h"

#include "../Resources/Water.h"
#include "../Pollution/WaterPollution.h"

class Farm final : public virtual Factory, public virtual Water
{
public:
    Farm(int x, int y);

    // ----- GETTER ----- //
    bool isWorking() const;

    // ----- SETTER ----- //
    void init(WaterPollution* water_pollution);
    void update();

private:
    p_uint m_output_rate;

    WaterPollution* m_water_pollution;
};

#endif // FARM_H