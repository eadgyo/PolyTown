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
		"Charger", "Score", "Crédit", "Exit", ""};

	int posX = width/2;
	int startY = (int) (height*0.2f);

	// Création des boutons
	unsigned i = 0;
	while(boutonsTexte[i].compare("") != 0)
	{
		Bouton* bouton = new Bouton(boutonsTexte[i], posX, startY, SIZE_BW, SIZE_BH);
		bouton->setColor(1.0f, 0, 0, 1);
		boutons.push_back(bouton);
		startY += (int) (SIZE_BH*1.2f);
		i += 1;
	}

	// Si besoin de Boutons spéciaux, cette méthode est à modifier
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
HudNs::HudEvent Menu::handleEvent(Input& input)
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

void Menu::resize(int width, int height)
{
}
