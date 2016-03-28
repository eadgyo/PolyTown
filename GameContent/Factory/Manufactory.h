#ifndef MANUFACTORY_H
#define MANUFACTORY_H

#include "Factory.h"

#include "../Resources/Energy.h"
#include "../Resources/Water.h"
#include "../Pollution/WaterPollution.h"
#include "../Pollution/AirPollution.h"

class Manufactory final : public virtual Factory, public virtual Energy, public virtual Water
{
public:
    Manufactory(int x, int y);

    // ----- GETTER ----- //
    p_uint getEnergyNeeds() const;
    p_uint getWaterNeeds() const;
    bool isWorking() const;

    // ----- SETTER ----- //
    void init(WaterPollution* water_pollution, AirPollution* air_pollution);
    void update();

private:
    WaterPollution* m_water_pollution;
    AirPollution* m_air_pollution;
};

#endif // !MANUFACTORY_H