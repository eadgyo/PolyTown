#pragma once

#include "../Quadtree/QTEntity.h"
#include "../HUD/Input.h"
#include "../GameContent/Connector.h"
#include "GameStruct.h"
#include "../Layers/Layer.h"
#include "../GameContent/Road.h"
#include "LinkManager.h"
#include "../GameContent/Road.h"

// Readme

// Pour la création des roads le snapp peut se coller plus loins
// A l'inverse pour les batiments on regarde juste le snapp si en collision

class CreatorManager
{
public:
	struct CRoadStruct
	{
		// notre == la route qu'on est en train de créer
		// Debut
		std::vector<Road*> startRoads0;
		std::vector<Road*> startRoads1; // l'autre début est dans notre début
		std::vector<Road*> startRoads2; // l'autre fin est dans notre début
		std::vector<Connector*> startConnector;

		// End
		std::vector<Road*> endRoads0;
		std::vector<Road*> endRoads1; // l'autre début est dans notre fin
		std::vector<Road*> endRoads2; // l'autre fin est dans notre fin
		std::vector<Connector*> endConnector;

		// Mid
		std::vector<Road*> midRoads0; 
		std::vector<Road*> midRoads1; // l'autre début est dans notre mid
		std::vector<Road*> midRoads2; // l'autre fin est dans notre mid

		void clear()
		{
			startConnector.clear();
			startRoads0.clear();
			startRoads1.clear();
			startRoads2.clear();

			endConnector.clear();
			endRoads0.clear();
			endRoads1.clear();
			endRoads2.clear();

			midRoads0.clear();
			midRoads1.clear();
			midRoads2.clear();
		};

		void set(CRoadStruct& cRS)
		{
			clear();

			startConnector.insert(startConnector.end(), cRS.startConnector.begin(), cRS.startConnector.end());
			startRoads0.insert(startRoads0.end(), cRS.startRoads0.begin(), cRS.startRoads0.end());
			startRoads1.insert(startRoads1.end(), cRS.startRoads1.begin(), cRS.startRoads1.end());
			startRoads2.insert(startRoads2.end(), cRS.startRoads2.begin(), cRS.startRoads2.end());

			endConnector.insert(endConnector.end(), cRS.endConnector.begin(), cRS.endConnector.end());
			endRoads0.insert(endRoads0.end(), cRS.endRoads0.begin(), cRS.endRoads0.end());
			endRoads1.insert(endRoads1.end(), cRS.endRoads1.begin(), cRS.endRoads1.end());
			endRoads2.insert(endRoads2.end(), cRS.endRoads2.begin(), cRS.endRoads2.end());

			midRoads0.insert(midRoads0.end(), cRS.midRoads0.begin(), cRS.midRoads0.end());
			midRoads1.insert(midRoads1.end(), cRS.midRoads1.begin(), cRS.midRoads1.end());
			midRoads2.insert(midRoads2.end(), cRS.midRoads2.begin(), cRS.midRoads2.end());
		};

		std::set<Road*> getAll()
		{
			std::set<Road*> roads;
			for (unsigned i = 0; i < startConnector.size(); i++)
			{
				roads.insert(startConnector[i]);
			}
			for (unsigned i = 0; i < startRoads0.size(); i++)
			{
				roads.insert(startRoads0[i]);
			}
			for (unsigned i = 0; i < startRoads1.size(); i++)
			{
				roads.insert(startRoads1[i]);
			}
			for (unsigned i = 0; i < startRoads2.size(); i++)
			{
				roads.insert(startRoads2[i]);
			}

			for (unsigned i = 0; i < endConnector.size(); i++)
			{
				roads.insert(endConnector[i]);
			}
			for (unsigned i = 0; i < endRoads0.size(); i++)
			{
				roads.insert(endRoads0[i]);
			}
			for (unsigned i = 0; i < endRoads1.size(); i++)
			{
				roads.insert(endRoads1[i]);
			}
			for (unsigned i = 0; i < endRoads2.size(); i++)
			{
				roads.insert(endRoads2[i]);
			}

			for (unsigned i = 0; i < midRoads0.size(); i++)
			{
				roads.insert(midRoads0[i]);
			}
			for (unsigned i = 0; i < midRoads1.size(); i++)
			{
				roads.insert(midRoads1[i]);
			}
			for (unsigned i = 0; i < midRoads2.size(); i++)
			{
				roads.insert(midRoads2[i]);
			}

			return roads;
		}
	};

	CreatorManager();
	~CreatorManager();

	void initialize(GameStruct* gs, LinkManager* linkManager);

	bool addRoad(Road* road);
	bool add(QTEntityBuild* qtEntity);
	
	bool isMakableSnappRoad(Road* road);
	bool isMakableSnappRoad(Road* road, CRoadStruct& cRoadStrcut);
	bool isMakableSnapp(QTEntity* qtEntity);
	bool isMakable(QTEntity* qtEntity);

	void removeRoad(Road* road);
	void remove(QTEntityBuild* qtEntity);

	// Handle 	
	// Pour détecter les types
	void handleAllStart(CRoadStruct& cRoadStruct, Road* startR);
	void handleAllEnd(CRoadStruct& cRoadStruct, Road* endR);
	void handleAllMid(CRoadStruct& cRoadStruct, std::map<float, Road*>& myRoad, const Vector3D& start, const Vector3D& director, float width, float theta);
	Road* createConnectorFromMap(Road* actualRoad, Road* roadi, std::map<float, Road*>& myRoad, const Vector3D& start, const Vector3D& director, float width, float theta);
	bool verifyAfterCorrection(Road* road, std::set<Road*> roadsConnected);
	Connector* createConnector(Road* r1, bool isLast);

	// Add road functions
	// Pour la création de la route finale
	void handleStartDivision(Road* actualRoad, Road* colliding, Road* connector);
	void handleEndDivision(Road* actualRoad, Road* colliding, Road* connector);
	void handleDoubleDivision(Road* actualRoad, Road* colliding, Road* connector);
	Road* divide(Road* actual, std::map<float, Road*>& myRoad, float scalar,
		const Vector3D& start, const Vector3D& director, float width, float width2, float thetat);
	

	// IsMakableRoadSnapp function
	// Un nettoyage de cRoadStruct dans ces fonctions
	bool moveStart(Road* road, const Vector3D& director, float width, const Vector3D& end, CRoadStruct& cRoadStruct);
	bool moveEnd(Road* road, const Vector3D& director, float width, const Vector3D& start, CRoadStruct& cRoadStruct);
	void cleanListsConnector(std::vector<Connector*>& connectors, std::vector<Road*>& roadsStart, std::vector<Road*>& roadsEnd);
	bool cleanAndGetBest(Road * road, const Vector3D& director, const Vector3D& otherSideP, std::vector<Connector*> connectors,
		std::vector<Road*> roads0, std::vector<Road*> roads1, std::vector<Road*> roads2, Vector3D& pToModified);

	// IsMakableRoadSnapp function
	bool isCorrect(Road* road, CRoadStruct cRoadStruct);
	bool analyseType(myRectangle& startColl, myRectangle& endColl, std::vector<myRectangle> midColls,
		Road* roadi, const Vector3D& director, const Vector3D& normalDirector, float scalarStartNormal, float scalarEndNormal, CRoadStruct& cRoadStruct);
	bool setTypeStartColliding(Road* roadi, myRectangle& coll, CRoadStruct& cRoadStruct);
	bool setTypeEndColliding(Road* roadi, myRectangle& coll, CRoadStruct& cRoadStruct);
	bool setTypeMidColliding(Road* roadi, float scalarStartR, float scalarEndR, const Vector3D normalDirector, CRoadStruct& cRoadStruct);
	

	// Gestion des connecteurs
	int alreadyIn(Road* road, std::vector<Road*>& roads);
	bool alreadyInCo(Connector* connector, std::vector<Road*>& roads);
	void alreadyInAndDelete(Connector* connector, std::vector<Road*>& roads);
	//void addIfPossible(Road* road, Road* co, std::vector<Road*>& roads);

	bool getRoadColliding(Form form, std::vector<Road*>& roads);
	bool getIsCollidingEntity(Road* road);

	void getColliding(QTEntity* qtEntity, std::vector<QTEntity*>& colliding);
	void getColliding(QTEntity* qtEntity, std::vector<QTEntity*>& colliding, Vector3D& push);
	void getCollidingStop(QTEntity* qtEntity, std::vector<QTEntity*>& colliding, Vector3D& push);
	QTEntity* getCollidingPushMax(QTEntity* qtEntity, std::vector<QTEntity*>& colliding, Vector3D& push, float& t_max);

	float getMaxOfMin(const Vector3D& center, const Vector3D& director, const Form& form);
	float getMinOfMax(const Vector3D& center, const Vector3D& director, const Form& form);

private:
	GameStruct *gs;
	LinkManager *linkManager;
	
	// Nombre d'essais max pour isMakableSnapp
	const int MAX_TRY_SNAPP_QTENTITY = 10;
	// Distance maximale pour le snapp, isMakableSnapp
	const float DISTANCE_MAX_SNAPP = 40.0f;
	
	// PreIsMakableSnappRoad
	// Angle Min entre 2 routes lors de la collision Debut/Fin
	const float MIN_ANGLE2D = 0.25f;
	// Angrandissement des rectangles Debut/Fin
	const float DEF_WIDTH_ROAD = 10.0f;
	const float DEF_HEIGHT_ROAD = 10.0f;
	// Taille à pupdateManagerartir de laquelle on considère que l'élément est trop petit
	// Pour MidColls
	const float LESS_HEIGHT_MID_ROAD = 40.0f;
	// Taille de route considérée comme trop petite
	const float MIN_HEIGHT_ROAD = 15.0f;
	const float MIN_DIFF_CONNECTOR = 0.5f;
};