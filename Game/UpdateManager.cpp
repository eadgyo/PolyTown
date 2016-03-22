#include "UpdateManager.h"

#include "../GameContent/Housing/Housing.h"
#include "../GameContent/Factory/Factory.h"
#include "../GameContent/Factory/Shop.h"

using namespace std;

UpdateManager::UpdateManager() : gs(NULL)
{
}

UpdateManager::UpdateManager(GameStruct* game_struct)
{
    gs = game_struct;
}

// ----- GETTER ----- //
std::vector<QTEntity*> UpdateManager::getEntities(QuadTree qt) const
{
    vector<QTEntity*> entities;

    qt.addEntities(entities);

    return entities;
}

// ----- SETTER ----- //
void UpdateManager::setGameStruct(GameStruct* game_struct)
{
    gs = game_struct;
}

// ----- UPDATE ----- //
void UpdateManager::update()
{
    updateInhabitants();
    updateWorkers();
}

void UpdateManager::updateScoreDD()
{
    gs->score_dd = (gs->score_soc + gs->score_eco + gs->score_env) / 3;
}

void UpdateManager::updateScoreSoc()
{
}

void UpdateManager::updateScoreEco()
{
}

void UpdateManager::updateScoreEnv()
{
}

void UpdateManager::updateInhabitants()
{
    vector<QTEntity*> entities = getEntities(gs->QTHabitations);
    p_uint inhabitants = 0;

    for (unsigned i = 0; i < entities.size(); i++) {
        inhabitants += (dynamic_cast<Housing*> (entities[i]))->getInhabitants();
    }

    gs->inhabitants = inhabitants;
}

void UpdateManager::updateWorkers()
{
    vector<QTEntity*> entities = getEntities(gs->QTElecRes);
    Factory* factory = NULL;
    p_uint workers = 0;

    for (unsigned i = 0; i < entities.size(); i++) {
        factory = dynamic_cast<Factory*> (entities[i]);
        if (factory) {
            workers += factory->getWorkers();
        }
    }

    gs->workers = workers;
}