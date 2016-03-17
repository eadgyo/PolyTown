#include "StructFactory.h"

// ----- GETTER ----- //

// Housing
House* StructFactory::newHouse(Graphics* graphics, int x, int y)
{
    return new House(graphics, x, y);
}

House* StructFactory::newLowImpactHouse(Graphics* graphics, int x, int y)
{
    return new House(graphics, x, y, LOW_IMPACT_HOUSE_ENERGY_NEEDS, LOW_IMPACT_HOUSE_WATER_NEEDS);
}

Building* StructFactory::newBuilding(Graphics* graphics, int x, int y)
{
    return new Building(graphics, x, y);
}

Building* StructFactory::newLowImpactBuilding(Graphics* graphics, int x, int y)
{
    return new Building(graphics, x, y, LOW_IMPACT_BUILDING_ENERGY_NEEDS, LOW_IMPACT_BUILDING_WATER_NEEDS);
}

// SocialBuilding
SocialBuilding* StructFactory::newSchool(Graphics* graphics, int x, int y)
{
    return new SocialBuilding(SCHOOL_NAME, SCHOOL_RECTANGLE(x, y), SCHOOL_FRAME_WIDTH, SCHOOL_FRAME_HEIGHT, SCHOOL_FRAME_NUMBER, SCHOOL_IMAGE_COLS, SCHOOL_IMAGE_NAME, graphics, x, y, SCHOOL_SCORE, SCHOOL_RATIO, SCHOOL_RADIUS);
}

SocialBuilding* StructFactory::newHospital(Graphics* graphics, int x, int y)
{
    return new SocialBuilding(HOSPITAL_NAME, HOSPITAL_RECTANGLE(x, y), HOSPITAL_FRAME_WIDTH, HOSPITAL_FRAME_HEIGHT, HOSPITAL_FRAME_NUMBER, HOSPITAL_IMAGE_COLS, HOSPITAL_IMAGE_NAME, graphics, x, y, HOSPITAL_SCORE, HOSPITAL_RATIO, HOSPITAL_RADIUS);
}

FireStation* StructFactory::newFireStation(Graphics* graphics, int x, int y)
{
    return new FireStation(graphics, x, y);
}

SocialBuilding* StructFactory::newPoliceStation(Graphics* graphics, int x, int y)
{
    return new SocialBuilding(POLICE_STATION_NAME, POLICE_STATION_RECTANGLE(x, y), POLICE_STATION_FRAME_WIDTH, POLICE_STATION_FRAME_HEIGHT, POLICE_STATION_FRAME_NUMBER, POLICE_STATION_IMAGE_COLS, POLICE_STATION_IMAGE_NAME, graphics, x, y, POLICE_STATION_SCORE, POLICE_STATION_RATIO, POLICE_STATION_RADIUS);
}

// Resources
PowerPlant* StructFactory::newPowerPlant(Graphics* graphics, int x, int y)
{
    return new PowerPlant(POWER_PLANT_NAME, graphics, x, y);
}

WaterTower* StructFactory::newWaterTower(Graphics* graphics, int x, int y)
{
    return new WaterTower(graphics, x, y);
}

// Factory
Farm* StructFactory::newFarm(Graphics* graphics, int x, int y)
{
    return new Farm(graphics, x, y);
}

Shop* StructFactory::newShop(Graphics* graphics, int x, int y)
{
    return new Shop(graphics, x, y);
}

Manufactory* StructFactory::newManufactory(Graphics* graphics, int x, int y)
{
    return new Manufactory(graphics, x, y);
}