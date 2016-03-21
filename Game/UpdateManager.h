#pragma once
#include "../GameContent/Road.h"
#include "../GameContent/Connector.h"
#include "../Game/GameStruct.h"
#include "../Quadtree/QTEntityBuild.h"

class LinkManager
{
public:
	LinkManager();
    LinkManager(GameStruct* game_struct);

	void initialize(GameStruct* gameStruct);

	// ----- SETTER ----- //
    void setGameStruct(GameStruct* game_struct);
	
	// Links automatiquement faits
	void add(QTEntityBuild* qtEntity);
	void addRoad(QTEntity* qtEntity);
	void remove(QTEntityBuild* qtEntity);
	void removeRoad(Road* road); // Suppresion des connectors...

	void linkRoadGuess(Road* r1, Road* connector);
	void linkRoadNext(Road* r1, Road* connector); // Road Connector
	void linkRoadLast(Road* r1, Road* connector);
	void linkRoadNextLast(Road* r1, Road* r2);
	void linkRoadLastLast(Road* r1, Road* r2);
	void linkRoadNextNext(Road* r1, Road* r2);
	void linkRoadLastNext(Road* r1, Road* r2);


	void linkRoadCopyNext(Road* source, Road* dest);
	void linkRoadCopyLast(Road* source, Road* dest);

	// Connexitude
	int computeRoadIndex(std::map<float, Road*> myRoad);
	//void setConnexitudeOptimized(std::map<float, Road*> myRoad, int connex);
	int getConnexitude();
	void freeConnexitude(int n);
	void recalculateAfterRemove(Road* road);
	void setConnexitude(Road* start, int connex);
	bool stillConnected(Road* start, Road* end);

private:
	GameStruct* gameStruct;
};