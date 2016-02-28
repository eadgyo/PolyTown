

#ifndef MATRIX4_H_
#define MATRIX4_H_
#define COL 4
#define LINE 4
#define SIZE_M COL*LINE

class Matrix4;

#include <assert.h>
#include <iostream>
#include "Quaternion.h"
#include "Vector3D.h"

class Matrix4
{
public:
	inline Matrix4() {} ;
	Matrix4(const float* m);
	Matrix4(const Quaternion& q);
	Matrix4(const Quaternion& q, const Vector3D& v);
	Matrix4(const Quaternion& q, const Vector3D& v, float factor);

	void set(const Matrix4& m4);
	Matrix4 copy();

	// Surchage opérateurs
	Matrix4 operator+(const Matrix4& m4) const;
	void operator+=(const Matrix4& m4);
	Matrix4 operator-(const Matrix4& m4) const;
	void operator-=(const Matrix4& m4);
	Matrix4 operator*(const float& f) const;
	void operator*=(const float& f);
	Matrix4 operator*(const Matrix4& m4) const;
	void operator*=(const Matrix4& m4);
	Vector3D operator*(const Vector3D vec) const;
	float& operator[](int i);
	float& operator[](int i, int j);

	// Getter
	const float get(int i) const { assert(i >= 0 && i < SIZE_M); return m[i]; };
	float getDeterminant() const;
	Matrix4 getInverse() const;
	Matrix4 getTranspose() const;
	inline const float* const getMatrix4() { return m; };

	// Setter
	void setInverse(const Matrix4& m4);
	void setTranspose(const Matrix4& m4);
	void setOrientation(const Quaternion& q5);
	void setOrientation(const Quaternion& q, const Vector3D& vec);
	void setOrientation(const Vector3D& vec);
	void setOrientation(const Quaternion& q, const Vector3D& vec, float factor);
	void setIdentity(float factor);
	void setIdentity();
	inline void setPos(const Vector3D& pos) { setOrientation(pos); };
	void setX(float x);
	void setY(float y);
	void setZ(float z);
	void setW(float w);

	// Transformations
	Vector3D transform(const Vector3D& v) const;
	void invert();
	void transpose();
	void changeBasis(const Matrix4& m4);

	// Create
	static Matrix4 createIdentity();
	static Matrix4 createIdentity(float factor);
	static Matrix4 createRotateX(float theta);
	static Matrix4 createRotateY(float theta);
	static Matrix4 createRotateZ(float theta);
	static Matrix4 createRotate(const Vector3D& v, float theta);

	void display();

private:
	float m[SIZE_M];
};

#endif /* MATRIX4_H_ */
