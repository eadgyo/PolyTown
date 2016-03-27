/*
 * sRectangle.h
 *
 *  Created on: Feb 28, 2016
 *      Author: ronan-h
 */

#ifndef SRECTANGLE_H_
#define SRECTANGLE_H_

class sRectangle;

#include <SDL2/SDL.h>
#include "Form.h"
#include "Vector3D.h"

class sRectangle : public Form
{
public:
	sRectangle();
	sRectangle(const Vector3D& left, float width, float height);
	sRectangle(int x, int y, int width, int height);
	sRectangle(float x, float y, float width, float height);
	sRectangle(const Form& form);
	sRectangle(const sRectangle& sRec);
	~sRectangle();

	sRectangle clone() const;

	static sRectangle createSRectangleCenter(const Vector3D& center, float width, float height);

	// Setter
	void set(const Form& form);
	void set(const sRectangle& rec);
	void set(float x, float y, float width, float height);
	void set(const Vector3D& center, float width, float height);
	void setLeft(const Vector3D& left, float width, float height);
	void setLeft(float x, float y, float width, float height);
	void setLeft(float x, float y);
	void setLeft(const Vector3D& left);

	// Getter
	inline float getLeftX() const { return getX(0); };
	inline float getLeftY() const { return getY(0); };
	inline float getWidth() const { return width; };
	inline float getHeight() const { return height; };
	bool isColliding(const Vector3D& pos) { return isInsideBorder(pos); };
	bool isInside(const sRectangle& rect) const;
	bool isInside(const Vector3D& p) const;
	bool isInsideBorder(const sRectangle& rect) const;
	bool isInsideBorder(const Vector3D& p) const;
	bool collision(const sRectangle& rect) const;
	bool collisionBorder(const sRectangle& rect) const;
	inline Vector3D getLeft() const { return get(0); };
	SDL_Rect getSDLRect();
	SDL_Rect getSDLRect(bool flipH, bool flipW);
	SDL_Rect getSDLRectDest();


	inline virtual unsigned getType() { return 3; };
private:
	float width, height;

};

#endif /* SRECTANGLE_H_ */
