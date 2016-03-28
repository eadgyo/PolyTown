#ifndef STRUCT_FACTORY_H
#define STRUCT_FACTORy_H

class StructFactory;


#include "GameContent.h"

class StructFactory
{
public:
    // ----- GETTER ----- //

	// Roads
	static Road* newRoad(int x1, int y1, int x2, int y2, float width);

    // Housing
    static House* newHouse(int x, int y);
    static House* newLowImpactHouse(int x, int y);
    static Building* newBuilding(int x, int y);
    static Building* newLowImpactBuilding(int x, int y);

    // SocialBuilding
    static SocialBuilding* newSchool(int x, int y);
    static SocialBuilding* newHospital(int x, int y);
    static FireStation* newFireStation(int x, int y);
    static SocialBuilding* newPoliceStation(int x, int y);

    // Resources
    static PowerPlant* newPowerPlant(int x, int y);
    static WaterTower* newWaterTower(int x, int y);

    // Factory
    static Farm* newFarm(int x, int y);
    static Shop* newShop(int x, int y);
    static Manufactory* newManufactory(int x, int y);

    // Pollution
    static WaterPollution* newWaterPollution();
    static AirPollution* newAirPollution();

private:
    StructFactory();
};

#endif // !STRUCT_FACTORY_H