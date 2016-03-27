#pragma once

#include "Layer.h"
#include "../GameElements/Bouton2Images.h"
#include "../GameElements/BoutonText.h"
#include "LLPopUp.h"

class LeftLayer : public Layer
{
public:
	LeftLayer(Graphics* g);
	void initialize(int x, int y, int width, int height);
	
	void reset();
	void resize(int width, int height);
	virtual void render(Graphics* g);
	virtual void render(Graphics * g, const Vector3D translation);
	void update(float dt);
	LayerNs::LayerEvent handleEvent(Input& input);

	inline int getState() { return state; };
	inline int getStateInt() { return stateIn; };
private:
	std::vector<Bouton*> boutons;
	int state;
	int stateIn;
	Image* sideI;

	std::vector<LLPopUp*> popUps;
	int actualI;


	const int posImage[7] = { 4, 5, 2, 3, 6, 7, 8 };
	const float color1[7] = { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };
	const float color2[7] = { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };
	const float color3[7] = { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };

	const int sizeTexts[7] = { 1, 4, 6, 4, 3, 4, 3};
	std::string textsP[7][6] = { {"roads"},
										{"Residentielle", "Industrielle", "Commerciale", "Agricole"},
										{"Eolienne", "Hydrolienne", "Panneau solaire", "Usine à charbon", "Usine à pétrole", "Centrale Nucléaire"},
										{"Usine Incinération", "Centre enfouissement", "Centre Méthanisation", "Centre compostage"},
										{"Traitement Eaux Usées", "Stockage Eau potable", "Traitement Eau Potable"},
										{"Police", "Pompier", "Ecoles", "Hopitaux"},
										{"Stades", "Cinémas", "Parcs"}
										};


	const int SIZE_CIRCLE_LL = 64;
	const int NUMBER_OF_TYPES_LL = 7;
	const int STARTX_POPUP_LL = 105;
	const int WIDTH_POPUP_LL = 326;
	const int SIZE_PER_TEXT_POPUP_LL = 32;
	const int STARTY_BUTTON_POPUP = 20;
	const int PAD_Y_POPUP_LL = 5;
	const int ADD_Y_POPUP_LL = PAD_Y_POPUP_LL + SIZE_PER_TEXT_POPUP_LL;
	const float FACTOR_SIZE_BOUTON_POPUP_LL = 0.9f;
};