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


	const int posImage[8] = { 4, 5, 2, 6, 3, 7, 8, 12};
	const float color1[8] = { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };
	const float color2[8] = { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };
	const float color3[8] = { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };

	const int sizeTexts[8] = { 1, 4, 6, 4, 3, 4, 3, 1};
	std::string textsP[8][6] = { {"routes"},
										{"Residentielle", "Industrielle", "Commerciale", "Agricole"},
										{"Eolienne", "Hydrolienne", "Panneau solaire", "Usine à charbon", "Usine à pétrole", "Centrale Nucléaire"},
										{"Usine Incinération", "Centre enfouissement", "Centre Méthanisation", "Centre compostage"},
										{"Traitement Eaux Usées", "Stockage Eau potable", "Traitement Eau Potable"},
										{"Police", "Pompier", "Ecoles", "Hopitaux"},
										{"Stades", "Cinémas", "Parcs"},
									{"Destructor"} };


	const int SIZE_CIRCLE_LL = 64;
	const int NUMBER_OF_TYPES_LL = 8;
	const int STARTX_POPUP_LL = 105;
	const int WIDTH_POPUP_LL = 200;
	const int SIZE_PER_TEXT_POPUP_LL = 32;
	const int STARTY_BUTTON_POPUP = 10;
	const int PAD_Y_POPUP_LL = 5;
	const int ADD_Y_POPUP_LL = PAD_Y_POPUP_LL + SIZE_PER_TEXT_POPUP_LL;
	const float FACTOR_SIZE_BOUTON_POPUP_LL = 0.9f;
};