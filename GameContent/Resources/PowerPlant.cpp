#include "PowerPlant.h"

PowerPlant::PowerPlant(std::string name, Graphics* graphics, int x, int y) :
    Displayable(name, POWER_PLANT_RECTANGLE(x, y), new Image(graphics, POWER_PLANT_FRAME_WIDTH, POWER_PLANT_FRAME_HEIGHT, POWER_PLANT_FRAME_NUMBER, POWER_PLANT_IMAGE_COLS, POWER_PLANT_IMAGE_NAME), x, y)
{
}