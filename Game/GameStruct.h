#pragma once
// Contient les information nécessaires pour le jeu
#include "../Quadtree/QTEntity.h"
#include "../Quadtree/QuadTree.h"

struct GameStruct
{
	// Gérer collisions et affichages
	// Autre que les routes
	QuadTree QTCollision;

	// Gestion des ressources
	
	// Gestion de l'eau
	QuadTree QTWaterGen;
	QuadTree QTWaterRes;

	// Gestion de l'électricité
	QuadTree QTElecGen;
	QuadTree QTElecRes;

	// Gestion des routes
	QuadTree QTRoads;
	QuadTree QTHabitations;

	QuadTree QTPollutionWater;
	QuadTree QTPollutionAir;


	// Roads
	std::map<int, int> roadsConnex;


	//

	std::set<QTEntity*> noElecGen;
	std::set<QTEntity*> noWaterGen;


	// CreatorManager
	int topConnexitude = 0;
	std::vector<int> fConnexitudes;

	QTEntity* lastSelected;
	Form* possibleForm;
	bool isLastMakable;
};