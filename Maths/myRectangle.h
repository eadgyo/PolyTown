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
	myRectangle(const Vector3D& center, float width, float height, float omega);
	myRectangle(float x, float y, float width, float height, float omega);
	myRectangle(const Vector3D& center, float width, float height);
	~myRectangle();

	static myRectangle create2points(const Vector3D& A, const Vector3D& B, float width);

	myRectangle clone() const;

	// Setter
	void set(const Vector3D& center, float width, float height);
	void set(const Vector3D& center, float width, float height, float omega);
	void set(const myRectangle& rec);
	void set(const Form& form);
	void set2points(const Vector3D& A, const Vector3D& B, float width);

	// Getter
	Vector3D getVecLocal() const;
	Vector3D getVecWorld() const;
	Vector3D getVecWorldNormal() const;
	inline Vector3D getLeft() const { return get(0); };
	inline float getWidth() const { return width; };
	inline float getHeight() const { return height; };

	float getAngle(const Vector3D& vec) const;
	float getAngle() const;
	virtual void scaleF(float factor, const Vector3D& center);


	inline virtual unsigned getType() { return 2; };
private:
	float width;
	float height;

};

