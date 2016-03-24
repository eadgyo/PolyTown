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
    void update(unsigned int dt);
    void updateFast(unsigned int dt);
    void updateSlow(unsigned int dt);
    void updateTime(unsigned int dt);

    void updateScoreDD();
    void updateScoreSoc();
    void updateScoreEco();
    void updateScoreEnv();

    void updateInhabitants();
    void updateWorkers();
    void updateUnemployment();
    void updateMoney();

private:
    GameStruct* gs;
};