#ifndef WATER_TOWER_H
#define WATER_TOWER_H

class WaterTower;

#include "Water.h"
#include "Resources.h"

class WaterTower : public virtual Resources
{
public:
    WaterTower(int x, int y);
	bool addConsumer(QTEntity* qtEntity);

private:

};

#endif // ! WATER_TOWER_H