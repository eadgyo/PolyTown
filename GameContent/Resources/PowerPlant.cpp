#include "PowerPlant.h"

PowerPlant::PowerPlant(std::string name, int x, int y) :
    QTEntityBuild(POWER_PLANT_RECTANGLE(x, y)), Resources(POWER_PLANT_OUTPUT, POWER_PLANT_RADIUS)
{
    setName(name);
}