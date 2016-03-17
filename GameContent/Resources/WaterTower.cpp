#include "WaterTower.h"

WaterTower::WaterTower(Graphics * graphics, int x, int y) :
    QTEntity(WATER_TOWER_RECTANGLE(x, y)),
    Displayable(WATER_TOWER_NAME, new Image(graphics, WATER_TOWER_FRAME_WIDTH, WATER_TOWER_FRAME_HEIGHT, WATER_TOWER_FRAME_NUMBER, WATER_TOWER_IMAGE_COLS, WATER_TOWER_IMAGE_NAME), x, y)
{
}
