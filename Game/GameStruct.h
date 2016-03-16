#pragma once
// Contient les information nécessaires pour le jeu
#include "../Quadtree/QTEntity.h"
#include "../Quadtree/QuadTree.h"

struct GameStruct
{
	// Gérer collisions et affichages
	QuadTree QTCollision;

	// Gestion des ressources
	
	// Gestion de l'eau
	QuadTree QTWaterGen;
	QuadTree QTEauRes;

	// Gestion de l'électricité
	QuadTree QTElecGen;
	QuadTree QTElecRes;

	// Gestion des routes
	QuadTree QTRoads;
	QuadTree QTHabitations;


};