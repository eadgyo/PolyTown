#ifndef STRUCT_FACTORY_H
#define STRUCT_FACTORy_H

#include "../Graphics/Graphics.h"

#include "../GameContent/Housing/House.h"
#include "../GameContent/Housing/Building.h"

#include "../GameContent/SocialBuilding/SocialBuilding.h"
#include "../GameContent/SocialBuilding/FireStation.h"

#include "../GameContent/Resources/PowerPlant.h"
#include "../GameContent/Resources/WaterTower.h"

#include "../GameContent/Factory/Farm.h"
#include "../GameContent/Factory/Shop.h"
#include "../GameContent/Factory/Manufactory.h"

class StructFactory
{
public:
    // ----- GETTER ----- //

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

private:
    StructFactory();
};

#endif // !STRUCT_FACTORY_H