#include "WaterTower.h"

WaterTower::WaterTower(int x, int y) :
    QTEntity(WATER_TOWER_RECTANGLE(x, y))
{
    setName(WATER_TOWER_NAME);
}
