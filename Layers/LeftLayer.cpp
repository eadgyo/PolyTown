#include "LeftLayer.h"

LeftLayer::LeftLayer(Graphics* g) : Layer(g)
{

	actualI = -1;
}

void LeftLayer::initialize(int x, int y, int width, int height, GameStruct* gs)
{
	Layer::initialize(x, y, width, height, gs);

	gs->state = -1;
	gs->stateIn = 1;
	
	// Création des infrastructures
	int addY = height / 8;
	int posX = width / 2;
	int posY = addY / 2;

	Vector3D left = rec.getLeft();

	sideI = new Image(graphics, 128, 128, 1, "LeftLayer.png");

	// Création des boutons
	for (unsigned i = 0; i < (unsigned) NUMBER_OF_TYPES_LL; i++)
	{
		Image* image = new Image();
		image->initialize(graphics, 128, 128, posImage[i], "LeftLayer.png");
		image->setSize(SIZE_CIRCLE_LL);
		Image* imageB = new Image();
		imageB->setColor(color1[i], color2[i], color3[i]);
		imageB->initialize(graphics, 128, 128, 0, "LeftLayer.png");
		imageB->setSize(SIZE_CIRCLE_LL);
		Bouton *bouton = new Bouton2Images(graphics, image, imageB, posX, posY,
			SIZE_CIRCLE_LL, SIZE_CIRCLE_LL, false);
		posY += addY;
		boutons.push_back(bouton);
	}
	
	posY = (int) (addY / 2  - SIZE_CIRCLE_LL*0.5f);
	// Creation des popUps
	for (unsigned i = 0; i < (unsigned) NUMBER_OF_TYPES_LL; i++)
	{
		LLPopUp* popUp = new LLPopUp(graphics);
		myColor color(color1[i], color2[i], color3[i]);
		// Initialisation du popup
		int add = (sizeTexts[i] > 1 ? PAD_Y_POPUP_LL*(sizeTexts[i] - 1) + PAD_Y_POPUP_LL : PAD_Y_POPUP_LL*sizeTexts[i] + PAD_Y_POPUP_LL);
		popUp->initialize(
			STARTX_POPUP_LL,
			posY,
			WIDTH_POPUP_LL,
			(int) ((SIZE_PER_TEXT_POPUP_LL)*(sizeTexts[i] + 0.5f) + add),
			color,
			(int) (FACTOR_SIZE_BOUTON_POPUP_LL*WIDTH_POPUP_LL),
			SIZE_PER_TEXT_POPUP_LL,
			Vector3D((int) (WIDTH_POPUP_LL*0.5f), STARTY_BUTTON_POPUP),
			Vector3D(0.0f, (float) ADD_Y_POPUP_LL),
			textsP[i], color*0.8f,
			sizeTexts[i],
			15,
			"test",
			myColor(0.0f, 0.0f, 0.0f),
			gs);
		posY += addY;
		popUps.push_back(popUp);
	}

	
	for (unsigned i = 0; i < boutons.size(); i++)
	{
		boutons[i]->setColor(0.5f, 0.5f, 0.5f, 1.0f);
	}

	isInitialized = true;
}

bool LeftLayer::isColliding(const Vector3D & mousePos)
{
	bool popUpb = false;
	if (actualI != -1)
	{
		popUpb = popUps[actualI]->isColliding(mousePos - rec.getLeft());
	}
	return Layer::isColliding(mousePos) || popUpb;
}

void LeftLayer::reset()
{
	if (gs->state != -1)
	{
		popUps[gs->state]->setState(-1);
	}
	actualI = -1;
	gs->state = -1;
	gs->stateIn = -1;
}

void LeftLayer::resize(int width, int height)
{
}

void LeftLayer::render(Graphics * g)
{
	graphics->translate(rec.getLeft());

	for (unsigned i = 0; i < boutons.size(); i++)
	{
		if (actualI != i)
		{
			if (gs->state != i)
			{
				boutons[i]->render(g);
			}
			else
			{
				Bouton2Images* cast = dynamic_cast<Bouton2Images*>(boutons[i]);
				if (cast != NULL)
				{
					cast->addColor2(myColor(-0.0f, -0.3f, -0.3f, 0.0f));
					boutons[i]->render(g);
					cast->addColor2(myColor(0.0f, 0.0f, 0.0f, 0.0f));
				}
			}
		}
		else
		{
			Bouton2Images* cast = dynamic_cast<Bouton2Images*>(boutons[i]);
			if (cast != NULL)
			{
				cast->addColor2(myColor(-0.0f, -0.5f, -0.5f, 0.0f));
				boutons[i]->render(g);
				cast->addColor2(myColor(0.0f, 0.0f, 0.0f, 0.0f));
			}
		}
	}

	if (actualI != -1)
	{
		popUps[actualI]->render(g);
	}

	graphics->translate(-rec.getLeft());
}

void LeftLayer::update(float dt)
{

}

LayerNs::LayerEvent LeftLayer::handleEvent(Input & input, const Vector3D& translation)
{
	Vector3D trans = translation + rec.getLeft();
	if (input.getMousePressed(0))
	{
		Vector3D mousePos = input.getMousePos();
		mousePos -= trans;

		// Si y a une collision avec un popUp
		if (actualI != -1 && popUps[actualI]->isColliding(mousePos))
		{
			LayerNs::LayerEvent res = popUps[actualI]->handleEvent(input, trans);
			if (res % LayerNs::UPDATE_STATE)
			{
				if (gs->state != -1 && gs->state != actualI)
				{
					// Reset ancien élément séléctionné
					popUps[gs->state]->setState(-1);

				}
				// On update l'élément
				gs->state = actualI;
				gs->stateIn = popUps[actualI]->getState();
				
			}

			if (res % LayerNs::CLOSE)
			{
				actualI = -1;
			}
		}
		else
		{
			for (unsigned i = 0; i < boutons.size(); i++)
			{
				if (boutons[i]->isColliding(mousePos))
				{
					if (actualI == i)
					{
						actualI = -1;
					}
					else
					{
						actualI = i;
					}
					return LayerNs::COLLISION;
				}
			}
		}
	}
	return LayerNs::NOCOLLISION;
}
