#include "Quaternion.h"


Quaternion::Quaternion(float r)
{
	this->r = r;
	this->i = 0;
	this->j = 0;
	this->k = 0;
}
Quaternion::Quaternion(float r, float i)
{
	this->r = r;
	this->i = i;
	this->j = 0;
	this->k = 0;
}
Quaternion::Quaternion(float r, float i, float j)
{
	this->r = r;
	this->i = i;
	this->j = j;
	this->k = 0;
}
Quaternion::Quaternion(float r, float i, float j, float k)
{
	this->r = r;
	this->i = i;
	this->j = j;
	this->k = k;
}
Quaternion::Quaternion(const Quaternion& q)
{
	this->r = q.get(0);
	this->i = q.get(1);
	this->j = q.get(2);
	this->k = q.get(3);
}
Quaternion::Quaternion(const Vector3D& vec3D, float theta)
{
	set(vec3D, theta);
}

Quaternion Quaternion::copy() const
{
	return Quaternion((*this));
}

//====================================================
// Getter
//====================================================
float Quaternion::get(int a) const
{
	assert(a >=0 && a < 4);
	switch(a)
	{
	case 0:
		return r;
	case 1:
		return i;
	case 2:
		return j;
	case 3:
		return k;
	default:
		return 0;
	}
}

//====================================================
// Setter
//====================================================
void Quaternion::set(const Quaternion& q)
{
	r = q.getR();
	i = q.getI();
	j = q.getJ();
	k = q.getK();
}
void Quaternion::set(int a, float f)
{
	assert(a >=0 && a < 4);
	switch(a)
	{
	case 0:
		r = f;
		break;
	case 1:
		i = f;
		break;
	case 2:
		j = f;
		break;
	case 3:
		k = f;
		break;
	default:
		break;
	}
}
void Quaternion::set(float r, float i, float j, float k)
{
	this->r = r;
	this->i = i;
	this->j = j;
	this->k = k;
}
void Quaternion::set(float theta)
{
	set(Vector3D(1.0f, 0, 0), theta);
}
void Quaternion::set(const Vector3D& vec, float theta)
{
	float magn = vec.getMagnitude();
	float s = sin(theta/2.0f);
	if(magn != 0)
		set((float) cos(theta/2.0), s*vec.getX()/magn, s*vec.getY()/magn, s*vec.getZ()/magn);
	else
		set((float) cos(theta/2.0), 0.0, 0.0, 0.0);
}

//====================================================
// Surchage opérateurs
//====================================================

Quaternion Quaternion::operator*(const Quaternion& q) const
{
	Quaternion q1;
	q1[0] = r*q.getR() - i*q.getI() - j*q.getJ() - k*q.getK();
	q1[1] = r*q.getI() + i*q.getR() + j*q.getK() - k*q.getJ();
	q1[2] = r*q.getJ() + j*q.getR() + k*q.getI() - i*q.getK();
	q1[3] = r*q.getK() + k*q.getR() + i*q.getJ() - j*q.getI();
	return q1;
}
void Quaternion::operator*=(const Quaternion& q)
{
	Quaternion q1 = (*this)*q;
	set(q1);
}
Quaternion Quaternion::operator/(const Quaternion& q2) const
{
	Quaternion q;
	float div = q2.getSqMagnitude();
	q[0] = (q2.get(0)*r + q2.get(1)*i + q2.get(2)*j + q2.get(3)*k)/div;
	q[1] = (q2.get(0)*i - q2.get(1)*r - q2.get(2)*k + q2.get(3)*j)/div;
	q[2] = (q2.get(0)*j + q2.get(1)*k - q2.get(2)*r - q2.get(3)*i)/div;
	q[3] = (q2.get(0)*k - q2.get(1)*j + q2.get(2)*i - q2.get(3)*r)/div;
	return q;
}
void Quaternion::operator/=(const Quaternion& q)
{
	Quaternion q1 = (*this)*q;
	set(q1);
}
Quaternion Quaternion::operator+(const Quaternion& q) const
{
	Quaternion q1(r+q.getR(), i+q.getI(), j+q.getJ(), k+q.getK());
	return q1;
}
void Quaternion::operator +=(const Quaternion& q)
{
	r += q.getR();
	i += q.getI();
	j += q.getJ();
	k += q.getK();
}
Quaternion Quaternion::operator*(float f) const
{
	return Quaternion(r*f, i*f, j*f, k*f);
}
Quaternion Quaternion::operator*(int f) const
{
	return Quaternion(r*f, i*f, j*f, k*f);
}
Quaternion Quaternion::operator-() const
{
	return Quaternion(-r, -i, -j, -k);
}
void Quaternion::operator*=(const float& f)
{
	r *= f;
	i *= f;
	j *= f;
	k *= f;
}
Quaternion Quaternion::operator/(const float& f) const
{
	if(f!=0)
		return Quaternion(r/f, i/f, j/f, k/f);
	return copy();
}
void Quaternion::operator/=(const float& f)
{
	if(f != 0)
	{
		r /= f;
		i /= f;
		j /= f;
		k /= f;
	}
}
Vector3D Quaternion::operator*(const Vector3D& v) const
{
	return transform(v, Vector3D(true));
}
float& Quaternion::operator[](int a)
{
	assert(a >= 0 && a < 4);
	switch(a)
	{
	case 0:
		return r;
	case 1:
		return i;
	case 2:
		return j;
	case 3:
		return k;
	default:
		return r;
	}
}

//====================================================
// Opérations
//====================================================
void Quaternion::rotateByVector(const Vector3D& vec, float theta)
{
	Quaternion q(vec, theta);
	(*this) *= q;
}
Vector3D Quaternion::transform(const Vector3D& vec) const
{
	return transform(vec, Vector3D(true));
}
Vector3D Quaternion::transform(const Vector3D& vec, const Vector3D& center) const
{
	// qpq*
	Vector3D center1 = vec.copy();
	if(vec.getW() != 0)
	{
		center1 += center;
	}

	Quaternion vec3DQ = Quaternion(0, center1.getX(), center1.getY(), center1.getZ());
	Quaternion qpqc = ((*this)*vec3DQ)*getConjugate();
	Vector3D point = Vector3D(qpqc.getI(), qpqc.getJ(), qpqc.getK());

	if(vec.getW() != 0)
	{
		point -= center;
		point.setW(1);
	}
	return point;
}
void Quaternion::conjugate()
{
	i = -i;
	j = -j;
	k = -k;
}
void Quaternion::normalize()
{
	float d = getSqMagnitude();
	if(!d)
		(*this) /= d;
}

void Quaternion::setInverse(const Quaternion& q)
{
	float div = q.getSqMagnitude();
	r = q.getR()/div;
	i = -q.getI()/div;
	j = -q.getJ()/div;
	k = -q.getK()/div;
}
void Quaternion::setConjugate(const Quaternion& q)
{
	i = -q.getI();
	j = -q.getJ();
	k = -q.getK();
}

Quaternion Quaternion::getInverse() const
{
	Quaternion q;
	q.setInverse((*this));
	return q;
}
Quaternion Quaternion::getConjugate() const
{
	Quaternion q;
	q.setConjugate((*this));
	return q;
}
float Quaternion::getVecAndRot(Vector3D& vec) const
{
	float theta = acos(r);
	float s = sin(theta);
	if(s!=0)
	{
		vec.set(i/s, j/s, k/s);
		return theta;
	}
	else
		return 0;
}
Matrix4 Quaternion::getRotationMatrix() const
{
	Matrix4 m4;
	m4.setOrientation((*this));
	return m4;
}
float Quaternion::getMagnitude() const
{
	return sqrt(getSqMagnitude());
}
float Quaternion::getSqMagnitude() const
{
	return r*r + i*i + j*j + k*k;
}
Quaternion Quaternion::getInterpolation(float t, float theta, const Quaternion& q) const
{
	float s = sin(theta);
	float s1 = sin((theta)*(1-t));
	float s2 = sin((theta)*t);
	return (*this)*(s1/s) + q*(s2/s);
}

void Quaternion::display() const
{
	std::cout << "r: " << r << "  i: " << i << "  j: " << j << "  k: " << k;
}


