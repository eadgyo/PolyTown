/*
 * sRectangle.h
 *
 *  Created on: Feb 28, 2016
 *      Author: ronan-h
 */

#ifndef SRECTANGLE_H_
#define SRECTANGLE_H_

#include "Form.h"
#include "Vector3D.h"

class sRectangle : public Form
{
public:
	sRectangle();
	sRectangle(const Vector3D& left, const Vector3D& length);
	sRectangle(float x, float y, float width, float height);
	sRectangle(const Form& form);
	virtual ~sRectangle();

	static sRectangle createSRectangleCenter(const Vector3D& center, const Vector3D& length);

	// Setter
	void set(const Form& form);
	void set(const sRectangle& rec);
	void set(const Vector3D& center, const Vector3D& length);
	void set(float x, float y, float width, float height);
	void setLeft(const Vector3D& left, const Vector3D& length);
	void setLeft(float x, float y, float width, float height);

	// Getter
	inline float getWidth() const { return length.getX(); };
	inline float getHeight() const { return length.getY(); };
	const Vector3D& getLength() const { return length; };
	bool isInside(const sRectangle& rect) const;
	bool isInside(const Vector3D& p) const;
	bool isInsideBorder(const sRectangle& rect) const;
	bool isInsideBorder(const Vector3D& p) const;
	bool collision(const sRectangle& rect) const;
	bool collisionA(const sRectangle& rect) const;
	bool collisionBorder(const sRectangle& rect) const;
	bool collisionBorder(const sRectangle& rect) const;
	inline const Vector3D& getLeft() const { return points.at(0); };



private:
	Vector3D length;

};

#endif /* SRECTANGLE_H_ */
