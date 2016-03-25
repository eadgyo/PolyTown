#include "AirPollution.h"

AirPollution::AirPollution(int x, int y) :
    QTEntity(Circle(Vector3D(x, y), 0)),
    PollutionArea(AIR_POLLUTION, AIR_POLLUTION_DECREASE_RATE)
{
}