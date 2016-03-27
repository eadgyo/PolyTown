#pragma once
#include "Layer.h"

class ScoresLayer : public Layer
{
public:
	ScoresLayer(Graphics* g);
	~ScoresLayer();

	void initialize(int x, int y, int width, int height, std::string police, unsigned size,
		myColor textColor, myColor backgroundColor, GameStruct* gs);
	void update(float dt);
	void render(Graphics* g);
	LayerNs::LayerEvent handleEvent(Input& input, const Vector3D& translation);
protected:
	std::string m_police;
	unsigned m_size;
	myColor m_textColor;
	myColor m_backGroundColor;
	Image* round;

	const std::string IMAGE_NAME_LL = "LeftLayer.png";
	const int POS_IMAGE_ROUND_LL = 1;
	const int SIZE_SPRITE_LL = 128;
	const int SIZE_IMAGE_ROUND_LL = 8;
};

