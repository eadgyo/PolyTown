#pragma once

#include "GameStruct.h"

class UpdateManager
{
public:
    UpdateManager();
    UpdateManager(GameStruct* game_struct);

    // ----- SETTER ----- //
    void setGameStruct(GameStruct* game_struct);

    // ----- UPDATE ----- //
    void update();

private:
    GameStruct* gs;

};