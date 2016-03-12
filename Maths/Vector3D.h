/*
Calcul et Gestion Vector3D
Le vecteur 3D comporte 4 valeurs.
Les 3 premières concernent les coordonnées
La dernière: 0 si c'est un vecteur
             1 si c'est un point
-> Simplification calcul avec les matrices 4x4
*/


#ifndef VECTOR3D_H_
#define VECTOR3D_H_

class Vector3D;

#define SIZE_V 4
#define MIN_DIFF_EQ 0.000001f
#define PI 3.14159265359

#include "Matrix4.h"
#include <assert.h>
#include <cmath>
#include <iostream>

class Vector3D
{
public:
	static Vector3D vecZeros() { return Vector3D(0, 0, 0); };
	inline Vector3D() {};
	Vector3D(bool isPoint);
	Vector3D(const Vector3D& a);
	Vector3D(float, float);
	Vector3D(float, float, float);
	Vector3D(float, float, float, bool);

	static Vector3D sub(const Vector3D&, const Vector3D&);

	Vector3D copy() const;
	Vector3D getTransformation(const Matrix4&) const;

	inline bool isPoint() const { return coor[3] == 0; };
	float getMagnitude() const;
	float getSqMagnitude() const;
	float normalize();
	inline bool isColinear2D(const Vector3D v) const { return std::abs((*this)*(v.getPerpendicular2D())) < 0.000001f; };

	// Getter
	float get(int i) const;
	float getAngle2D(const Vector3D& vec) const;
	float getAngle2D(const Vector3D& A, const Vector3D& C) const;
	Vector3D getNormalize() const;
	inline float x() const { return coor[0]; };
	inline float y() const { return coor[1]; };
	inline float z() const { return coor[2]; };
	inline float w() const { return coor[3]; };
	inline float getX() const { return coor[0]; };
	inline float getY() const { return coor[1]; };
	inline float getZ() const { return coor[2]; };
	inline float getW() const { return coor[3]; };
	inline const float* getCoor() const { return coor; };
	inline Vector3D getPerpendicular2D() const { return Vector3D(-y(), x(), 0, true); };
	Vector3D getProjection2D(const Vector3D& vec, const Vector3D& p) const;
	bool computeIntersection2D(const Vector3D& v1, const Vector3D& v2, const Vector3D& p1, const Vector3D& p2);

	// Setter
	inline void addX(float f) { set(0, getX() + f); };
	inline void addY(float f) { set(1, getY() + f); };
	inline void addZ(float f) { set(2, getZ() + f); };
	inline void addW(float f) { set(3, getW() + f); };
	inline void setX(float f) { set(0, f); };
	inline void setY(float f) { set(1, f); };
	inline void setZ(float f) { set(2, f); };
	inline void setW(float f) { set(3, f); };
	void set(const Vector3D& a, const Vector3D& b);
	void set(const Vector3D& a);
	void set(int, float);
	void set(float);
	inline void set2D(float x, float y) { set(x, y, 0, 1); };
	void set(float, float);
	void set(float, float, float);
	void set(float, float, float, float);

	// Surchage opérateurs
	Vector3D operator-() const;
	Vector3D operator-(Vector3D const& v) const;
	void operator+=(Vector3D const&);
	Vector3D operator+(Vector3D const&) const;
	void operator-=(Vector3D const&);
	float operator*(Vector3D const&) const;
	Vector3D operator*(float const&) const;
	Vector3D operator*(Matrix4 const&) const;
	void operator*=(float const&);
	void operator*=(Matrix4 const&);
	Vector3D operator/(float const&) const;
	void operator/=(float const&);
	Vector3D operator%(Vector3D const&) const;
	void operator%=(Vector3D const&);
	bool operator==(Vector3D const&);
	float& operator[](int const&);
	bool operator<(const Vector3D&) const;

	void display();

	static float orientation(const Vector3D& v1, const Vector3D& v2, const Vector3D& v3);
private:
	float coor[SIZE_V];

};

#endif /* VECTOR3D_H_ */
