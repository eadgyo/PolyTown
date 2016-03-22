#pragma once

#include "GameStruct.h"

#include <vector>

class UpdateManager
{
public:
    UpdateManager();
    UpdateManager(GameStruct* game_struct);

    // ----- GETTER ----- //
    std::vector<QTEntity*> getEntities(QuadTree);

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