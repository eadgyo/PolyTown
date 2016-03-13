#include "Menu.h"

Menu::Menu()
{
}

Menu::~Menu()
{
}

void Menu::initialize(int width, int height)
{
	if (isInitialized)
		return;

	// Initialisation des noms boutons
	std::string boutonsTexte[] = { "Nouvelle Partie",
		"Charger", "Score", "Cr�dit", "Exit", ""};

	int posX = width/2;
	int startY = (int) (height*0.2f);

	// Cr�ation des boutons
	unsigned i = 0;
	while(boutonsTexte[i].compare("") != 0)
	{
		Bouton* bouton = new Bouton(boutonsTexte[i], posX, startY, SIZE_BW, SIZE_BH);
		bouton->setColor(1.0f, 0, 0, 1);
		boutons.push_back(bouton);
		startY += (int) (SIZE_BH*1.2f);
		i += 1;
	}

	// Si besoin de Boutons sp�ciaux, cette m�thode est � modifier
	isInitialized = true;
}
void Menu::reset()
{

}
void Menu::render(Graphics* g)
{
	// On affiche les boutons
	for (unsigned i = 0; i < boutons.size(); i++)
	{
		boutons[i]->render(g);
	}

}
void Menu::update(float dt)
{

}
HudEvent Menu::handleEvent(Input& input)
{
	if (input.getLastEvent() == SDL_MOUSEBUTTONUP && input.getMousePressed(0))
	{
		const int *mousePosI = input.getMousePos();
		Vector3D mousePos((float) mousePosI[0], (float) mousePosI[1], 0, true);

		// On regarde si le clique est sur un bouton
		unsigned i = 0;
		while(i < boutons.size() && !boutons[i]->isColliding(mousePos))
		{
			i++;
		}
		switch (i)
		{
		case 0: // Nouvelle partie
			std::cout << "Ok";
			return NEW_GAME | RESET;
		case 1:
			return LOAD_GAME | RESET;
		case 2:
			return SCORE | RESET;
		case 3:
			return CREDIT | RESET;
		case 4:
			return EXIT;
		default:
			return OK;
		}
	}

	return HudEvent::OK;
}

void Menu::resize(int width, int height)
{
}
