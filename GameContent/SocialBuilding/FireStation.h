#ifndef FIRE_STATION_H
#define FIRE_STATION_H

#include "SocialBuilding.h"
#include "../Resources/Water.h"

class FireStation : public virtual SocialBuilding, public virtual Water
{
public:
    FireStation(int x, int y);

    // ----- GETTER ----- //
    p_uint getWaterNeeds() const;
    bool isWorking() const;

    // ----- SETTER ----- //
    void init(PowerPlant* power_plant, WaterTower* water_tower);

private:

};

#endif // !FIRE_STATION_H