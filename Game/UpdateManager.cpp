#include "UpdateManager.h"

UpdateManager::UpdateManager() : gs(NULL)
{
}

UpdateManager::UpdateManager(GameStruct* game_struct)
{
    gs = game_struct;
}

// ----- GETTER ----- //


// ----- SETTER ----- //
void UpdateManager::setGameStruct(GameStruct* game_struct)
{
    gs = game_struct;
}

// ----- UPDATE ----- //
void UpdateManager::update()
{

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