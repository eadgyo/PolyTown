#include "StartMenu.h"

StartMenu::StartMenu()
{
}

StartMenu::~StartMenu()
{
}

void StartMenu::initialize(int width, int height)
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
void StartMenu::reset()
{

}
void StartMenu::render(Graphics* g)
{
	// On affiche les boutons
	for (unsigned i = 0; i < boutons.size(); i++)
	{
		boutons[i]->render(g);
	}

}

HudNs::HudEvent StartMenu::handleEvent(Input& input)
{
	if (input.getMousePressed(0))
	{
		Vector3D mousePos = input.getMousePos();

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
			return HudNs::NEW_GAME | HudNs::RESET;
		case 1:
			return HudNs::LOAD_GAME | HudNs::RESET;
		case 2:
			return HudNs::SCORE | HudNs::RESET;
		case 3:
			return HudNs::CREDIT | HudNs::RESET;
		case 4:
			return HudNs::EXIT;
		default:
			return HudNs::OK;
		}
	}

	return HudNs::OK;
}

void StartMenu::resize(int width, int height)
{
}