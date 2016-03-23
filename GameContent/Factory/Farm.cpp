#include "Farm.h"

Farm::Farm(int x, int y) :
    QTEntity(FARM_RECTANGLE(x, y)),
    Factory(FARM_MAX_WORKERS, FARM_INCOME_RATE),
    Water(FARM_ENERGY_NEEDS),
    m_output_rate(FARM_OUTPUT_RATE)
{
    setName(FARM_NAME);
}