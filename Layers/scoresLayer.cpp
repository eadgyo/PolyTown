#include "ScoresLayer.h"



ScoresLayer::ScoresLayer(Graphics* g) : Layer(g)
{
	m_textColor = 0;
	m_backGroundColor = 0;
	// Création de l'image servant dessiner le PopUp
	round = new Image(g, (float)SIZE_SPRITE_LL, (float)SIZE_SPRITE_LL, POS_IMAGE_ROUND_LL, IMAGE_NAME_LL);
	// On met la bonne taille à l'image
	round->setSize(SIZE_IMAGE_ROUND_LL);
	round->setFlipV(true);
}


ScoresLayer::~ScoresLayer()
{
}

void ScoresLayer::initialize(int x, int y, int width, int height,
	std::string police, unsigned size, myColor textColor, myColor backgroundColor,
	GameStruct* gs)
{
	Layer::initialize(x, y, width, height, gs);
	m_police = police;
	m_size = size;
	m_textColor = textColor;
	m_backGroundColor = backgroundColor;
	round->setColor(backgroundColor);

	round->setX(round->getWidth()*0.5f);
	round->setY(height - round->getHeight()*0.5f);
}

void ScoresLayer::update(float dt)
{
}

void ScoresLayer::render(Graphics * g)
{
	g->translate(rec.getLeft());

	sRectangle rec1(0.0f, 0.0f, rec.getWidth(), rec.getHeight() - round->getHeight());
	sRectangle rec2(round->getWidth(), rec.getHeight() - round->getHeight(), rec.getWidth() - round->getWidth(), round->getHeight());

	g->setColor(m_backGroundColor);
	g->render(rec1);
	g->render(rec2);

	g->render((*round));

	g->renderTextCenteredTTF("test", gs->getScore(), myColor::WHITE(), Vector3D(rec.getWidth()*0.5f, rec.getHeight()*0.5f), 14);

	g->translate(-rec.getLeft());
}

LayerNs::LayerEvent ScoresLayer::handleEvent(Input & input, const Vector3D & translation)
{
	return LayerNs::NOCOLLISION;
}
