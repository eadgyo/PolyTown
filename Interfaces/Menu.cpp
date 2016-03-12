#include "Menu.h"

Menu::Menu()
{
}

Menu::~Menu()
{
}

void Menu::initialize(int width, int height)
{

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
		bouton->setColor(1.0f, 0, 0, 0);
		boutons.push_back(bouton);
		startY += (int) (SIZE_BH*1.2f);
		i += 1;
	}

	// Si besoin de Boutons spéciaux, cette méthode est à modifier
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


	return HudEvent::OK;
}

void Menu::resize(int width, int height)
{
}
