#include "WaterTower.h"

WaterTower::WaterTower(int x, int y) :
    QTEntityBuild(WATER_TOWER_RECTANGLE(x, y)), Resources(WATER_TOWER_RADIUS)
{
    setName(WATER_TOWER_NAME);
}
