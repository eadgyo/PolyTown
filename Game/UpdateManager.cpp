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
void UpdateManager::update(unsigned int dt)
{
    updateFast(dt);
    updateSlow(dt);
    updateTime(dt);
}

void UpdateManager::updateFast(unsigned int dt)
{
    static unsigned int time = 0;
    time += dt;
    if (time > 1000 / GAME_SPEED) {
        time -= 1000 / GAME_SPEED;
        gs->display();
        updateInhabitants();
        updateWorkers();
        updateUnemployment();
    }
}

void UpdateManager::updateSlow(unsigned int dt)
{
    static unsigned int time = 0;
    time += dt;
    if (time > 10 * 1000 / GAME_SPEED) {
        time -= 10 * 1000 / GAME_SPEED;
        updateMoney();
    }
}

void UpdateManager::updateTime(unsigned int dt)
{
    gs->time += dt;
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
    p_uint inhabitants = 0;

    for (unsigned i = 0; i < gs->housing.size(); i++) {
        inhabitants += gs->housing[i]->getInhabitants();
    }

    gs->inhabitants = inhabitants;
}

void UpdateManager::updateWorkers()
{
    p_uint workers = 0;

    for (unsigned i = 0; i < gs->factory.size(); i++) {
        workers += gs->factory[i]->getWorkers();
    }

    gs->workers = workers;
}

void UpdateManager::updateUnemployment()
{
    gs->unemployment = (float) (gs->inhabitants - gs->workers) / (float) (gs->inhabitants);
}

void UpdateManager::updateMoney()
{
    gs->money += 0;
}