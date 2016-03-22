#include "BoutonText.h"

BoutonText::BoutonText(Graphics* g, int x, int y, int width, int height) : Bouton(g, x, y, width, height)
{
	text = "";
	textImage = NULL;
	creatImage();
}

BoutonText::BoutonText(Graphics* graphics, std::string text, int x, int y, int width, int height) : Bouton(graphics, x, y, width, height)
{
	this->text = text;
	this->police = POLICE_DEFAULT;
	this->textSize = SIZE_DEFAULT;
	textImage = NULL;
	creatImage();
}

BoutonText::BoutonText(Graphics* graphics, std::string text, unsigned int size, int x, int y, int width, int height) : Bouton(graphics, x, y, width, height)
{
	this->text = text;
	this->police = POLICE_DEFAULT;
	this->textSize = size;
	textImage = NULL;
	creatImage();
}

BoutonText::BoutonText(Graphics * graphics, std::string text, unsigned int size, std::string police, int x, int y, int width, int height) : Bouton(graphics, x, y, width, height)
{
	this->police = police;
	this->text = text;
	this->textSize = size;
	textImage = NULL;
	creatImage();
}

void BoutonText::update(float dt)
{
}

void BoutonText::render(Graphics* graphics)
{
	Bouton::render(graphics);
	if (strcmp(text.c_str(), ""))
	{
		graphics->renderTextCentered("test.ttf", text, rectangle.getCenter(), textSize);
	}
}
void BoutonText::render(Graphics* graphics, const Vector3D& translation)
{
	Bouton::render(graphics, translation);
	if (strcmp(text.c_str(), ""))
	{
		graphics->renderTextCentered("test.ttf", text, rectangle.getCenter() + translation, textSize);
	}
}

void BoutonText::creatImage()
{
	if (textImage != NULL)
	{
		delete textImage;
	}
	// Si le font n'est pas dispo
	// On le crée
	if (!graphics->isAlreadyPresent(police, textSize))
	{
		graphics->pushFontTTF(police, textSize);
	}

	// On crée l'image
	textImage = graphics->createImageFromFont(police, textSize, text);
}

void BoutonText::set(std::string text, unsigned size, std::string fontName)
{
	this->text = text;
	this->police = fontName;
	this->textSize = size;
}

void BoutonText::setPoliceSize(unsigned size)
{
	this->textSize = size;
}

void BoutonText::setText(std::string text)
{
	this->text = text;
}

void BoutonText::setFontName(std::string fontName)
{
	this->police = fontName;
}

int BoutonText::getPoliceSize()
{
	return textSize;
}

std::string BoutonText::getFontName()
{
	return police;
}

std::string BoutonText::getText()
{
	return text;
}
