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

        housingBestWorst();
        factoryBestWorst();
        
        inOutInhabitants();
        updateInhabitants();
        updateUnemployment();
        inOutWorkers();
        updateWorkers();
        updateUnemployment();

        updateFood();
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
        score += gs->social[i]->getScore();
    }
    gs->score_soc = (p_uint) ((score + gs->inhabitants) * gs->unemployment);
}

void UpdateManager::updateScoreEco()
{
    gs->score_eco = (p_uint) (gs->money_earned / gs->unemployment);
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
    if (gs->inhabitants != 0) {
        gs->unemployment = (float) (gs->inhabitants - gs->workers) / (float) (gs->inhabitants);
    } else {
        gs->unemployment = 1.0f;
    }
}

void UpdateManager::updateMoney()
{
    p_uint money = (p_uint) (gs->inhabitants * HOUSING_INCOME * gs->taxation_inhab);

    p_uint tva = 0;
    for (unsigned i = 0; i < gs->factory.size(); i++) {
        if (gs->factory[i]->isWorking()) {
            tva += gs->factory[i]->getIncome();
        }
    }
    money += (p_uint) (tva * gs->taxation_work);

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
        if (gs->housing[i]->hasFood()) {
            food_needs += gs->housing[i]->getFoodNeeds();
        }
    }

    p_uint food_production = 0;
    Farm* farm;
    for (unsigned i = 0; i < gs->factory.size(); i++) {
        if (farm = dynamic_cast<Farm*> (gs->factory[i])) {
            food_production += farm->getProdution();
        }
    }

    unsigned i = 0;
    while (food_production < food_needs && i < gs->housing.size()) {
        if (gs->housing[i]->hasFood()) {
            gs->housing[i]->noFood();
            food_needs -= gs->housing[i]->getFoodNeeds();
        }
        i++;
    }

    i = 0;
    while (food_production > food_needs && i < gs->housing.size()) {
        if (!gs->housing[i]->hasFood() && food_needs + gs->housing[i]->getFoodNeeds() <= food_production) {
            gs->housing[i]->food();
            food_needs += gs->housing[i]->getFoodNeeds();
        }
        i++;
    }
}

// ----- In - Out ----- //
void UpdateManager::housingBestWorst()
{
    Housing* best = NULL;
    Housing* worst = NULL;
    p_uint score_max = 0;
    p_uint score_min = -1; // Infini du pauvre

    for (unsigned i = 0; i < gs->housing.size(); i++) {
        if (!gs->housing[i]->isFull() && gs->housing[i]->getScore() >= score_max) {
            best = gs->housing[i];
            score_max = best->getScore();
        }
        if (!gs->housing[i]->isEmpty() && gs->housing[i]->getScore() < score_min) {
            worst = gs->housing[i];
            score_min = worst->getScore();
        }
    }

    gs->best_housing = best;
    gs->worst_housing = worst;
}

void UpdateManager::factoryBestWorst()
{
    Factory* best = NULL;
    Factory* worst = NULL;
    p_uint score_max = 0;
    p_uint score_min = -1; // Infini du pauvre

    for (unsigned i = 0; i < gs->factory.size(); i++) {
        if (!gs->factory[i]->isFull() && gs->factory[i]->getFreeWorkers() >= score_max) {
            best = gs->factory[i];
            score_max = best->getFreeWorkers();
        }
        if (!gs->factory[i]->isEmpty() && gs->factory[i]->getFreeWorkers() < score_min) {
            worst = gs->factory[i];
            score_min = worst->getFreeWorkers();
        }
    }

    gs->best_factory = best;
    gs->worst_factory = worst;
}

void UpdateManager::inOutInhabitants()
{
    p_uint incoming = gs->free_inhabitants / 2;
    p_uint outgoing = (p_uint) (gs->inhabitants * gs->unemployment / 2);

    if (gs->worst_housing) {
        gs->worst_housing->delInhabitants(outgoing);
    }
    if (gs->best_housing) {
        gs->best_housing->addInhabitants(incoming);
    }
}

void UpdateManager::inOutWorkers()
{
    p_uint incoming = (p_uint) (gs->inhabitants * gs->unemployment / 2);

    if (gs->worst_factory) {
        if (gs->worst_factory->isWorking()) {
            gs->worst_factory->delWorkers(1);
        } else {
            gs->worst_factory->empty();
        }
    }
    if (gs->best_factory) {
        gs->best_factory->addWorkers(incoming);
    }
}