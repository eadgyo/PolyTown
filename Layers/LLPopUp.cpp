#include "LLPopUp.h"



LLPopUp::LLPopUp(Graphics* g) : Layer(g)
{
	state = -1;
	// Création de l'image servant dessiner le PopUp
	round = new Image(g, (float) SIZE_SPRITE_LL, (float) SIZE_SPRITE_LL, POS_IMAGE_ROUND_LL, IMAGE_NAME_LL);
	// On met la bonne taille à l'image
	round->setSize(SIZE_IMAGE_ROUND_LL);
}


LLPopUp::~LLPopUp()
{
}

void LLPopUp::initialize(
	int x,
	int y,
	int width,
	int height,
	myColor backGround,
	int widthButton,
	int heightButton, 
	const Vector3D & posStart,
	const Vector3D & add,
	std::string* texts,
	myColor color,
	int numberOfTexts,
	unsigned int size,
	std::string police,
	myColor colorText)
{
	Layer::initialize(x, y, width, height);
	this->backGround = backGround;
	round->setColor(backGround);
	// Initialisation par bouton texte
	Vector3D pos = posStart;
	// Création des boutons textes
	for (unsigned i = 0; i < (unsigned) numberOfTexts; i++)
	{
		BoutonText* b = new BoutonText(graphics, texts[i], colorText, size,  police, (int) pos.x(), (int) (pos.y() + heightButton*0.5f), widthButton, heightButton);
		b->setColor(color);
		b->setDrawRec(true);
		boutons.push_back(b);
		pos += add;
	}
}

void LLPopUp::update(float dt)
{

}

void LLPopUp::render(Graphics* g)
{
	graphics->translate(rec.getLeft());

	// On rend le background
	// L'affichage du background est légérement différent
	float width = round->getWidth();
	float height = round->getHeight();

	// Affichage des rounds
	round->setFlipH(false);
	round->setFlipV(false);
	round->setLeftPos(Vector3D(0, 0));
	round->draw(g);
	round->setFlipH(true);
	round->setLeftPos(Vector3D(rec.getWidth() - width, 0.0f));
	round->draw(g);
	round->setFlipV(true);
	round->setLeftPos(Vector3D(rec.getWidth() - width, rec.getHeight() - height));
	round->draw(g);
	round->setFlipH(false);
	round->setLeftPos(Vector3D(0.0f, rec.getHeight() - height));
	round->draw(g);

	// Maintenant on affiche les rectangles
	sRectangle rec1(0.0f, height, rec.getWidth(), rec.getHeight() - 2 * height);
	sRectangle rec2(width, 0.0f, rec.getWidth() - 2 * width, height);
	sRectangle rec3(width, rec.getHeight() - height, rec.getWidth() - 2 * width, height);

	g->setColor(backGround);

	g->render(rec1);
	g->render(rec2);
	g->render(rec3);

	for (unsigned i = 0; i < boutons.size(); i++)
	{
		if (i != state)
			boutons[i]->render(g);
		else
		{
			myColor color = boutons[i]->getColor();
			myColor remplacement;
			remplacement = color * 1.2f;
			remplacement.a = 1.0f;
			boutons[i]->setColor(remplacement);
			boutons[i]->render(g);
			boutons[i]->setDrawRec(true);
			boutons[i]->setColor(color);
		}
	}

	graphics->translate(-rec.getLeft());
}

LayerNs::LayerEvent LLPopUp::handleEvent(Input& input, const Vector3D& translation)
{
	if (input.getMousePressed(0))
	{
		Vector3D mousePos = input.getMousePos();
		mousePos -= rec.getLeft();
		for (unsigned i = 0; i < boutons.size(); i++)
		{
			if (boutons[i]->isColliding(mousePos))
			{
				state = i;
				return LayerNs::COLLISION | LayerNs::UPDATE_STATE | LayerNs::CLOSE;
			}
		}
	}
	return LayerNs::NOCOLLISION;
}
