#include "FireStation.h"

FireStation::FireStation(int x, int y) :
    QTEntityBuild(FIRE_STATION_RECTANGLE(x, y)),
    SocialBuilding(FIRE_STATION_SCORE, FIRE_STATION_RADIUS)
{
    setName(FIRE_STATION_NAME);
}

// ----- GETTER ----- //
p_uint FireStation::getWaterNeeds() const
{
    if (isWorking()) {
        return m_water_needs;
    } else {
        return 0;
    }
}

bool FireStation::isWorking() const
{
    return (PoweredSocialBuilding::isWorking() && (m_water_tower != NULL));
}

// ----- SETTER ----- //
void FireStation::init(PowerPlant* power_plant, WaterTower* water_tower)
{
    PoweredSocialBuilding::init(power_plant);
    m_water_tower = water_tower;
}