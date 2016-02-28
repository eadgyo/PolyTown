#pragma once
#include "Vector3D.h"
#include "Form.h"

class Rectangle : public Form
{
public:
	Rectangle();
	Rectangle(const Rectangle& rectangle);
	Rectangle(const Form& form);
	Rectangle(const Vector3D& center, const Vector3D& length, float omega);
	virtual ~Rectangle();

	Rectangle clone();

	// Setter
	void set(const Vector3D& center, const Vector3D& length, float omega);
	void set(const Rectangle& rec);
	void set(const Form& form);

	// Getter
	Vector3D getVecLocal() const;
	Vector3D getVecWorld() const;
	inline Vector3D getLeft() const { return get(0); };
	inline Vector3D getLength() const { return length; };
	inline float getWidth() const { return length.x; };
	inline float getHeight() const { return length.y; };

	float getAngle(const Vector3D& vec) const;
	float getAngle() const;
	void scaleF(float factor, const Vector3D& center);

private:
	Vector3D length;

};

