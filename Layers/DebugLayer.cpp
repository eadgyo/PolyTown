#include "DebugLayer.h"

DebugLayer::DebugLayer(Graphics * g) : Layer(g)
{
	m_textColor = 0;
	m_backGroundColor = 0;
}

DebugLayer::~DebugLayer()
{
}

void DebugLayer::initialize(int x, int y, int width, int height, std::string police, unsigned size, myColor textColor, myColor backgroundColor, GameStruct * gs)
{
	Layer::initialize(x, y, width, height, gs);
	m_textColor = textColor;
	m_backGroundColor = backgroundColor;

	
	int addX = 30;
	int posX = 4*addX;

	BoutonText* road = new BoutonText(graphics, "R", textColor, size, posX, (int) (height/3), 30, 10);
	posX += addX;
	buttons.push_back(road);
	BoutonText* quadtree = new BoutonText(graphics, "Q", textColor, size, posX, (int)(height / 3), 30, 10);
	posX += addX;
	buttons.push_back(quadtree);
	BoutonText* entities = new BoutonText(graphics, "E", textColor, size, posX, (int)(height / 3), 30, 10);
	posX += addX;
	buttons.push_back(entities);
	BoutonText* link = new BoutonText(graphics, "L", textColor, size, posX, (int)(height / 3), 30, 10);
	buttons.push_back(link);
}

void DebugLayer::update(float dt)
{
}

void DebugLayer::render(Graphics * g)
{
	g->translate(rec.getLeft());

	if (gs->isDebugRoad)
		buttons[0]->setColor(m_backGroundColor*1.4f);
	else
		buttons[0]->setColor(m_backGroundColor);
	buttons[0]->render(g);

	if (gs->isDebugQuadTree)
		buttons[1]->setColor(m_backGroundColor*1.4f);
	else
		buttons[1]->setColor(m_backGroundColor);
	buttons[1]->render(g);

	if (gs->isDebugEntity)
		buttons[2]->setColor(m_backGroundColor*1.4f);
	else
		buttons[2]->setColor(m_backGroundColor);
	buttons[2]->render(g);

	if (gs->isDebugGenResLink)
		buttons[3]->setColor(m_backGroundColor*1.4f);
	else
		buttons[3]->setColor(m_backGroundColor);
	buttons[3]->render(g);

	g->translate(-rec.getLeft());
}

LayerNs::LayerEvent DebugLayer::handleEvent(Input & input, const Vector3D & translation)
{
	Vector3D mousePos = input.getMousePos();
	mousePos -= rec.getLeft();
	if (input.getMousePressed(0))
	{

		unsigned i = 0;
		while (i < buttons.size() && !buttons[i]->isColliding(mousePos))
		{
			i++;
		}

		if (i != buttons.size())
		{
			switch (i)
			{
			case 0:
				gs->isDebugRoad = !gs->isDebugRoad;
				break;
			case 1:
				gs->isDebugQuadTree = !gs->isDebugQuadTree;
				break;
			case 2:
				gs->isDebugEntity = !gs->isDebugEntity;
				break;
			case 3:
				gs->isDebugGenResLink = !gs->isDebugGenResLink;
				break;
			default:
				break;
			}
			return LayerNs::COLLISION;
		}
	}
	return LayerNs::NOCOLLISION;
}
