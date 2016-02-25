/*
 * Quaternion.h
 *
 *  Created on: Feb 24, 2016
 *      Author: ronan-h
 */

#ifndef QUATERNION_H_
#define QUATERNION_H_
class Quaternion;
#include "Vector3D.h"
#include "Matrix4.h"

class Quaternion
{
public:
	Quaternion(float r);
	Quaternion(float r, float i);
	Quaternion(float r, float i, float j);
	Quaternion(float r, float i, float j, float k);
	Quaternion(const Quaternion& q);
	Quaternion(float theta, const Vector3D& vec3D);

	Quaternion copy();

	// Getter
	inline float getR() const { return r; };
	inline float getI() const { return i; };
	inline float getJ() const { return j; };
	inline float getK() const { return k; };
	float get(int i) const;

	// Setter
	inline void setR(float f) { r = f; };
	inline void setI(float f) { i = f; };
	inline void setJ(float f) { j = f; };
	inline void setK(float f) { k = f; };
	float set(int i, float f);
	float set(float theta, const Vector3D& vec);

	// Surchage opérateurs
	Quaternion operator*(const Quaternion& q) const;
	void operator*=(const Quaternion& q);
	Quaternion operator/(const Quaternion& q) const;
	void operator/=(const Quaternion& q);
	Quaternion operator+(const Quaternion& q) const;
	void operator +=(const Quaternion& q);

	// Operations
	void rotateByVector(const Vector3D& vec, float theta);
	Vector3D transform(const Vector3D& vec);
	Vector3D transform(const Vector3D& vec, const Vector3D& center);
	void conjugate();
	void normalize();

	Quaternion getInverse() const;
	Quaternion getConjugate() const;
	float getVecAndRot(Vector3D& vec);
	Matrix4 getRotationMatrix() const;
	float getMagnitude() const;
	float getSqMagnitude() const;
	Quaternion getInterpolation(float t, float theta, const Quaternion& q) const;

	void display() const;

private:
	float r, i, j, k;
};

#endif /* QUATERNION_H_ */
