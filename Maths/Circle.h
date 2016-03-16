#pragma once
#include "Form.h"
class Circle : public Form
{
public:
	Circle();
	Circle(const Circle& circle);
	Circle(const Vector3D& center, float radius);
	~Circle();

	inline Circle clone() { return Circle((*this)); };
	void set(const Circle& circle);
	void set(const Vector3D& center, float radius);
	inline float getRadius() const { return radius; };

	inline virtual unsigned getType() { return 1; };

	void scaleF(float factor, Vector3D center);
	float getMinX() const;
	float getMinY() const;
	float getMaxX() const;
	float getMaxY() const;
	bool isColliding(const Circle& circle) const;

	/*
	bool collisionSat(Form& form);
	bool collisionSat(Form& form, const Vector3D& VA,
		const Vector3D& VB, const Vector3D& push, float& t);
	bool collisionSatFree(const Form& B, const Vector3D& VA, const Vector3D& VB);
	*/
protected:
	float radius;
};

