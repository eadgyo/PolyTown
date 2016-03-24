#include "Matrix4.h"

Matrix4::Matrix4(const float* m4)
{
	for(int i=0; i<SIZE_M; i++)
	{
		m[i] = m4[i];
	}
}
Matrix4::Matrix4(const Quaternion& q)
{
	setOrientation(q);
}
Matrix4::Matrix4(const Quaternion& q, const Vector3D& v)
{
	setOrientation(q, v);
}
Matrix4::Matrix4(const Quaternion& q, const Vector3D& v, float factor)
{
	setOrientation(q, v, factor);
}

void Matrix4::set(const Matrix4& m4)
{
	for(int i=0; i<SIZE_M; i++)
	{
		m[i] = m4.get(i);
	}
}
Matrix4 Matrix4::copy()
{
	Matrix4 m4;
	m4.set((*this));
	return m4;
}

//====================================================
// Surchage opérateurs
//====================================================
Matrix4 Matrix4::operator+(const Matrix4& m4) const
{
	Matrix4 res;
	for(int i=0; i<SIZE_M; i++)
	{
		res[i] = m[i] + m4.get(i);
	}
	return res;
}
void Matrix4::operator+=(const Matrix4& m4)
{
	for(int i=0; i<SIZE_M; i++)
	{
		m[i] += m4.get(i);
	}
}
Matrix4 Matrix4::operator-(const Matrix4& m4) const
{
	Matrix4 res;
	for(int i=0; i<SIZE_M; i++)
	{
		res[i] = m[i] - m4.get(i);
	}
	return res;
}
void Matrix4::operator-=(const Matrix4& m4)
{
	for(int i=0; i<SIZE_M; i++)
	{
		m[i] -= m4.get(i);
	}
}
Matrix4 Matrix4::operator*(const float& f) const
{
	Matrix4 res;
	for(int i=0; i<SIZE_M; i++)
	{
		res[i] = m[i]*f;
	}
	return res;
}
void Matrix4::operator*=(const float& f)
{
	for(int i=0; i<SIZE_M; i++)
	{
		 m[i] *= f;
	}
}
Matrix4 Matrix4::operator*(const Matrix4& m4) const
{
	Matrix4 res;
	for(int i=0; i<LINE; i++)
	{
		for(int j=0; j<COL; j++)
		{
			int startX = i*COL;
			int y = j;
			res[(j + i*COL)] = 0;
			for(int x=startX; x<startX+COL; x++)
			{
				res[(j + i*COL)] += m[x]*m4.get(y);
				y += COL;
			}
		}
	}
	return res;
}
Vector3D Matrix4::operator*(const Vector3D vec) const
{
	return transform(vec);
}
void Matrix4::operator*=(const Matrix4& m4)
{
	Matrix4 res = (*this)*m4;
	set(res);
}
float& Matrix4::operator[](int i)
{
	assert(i >=0 && i < SIZE_M);
	return m[i];
}


//====================================================
// Getter
//====================================================
float Matrix4::getDeterminant() const
{
	return	m[0]*(m[5]*(m[10]*m[15] - m[14]*m[11]) - m[9]*(m[6]*m[15] - m[7]*m[14]) + m[13]*(m[6]*m[11] - m[10]*m[7])) -
			m[4]*(m[1]*(m[10]*m[15] - m[14]*m[11]) - m[9]*(m[2]*m[15] - m[14]*m[3]) + m[13]*(m[2]*m[11] - m[10]*m[3])) +
			m[8]*(m[1]*(m[6]*m[15]  - m[14]*m[7])  - m[5]*(m[2]*m[15] - m[14]*m[3]) + m[13]*(m[2]*m[7]  - m[6]*m[3]))   -
			m[12]*(m[1]*(m[6]*m[11] - m[10]*m[7])  - m[5]*(m[2]*m[11] - m[10]*m[3]) + m[9]* (m[2]*m[7]  - m[6]*m[3]));
}
Matrix4 Matrix4::getInverse() const
{
	Matrix4 res;
	res[0] = m[6]*m[11]*m[13] - m[7]*m[10]*m[13] + m[7]*m[9]*m[14] - m[5]*m[11]*m[14] - m[6]*m[9]*m[15] + m[5]*m[10]*m[15];
	res[1] = m[3]*m[10]*m[13] - m[2]*m[11]*m[13] - m[3]*m[9]*m[14] + m[1]*m[11]*m[14] + m[2]*m[9]*m[15] - m[1]*m[10]*m[15];
	res[2] = m[2]*m[7]*m[13] - m[3]*m[6]*m[13] + m[3]*m[5]*m[14] - m[1]*m[7]*m[14] - m[2]*m[5]*m[15] + m[1]*m[6]*m[15];
	res[3] = m[3]*m[6]*m[9] - m[2]*m[7]*m[9] - m[3]*m[5]*m[10] + m[1]*m[7]*m[10] + m[2]*m[5]*m[11] - m[1]*m[6]*m[11];
	res[4] = m[7]*m[10]*m[12] - m[6]*m[11]*m[12] - m[7]*m[8]*m[14] + m[4]*m[11]*m[14] + m[6]*m[8]*m[15] - m[4]*m[10]*m[15];
	res[5] = m[2]*m[11]*m[12] - m[3]*m[10]*m[12] + m[3]*m[8]*m[14] - m[0]*m[11]*m[14] - m[2]*m[8]*m[15] + m[0]*m[10]*m[15];
	res[6] = m[3]*m[6]*m[12] - m[2]*m[7]*m[12] - m[3]*m[4]*m[14] + m[0]*m[7]*m[14] + m[2]*m[4]*m[15] - m[0]*m[6]*m[15];
	res[7] = m[2]*m[7]*m[8] - m[3]*m[6]*m[8] + m[3]*m[4]*m[10] - m[0]*m[7]*m[10] - m[2]*m[4]*m[11] + m[0]*m[6]*m[11];
	res[8] = m[5]*m[11]*m[12] - m[7]*m[9]*m[12] + m[7]*m[8]*m[13] - m[4]*m[11]*m[13] - m[5]*m[8]*m[15] + m[4]*m[9]*m[15];
	res[9] = m[3]*m[9]*m[12] - m[1]*m[11]*m[12] - m[3]*m[8]*m[13] + m[0]*m[11]*m[13] + m[1]*m[8]*m[15] - m[0]*m[9]*m[15];
	res[10]= m[1]*m[7]*m[12] - m[3]*m[5]*m[12] + m[3]*m[4]*m[13] - m[0]*m[7]*m[13] - m[1]*m[4]*m[15] + m[0]*m[5]*m[15];
	res[11]= m[3]*m[5]*m[8] - m[1]*m[7]*m[8] - m[3]*m[4]*m[9] + m[0]*m[7]*m[9] + m[1]*m[4]*m[11] - m[0]*m[5]*m[11];
	res[12]= m[6]*m[9]*m[12] - m[5]*m[10]*m[12] - m[6]*m[8]*m[13] + m[4]*m[10]*m[13] + m[5]*m[8]*m[14] - m[4]*m[9]*m[14];
	res[13]= m[1]*m[10]*m[12] - m[2]*m[9]*m[12] + m[2]*m[8]*m[13] - m[0]*m[10]*m[13] - m[1]*m[8]*m[14] + m[0]*m[9]*m[14];
	res[14]= m[2]*m[5]*m[12] - m[1]*m[6]*m[12] - m[2]*m[4]*m[13] + m[0]*m[6]*m[13] + m[1]*m[4]*m[14] - m[0]*m[5]*m[14];
	res[15]= m[1]*m[6]*m[8] - m[2]*m[5]*m[8] + m[2]*m[4]*m[9] - m[0]*m[6]*m[9] - m[1]*m[4]*m[10] + m[0]*m[5]*m[10];
	float det = getDeterminant();
	if(det != 0)
	{
		res *= 1.0f/det;
		return res;
	}
	else
		return NULL;
}
Matrix4 Matrix4::getTranspose() const
{
	Matrix4 res;
	res.setTranspose((*this));
	return res;
}

//====================================================
// Setter
//====================================================
void Matrix4::setInverse(const Matrix4& m4)
{
	Matrix4 res = m4.getInverse();
	set(res);
}
void Matrix4::setTranspose(const Matrix4& m4)
{
	for(int j=0; j<LINE; j++)
	{
		for(int i=0; i<COL; i++)
		{
			m[(COL - i - 1)*COL + j] = m4.get(i + j*COL);
		}
	}
}
void Matrix4::setOrientation(const Quaternion& q5)
{
	float n = q5.getMagnitude();
	if (std::abs(n) < 0.000001f)
	{
		setIdentity();
		return;
	}

	Quaternion q = q5*((float) sqrt(1.0f/n));
	float i2 = q.i*q.i;
	float j2 = q.j*q.j;
	float k2 = q.k*q.k;

	get(0,0) = 1 - (j2*2 + k2*2);
	get(0,1) = 2*q.i*q.j - 2*q.k*q.r;
	get(0,2) = 2*q.i*q.k + 2*q.j*q.r;

	get(1,0)= 2*q.i*q.j + 2*q.k*q.r;
	get(1,1) = 1 - (2*i2 + 2*k2);
	get(1,2) = 2*q.j*q.k - 2*q.i*q.r;

	get(2,0) = 2*q.i*q.k - 2*q.j*q.r;
	get(2,1) = 2*q.j*q.k + 2*q.i*q.r;
	get(2,2) = 1 - (2*i2 + 2*j2);

	get(3,3) = 1;
}

float& Matrix4::get(int i, int j)
{
	assert(i >=0 && i < COL && j>=0 && j < LINE);
	return m[i*COL + j];
}

void Matrix4::setOrientation(const Quaternion& q, const Vector3D& vec)
{
	setOrientation(q);
	get(0,3)= vec.getX();
	get(1,3) = vec.getY();
	get(2,3) = vec.getZ();
}
void Matrix4::setOrientation(const Vector3D& vec)
{
	get(0,3) = vec.getX();
	get(1,3) = vec.getY();
	get(2,3) = vec.getZ();

	get(3,3) = 1;
}
void Matrix4::setOrientation(const Quaternion& q, const Vector3D& vec, float factor)
{
	setOrientation(q, vec);
	(*this) *= Matrix4::createIdentity(factor);
}
void Matrix4::setOrientation(float omega, float scale, bool flipH, bool flipV, const Vector3D& vec)
{
	Quaternion qZ(Vector3D(true), omega);
	setOrientation(qZ, vec, scale);
	if(flipH)
		flipX();
	if(flipV)
		flipY();
}
void Matrix4::setOrientation(float omega, float scale, bool flipH, bool flipV)
{
	Quaternion qZ(Vector3D(0, 0, 1, false), omega);
	setOrientation(qZ, scale);
	if(flipH)
		flipX();
	if(flipV)
		flipY();
}
void Matrix4::setOrientation(const Quaternion& q, float scale)
{
	setOrientation(q);
	(*this) *= Matrix4::createIdentity(scale);
}
void Matrix4::setOrientation(float omega, float scale, bool flipH, bool flipV, bool flipM, const Vector3D& vec)
{
	Quaternion qZ(Vector3D(true), omega);
	setOrientation(qZ, vec, scale);
	if(flipH)
		flipX();
	if(flipV)
		flipY();
	if(flipM)
		flipZ();
}

void Matrix4::flipX()
{
	m[0] *= -1;
	m[4] *= -1;
	m[8] *= -1;
	m[12] *= -1;
}
void Matrix4::flipY()
{
	m[1] *= -1;
	m[5] *= -1;
	m[9] *= -1;
	m[13] *= -1;
}
void Matrix4::flipZ()
{
	m[2] *= -1;
	m[6] *= -1;
	m[10] *= -1;
	m[14] *= -1;
}
void Matrix4::flipW()
{
	m[3] *= -1;
	m[7] *= -1;
	m[11] *= -1;
	m[15] *= -1;
}

void Matrix4::setX(float x)
{
	get(0,3) = x;
}

void Matrix4::setY(float y)
{
	get(1,3) = y;
}

void Matrix4::setZ(float z)
{
	get(2,3) = z;
}

void Matrix4::setW(float w)
{
	get(3,3) = w;
}


void Matrix4::setIdentity(float factor)
{
	m[0] = factor;
	m[1] = m[2] = m[3] = 0;

	m[5] = factor;
	m[4] = m[6] = m[7] = 0;

	m[10] = factor;
	m[8] = m[9] = m[11] = 0;

	m[15] = factor;
	m[12] = m[13] = m[14] = 0;
}
void Matrix4::setIdentity()
{
	setIdentity(1.0f);
}


//====================================================
// Transformations
//====================================================
Vector3D Matrix4::transform(const Vector3D& v) const
{
	Vector3D res;
	for(int i=0; i<LINE; i++)
	{
		res[i] = 0;
		//std::cout << "res[" << i << "] = ";
		for(int j=0; j<COL; j++)
		{
			//std::cout << " + m[" << (i*COL + j) << "]*" << "v(" << j << ")";
			res[i] += m[i*COL + j]*v.get(j);
		}
		//std::cout << "\n";
	}
	return res;
}
void Matrix4::invert()
{
	Matrix4 res = getInverse();
	set(res);
}
void Matrix4::transpose()
{
	Matrix4 res = getTranspose();
	set(res);
}
void Matrix4::changeBasis(const Matrix4& m4)
{
	Vector3D a;
	a.set(0.0f, 1.0f);
	Matrix4 inv = getInverse();
	(*this) *= (m4*inv);
}
float Matrix4::multiplyX(const Vector3D& v) const
{
	return m[0]*v.getX() + m[1]*v.getY() + m[2]*v.getZ() + m[3]*v.getW();
}

float Matrix4::multiplyY(const Vector3D& v) const
{
	return m[4]*v.getX() + m[5]*v.getY() + m[6]*v.getZ() + m[7]*v.getW();
}

float Matrix4::multiplyZ(const Vector3D& v) const
{
	return m[8]*v.getX() + m[9]*v.getY() + m[10]*v.getZ() + m[11]*v.getW();
}
void Matrix4::translate(const Vector3D& v)
{
	m[3] += v.getX();
	m[7] += v.getY();
	m[11] += v.getZ();
	// W == 0, donc pas de translation suivant la coordonnée W
}
void Matrix4::rotateRadiansZFree(float omega, const Vector3D& center)
{
	Vector3D pos = getPos();
	Matrix4 rotation = createRotateZ(omega);
	rotation.setPos(center);
	// Ne pas oublier de faire d'abord une translation
	pos -= center;
	pos.setW(1.0f);
	setPos(rotation*pos);
}
void Matrix4::scale(float factor, const Vector3D& center)
{
	Matrix4 l_scale = createIdentity(factor);
	l_scale.setPos(center);
	translate(-center);
	(*this) = l_scale*(*this);
}
void Matrix4::scale(float factor)
{
	scale(factor, Vector3D(true));
}
void Matrix4::flipX(const Vector3D& center)
{
	Matrix4 l_flipH = createIdentity();
	l_flipH.get(0, 0) = -1.0f;
	l_flipH.setPos(center);
	translate(-center);
	(*this) = l_flipH*(*this);
}
void Matrix4::flipY(const Vector3D& center)
{
	Matrix4 l_flipV = createIdentity();
	l_flipV.get(1, 1) = -1.0f;
	l_flipV.setPos(center);
	translate(-center);
	(*this) = l_flipV*(*this);
}
void Matrix4::flipZ(const Vector3D& center)
{
	Matrix4 l_flipZ = createIdentity();
	l_flipZ.get(2, 2) = -1.0f;
	l_flipZ.setPos(center);
	translate(-center);
	(*this) = l_flipZ*(*this);
}
void Matrix4::flipW(const Vector3D& center)
{
	Matrix4 l_flipW = createIdentity();
	l_flipW.get(3, 3) = -1.0f;
	l_flipW.setPos(center);
	translate(-center);
	(*this) = l_flipW*(*this);
}

//====================================================
// Create
//====================================================
Matrix4 Matrix4::createIdentity()
{
	Matrix4 res;
	res.setIdentity();
	return res;
}
Matrix4 Matrix4::createIdentity(float factor)
{
	Matrix4 res;
	res.setIdentity(factor);
	return res;
}
Matrix4 Matrix4::createRotateX(float theta)
{
	float tab[] = {1.0f, 0, 0, 0,
				0, (float) cos(theta), (float) -sin(theta), 0,
				0, (float) sin(theta), (float) cos(theta), 0,
				0, 0, 0, 1.0f};
	return Matrix4(tab);
}
Matrix4 Matrix4::createRotateY(float theta)
{
	float tab[] = {(float) cos(theta), 0, (float) sin(theta), 0,
					0, 1.0f, 0, 0,
					(float) -sin(theta), 0, (float) cos(theta), 0,
					0, 0, 0, 1.0f};
	return Matrix4(tab);
}
Matrix4 Matrix4::createRotateZ(float theta)
{
	float tab[] = { (float) cos(theta), (float) -sin(theta), 0, 0,
					(float) sin(theta), (float) cos(theta), 0, 0,
					0, 0, 1.0f, 0,
					0, 0, 0, 1.0f};
	return Matrix4(tab);
}
Matrix4 Matrix4::createRotate(const Vector3D& v, float theta)
{
	float c = cos(theta);
	float s = sin(theta);
	float Ax = v.getX();
	float Ay = v.getY();
	float Az = v.getZ();

	float tab[] = {c+(1-c)*Ax*Ax, (1-c)*Ax*Ay - s*Az, (1-c)*Ax*Az + s*Ay, 0,
					(1-c)*Ax*Ay + s*Az, c+(1-c)*Ay*Ay, (1-c)*Ay*Az - s*Ax, 0,
					(1-c)*Ax*Az - s*Ay, (1-c)*Ay*Az + s*Ax, c+(1-c)*Az*Az, 0,
					0,0,0,1.0f};
	return Matrix4(tab);
}

Vector3D Matrix4::getPos() const
{
	return Vector3D(m[3], m[7], m[11], m[15] != 0);
}

void Matrix4::display() const
{
	for(int i=0; i<LINE; i++)
	{
		std::cout << "| ";
		for(int j=0; j<COL-1; j++)
		{
			std::cout << m[i*COL + j] << ", ";
		}
		std::cout << m[i*COL + COL - 1];
		std::cout << " |\n";
	}
}
