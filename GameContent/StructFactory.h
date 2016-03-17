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
    static House* newHouse(Graphics* graphics, int x, int y);
    static House* newLowImpactHouse(Graphics* graphics, int x, int y);
    static Building* newBuilding(Graphics* graphics, int x, int y);
    static Building* newLowImpactBuilding(Graphics* graphics, int x, int y);

    // SocialBuilding
    static SocialBuilding* newSchool(Graphics* graphics, int x, int y);
    static SocialBuilding* newHospital(Graphics* graphics, int x, int y);
    static FireStation* newFireStation(Graphics* graphics, int x, int y);
    static SocialBuilding* newPoliceStation(Graphics* graphics, int x, int y);

    // Resources
    static PowerPlant* newPowerPlant(Graphics* graphics, int x, int y);
    static WaterTower* newWaterTower(Graphics* graphics, int x, int y);

    // Factory
    static Farm* newFarm(Graphics* graphics, int x, int y);
    static Shop* newShop(Graphics* graphics, int x, int y);
    static Manufactory* newManufactory(Graphics* graphics, int x, int y);

private:
    StructFactory();
};

#endif // !STRUCT_FACTORY_H