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
std::vector<QTEntity*> UpdateManager::getEntities(QuadTree qt)
{
    vector<QTEntity*> entities;

    qt.addEntities(entities);

    cout << "A : " << entities.size() << endl;

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
    vector<QTEntity*> entities = getEntities(gs->QTHabitations);
}

void UpdateManager::updateScoreDD()
{
    gs->score_dd = (gs->score_soc + gs->score_eco + gs->score_env) / 3;
}

void UpdateManager::updateScoreSoc()
{
    p_uint score = 0;
}

void UpdateManager::updateScoreEco()
{
}

void UpdateManager::updateScoreEnv()
{
}