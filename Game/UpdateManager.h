#pragma once

#include "../Constant.h"
#include "GameStruct.h"
#include "../Quadtree/QTEntity.h"

class UpdateManager
{
public:
    UpdateManager();
    UpdateManager(GameStruct* game_struct);

    // ----- SETTER ----- //
    void setGameStruct(GameStruct* game_struct);

	// Links automatiquement faits
	void add(QTEntity* qtEntity);
	void addRoad(QTEntity* qtEntity);
	void remove(QTEntity* qtEntity);
	void removeRoad(Road* road); // Suppresion des connectors...

	void linkRoadNext(Road* r1, Road* connector); // Road Connector
	void linkRoadPrev(Road* r1, Road* connector);
	void linkRoadNextPrev(Road* r1, Road* r2);
	void linkRoadPrevPrev(Road* r1, Road* r2);
	void linkRoadNextNext(Road* r1, Road* r2);
	void linkRoadPrevNext(Road* r1, Road* r2);

private:
    GameStruct* gs;
};