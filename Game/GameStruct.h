#pragma once

#include "../Constant.h"

// Contient les information nécessaires pour le jeu
#include "../Quadtree/QTEntity.h"
#include "../Quadtree/QuadTree.h"

class GameStruct
{
public:
    GameStruct() :
        score_dd(0),
        score_soc(0),
        score_eco(0),
        score_env(0),
        money(START_MONEY_AMOUNT),
        inhabitants(0),
        workers(0)
    {
    }

    void display()
    {
        std::cout << score_dd << ' ';
        std::cout << score_soc << ' ';
        std::cout << score_eco << ' ';
        std::cout << score_env << std::endl;
    }

    // Scores
    p_uint score_dd;
    p_uint score_soc;
    p_uint score_eco;
    p_uint score_env;

    // Stats
    p_uint money;
    p_uint inhabitants;
    p_uint workers;

    // Ratio
    float unemployment;

    // Compteur des structures alimentées
    unsigned int struct_counter[5] = {0}; // Housing | Social | Manufactory | Energy | Water

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