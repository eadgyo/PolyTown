#include "Shop.h"

Shop::Shop(Graphics* graphics, int x, int y) :
    Displayable(SHOP_RECTANGLE(x, y), new Image(graphics, SHOP_FRAME_WIDTH, SHOP_FRAME_HEIGHT, SHOP_FRAME_NUMBER, SHOP_IMAGE_COLS, SHOP_IMAGE_NAME), x, y),
    Factory(SHOP_MAX_WORKERS, SHOP_INCOME_RATE),
    Energy(SHOP_ENERGY_NEEDS)
{
}