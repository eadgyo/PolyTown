#include "StartMenu.h"

StartMenu::StartMenu(Graphics *g) : Interface(g)
{
}

StartMenu::~StartMenu()
{
}

void StartMenu::initialize(int width, int height)
{
	Interface::initialize(width, height);

	if (isInitialized)
		return;

	// Initialisation des noms boutons
	std::string boutonsTexte[] = { "Nouvelle Partie",
		"Charger", "Score", "Crédit", "Exit", ""};
	

	int posX = width/2;
	int startY = (int) (height*0.3f);

	// Création des boutons
	unsigned i = 0;
	while(boutonsTexte[i].compare("") != 0)
	{
		Bouton* bouton = new BoutonText(graphics, boutonsTexte[i], myColor(0.1f, 0.1f, 0.1f, 1.0f), 17, posX, startY, SIZE_BW, SIZE_BH);
		bouton->setColor(0.7f, 0.7f, 0.7f, 1.0f);
		boutons.push_back(bouton);
		startY += (int) (SIZE_BH*1.4f);
		i += 1;
	}

	// Si besoin de Boutons spéciaux, cette méthode est à modifier
	isInitialized = true;
}
void StartMenu::reset()
{

}
void StartMenu::render(Graphics* g)
{
	g->renderTextCenteredTTF("test", "POLYTOWN", myColor::WHITE(0.7f), Vector3D(width*0.5f, height*0.08f), 32);
	g->renderTextCenteredTTF("test", "--- DEVELOPPEMENT DURABLE ---", myColor::WHITE(0.5f), Vector3D(width*0.5f, height*0.12f), 16);
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