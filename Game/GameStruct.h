#pragma once

#include "../Constant.h"

#include "../GameContent/GameContent.h"

#include "../Quadtree/QTEntity.h"
#include "../Quadtree/QuadTree.h"
#include "../Quadtree/QuadTreeSpecial.h"

#include <iostream>
#include <string>

// Contient les information nécessaires pour le jeu

class GameStruct
{
public:
    GameStruct()
    {
    }

    void display()
    {
        std::cout << getDate() << " : ";
        std::cout << "DD = " << score_dd << " ";
        std::cout << "SS = " << score_soc << " ";
        std::cout << "SM = " << score_eco << " ";
        std::cout << "SE = " << score_env << " ";
        std::cout << "H = " << inhabitants << " ";
        std::cout << "W = " << workers << " ";
        std::cout << "U = " << unemployment*100 << "% ";
        std::cout << "M = " << money << " " << std::endl;
    }

	std::string getScore()
	{
		std::string a = "";
		a += "DD = " + std::to_string(score_dd) + " ";
		a += "SS = " + std::to_string(score_soc) + " ";
		a += "SM = " + std::to_string(score_eco) + " ";
		a += "SE = " + std::to_string(score_env) + " ";
		a += "M = " + std::to_string(money) + " " ;
		return a;
	}

    std::string getDate() const
    {
        std::string date = "";
        unsigned int t = time;

        date += std::to_string(2016 + GAME_SPEED * t / (360 * 1000));
        t = t % (360 * 1000 / GAME_SPEED);
        std::string months = std::to_string(1 + GAME_SPEED * t / (30 * 1000));
        t = t % (30 * 1000 / GAME_SPEED);
        if (months.size() == 1) {
            months = '0' + months;
        }
        date = months + '/' + date;
        std::string days = std::to_string(1 + GAME_SPEED * t / 1000);
        if (days.size() == 1) {
            days = '0' + days;
        }
        date = days + '/' + date;

        return date;
    }

    void initialize(float width, float height)
    {
		// Il faut des rec plus grands pour y stocker les grands cercles
		sRectangle bigRec = sRectangle::createSRectangleCenter(Vector3D(width*0.5f, height*0.5f), width*5.0f, height*5.0f);
		QTWaterGen.setRect(bigRec);
		QTElecGen.setRect(bigRec);

        sRectangle rec(0.0f, 0.0f, width, height);
        QTCollision.setRect(rec);
        
        QTWaterRes.setRect(rec);
       
        QTElecRes.setRect(rec);
        QTRoads.setRect(rec);
        QTHabitations.setRect(rec);
        QTPollutionWater.setRect(rec);
        QTPollutionAir.setRect(rec);
    }


    // Time
    unsigned int time = 0;

    // Scores
    p_uint score_dd = 0;
    p_uint score_soc = 0;
    p_uint score_eco = 0;
    p_uint score_env = 0;

    // Stats
    p_uint money = START_MONEY_AMOUNT;
    p_uint money_earned = 0;
    p_uint inhabitants = 0;
    p_uint free_inhabitants = 0;
    p_uint workers = 0;
    p_uint free_workers = 0;

    // Ratio
    float unemployment = 0.0f;
    float taxation_inhab = START_TAXATION_INHAB;
    float taxation_work = START_TAXATION_WORK;

    // Compteur des structures alimentées
    unsigned int struct_counter[5] = {0}; // Housing | Social | Manufactory | Energy | Water

    // ----- ENTITIES ----- //
    std::vector<Housing*> housing; // Habitations
    std::vector<Factory*> factory; // Bâtiments économiques
    std::vector<SocialBuilding*> social; // Bâtiments sociaux
    std::vector<PollutionArea*> pollution; // Zones de pollution

    Housing* best_housing = NULL;
    Housing* worst_housing = NULL;
    Factory* best_factory = NULL;
    Factory* worst_factory = NULL;

    // Gérer collisions et affichages
    // Autre que les routes
    QuadTree QTCollision;

    // Gestion des ressources

    // Gestion de l'eau
	QuadTreeSpecial QTWaterGen;
    QuadTree QTWaterRes;

    // Gestion de l'électricité
    QuadTreeSpecial QTElecGen;
    QuadTree QTElecRes;

    // Gestion des routes
    QuadTree QTRoads;
    QuadTree QTHabitations; // Toutes les habitations

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

    QTEntity* lastSelected = NULL;
    QTEntity* tempEntity = NULL;
    Form* possibleForm = NULL;
    bool isLastMakable = false;
    int roadState = -1;

    // Séléction Interface
    int state = -1;
    int stateIn = -1;

    // Affichage écran
    // Taille map
    sRectangle mapRec;
    // Zone affichage
    sRectangle zoneToDisplay;

    bool isReady = false;

	bool isDebugQuadTree = false;
	bool isDebugRoad = true;
	bool isDebugEntity = true;
	bool isDebugGenResLink = true;
};