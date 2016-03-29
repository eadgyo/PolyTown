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
SocialBuilding* StructFactory::newStadium(int x, int y)
{
    return new SocialBuilding(STADIUM_NAME, STADIUM_RECTANGLE(x, y), x, y, STADIUM_SCORE, STADIUM_RADIUS);
}

SocialBuilding* StructFactory::newCinema(int x, int y)
{
    return new SocialBuilding(CINEMA_NAME, CINEMA_RECTANGLE(x, y), x, y, CINEMA_SCORE, CINEMA_RADIUS);
}

SocialBuilding* StructFactory::newPark(int x, int y)
{
    return new SocialBuilding(PARK_NAME, PARK_RECTANGLE(x, y), x, y, PARK_SCORE, PARK_RADIUS);
}

// PoweredSocialBuilding
SocialBuilding* StructFactory::newSchool(int x, int y)
{
    return new PoweredSocialBuilding(SCHOOL_NAME, SCHOOL_RECTANGLE(x, y), x, y, SCHOOL_SCORE, SCHOOL_RADIUS);
}

SocialBuilding* StructFactory::newHospital(int x, int y)
{
    return new PoweredSocialBuilding(HOSPITAL_NAME, HOSPITAL_RECTANGLE(x, y), x, y, HOSPITAL_SCORE, HOSPITAL_RADIUS);
}

FireStation* StructFactory::newFireStation(int x, int y)
{
    return new FireStation(x, y);
}

SocialBuilding* StructFactory::newPoliceStation(int x, int y)
{
    return new PoweredSocialBuilding(POLICE_STATION_NAME, POLICE_STATION_RECTANGLE(x, y), x, y, POLICE_STATION_SCORE, POLICE_STATION_RADIUS);
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