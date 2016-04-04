#pragma once
#include "Layer.h"
#include "../GameElements/BoutonText.h"

class DebugLayer : public Layer
{
public:
	DebugLayer(Graphics* g);
	~DebugLayer();

	void initialize(int x, int y, int width, int height, std::string police, unsigned size,
		myColor textColor, myColor backgroundColor, GameStruct* gs);
	void update(float dt);
	void render(Graphics* g);
	LayerNs::LayerEvent handleEvent(Input& input, const Vector3D& translation);

protected:
	std::vector<BoutonText*> buttons;
	std::string m_police;
	unsigned m_size;
	myColor m_textColor;
	myColor m_backGroundColor;

};