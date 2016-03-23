#include "FireStation.h"

FireStation::FireStation(int x, int y) :
    QTEntity(FIRE_STATION_RECTANGLE(x, y)),
    SocialBuilding(FIRE_STATION_SCORE, FIRE_STATION_RATIO, FIRE_STATION_RADIUS)
{
    setName(FIRE_STATION_NAME);
}