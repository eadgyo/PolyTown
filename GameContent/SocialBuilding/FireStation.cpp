#include "FireStation.h"

FireStation::FireStation(int x, int y) :
    QTEntity(FIRE_STATION_RECTANGLE(x, y)),
    SocialBuilding(FIRE_STATION_SCORE, FIRE_STATION_RATIO, FIRE_STATION_RADIUS)
{
    setName(FIRE_STATION_NAME);
}

// ----- GETTER ----- //
bool FireStation::isWorking() const
{
    return (SocialBuilding::isWorking() && (m_water_tower != NULL));
}

// ----- SETTER ----- //
void FireStation::init(PowerPlant* power_plant, WaterTower* water_tower)
{
    SocialBuilding::init(power_plant);
    m_water_tower = water_tower;
}