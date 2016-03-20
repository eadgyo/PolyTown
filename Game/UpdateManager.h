#pragma once
#include "../GameContent/Road.h"
#include "../Game/GameStruct.h"

class UpdateManager
{
public:
	UpdateManager();
    UpdateManager(GameStruct* game_struct);

	void initialize(GameStruct* gameStruct);

	// ----- SETTER ----- //
    void setGameStruct(GameStruct* game_struct);
	
	// Links automatiquement faits
	void add(QTEntity* qtEntity);
	void addRoad(QTEntity* qtEntity);
	void remove(QTEntity* qtEntity);
	void removeRoad(Road* road); // Suppresion des connectors...

	void linkRoadGuess(Road* r1, Road* connector);
	void linkRoadNext(Road* r1, Road* connector); // Road Connector
	void linkRoadLast(Road* r1, Road* connector);
	void linkRoadNextLast(Road* r1, Road* r2);
	void linkRoadLastLast(Road* r1, Road* r2);
	void linkRoadNextNext(Road* r1, Road* r2);
	void linkRoadLastNext(Road* r1, Road* r2);

private:
	GameStruct* gameStruct;
};