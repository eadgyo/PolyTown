#include "PowerPlant.h"

PowerPlant::PowerPlant(std::string name, int x, int y) :
    QTEntityBuild(POWER_PLANT_RECTANGLE(x, y)), Resources(POWER_PLANT_OUTPUT, POWER_PLANT_RADIUS)
{
    setName(name);
}

bool PowerPlant::addConsumer(QTEntity * qtEntity)
{
	// On tante un cast en energie
	Energy* cast = dynamic_cast<Energy*>(qtEntity);
	if (cast == NULL)
	{
		std::cout << "Tentative Liaison batiment non energivore" << std::endl;
		return false;
	}

	if (Resources::addConsumer(qtEntity, cast->getEnergyNeeds()))
	{
		cast->setPowerPlant(this);
		return true;
	}
	return false;
}
