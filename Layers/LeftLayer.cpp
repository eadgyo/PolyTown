#include "LeftLayer.h"

LeftLayer::LeftLayer(Graphics* g) : Layer(g)
{
	state = -1;
	stateIn = 1;
	actualI = -1;
}

void LeftLayer::initialize(int x, int y, int width, int height)
{
	Layer::initialize(x, y, width, height);
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
		Bouton *bouton = new Bouton2Images(graphics, image, imageB, posX, posY, SIZE_CIRCLE_LL, SIZE_CIRCLE_LL, false);
		posY += addY;
		boutons.push_back(bouton);
	}
	
	posY = addY / 2  - SIZE_CIRCLE_LL*0.5f;
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
			(SIZE_PER_TEXT_POPUP_LL)*(sizeTexts[i] + 1) + add,
			color,
			(int) (FACTOR_SIZE_BOUTON_POPUP_LL*WIDTH_POPUP_LL),
			SIZE_PER_TEXT_POPUP_LL,
			Vector3D((int) (WIDTH_POPUP_LL*0.5f), STARTY_BUTTON_POPUP),
			Vector3D(0.0f, (float) ADD_Y_POPUP_LL),
			textsP[i], color*0.8f,
			sizeTexts[i], 15,
			"test",
			myColor(0.0f, 0.0f, 0.0f));
		posY += addY;
		popUps.push_back(popUp);
	}

	
	for (unsigned i = 0; i < boutons.size(); i++)
	{
		boutons[i]->setColor(0.5f, 0.5f, 0.5f, 1.0f);
	}

	isInitialized = true;
}

void LeftLayer::reset()
{

}

void LeftLayer::resize(int width, int height)
{
}

void LeftLayer::render(Graphics * g)
{
	render(g, Vector3D(false));
}

void LeftLayer::render(Graphics * g, const Vector3D translation)
{
	Vector3D trans = translation + rec.getLeft();
	g->translate(trans);
	for (unsigned i = 0; i < boutons.size(); i++)
	{
		if(actualI != i)
			boutons[i]->render(g);
		else
		{
			Bouton2Images* cast = dynamic_cast<Bouton2Images*>(boutons[i]);
			if (cast != NULL)
			{
				cast->addColor2(myColor(-0.0f, -0.3f, -0.3f, 0.0f));
				boutons[i]->render(g);
				cast->addColor2(myColor(0.0f, 0.0f, 0.0f, 0.0f));
			}
			else
			{
				boutons[i]->setAddColorB(myColor(-0.0f, -0.2f, -0.2f, 0.0f));
				boutons[i]->render(g);
				boutons[i]->setAddColorB(myColor(0.0f, 0.0f, 0.0f, 0.0f));
			}
		}
	}

	if (actualI != -1)
	{
		popUps[actualI]->render(g);
	}

	
	g->translate(-trans);
}

void LeftLayer::update(float dt)
{

}

LayerNs::LayerEvent LeftLayer::handleEvent(Input & input)
{
	if (input.getMousePressed(0))
	{
		Vector3D mousePos = input.getMousePos();
		mousePos -= rec.getLeft();

		// Si y a une collision avec un popUp
		if (actualI != -1 && popUps[actualI]->isColliding(mousePos))
		{
			LayerNs::LayerEvent res = popUps[actualI]->handleEvent(input);
			if (res % LayerNs::UPDATE_STATE)
			{
				if (state != -1 && state != actualI)
				{
					// Reset ancien élément séléctionné
					popUps[state]->setState(-1);

				}
				// On update l'élément
				state = actualI;
				stateIn = popUps[actualI]->getState();
				
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
