#pragma once

#include "../Quadtree/QTEntity.h"
#include "../HUD/Input.h"
#include "../Layers/Layer.h"
#include "GameStruct.h"
#include "../GameContent/Road.h"
#include "UpdateManager.h"

// Readme

// Pour la création des roads le snapp peut se coller plus loins
// A l'inverse pour les batiments on regarde juste le snapp si en collision

class CreatorManager
{
public:
	CreatorManager();
	~CreatorManager();

	void initialize(GameStruct* gameStruct);

	void addRoad(Road* road);
	void add(QTEntity* qtEntity);
	bool isMakableRoadSnapp(Road* road);
	bool isMakableSnapp(QTEntity* qtEntity);
	bool isMakable(QTEntity* qtEntity);

	void removeRoad(Road* road);
	void remove(QTEntity* qtEntity);


	// Add road functions
	void handleStartDivision(Road* actualRoad, Road* colliding, Road* connector);
	void handleEndDivision(Road* actualRoad, Road* colliding, Road* connector);
	void handleDoubleDivision(Road* actualRoad, Road* colliding, Road* connector);
	Road* divide(Road* actual, std::map<float, Road*>& myRoad, float scalar,
		const Vector3D& start, const Vector3D& director, float width, float width2, float thetat);
	
	// IsMakableRoadSnapp function
	bool preIsMakableRoadSnapp(Road* road, std::vector<Road*>& roadsColliding, std::vector<int>& side);

	void getColliding(QTEntity* qtEntity, std::vector<QTEntity*>& colliding);
	void getColliding(QTEntity* qtEntity, std::vector<QTEntity*>& colliding, Vector3D& push);

	float getMaxOfMin(const Vector3D& center, const Vector3D& director, Form form);
	float getMinOfMax(const Vector3D& center, const Vector3D& director, Form form);

private:
	GameStruct *gameStruct;
	UpdateManager updateManager;

	//Save
	std::vector<Road*> roadsGood;
	std::vector<int> states;

	// Nombre d'essais max pour isMakableSnapp
	const int MAX_TRY_SNAPP_QTENTITY = 10;
	// Distance maximale pour le snapp, isMakableSnapp
	const float DISTANCE_MAX_SNAPP = 10.0f;
	
	// PreIsMakableSnappRoad
	// Angle Min entre 2 routes lors de la collision Debut/Fin
	const float MIN_ANGLE2D = 0.25f;
	// Angrandissement des rectangles Debut/Fin
	const float DEF_WIDTH_ROAD = 10.0f;
	const float DEF_HEIGHT_ROAD = 10.0f;
	// Taille à partir de laquelle on considère que l'élément est trop petit
	// Pour MidColls
	const float LESS_HEIGHT_MID_ROAD = 40.0f;
	// Taille de route considérée comme trop petite
	const float MIN_HEIGHT_ROAD = 15.0f;
};