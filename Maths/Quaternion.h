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
#include <assert.h>
#include <iostream>

class Quaternion
{
public:
	Quaternion() { set(0,0,0,0); };
	Quaternion(float r);
	Quaternion(float r, float i);
	Quaternion(float r, float i, float j);
	Quaternion(float r, float i, float j, float k);
	Quaternion(const Quaternion& q);
	Quaternion(const Vector3D& vec3D, float theta);

	Quaternion copy() const;

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
	void set(int a, float f);
	void set(const Vector3D& vec, float theta);
	void set(float theta);
	void set(float r, float i, float j, float k);
	void set(const Quaternion& q);

	// Surchage opérateurs
	Quaternion operator-() const;
	Quaternion operator*(const Quaternion& q) const;
	Vector3D operator*(const Vector3D& v) const;
	void operator*=(const Quaternion& q);
	Quaternion operator*(int f) const;
	Quaternion operator*(float f) const;
	void operator*=(const float& f);
	Quaternion operator/(const Quaternion& q) const;
	void operator/=(const Quaternion& q);
	Quaternion operator+(const Quaternion& q) const;
	Quaternion operator/(const float& f) const;
	void operator/=(const float& f);
	void operator +=(const Quaternion& q);
	float& operator[](int i);

	// Operations
	void rotateByVector(const Vector3D& vec, float theta);
	Vector3D transform(const Vector3D& vec) const;
	Vector3D transform(const Vector3D& vec, const Vector3D& center) const;
	void conjugate();
	void normalize();

	void setInverse(const Quaternion&);
	void setConjugate(const Quaternion&);
	Quaternion getInverse() const;
	Quaternion getConjugate() const;
	float getVecAndRot(Vector3D& vec) const;
	Matrix4 getRotationMatrix() const;
	float getMagnitude() const;
	float getSqMagnitude() const;
	Quaternion getInterpolation(float t, float theta, const Quaternion& q) const;

	void display() const;

	float r, i, j, k;

};

#endif /* QUATERNION_H_ */
