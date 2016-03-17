#include "Manufactory.h"

Manufactory::Manufactory(Graphics* graphics, int x, int y) :
    Displayable(MANUFACTORY_NAME, MANUFACTORY_RECTANGLE(x, y), new Image(graphics, MANUFACTORY_FRAME_WIDTH, MANUFACTORY_FRAME_HEIGHT, MANUFACTORY_FRAME_NUMBER, MANUFACTORY_IMAGE_COLS, MANUFACTORY_IMAGE_NAME), x, y),
    Factory(MANUFACTORY_MAX_WORKERS, MANUFACTORY_INCOME_RATE),
    Energy(MANUFACTORY_ENERGY_NEEDS),
    Water(MANUFACTORY_WATER_NEEDS)
{
}