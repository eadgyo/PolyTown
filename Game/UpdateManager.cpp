#include "UpdateManager.h"

UpdateManager::UpdateManager() : gs(NULL)
{
}

UpdateManager::UpdateManager(GameStruct* game_struct)
{
    gs = game_struct;
}

void UpdateManager::setGameStruct(GameStruct* game_struct)
{
    gs = game_struct;
}

