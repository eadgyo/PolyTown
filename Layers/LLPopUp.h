#pragma once
#include "Layer.h"
#include "../GameElements/BoutonText.h"

class LLPopUp : public Layer
{
public:
	LLPopUp(Graphics* g);
	~LLPopUp();

	// Initialisation du texte
	virtual void initialize(int x, int y, int width, int height, myColor backGround, int widthButton, int heightButton, const Vector3D& posStart,
		const Vector3D& add, std::string* texts, myColor color, int numberOfTexts, unsigned int size, std::string police, myColor textColor);
	virtual void initialize(int x, int y, int width, int height) {};
	void reset() {};
	void resize(int width, int height) {};

	virtual void update(float dt);
	virtual void render(Graphics* g);
	virtual void render(Graphics * g, const Vector3D translation);
	LayerNs::LayerEvent handleEvent(Input& input);

	int getState() const { return state; };
	void setState(int state) { this->state = state; };

protected:
	std::vector<Bouton*> boutons;
	int state;
	myColor backGround;
	myColor textColor;
	Image* round;

	// Const
	const std::string IMAGE_NAME_LL = "LeftLayer.png";
	const int POS_IMAGE_ROUND_LL = 1;
	const int SIZE_SPRITE_LL = 128;
	const int SIZE_IMAGE_ROUND_LL = 8;
	
};

