#include "Farm.h"

Farm::Farm(Graphics* graphics, int x, int y) :
    QTEntity(FARM_RECTANGLE(x, y)),
    Displayable(FARM_NAME, new Image(graphics, FARM_FRAME_WIDTH, FARM_FRAME_HEIGHT, FARM_FRAME_NUMBER, FARM_IMAGE_COLS, FARM_IMAGE_NAME), x, y),
    Factory(FARM_MAX_WORKERS, FARM_INCOME_RATE),
    Water(FARM_ENERGY_NEEDS),
    m_output_rate(FARM_OUTPUT_RATE)
{
}