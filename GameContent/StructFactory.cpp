#include "StructFactory.h"

// ----- GETTER ----- //

// RoadZ
Road* StructFactory::newRoad(int x1, int y1, int x2, int y2, float width)
{
	return Road::create2pointsP(Vector3D(x1, y1), Vector3D(x2, y2), width);
}

// Housing
House* StructFactory::newHouse(int x, int y)
{
    return new House(x, y);
}

House* StructFactory::newLowImpactHouse(int x, int y)
{
    return new House(x, y, LOW_IMPACT_HOUSE_ENERGY_NEEDS, LOW_IMPACT_HOUSE_WATER_NEEDS);
}

Building* StructFactory::newBuilding(int x, int y)
{
    return new Building(x, y);
}

Building* StructFactory::newLowImpactBuilding(int x, int y)
{
    return new Building(x, y, LOW_IMPACT_BUILDING_ENERGY_NEEDS, LOW_IMPACT_BUILDING_WATER_NEEDS);
}

// SocialBuilding
SocialBuilding* StructFactory::newSchool(int x, int y)
{
    return new SocialBuilding(SCHOOL_NAME, SCHOOL_RECTANGLE(x, y), SCHOOL_FRAME_WIDTH, SCHOOL_FRAME_HEIGHT, SCHOOL_FRAME_NUMBER, SCHOOL_IMAGE_COLS, SCHOOL_IMAGE_NAME, x, y, SCHOOL_SCORE, SCHOOL_RATIO, SCHOOL_RADIUS);
}

SocialBuilding* StructFactory::newHospital(int x, int y)
{
    return new SocialBuilding(HOSPITAL_NAME, HOSPITAL_RECTANGLE(x, y), HOSPITAL_FRAME_WIDTH, HOSPITAL_FRAME_HEIGHT, HOSPITAL_FRAME_NUMBER, HOSPITAL_IMAGE_COLS, HOSPITAL_IMAGE_NAME, x, y, HOSPITAL_SCORE, HOSPITAL_RATIO, HOSPITAL_RADIUS);
}

FireStation* StructFactory::newFireStation(int x, int y)
{
    return new FireStation(x, y);
}

SocialBuilding* StructFactory::newPoliceStation(int x, int y)
{
    return new SocialBuilding(POLICE_STATION_NAME, POLICE_STATION_RECTANGLE(x, y), POLICE_STATION_FRAME_WIDTH, POLICE_STATION_FRAME_HEIGHT, POLICE_STATION_FRAME_NUMBER, POLICE_STATION_IMAGE_COLS, POLICE_STATION_IMAGE_NAME, x, y, POLICE_STATION_SCORE, POLICE_STATION_RATIO, POLICE_STATION_RADIUS);
}

// Resources
PowerPlant* StructFactory::newPowerPlant(int x, int y)
{
    return new PowerPlant(POWER_PLANT_NAME, x, y);
}

WaterTower* StructFactory::newWaterTower(int x, int y)
{
    return new WaterTower(x, y);
}

// Factory
Farm* StructFactory::newFarm(int x, int y)
{
    return new Farm(x, y);
}

Shop* StructFactory::newShop(int x, int y)
{
    return new Shop(x, y);
}

Manufactory* StructFactory::newManufactory(int x, int y)
{
    return new Manufactory(x, y);
}