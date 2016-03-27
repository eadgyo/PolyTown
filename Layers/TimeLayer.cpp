#include "TimeLayer.h"



TimeLayer::TimeLayer(Graphics* g) : Layer(g)
{
	m_textColor = 0;
	m_backGroundColor = 0;
	// Création de l'image servant dessiner le PopUp
	round = new Image(g, (float)SIZE_SPRITE_LL, (float)SIZE_SPRITE_LL, POS_IMAGE_ROUND_LL, IMAGE_NAME_LL);
	// On met la bonne taille à l'image
	round->setSize(SIZE_IMAGE_ROUND_LL);
	round->setFlipV(true);
}


TimeLayer::~TimeLayer()
{
}

void TimeLayer::initialize(int x, int y, int width, int height, std::string police, unsigned size,
	myColor textColor, myColor backgroundColor, GameStruct* gs)
{

	Layer::initialize(x, y, width, height, gs);
	m_police = police;
	m_size = size;
	m_textColor = textColor;
	m_backGroundColor = backgroundColor;
	round->setColor(backgroundColor);

	
}

void TimeLayer::update(float dt)
{
}

void TimeLayer::render(Graphics * g)
{
	g->translate(rec.getLeft());

	round->setFlipH(false);
	round->setX(round->getWidth()*0.5f);
	round->setY(rec.getHeight() - round->getHeight()*0.5f);
	g->render((*round));

	round->setFlipH(true);
	round->setX(rec.getWidth() - round->getWidth()*0.5f);
	g->render((*round));

	sRectangle rec1(0.0f, 0.0f, rec.getWidth(), rec.getHeight() - round->getHeight());
	sRectangle rec2(round->getWidth(), rec.getHeight() - round->getHeight(), rec.getWidth() - round->getWidth()*2, round->getHeight());

	g->setColor(m_backGroundColor);
	g->render(rec1);
	g->render(rec2);

	

	
	
	g->translate(-rec.getLeft());
}

LayerNs::LayerEvent TimeLayer::handleEvent(Input& input, const Vector3D& translation)
{
	return LayerNs::NOCOLLISION;
}