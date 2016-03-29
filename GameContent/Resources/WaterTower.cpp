#include "WaterTower.h"

WaterTower::WaterTower(int x, int y) :
    QTEntityBuild(WATER_TOWER_RECTANGLE(x, y)), Resources(WATER_TOWER_OUTPUT, WATER_TOWER_RADIUS)
{
    setName(WATER_TOWER_NAME);
}

bool WaterTower::addConsumer(QTEntity * qtEntity)
{
	// On tante un cast en water
	Water* cast = dynamic_cast<Water*>(qtEntity);
	if (cast == NULL)
	{
		std::cout << "Tentative Liaison batiment non eaugivore" << std::endl;
		return false;
	}

	if (Resources::addConsumer(qtEntity, cast->getWaterNeeds()))
	{
		cast->setWaterTower(this);
		return true;
	}
	return false;
}