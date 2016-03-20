#include "UpdateManager.h"

UpdateManager::UpdateManager() {}

UpdateManager::UpdateManager(GameStruct* game_struct)
{
    setGameStruct(game_struct);
}

// ----- SETTER ----- //
void UpdateManager::setGameStruct(GameStruct* game_struct)
{
    gs = game_struct;
}

