/*
Calcul et Gestion Vector3D
Le vecteur 3D comporte 4 valeurs.
Les 3 premières concernent les coordonnées
La dernière: 0 si c'est un vecteur
             1 si c'est un point
-> Simplification calcul avec les matrices 4x4
*/
#define SIZE_V 4
#define MIN_DIFF_EQ 0.000001f

#ifndef VECTOR3D_H_
#define VECTOR3D_H_


class Vector3D;

#include "Matrix4.h"
#include <assert.h>
#include <cmath>
#include <iostream>

class Vector3D
{
public:
	static Vector3D vecZeros() { return Vector3D(0, 0, 0); };
	inline Vector3D() {};
	Vector3D(const Vector3D& a);
	Vector3D(const Vector3D&, const Vector3D&);
	Vector3D(float, float, float);
	Vector3D(float, float, float, bool);
	Vector3D(float const*);

	Vector3D copy() const;
	Vector3D getTransformation(const Matrix4&) const;

	inline bool isPoint() const { return coor[3] == 0; };
	float getMagnitude() const;
	float getSqMagnitude() const;
	void normalize();

	// Getter
	float get(int i) const;
	inline float getX() const { return coor[0]; };
	inline float getY() const { return coor[1]; };
	inline float getZ() const { return coor[2]; };
	inline float getW() const { return coor[3]; };
	inline const float* getCoor() const { return coor; };

	// Setter
	inline void setX(float f) { set(0, f); };
	inline void setY(float f) { set(1, f); };
	inline void setZ(float f) { set(2, f); };
	inline void setW(float f) { set(3, f); };
	void set(const Vector3D& a);
	void set(int, float);
	void set(float);
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

	void display();
private:
	float coor[SIZE_V];

};

#endif /* VECTOR3D_H_ */
