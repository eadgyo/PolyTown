#pragma once
// Contient les information n�cessaires pour le jeu
#include "../Quadtree/QTEntity.h"
#include "../Quadtree/QuadTree.h"

struct GameStruct
{
	// G�rer collisions et affichages
	QuadTree QTCollision;

	// Gestion des ressources
	
	// Gestion de l'eau
	QuadTree QTWaterGen;
	QuadTree QTEauRes;

	// Gestion de l'�lectricit�
	QuadTree QTElecGen;
	QuadTree QTElecRes;

	// Gestion des routes
	QuadTree QTRoads;
	QuadTree QTHabitations;


};