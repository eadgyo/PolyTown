#pragma once

#include "GameStruct.h"

#include <vector>

class UpdateManager
{
public:
    UpdateManager();
    UpdateManager(GameStruct* game_struct);

    // ----- GETTER ----- //
    std::vector<QTEntity*> getEntities(QuadTree) const;

    // ----- SETTER ----- //
    void setGameStruct(GameStruct* game_struct);

    // ----- UPDATE ----- //
    void update();
    void updateScoreDD();
    void updateScoreSoc();
    void updateScoreEco();
    void updateScoreEnv();

    void updateInhabitants();
    void updateWorkers();

private:
    GameStruct* gs;
};