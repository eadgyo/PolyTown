#pragma once

class myRectangle;
#include "Vector3D.h"
#include "Form.h"

class myRectangle : public Form
{
public:
	myRectangle();
	myRectangle(const myRectangle& rectangle);
	myRectangle(const Form& form);
	myRectangle(const Vector3D& center, const Vector3D& length);
	myRectangle(const Vector3D& center, const Vector3D& length, float omega);
	~myRectangle();

	myRectangle clone();

	// Setter
	void set(const Vector3D& center, const Vector3D& length, float omega);
	void set(const myRectangle& rec);
	void set(const Form& form);

	// Getter
	Vector3D getVecLocal() const;
	Vector3D getVecWorld() const;
	inline Vector3D getLeft() const { return get(0); };
	inline Vector3D getLength() const { return length; };
	inline float getWidth() const { return length.x(); };
	inline float getHeight() const { return length.y(); };

	float getAngle(const Vector3D& vec) const;
	float getAngle() const;
	void scaleF(float factor, const Vector3D& center);


	inline virtual unsigned getType() { return 2; };
private:
	Vector3D length;

};

