#ifndef POWER_PLANT_H
#define POWER_PLANT_H

class PowerPlant;

#include "Energy.h"
#include "Resources.h"

class PowerPlant : public Resources
{
public:
    PowerPlant(std::string name, int x, int y);
	bool addConsumer(QTEntity* qtEntity);

private:

};

#endif // !POWER_PLANT_H