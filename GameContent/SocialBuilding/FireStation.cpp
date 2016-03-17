#include "FireStation.h"

FireStation::FireStation(Graphics* graphics, int x, int y) :
    QTEntity(FIRE_STATION_RECTANGLE(x, y)),
    Displayable(FIRE_STATION_NAME, new Image(graphics, FIRE_STATION_FRAME_WIDTH, FIRE_STATION_FRAME_HEIGHT, FIRE_STATION_FRAME_NUMBER, FIRE_STATION_IMAGE_COLS, FIRE_STATION_IMAGE_NAME), x, y),
    SocialBuilding(FIRE_STATION_SCORE, FIRE_STATION_RATIO, FIRE_STATION_RADIUS)
{
}