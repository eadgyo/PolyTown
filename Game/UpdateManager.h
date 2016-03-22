#pragma once

#include "GameStruct.h"

class UpdateManager
{
public:
    UpdateManager();
    UpdateManager(GameStruct* game_struct);

    // ----- GETTER ----- //

    // ----- SETTER ----- //
    void setGameStruct(GameStruct* game_struct);

    // ----- UPDATE ----- //
    void update();
    void updateScoreDD();
    void updateScoreSoc();
    void updateScoreEco();
    void updateScoreEnv();

private:
    GameStruct* gs;

};