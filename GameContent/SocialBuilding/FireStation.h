#ifndef FIRE_STATION_H
#define FIRE_STATION_H

#include "SocialBuilding.h"
#include "../Resources/Water.h"

class FireStation : public virtual SocialBuilding, public virtual Water
{
public:
    FireStation(Graphics* graphics, int x, int y);

private:

};

#endif // !FIRE_STATION_H