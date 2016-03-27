#pragma once

#include "Bouton.h"
class BoutonText : public Bouton
{
public:
	BoutonText(Graphics* graphics, int x, int y, int width, int height);
	BoutonText(Graphics* graphics, std::string text, myColor colorText, int x, int y, int width, int height);
	BoutonText(Graphics* graphics, std::string text, myColor colorText, unsigned int size, int x, int y, int width, int height);
	BoutonText(Graphics* graphics, std::string text, myColor colorText, unsigned int size, std::string police, int x, int y, int width, int height);

	virtual void update(float dt);
	virtual void render(Graphics* g);
	virtual void render(Graphics* g, const Vector3D& translation);
	
	void creatImage();

	// Setter
	void set(std::string name, unsigned size, std::string fontName);
	void setPoliceSize(unsigned size);
	void setText(std::string text);
	void setFontName(std::string fontName);

	// Getter
	int getPoliceSize();
	std::string getFontName();
	std::string getText();

	void setColorText(myColor colorText);

protected:
	std::string text;
	std::string police;
	unsigned textSize;
	myColor colorText;

	Image* textImage;
	const std::string POLICE_DEFAULT = "test";
	const int SIZE_DEFAULT = 16;
};