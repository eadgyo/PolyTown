#include "PowerPlant.h"

PowerPlant::PowerPlant(std::string name, int x, int y) :
    QTEntity(POWER_PLANT_RECTANGLE(x, y))
{
    setName(name);
}