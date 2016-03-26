#pragma once

#include "../Constant.h"

#include "../GameContent/Housing/House.h"
#include "../GameContent/Housing/Building.h"

#include "../GameContent/SocialBuilding/SocialBuilding.h"
#include "../GameContent/SocialBuilding/FireStation.h"

#include "../GameContent/Resources/PowerPlant.h"
#include "../GameContent/Resources/WaterTower.h"

#include "../GameContent/Factory/Farm.h"
#include "../GameContent/Factory/Shop.h"
#include "../GameContent/Factory/Manufactory.h"

// Contient les information nécessaires pour le jeu
#include "../Quadtree/QTEntity.h"
#include "../Quadtree/QuadTree.h"

#include <iostream>
#include <string>

class GameStruct
{
public:
    GameStruct() :
        time(0),
        
        score_dd(0),
        score_soc(0),
        score_eco(0),
        score_env(0),
        
        money(START_MONEY_AMOUNT),
        inhabitants(0),
        workers(0),

        unemployment(0),
        taxation_inhab(START_TAXATION_INHAB),
        taxation_work(START_TAXATION_WORK)
    {
    }

    void display()
    {
        /*std::cout << score_dd << ' ';
        std::cout << score_soc << ' ';
        std::cout << score_eco << ' ';
        std::cout << score_env << std::endl;*/

        std::cout << getDate() << " : ";
        std::cout << "H = " << inhabitants << " ";
        std::cout << "W = " << workers << " ";
        std::cout << "U% = " << unemployment << " ";
        std::cout << "M = " << money << " " << std::endl;
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
		sRectangle rec(width*0.5f, height*0.5f, width, height);
		QTCollision.setRect(rec);
		QTWaterGen.setRect(rec);
		QTWaterRes.setRect(rec);
		QTElecGen.setRect(rec);
		QTElecRes.setRect(rec);
		QTRoads.setRect(rec);
		QTHabitations.setRect(rec);
		QTPollutionWater.setRect(rec);
		QTPollutionAir.setRect(rec);
	}
	

    // Time
    unsigned int time;

    // Scores
    p_uint score_dd;
    p_uint score_soc;
    p_uint score_eco;
    p_uint score_env;

    // Stats
    p_uint money;
    p_uint inhabitants;
    p_uint workers;
    p_uint food_production;
    p_uint food_consumption;

    // Ratio
    float unemployment;
    float taxation_inhab;
    float taxation_work;

    // Compteur des structures alimentées
    unsigned int struct_counter[5] = {0}; // Housing | Social | Manufactory | Energy | Water

    // ----- ENTITIES ----- //
    std::vector<Housing*> housing; // Habitations
    std::vector<Factory*> factory; // Bâtiments économiques
    std::vector<SocialBuilding*> social; // Bâtiments sociaux

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

    QTEntity* lastSelected;
    Form* possibleForm;
    bool isLastMakable;
};