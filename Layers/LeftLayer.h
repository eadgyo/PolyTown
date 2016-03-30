#pragma once

#include "Layer.h"
#include "../GameElements/Bouton2Images.h"
#include "../GameElements/BoutonText.h"
#include "LLPopUp.h"

class LeftLayer : public Layer
{
public:
	LeftLayer(Graphics* g);
	void initialize(int x, int y, int width, int height, GameStruct* gs);
	
	virtual bool isColliding(const Vector3D& mousePos);
	void reset();
	void resize(int width, int height);
	virtual void render(Graphics* g);
	void update(float dt);
	LayerNs::LayerEvent handleEvent(Input& input, const Vector3D& translation);

	inline int getState() { return gs->state; };
	inline int getStateInt() { return gs->stateIn; };
private:
	std::vector<Bouton*> boutons;
	Image* sideI;

	std::vector<LLPopUp*> popUps;
	int actualI;


	const int posImage[9] = { 4, 5, 2, 6, 3, 7, 8, 9, 10};
	const float color1[9] = { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };
	const float color2[9] = { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };
	const float color3[9] = { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };

    const int sizeTexts[9] = {1, 4, 3, 4, 3, 3, 2, 1, 1};
	//const int sizeTexts[9] = { 1, 4, 3, 4, 3, 6, 2, 4, 1};
	std::string textsP[9][6] = { {"Route"},
								{"Maison", "Maison à faible impact", "Immeuble", "Immeuble à faible impact"},
								{"Zone industrielle", "Zone commerciale", "Zone agricole"},
								{"Commissariat", "Caserne", "École", "Hôpital"},
								{"Stade", "Cinéma", "Parc"},
                                {"Centrale électrique", "Eolienne", "Panneau solaire"},
								//{"Eolienne", "Hydrolienne", "Panneau solaire", "Usine à charbon", "Usine à pétrole", "Centrale nucléaire"},
								{"Stockage de l'eau potable", "Indisponible"},//"Traitement des eaux usées"},
                                {"Indisponible"},
								//{"Usine d'incinération", "Centre d'enfouissement", "Centre de méthanisation", "Centre de compostage"},
								{"Démolition"} };

	const int SIZE_CIRCLE_LL = 64;
	const int NUMBER_OF_TYPES_LL = 9;
	const int STARTX_POPUP_LL = 105;
	const int WIDTH_POPUP_LL = 240;
	const int SIZE_PER_TEXT_POPUP_LL = 32;
	const int STARTY_BUTTON_POPUP = 10;
	const int PAD_Y_POPUP_LL = 5;
	const int ADD_Y_POPUP_LL = PAD_Y_POPUP_LL + SIZE_PER_TEXT_POPUP_LL;
	const float FACTOR_SIZE_BOUTON_POPUP_LL = 0.9f;
};