#include "UpdateManager.h"

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
    updateSlow(dt);
    updateFast(dt);
    updateTime(dt);
}

void UpdateManager::updateFast(unsigned int dt)
{
    static unsigned int time = 0;
    time += dt;
    if (time > 1000 * UPDATE_TIME / GAME_SPEED) {
        time -= 1000 * UPDATE_TIME / GAME_SPEED;
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
    if (time > 10 * 1000 * UPDATE_TIME / GAME_SPEED) {
        time -= 10 * 1000 * UPDATE_TIME / GAME_SPEED;
        updateMoney();
        updateFactories();
        updatePollution();

        updateScoreSoc();
        updateScoreEco();
        updateScoreEnv();
        updateScoreDD();
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
    p_uint score = 0;
    for (unsigned i = 0; i < gs->social.size(); i++) {
        if (gs->social[i]->isWorking()) {
            score += gs->social[i]->getScore();
        }
    }
    gs->score_soc = (score + gs->inhabitants) * gs->unemployment;
}

void UpdateManager::updateScoreEco()
{
    gs->score_eco = gs->money * gs->unemployment + gs->money_earned;
}

void UpdateManager::updateScoreEnv()
{
    p_uint pollution = 0;
    for (unsigned i = 0; i < gs->pollution.size(); i++) {
        pollution += gs->pollution[i]->getIntensity(0);
    }
    gs->score_env = pollution;
}

void UpdateManager::updateInhabitants()
{
    p_uint inhabitants = 0;
    p_uint free_inhabitants = 0;

    for (unsigned i = 0; i < gs->housing.size(); i++) {
        inhabitants += gs->housing[i]->getInhabitants();
        free_inhabitants += gs->housing[i]->getFreeInhabitants();
    }

    gs->inhabitants = inhabitants;
    gs->free_inhabitants = free_inhabitants;
}

void UpdateManager::updateWorkers()
{
    p_uint workers = 0;
    p_uint free_workers = 0;

    for (unsigned i = 0; i < gs->factory.size(); i++) {
        workers += gs->factory[i]->getWorkers();
        free_workers += gs->factory[i]->getFreeWorkers();
    }

    gs->workers = workers;
    gs->free_workers = free_workers;
}

void UpdateManager::updateUnemployment()
{
    gs->unemployment = (float) (gs->inhabitants - gs->workers) / (float) (gs->inhabitants);
}

void UpdateManager::updateMoney()
{
    p_uint money = gs->inhabitants * HOUSING_INCOME * gs->taxation_inhab;

    p_uint tva = 0;
    for (unsigned i = 0; i < gs->factory.size(); i++) {
        if (gs->factory[i]->isWorking()) {
            tva += gs->factory[i]->getIncome();
        }
    }
    money += tva * gs->taxation_work;

    gs->money += money;
    gs->money_earned = money;
}

void UpdateManager::updateFactories()
{
    for (unsigned i = 0; i < gs->factory.size(); i++) {
        gs->factory[i]->update();
    }
}

void UpdateManager::updatePollution()
{
    for (unsigned i = 0; i < gs->pollution.size(); i++) {
        gs->pollution[i]->decreasePollution();
    }
}

void UpdateManager::updateFood()
{
    p_uint food_needs = 0;
    for (unsigned i = 0; i < gs->housing.size(); i++) {
        food_needs += gs->housing[i]->getFoodNeeds();
    }
    gs->food_needs = food_needs;

    p_uint food_production = 0;
    Farm* farm;
    for (unsigned i = 0; i < gs->factory.size(); i++) {
        if (farm = dynamic_cast<Farm*> (gs->factory[i])) {
            food_production += farm->getProdution();
        }
    }
    gs->food_production = food_production;
}