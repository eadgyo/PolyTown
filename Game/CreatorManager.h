#pragma once

#include "../Quadtree/QTEntity.h"
#include "../HUD/Input.h"
#include "../Layers/Layer.h"
#include "GameStruct.h"
#include "../GameContent/Road.h"


// Readme

// Pour la cr�ation des roads le snapp peut se coller plus loins
// A l'inverse pour les batiments on regarde juste le snapp si en collision

class CreatorManager
{
public:
	CreatorManager();
	~CreatorManager();

	void initialize(GameStruct* gameStruct);
	
	// Fonction d'ajout ou de suppression � appeler pour ajouter ou pour savoir si l'utilisateur souhaite ajouter
	void add(QTEntity* qtEntity);
	void addRoad(Road* road);
	bool isMakableRoadSnapp(Road* road); // Avec ou non gestion d'un snapps
	bool isMakableSnapp(QTEntity* qtEntity); // Avec ou non gestion d'un snapp
	bool isMakableRoad(Road* road); // Avec ou non gestion d'un snapps
	bool isMakable(QTEntity* qtEntity); // Avec ou non gestion d'un snapp

	void replaceRoad(Road* road);
	void removeRoad(Road* road);
	void removeRoad(Road* road, const Vector3D& center, float dist);
	void remove(QTEntity* qtEntity);

	// GameStruct
	void setGameStruct(GameStruct* gameStruct);

	bool snappRoad(Road* road, std::vector<Road*>& roadsGood, std::vector<int>& sides);
	bool snapp(QTEntity* qtEntity, float minDif, std::vector<QTEntity*>& entitiesColliding, std::vector<Vector3D>& pushes, std::vector<float>& ts);

	// isPossibleToMake
	// Fonction compl�te utiliser pour les snapps
	// Ne pas utiliser directement
	bool preIsMakableRoadSnapp(Road* road, std::vector<Road*>& roadsColliding, std::vector<int>& side);
	bool preIsMakableSnapp(QTEntity* qtEntity, float minDif, std::vector<QTEntity*>& entitiesColliding, std::vector<Vector3D>& pushes, std::vector<float>& ts);
	bool preIsMakableRoad(Road* road, std::vector<Road*>& roadsColliding, std::vector<int>& side);
	bool preIsMakable(QTEntity* qtEntity);

	// Add gameStruct
	// Pas besoin
	void addGameStruct(QTEntity* qtEntity);
	void addRoadGameStruct(Road* road);

	Road* findRoad(Road* road, std::map<float, Road*>& myRoad);
	void handleStartRoad(Road* road, Road* roadSnapp, std::vector<Road*>& roads, std::map<float, Road*>& myRoad);
	void handleEndRoad(Road* road, Road* roadSnapp, std::vector<Road*>& roads, std::map<float, Road*>& myRoad);
	void handleCrossingRoad(Road* road, Road* roadSnapp, std::vector<Road*>& roads, std::map<float, Road*>& myRoad);


	// Remove compute
	void recalculateAfterRemove(Road* road);
	void removeGameStruct(QTEntity* qtEntity);
	void removeRoadGameStruct(Road* road);

	void render(Graphics * g, const Vector3D translation);
	LayerNs::LayerEvent virtual handleEvent(Input& input);
	
	// Connexitude
	bool stillConnected(Road* start, Road* end);
	int getConnexitude();
	void freeConnexitude(int n);
	void setConnexitude(Road* start, int n);



protected:
	GameStruct* gameStruct;

	// Save
	std::vector<Road*> roadsGood;
	std::vector<int> side;

};

