
#include "Form.h"

Form::Form()
{
	this->omega = 0;
	this->scale = 1.0f;
	this->flipH = false;
	this->flipV = false;
	this->surface = 0;
	this->orientation.setIdentity();
	this->orientation.setOrientation(omega, scale, flipH, flipV, Vector3D(true));
}

Form::~Form()
{
}

Form::Form(int size)
{
	this->omega = 0;
	this->scale = 1.0f;
	this->flipH = false;
	this->flipV = false;
	this->surface = 0;
	points.resize(size);
	orientation.setIdentity();
	orientation.setOrientation(omega, scale, flipH, flipV, Vector3D(true));
}

Form::Form(float omega, float scale, bool flipH, bool flipV, float surface, const Vector3D& vec)
{
	this->omega = omega;
	this->scale = scale;
	this->flipH = flipH;
	this->flipV = flipV;
	this->surface = surface;
	orientation.setIdentity();
	orientation.setOrientation(omega, scale, flipH, flipV, vec);
}

Form::Form(const Form& form)
{
	// Copie de convexForms
	convexForms.reserve(form.getConvexFormsSize());
	for(int i=0; i<form.getConvexFormsSize(); i++)
	{
		convexForms.push_back(form.getConvexForms().at(i).clone());
	}

	points.reserve(form.size());
	for(unsigned i=0; i<form.size(); i++)
	{
		points.push_back(form.get(i).copy());
	}

	omega = form.getOmega();
	scale = form.getScale();
	flipH = form.getFlipH();
	flipV = form.getFlipV();
	surface = form.getSurface();

	orientation.setOrientation(omega, scale, flipH, flipV, form.getCenter());
}

Form Form::clone() const
{
	Form form((*this));
	return form;
}


void Form::resetTransformations()
{
	omega = 0;
	scale = 1.0f;
	flipH = false;
	flipV = false;
	surface = false;

	orientation.setOrientation(omega, scale, flipH, flipV, Vector3D(true));
}

void Form::clearTransformations()
{
	resetTransformations();
}

void Form::setInit(Form form)
{
	omega = form.getOmega();
	scale = form.getScale();
	flipH = form.getFlipH();
	flipV = form.getFlipV();
}

const Matrix4& Form::getOrientation() const
{
	return orientation;
}

Matrix4 Form::getOrientationInverse() const
{
	return orientation.getInverse();
}

Vector3D Form::getCentroidWorld() const
{
	return orientation * getCentroidLocal();
}

Vector3D Form::getCentroidLocal() const
{
	if(points.size() == 0)
		return Vector3D();
	else if(points.size() == 1)
		return getLocal();
	else if(points.size() == 2)
	{

		const Vector3D* locals = getPointsLocal();
		std::vector<Vector3D> points(locals, locals + size());
		return Vector3D((points.at(0).x() + points.at(1).x())/2,
							(points.at(0).y() + points.at(1).y())/2);
	}
	Vector3D center(true);
	float x0 = 0, y0 = 0, x1 = 0, y1 = 0, signedArea = 0, a = 0;
	const Vector3D* locals = getPointsLocal();
	std::vector<Vector3D> points(locals, locals + size());
	for(unsigned j=points.size()-1, i=0; i<points.size(); j=i, i++)
	{
		x0 = points.at(i).x();
		y0 = points.at(i).y();
		x1 = points.at(j).x();
		y1 = points.at(j).y();
		a = x0*y1 - x1*y0;
		signedArea += a;
		center.setX((x0 + x1)*a + center.getX());
		center.setY((y0 + y1)*a + center.getY());
	}

	signedArea *= 0.5;
	center.setX(center.getX() / (6.0f*signedArea));
	center.setY(center.getY() / (6.0f*signedArea));

	return center;
}

float Form::getLocalX() const
{
	if(size() > 0)
		return points.at(0).getX();
	return 0;
}

float Form::getLocalY() const
{
	if(size() > 0)
		return points.at(0).getY();
	return 0;
}

const Vector3D& Form::getLocal() const
{
	assert(size() > 0);
	return points.at(0);
}

float Form::getLocalX(unsigned n) const
{
	assert(n < size());
	return points.at(n).getX();
}

float Form::getLocalY(unsigned n) const
{
	assert(n < size());
	return points.at(n).getY();
}

Vector3D Form::getLocal(unsigned n) const
{
	assert(n < size());
	return points.at(n);
}

float Form::getX() const
{
	return getX(0);
}

float Form::getY() const
{
	return getY(0);
}

float Form::getX(unsigned n) const
{
	assert(n < size());
	return orientation.multiplyX(points.at(n));
}

float Form::getY(unsigned n) const
{
	assert(n < size());
	return orientation.multiplyY(points.at(n));
}

Vector3D Form::get() const
{
	return get(0);
}

Vector3D Form::get(unsigned n) const
{
	assert(n < size());
	Vector3D local = points.at(n);
	Vector3D world = orientation*local;
	return world;
}

float Form::getCenterX() const
{
	return orientation.getX();
}

float Form::getCenterY() const
{
	return orientation.getY();
}

Vector3D Form::getCenter() const
{
	return orientation.getPos();
}

int* Form::getXIntArray() const
{
	// Penser à free le tableau une fois que c'est plus utilisé
	int* l_X = new int[size()];
	for(unsigned i=0; i<points.size(); i++)
	{
		l_X[i] = (int) getX(i);
	}
	return l_X;
}

int* Form::getYIntArray() const
{
	int* l_Y = new int[size()];
	for(unsigned i=0; i<points.size(); i++)
	{
		l_Y[i] = (int) getY(i);
	}
	return l_Y;
}

float Form::getMinX() const
{
	float xMin = getX(0);
	for(unsigned i=1; i<points.size(); i++)
	{
		float x = getX(i);
		if(x < xMin)
			xMin = x;
	}
	return xMin;
}

float Form::getMinY() const
{
	float yMin = getY(0);
	for(unsigned i=1; i<points.size(); i++)
	{
		float y = getY(i);
		if(y < yMin)
			yMin = y;
	}
	return yMin;
}

float Form::getMaxX() const
{
	float xMax = getX(0);
	for(unsigned i=1; i<points.size(); i++)
	{
		float x = getX(i);
		if(x > xMax)
			xMax = x;
	}
	return xMax;
}

float Form::getMaxY() const
{
	float yMax = getY(0);
	for(unsigned i=1; i<points.size(); i++)
	{
		float y = getY(i);
		if(y > yMax)
			yMax = y;
	}
	return yMax;
}

// Penser à liberer lorsque fin d'utilisation du tableau
std::vector<Vector3D> Form::getVectorsSatLocal() const
{
	std::vector<Vector3D> l_vectors;
	for(unsigned j=points.size()-1, i=0; i<points.size(); j=i, i++)
	{
		Vector3D v(points.at(j), points.at(i));
		l_vectors.push_back(v.getPerpendicular2D());
	}

	//On enleve les vectors colinéaires
	for(unsigned i=0; i<l_vectors.size()-1; i++)
	{
		//Si on est en dessous de 2 vecteurs ca sert à rien de continuer,
		//On sait que ces 2 vecteurs (ou moins) ne sont pas colinéaires
		if(l_vectors.size() < 3)
			break;

		for(unsigned j=i+1; j<l_vectors.size(); j++)
		{
			if(l_vectors.at(i).isColinear2D(l_vectors.at(j)))
			{
				l_vectors.erase(l_vectors.begin() + i);
				i--;
				break;
			}
		}
	}
	return l_vectors;
}

Vector3D* Form::getVectorsLocal() const
{
	Vector3D* l_vectors = new Vector3D[size()];
	for(unsigned j=size()-1, i=0; i<size(); j=i, i++)
	{
		new (l_vectors + i) Vector3D(i, Vector3D(points.at(j), points.at(i)));
	}
	return l_vectors;
}

Vector3D* Form::getVectorsWorld() const
{
	Vector3D* l_vectors = getVectorsLocal();
	for(unsigned i=0; i<size(); i++)
	{
		l_vectors[i].set(orientation*l_vectors[i]);
	}
	return l_vectors;
}

Vector3D* Form::getPointsLocal() const
{
	Vector3D* l_vectors = new Vector3D[size()];
	for(unsigned i=0; i<size(); i++)
	{
		new (l_vectors + i) Vector3D(getLocal(i));
	}
	return l_vectors;
}

Vector3D* Form::getPointsWorld() const
{
	if(orientation.getX() == 0 && orientation.getY() == 0 && omega == 0 && scale == 1.0f && !flipV && !flipH)
		return getPointsLocal();
	Vector3D* l_vectors = new Vector3D[size()];
	for(unsigned i=0; i<size(); i++)
	{
		new (l_vectors + i) Vector3D(get(i));
	}
	return l_vectors;
}

Vector3D Form::transform(const Vector3D& vertex, const Vector3D& p,
		const Vector3D& v, const Matrix4& orientation, float& t) const
{
	Vector3D T = p + (orientation*vertex);

	if(t > 0)
		T += (v*t);
	return T;
}

Vector3D Form::handleEdgePoint(const Vector3D& PA, const Vector3D& PB1,
		const Vector3D& PB2) const
{
	Vector3D edgeB(PB1, PB2);
	Vector3D projection(PB1, PB2);
	float fProjection = edgeB*projection;

	return edgeB*fProjection;
}

std::vector<Form> Form::splitUnsecured(const Vector3D& p0, const Vector3D& p1, std::vector< std::set<Vector3D> > bst)
{
	std::vector<Form> forms;

	// On cherche la position des 2 points
	int pos0 = -1;
	int pos1 = -1;
	int pos = 0;
	while(pos0 == -1 || pos1 == -1)
	{
		if(&p0 == &(points[pos]))
		{
			pos0 = pos;
		}
		else if(&p1 == &(points[pos]))
		{
			pos1 = pos;
		}
		pos++;
	}

	if(pos0 + 1 != pos1 && pos1 + 1 != pos0)
	{
		// Form1
		Form form1;
		bst.push_back(std::set<Vector3D>());

		pos = pos0;
		while(pos != pos1)
		{
			form1.addPointFree(points[pos]);
			(bst[size() - 1]).insert(points[pos1]);
			pos = (pos + 1)%points.size();
		}
		form1.addPointFree(points[pos1]);
		bst[size() - 1].insert(points[pos1]);

		// Form2
		Form form2;
		bst.push_back(std::set<Vector3D>());

		pos = pos1;
		while(pos != pos0)
		{
			form2.addPointFree(points[pos]);
			bst[size() - 1].insert(points[pos]);
			pos = (pos + 1)%size();
		}
		form2.addPointFree(points[pos0]);
		bst[size() - 1].insert(points[pos0]);

		forms.push_back(form1);
		forms.push_back(form2);
	}
	else
	{
		forms.push_back((*this));
	}
	return forms;
}

Vector3D& Form::operator [](int i)
{
	return points[i];
}

void Form::updateCenter()
{
	Vector3D newCenter = getCentroidWorld();
	// Cas NaN, lorsque un flaot est NaN la comparaison avec elle même est toujours fausse
	if(newCenter.x() != newCenter.x() || newCenter.y() != newCenter.y())
	{
		calculateSurface();
		return;
	}

	Matrix4 lastCoor = orientation; //this.center
	Matrix4 newCoor = orientation.copy();
	newCoor.setPos(newCenter);
	Matrix4 inverse = newCoor.getInverse();
	Matrix4 result = inverse*(lastCoor);


	for(unsigned i=0; i<points.size(); i++)
	{
		/*
		result équivaut à ces opérations

		Vector2D p = points.get(i);
		Vector2D pW = orientation.multiply(p);
		Vector2D pN = inverse.multiply(pW);

		*/
		// Vector3D vec = result*points.at(i);
		points[i].set(result*points.at(i));
	}
	orientation.setPos(newCenter);

	//update inertia
	calculateSurface();
}

void Form::updateOrientation()
{
	orientation.setOrientation(omega, scale, flipH, flipV);
}

void Form::setCenter(const Vector3D& center)
{
	Vector3D vec(getCenter(), center);
	translate(vec);
}

void Form::setPoint(unsigned n, const Vector3D& p)
{
	assert(n < size());
	points[n].set(orientation.getInverse()*p);
}

void Form::addPointFree(const Vector3D& p)
{
	// Pas d'actualisation du centre
	if(orientation.getDeterminant() != 0)
		points.push_back(orientation.getInverse()*p);
	else
		points.push_back(Vector3D(getCenter(), p));
	convexForms.clear();
}

void Form::addPoint(const Vector3D& p)
{
	addPointFree(p);
	updateCenter();
}

void Form::removePoint(unsigned i)
{
	assert(i < size() && i > 0);
	points.erase(points.begin() + i);
	convexForms.clear();
	updateCenter();
}

void Form::removeLast()
{
	removePoint(size() - 1);
}

Vector3D Form::transformLocalToWorld(const Vector3D& point) const
{
	return orientation*point;
}

Vector3D Form::transformWorldToLocal(const Vector3D& point) const
{
	Matrix4 inverse = orientation.getInverse();
	return inverse*point;
}

void Form::translate(const Vector3D& v)
{
	orientation.translate(v);
}

void Form::translateX(float x)
{
	orientation.translateX(x);
}

void Form::translateY(float y)
{
	orientation.translateY(y);
}

void Form::rotateDegrees(float omega, const Vector3D& center)
{
	rotateRadians((float) (omega*PI)/180, center);
}

void Form::rotateRadians(float omega, const Vector3D& center)
{
	this->omega += omega;
	orientation.rotateRadiansZFree(omega, center);
	updateOrientation();
}

void Form::scaleF(float factor, const Vector3D& center)
{
	scale *= factor;
	orientation.scale(factor, center);
}

void Form::flipHF(const Vector3D& center)
{
	flipH = !flipH;
	orientation.flipX(center);
}

void Form::flipVF(const Vector3D& center)
{
	flipV = !flipV;
	orientation.flipY(center);
}

void Form::setPos(const Vector3D& v)
{
	assert(v.getW() != 0); // Ce n'est pas un point mais un vecteur
	orientation.setPos(v);
}

void Form::setRadians(float omega)
{
	float f = omega - this->omega;
	this->omega = omega;
	orientation.rotateRadiansZFree(f, Vector3D(true));
	updateOrientation();
}

void Form::setScale(float scale)
{
	float factor = scale/this->scale;
	assert(factor == factor); // Pas de cas NaN
	orientation.scale(factor);
}

void Form::setFlipH(bool flipH)
{
	if(this->flipH != flipH)
	{
		this->flipH = flipH;
		orientation.flipX();
	}
}

void Form::setFlipV(bool flipV)
{
	if(this->flipV != flipV)
	{
		this->flipV = flipV;
		orientation.flipY();
	}
}

void Form::calculateSurface()
{
	surface = 0;
	if(points.size() < 3)
		return;
	for(unsigned i=points.size()-2, i1=points.size()-1, i2=0; i2<points.size(); i=i1, i1=i2, i2++)
	{
		surface += points.at(i1).x()*(points.at(i2).y()-points.at(i).y()) + points.at(i1).y()*(points.at(i).x()-points.at(i2).x());
	}
	surface /= 2;
}

bool Form::collisionSat(Form& form)
{
	if(convexForms.size() == 0)
		updateConvexForms();
	if(form.getConvexForms().size() == 0)
		form.updateConvexForms();

	for(unsigned i=0; i<convexForms.size(); i++)
	{
		Vector3D VA(true);
		Vector3D VB(true);
		if(convexForms.at(i).collisionSatFree(form, VA, VB))
			return true;
	}
	return false;
}

bool Form::collisionSat(Form& form, const Vector3D& VA,
		const Vector3D& VB, const Vector3D& push, float& t)
{
	if(convexForms.size() == 0)
		updateConvexForms();
	if(form.getConvexForms().size() == 0)
		form.updateConvexForms();

	for(unsigned i=0; i<convexForms.size(); i++)
	{
		Vector3D VA(true);
		Vector3D VB(true);
		if(convexForms.at(i).collisionSatA(form, VA, VB, push, t))
			return true;
	}
	return false;
}

bool Form::collisionSatFree(const Form& B, const Vector3D& VA,
		const Vector3D& VB)
{
	Form& A = (*this);

	//Les vecteurs VA et VB sont exprimés dans le repère world
	//Les points PA et PB sont exprimés dans le repères world

	Matrix4 OA = A.getOrientation();
	Matrix4 OB = B.getOrientation();
	Matrix4 OBi = OB.getInverse();
	//La matrice orient permet le passage d'un point du repère local de A à B
	Matrix4 orient = OA*OBi;
	//La matrice orientI permet le passage d'un point du repère local de B à A
	Matrix4 orientI = orient.getInverse();

	Vector3D PA = getCenter();
	Vector3D PB = B.getCenter();

	Vector3D relPos = OBi*(PA-PB);
	Vector3D relVel = OBi*(VA-VB);

	Vector3D* pointsA = getPointsLocal();
	Vector3D* pointsB = B.getPointsLocal();

	std::vector<Vector3D> axisA = getVectorsSatLocal();
	std::vector<Vector3D> axisB = B.getVectorsSatLocal();

	AxesSat axesSat();

	int sizeA = size();
	int sizeB = B.size();

	float squaredVel = relVel.getSqMagnitude();
	if(squaredVel > 0.000001f)
	{
		if(!intervalIntersectionFree(relVel.getPerpendicular2D(), pointsA, sizeA, pointsB, sizeB, relPos, relVel, orientI))
		{
			delete[] pointsA; delete[] pointsB;
			return false;
		}
	}

	for(unsigned i=0; i<axisA.size(); i++)
	{
		if(!intervalIntersectionFree(orient*axisA.at(i), pointsA, sizeA, pointsB, sizeB, relPos, relVel, orientI))
		{
			delete[] pointsA; delete[] pointsB;
			return false;
		}
	}

	for(unsigned i=0; i<axisB.size(); i++)
	{
		if(!intervalIntersectionFree(axisB.at(i), pointsA, sizeA, pointsB, sizeB, relPos, relVel, orientI))
		{
			delete[] pointsA; delete[] pointsB;
			return false;
		}
	}
	delete[] pointsA; delete[] pointsB;
	return true;
}

bool Form::intervalIntersectionFree(const Vector3D& axis,
		const Vector3D* pointsA, unsigned sizeA, const Vector3D* pointsB, unsigned sizeB,
		const Vector3D& relPos, const Vector3D& relVel, const Matrix4& orientI) const
{
	Vector3D minMaxA = getInterval(orientI*axis, pointsA, sizeA);
	Vector3D minMaxB = getInterval(axis, pointsB, sizeB);

	//On ajoute le décalage entre les deux repères
	float h = relPos*(axis);
	minMaxA.addX(h);
	minMaxA.addY(h);

	//On calcule les distances pour determiner le chevauchement
	float d0 = minMaxA.x() - minMaxB.y();
	float d1 = minMaxB.x() - minMaxA.y();

	if(d0 > 0 || d1 > 0)//Pas de chevauchement
		return false;
	return true;
}

bool Form::collisionSatA(const Form& B, const Vector3D& VA, const Vector3D& VB,
		const Vector3D& push, float& t) const
{
	// Les vecteurs VA et VB sont exprimés dans le repère world
	// Les points PA et PB sont exprimés dans le repères world

	Matrix4 OA = getOrientation();
	Matrix4 OB = B.getOrientation();
	Matrix4 OBi = OB.getInverse();
	// La matrice orient permet le passage d'un point du repère local de A à B
	Matrix4 orient = OA*OBi;
	// La matrice orientI permet le passage d'un point du repère local de B à A
	Matrix4 orientI = orient.getInverse();

	Vector3D PA = getCenter();
	Vector3D PB = B.getCenter();

	Vector3D relPos = OBi*(PA-PB);
	Vector3D relVel = OBi*(VA-VB);

	Vector3D* pointsA = getPointsLocal();
	Vector3D* pointsB = B.getPointsLocal();

	std::vector<Vector3D> axisA = getVectorsSatLocal();
	std::vector<Vector3D> axisB = B.getVectorsSatLocal();

	AxesSat axesSat; // = new AxesSat();

	int sizeA = size();
	int sizeB = B.size();

	float squaredVel = relVel.getSqMagnitude();

	if(squaredVel > 0.000001f)
	{
		if(!intervalIntersection(relVel.getPerpendicular2D(), pointsA, sizeA,
				pointsB, sizeB, relPos, relVel, orientI, axesSat, t))
		{
			delete[] pointsA; delete[] pointsB;
			return false;
		}
	}

	for(unsigned i=0; i<axisA.size(); i++)
	{
		if(!intervalIntersection(orient*axisA.at(i), pointsA, sizeA,
				pointsB, sizeB, relPos, relVel, orientI, axesSat, t))
		{
			delete[] pointsA; delete[] pointsB;
			return false;
		}
	}

	for(unsigned i=0; i<axisB.size(); i++)
	{
		if(!intervalIntersection(axisB.at(i), pointsA, sizeA,
				pointsB, sizeB, relPos, relVel, orientI, axesSat, t))
		{
			delete[] pointsA; delete[] pointsB;
			return false;
		}
	}
	delete[] pointsA; delete[] pointsB;
	return true;
}

bool Form::intervalIntersection(const Vector3D& axis, const Vector3D* pointsA,
		unsigned sizeA, const Vector3D* pointsB, unsigned sizeB, const Vector3D& relPos,
		const Vector3D& relVel, const Matrix4& orientI, AxesSat& axes, float& t) const
{
	Vector3D minMaxA = getInterval(orientI*axis, pointsA, sizeA);
	Vector3D minMaxB = getInterval(axis, pointsB, sizeB);

	// On ajoute le décalage entre les deux repères
	float h = relPos*axis;
	minMaxA.addX(h);
	minMaxA.addY(h);

	// On calcule les distances pour determiner le chevauchement
	float d0 = minMaxA.x() - minMaxB.y();
	float d1 = minMaxB.x() - minMaxA.y();

	if(d0 > 0 || d1 > 0) // Pas de chevauchement
	{
		float fVel = relVel*axis;
		if(std::abs(fVel) > 0.00000001f)
		{
			float t0 =-d0/fVel;
			float t1 = d1/fVel;

			if(t0 > t1) {float temp = t0; t0 = t1; t1 = temp;}
			float l_tAxis = (t0 > 0)? t0:t1;

			if(l_tAxis < 0 || l_tAxis > t)
				return false;

			axes.axesT.push_back(axis);
			axes.tAxesT.push_back(l_tAxis);
			return true;
		}
		return false;
	}
	else
	{
		axes.axes.push_back(axis);
		axes.tAxes.push_back((d0 > d1)? d0:d1);
		return true;
	}
}

Vector3D Form::getInterval(const Vector3D& axis, const Vector3D* points, unsigned size) const
{
	Vector3D minMax(points[0].getX(), points[0].getY(), 0, true);
	for(unsigned i=1; i<size; i++)
	{
		float scalar = points[i]*axis;
		if(scalar < minMax.x())
		{
			minMax[0] = scalar;
		}
		else if(scalar > minMax.y())
		{
			minMax[1] = scalar;
		}
	}
	return minMax;
}

void Form::getPushVector(AxesSat& axesSat, Vector3D& push, float& t)
{
	t = 0;
	bool found = false;
	for(int i=0; axesSat.axesT.size(); i++)
	{
		if(axesSat.tAxesT.at(i) > t)
		{
			t = axesSat.tAxesT.at(i);
			push.set(axesSat.axesT.at(i));
			found = true;
		}
	}
	push.normalize();

	if(!found)
	{
		float magnitude1 = axesSat.axes[0].normalize();
		axesSat.tAxes[0] = axesSat.tAxes.at(0)/magnitude1;
		t = axesSat.tAxes[0];
		push.set(axesSat.axes[0]);

		for(unsigned i=1; i<axesSat.axes.size(); i++)
		{
			float magnitude = axesSat.axes[i].normalize();
			axesSat.tAxes[1] = axesSat.tAxes[i]/magnitude;
			if(axesSat.tAxes[i] > t)
			{
				t = axesSat.tAxes[i];
				push.set(axesSat.axes[i]);
				found = true;
			}
		}
	}
}

bool Form::isConvex() const
{
	if(size() < 3)
		return true;
	Vector3D* locals = getVectorsLocal();
	unsigned i=0;
	float crossProductZ = 0;

	while(crossProductZ == 0 && i<size())
	{
		crossProductZ = (locals[i]%locals[(i+1)%size()]).getZ();
		i++;
	}

	for(; i<size(); i++)
	{
		float crossProductZ2 = (locals[i]%locals[(i+1)%size()]).getZ();

		//Si les deux vectoriels z sont de sens différents, alors la forme n'est pas convexe
		if(crossProductZ * crossProductZ2 < 0)
			return false;
	}

	return true;
}

int Form::getClockwise() const
{
	if(size() < 3)
		return 0;
	double sum = 0;
	//float sumInt = 0;
	for(unsigned i=0; i<size(); i++)
	{
		sum = sum + (PI - (points.at((i+1)%size()).getAngle2D(points.at(i), points.at((i+2)%size()))));
	}

	if(PI*2 - 0.001 < std::abs(sum) && std::abs(sum) < 2*PI + 0.001f)
	{
		if(sum < 0)
			return -1;
		return 1;
	}
	else
	{
		std::cout << sum;
		return 0;
	}
}

std::vector<Edge> Form::getEdgesLocal() const
{
	int factor = getClockwise();
	std::vector<Edge> edges;
	if(points.size() < 2 || factor == 0)
		return edges;

	PointType* pointsType = new PointType[size()];

	if(factor == 1)
	{
		for(int i=size()-1, j=0; i>-1; i--, j++)
		{
			new (pointsType + j) PointType(points.at(i));
			pointsType[j].posPoint = i;
			pointsType[j].posEdge = j;
			pointsType[j].type = -1;
		}
	}
	else
	{
		for(unsigned i=0; i<size(); i++)
		{
			new (pointsType + i) PointType(points.at(i));
			pointsType[i].posPoint = i;
			pointsType[i].posEdge = i;
			pointsType[i].type = -1;
		}
	}

	for(unsigned i=0; i<size(); i++)
	{
		edges.push_back(Edge());

		edges[i].p0 = &pointsType[i];
		edges[i].p1 = &pointsType[(i+1)%size()];

		if(i != 0)
		{
			edges[i].prev = &edges[i - 1];
			edges[i - 1].next = &edges[i];
		}
	}
	edges[0].prev = &edges[size() - 1];
	edges[size() - 1].next = &edges[0];

	return edges;
}

//--------------------
//	  Triangulate
//--------------------
void Form::triangulate()
{
	convexForms.clear();

	std::vector<Form> monotonesForms = makeMonotone();
	if(monotonesForms.size() != 0)
	{
		for(unsigned i=0; i<monotonesForms.size(); i++)
		{
			convexForms.insert(convexForms.begin(), monotonesForms.begin(), monotonesForms.end());
		}
	}
	else
		convexForms.push_back((*this));
}

//******************
//  Make Monotone
//******************

std::vector<Form> Form::makeMonotone()
{
	std::vector<Edge> edges = getEdgesLocal();
	std::vector<Form> forms;
	if(size() < 2 || size() == 3)
		return forms;

	//***************
	//Initialization
	//***************
	int sizeV = size();
	int* v = new int[sizeV];

	//Scanning line l store Edges colliding with l, sorted by x
	std::map<float, std::vector<Edge> > l;
	std::vector<Edge> preBufferL;

	//<Edge, PointType>
	std::map<Edge, PointType> helpers;
	std::set<PointType> trash;

	//***************
	//   Sorting
	//***************
	//1) on range par ordre croissant suivant Y les points
	sortPointsY(edges, v, sizeV);

	//***************
	//     Loop
	//***************
	PointType *p0, *p1, *p2;
	//2) On applique une méthode pour chaque point
	int cur = 0;
	while(cur < sizeV)
	{
		int pos = v[cur];
		Edge edge = edges[pos];
		cur++;

		//On determine le type de point
		p0 = edge.prev->p0;
		p1 = edge.p0;
		p2 = edge.p1;

		trash.insert((*p1));

		//On regarde si les 2 segments débutent à partir de ce point
		//ou finissent à partir de ce point
		bool is_in = trash.find((*p0)) != trash.end();
		if(is_in)
		{
			float minX = edge.prev->getMinX();
			// assert(l.find(minX) != NULL);
			std::vector<Edge> e = l.at(minX);
			if(e.size() == 1)
			{
				e.clear();
				l.erase(minX);
			}
			else
			{
				for(std::vector<Edge>::iterator it = e.begin(); it != e.end(); it++)
				{
					if(&(*it) == edge.prev)
					{
						e.erase(it);
						break;	//it is now invalud must break!
					}
				}
			}
		}
		else
			preBufferL.push_back((*edge.prev));

		is_in = trash.find((*p2)) != trash.end();
		if(is_in)
		{
			float minX = edge.getMinX();
			std::vector<Edge> e = l.at(minX);
			if(e.size() == 1)
			{
				e.clear();
				l.erase(minX);
			}
			else
			{
				for(std::vector<Edge>::iterator it = e.begin(); it != e.end(); it++)
				{
					if(&(*it) == edge.prev)
					{
						e.erase(it);
						break;	//it is now invalud must break!
					}
				}
			}

		}
		else
			preBufferL.push_back((*edge.prev));

		//***************
		//     Type
		//***************
		determineType(pos, edges, helpers, l);

		//On ajoute les nouveaux segments stockés dans le prébuffer
		for(unsigned i=0; i<preBufferL.size(); i++)
		{
			float minX = preBufferL.at(i).getMinX();
			is_in = l.find(minX) != l.end();
			if(is_in)
			{
				(l.at(minX)).push_back(preBufferL.at(i));
			}
			else
			{
				std::vector<Edge> e;
				e.push_back(preBufferL[i]);
				l[minX] = e;
			}
		}
		preBufferL.clear();
	}

	return transformEdges(edges);
}

void Form::sortPointsY(std::vector<Edge>& edges, int* v, unsigned sizeV)
{
	PointType *p0, *p1;
	for(unsigned i=0; i<points.size(); i++)
	{
		v[i] = i;
	}

	// Tri à bulles
	// Opti dégueu mais bon
	for(unsigned t=0; t<sizeV-1; t++)
	{
		for(unsigned i=t; i<sizeV-1; i++)
		{
			p0 = edges[v[i]].p0;
			p1 = edges[v[i+1]].p0;
			if(p0->y() > p1->y())
			{
				// Echange
				int tmp = v[i+1];
				v[i+1] = v[i];
				v[i] = tmp;
			}
			else if(p0->y() == p1->y())
			{
				if(p0->x() < p1->y())
				{
					// Echange
					int tmp = v[i+1];
					v[i+1] = v[i];
					v[i] = tmp;
				}
			}
		}
	}
}

void Form::sortPointsY(std::vector<Edge>& edges, std::vector<int>& v)
{
	PointType *p0, *p1;
	for(unsigned i=0; i<points.size(); i++)
	{
		v.push_back(i);
	}

	// Tri à bulles
	// Opti dégueu mais bon
	for(unsigned i=v.size()-1; i != 1; i++)
	{
		for(unsigned j=0; j<i-1; j++)
		{
			p0 = edges[v[i]].p0;
			p1 = edges[v[i+1]].p0;
			if(p0->y() > p1->y())
			{
				// Echange
				int tmp = v[i+1];
				v[i+1] = v[i];
				v[i] = tmp;
			}
			else if(p0->y() == p1->y())
			{
				if(p0->x() < p1->y())
				{
					// Echange
					int tmp = v[i+1];
					v[i+1] = v[i];
					v[i] = tmp;
				}
			}
		}
	}
}

void Form::determineType(int pos, std::vector<Edge> edges,
		std::map<Edge, PointType>& helpers,
		std::map<float, std::vector<Edge> >& I)
{
	Edge edge = edges[pos];

	// On determine le type de point
	PointType* p0 = edge.prev->p0;
	PointType* p1 = edge.p0;
	PointType* p2 = edge.p1;

	float theta = -(PI - p1->getAngle2D((*p0), (*p2)));
	if(p1->y() < p0->y() && p1->y() < p2->y())
	{
		if(theta > 0 && theta < PI)
		{
			// Start
			p1->type = PointType::START;
			handleStartVertex(pos, edges, helpers);
		}
		else
		{
			// Split
			p1->type = PointType::SPLIT;
			handleSplitVertex(pos, edges, helpers, I);
		}
	}
	else if(p1->y() > p0->y() && p1->y() > p2->y())
	{
		if(theta > 0 && theta < PI)
		{
			// End
			p1->type = PointType::END;
			handleEndVertex(pos, edges, helpers);
		}
		else
		{
			// Merge
			handleMergeVertex(pos, edges, helpers, I);
		}
	}
	else if(p1->y() == p0->y() || p1->y() == p2->y())
	{
		if((p1->y() < p0->y() && p1->x() > p2->x()) || (p1->y() < p2->y() && p1->x() > p0->x()))
		{
			if(theta > 0 && theta < PI)
			{
				// Start
				p1->type = PointType::START;
				handleStartVertex(pos, edges, helpers);
			}
			else
			{
				// Split
				p1->type = PointType::SPLIT;
				handleSplitVertex(pos, edges, helpers, I);
			}
		}
		else if((p1->y() > p0->y() && p1->x() < p2->x()) || (p1->y() > p2->y() && p1->x() < p0->x()))
		{
			if(theta > 0 && theta < PI)
			{
				// End
				p1->type = PointType::END;
				handleEndVertex(pos, edges, helpers);
			}
			else
			{
				// Merge
				p1->type = PointType::MERGE;
				handleMergeVertex(pos, edges, helpers, I);
			}
		}
		else if(p1->y() == p0->y() && p1->y() == p2->y())
		{
			// Nothing
		}
		else
		{
			// Regular
			p1->type = PointType::REGULAR;
			handleRegularVertex(pos, edges, helpers, I);
		}
	}
	else
	{
		// Regular
		p1->type = PointType::REGULAR;
		handleRegularVertex(pos, edges, helpers, I);
	}
}

Edge* Form::getLeftEdge(int pos, std::vector<Edge> edges,
		std::map<float, std::vector<Edge> >& I)
{
	PointType* p = edges[pos].p0;
	std::map<float, std::vector<Edge> >::iterator low, lastLow;
	low = I.lower_bound(p->x());
	Edge* leftEdge = getLeftEdge((*p), low->second);

	while(leftEdge == NULL)
	{
		lastLow = low;
		low = I.lower_bound(low->first);
		if((low == I.end()) || (low->second == lastLow->second))
			return NULL;
		leftEdge = getLeftEdge((*p), low->second);
	}
	return leftEdge;
}

Edge* Form::getLeftEdge(PointType& p, std::vector<Edge> lEdges)
{
	for(unsigned i=0; i<lEdges.size(); i++)
	{
		Vector3D vec(lEdges[i].p0, lEdges[i].p1);
		Vector3D projection = p.getProjection2D(vec, lEdges[i].p0);
		projection = projection - p;
		if(projection.x() < 0)
			return &lEdges[i];
	}
	return NULL;
}

std::vector<Form> Form::transformEdges(std::vector<Edge> edges)
{
	std::vector<Form> forms;
	std::vector<std::set<Vector3D> > bst;

	forms.push_back((*this));
	bst.push_back(std::set<Vector3D>());
	bst[0].insert(points.begin(), points.end());

	for(unsigned i=points.size(); i<edges.size(); i++)
	{
		Edge edge = edges[i];
		Vector3D *p0 = &points[edge.p0->posPoint];
		Vector3D *p1 = &points[edge.p1->posPoint];

		int n = 0;
		int max = forms.size();
		for(int j=0; j<max; j++)
		{
			bool is_in = (bst[j]).find(p0) != bst[j].end();
			bool is_in1 = (bst[j]).find(p1) != bst[j].end();
			if(is_in && is_in1)
			{
				std::vector<std::set<Vector3D> > bst2;
				std::vector<Form> newForm = forms[j].splitUnsecured(p0, p1, bst2);
				if(newForm.size() == 2)
				{
					forms.insert(forms.end(), newForm.begin(), newForm.end());
					forms.erase(forms.end() + j);
					bst.insert(bst.end(), bst2.begin(), bst2.end());
					bst.erase(bst.begin() + j);

					max--;
					j--;
					n++;
				}
			}
		}
	}
	return forms;
}

void Form::handleStartVertex(int pos, std::vector<Edge> edges,
		std::map<Edge, PointType>& helpers)
{
	helpers[edges[pos]] = (*edges[pos].p0);
}

void Form::handleEndVertex(int pos, std::vector<Edge> edges,
		std::map<Edge, PointType>& helpers)
{
	// Si c'est le helper du coté précédent est un point de type merge
	// il sera dans l'arbre

	if(helpers.find((*edges[pos].prev)) != helpers.end())
	{
		PointType helper = helpers.at((*edges[pos].prev));
		// On crée une diagnoale entre le point pos et le helper
		Edge diagonal;
		diagonal.p0 = edges[pos].p0;
		diagonal.p1 = &helper;
		diagonal.prev = NULL;
		diagonal.next = NULL;
		edges.push_back(diagonal);
	}
	helpers.erase((*edges[pos].prev));
}
void Form::handleSplitVertex(int pos, std::vector<Edge> edges,
		std::map<Edge, PointType>& helpers,
		std::map<float, std::vector<Edge> >& I)
{
	// On cherche le coté à gauche du point le plus proche
	Edge *leftEdge = getLeftEdge(pos, edges, I);
	assert(leftEdge != NULL);

	// On récupère le helper de ce coté
	PointType helper = helpers.at((*leftEdge));

	// On crée une diagonale entre le point pos et le helper
	Edge diagonal;
	diagonal.p0 = edges[pos].p0;
	diagonal.p1 = &helper;
	diagonal.prev = NULL;
	diagonal.next = NULL;
	edges.push_back(diagonal);

	//Le helper du coté à gauche devient vi
	helpers.erase((*leftEdge));
	helpers[(*leftEdge)] = (*diagonal.p0);
	helpers[edges[pos]] = (*edges[pos].p0);
}

void Form::handleMergeVertex(int pos, std::vector<Edge> edges,
		std::map<Edge, PointType>& helpers,
		std::map<float, std::vector<Edge> >& I)
{
	// On regarde le type du helper du dernier coté
	if(helpers.find((*edges[pos].prev)) != helpers.end())
	{
		PointType helper = helpers.at((*edges[pos].prev));
		if(helper.type == PointType::MERGE)
		{
			//On crée une diagonale entre le point pos et le helper
			Edge diagonal;
			diagonal.p0 = edges[pos].p0;
			diagonal.p1 = &helper;
			diagonal.prev = NULL;
			diagonal.next = NULL;
			edges.push_back(diagonal);
		}
	}
	helpers.erase((*edges[pos].prev));

	// On cherche le coté à gauche de ce point
	Edge* leftEdge = getLeftEdge(pos, edges, I);
	assert(leftEdge != NULL);

	// On récupère le helper de ce coté

	if(helpers.find((*leftEdge)) != helpers.end())
	{
		PointType helper = helpers.at((*leftEdge));
		if(helper.type == PointType::MERGE)
		{
			//On crée une diagonale entre le point pos et le helper
			Edge diagonal;
			diagonal.p0 = edges[pos].p0;
			diagonal.p1 = &helper;
			diagonal.prev = NULL;
			diagonal.next = NULL;
			edges.push_back(diagonal);
		}
	}
	//Le helper du coté à gauche devient vi
	helpers.erase((*leftEdge));
	helpers[(*leftEdge)] = (*edges[pos].p0);
}

void Form::handleRegularVertex(int pos, std::vector<Edge> edges,
		std::map<Edge, PointType>& helpers,
		std::map<float, std::vector<Edge> >& I)
{
	//On détermine si le polygone est à droite du coté
	//si le nombre de coté touché est pair = exterieur à droite
	//si le nombre de coté touché est impair = intérieur à droite

	int numberLines = numberLeftEdges(pos, edges, I);
	//System.out.println("size: " + numberLines);
	if(numberLines%2 == 0)
	{//impair

		if(helpers.find((*edges[pos].prev)) != helpers.end())
		{
			PointType helper = helpers.at((*edges[pos].prev));
			if(helper.type == PointType::MERGE)
			{
				//On crée une diagonale entre le point pos et le helper
				Edge diagonal;
				diagonal.p0 = edges[pos].p0;
				diagonal.p1 = &helper;
				diagonal.prev = NULL;
				diagonal.next = NULL;
				edges.push_back(diagonal);
			}
		}
		helpers.erase((*edges[pos].prev));
		helpers[edges[pos]] = (*edges[pos].p0);
	}
	else
	{//pair
		//On cherche le coté à gauche de ce point
		Edge* leftEdge = getLeftEdge(pos, edges, I);
		assert(leftEdge != NULL);

		//On récupère le helper de ce coté
		if(helpers.find((*edges[pos].prev)) != helpers.end())
		{
			PointType helper = helpers.at((*edges[pos].prev));
			if(helper.type == PointType::MERGE)
			{
				//On crée une diagonale entre le point pos et le helper
				Edge diagonal;
				diagonal.p0 = edges[pos].p0;
				diagonal.p1 = &helper;
				diagonal.prev = NULL;
				diagonal.next = NULL;
				edges.push_back(diagonal);
			}
		}
		//Le helper du coté à gauche devient vi
		helpers.erase((*leftEdge));
		helpers[(*leftEdge)] = (*edges[pos].p0);
	}
}

int Form::numberLeftEdges(int pos, std::vector<Edge> edges,
		std::map<float, std::vector<Edge> >& I)
{
	/*
	 *
	 * 	Peut être un problème ici
	 * 	A verifier
	 *
	 *
	 */

	int numberLines = 0;
	PointType* p = edges[pos].p0;

	std::map<float, std::vector<Edge> >::iterator low, lastLow;
	low = I.lower_bound(p->x());

	if(low != I.end())
	{
		numberLines += numberLeftEdges((*p), low->second);
		do
		{
			numberLines += numberLeftEdges((*p), low->second);
			lastLow = low;
			low = I.lower_bound(low->first);

		} while(low != I.end() && low->second != lastLow->second);
	}
	return numberLines;
}

int Form::numberLeftEdges(PointType& p, std::vector<Edge> edges)
{
	int numberLines = 0;
	for(unsigned i=0; i<edges.size(); i++)
	{
		Vector3D vec(edges[i].p0, edges[i].p1);
		Vector3D projection = p.getProjection2D(vec, (*edges[i].p0));
		projection -= p;

		if(projection.x() < 0)
			numberLines++;
	}
	return numberLines;
}

std::vector<Form> Form::triangulateMonotone()
{
	std::vector<Edge> edges = getEdgesLocal();

	std::vector<Form> forms;
	int sizeV = size();
	int* v = new int[sizeV];
	std::deque<int> l;

	if(edges.size() < 3)
	{
		return std::vector<Form>();
	}

	std::set<PointType> lChain;
	//1) on range par ordre croissant suivant Y les points
	sortPointsY(edges, v, sizeV);
	createChains(v, sizeV, edges, lChain);

	//int factorChain = determineFactorChain(edges.get(v.get(v.size() - 1)), edges);

	//2) Initialisation de L, on ajout les 2 premiers points
	int cur = 0;

	l.push_back(v[cur]);
	cur++;
	l.push_back(v[cur]);
	cur++;

	PointType *p1, *last;
	while(cur < sizeV)
	{
		int pos = v[cur];
		Edge edge = edges[pos];
		cur++;

		p1 = edge.p0;


		last = edges[l[l.size() - 1]].p0;

		//Si le point appartient à une chaine différente
		bool is_in  = lChain.find((*last)) != lChain.end();
		bool is_in2 = lChain.find((*p1)) != lChain.end();
		if(is_in != is_in2)
		{
			while(l.size() > 1)
			{
				Vector3D l_p0 = points[edges[l[0]].p0->posPoint];
				Vector3D l_p1 = points[edges[l[1]].p0->posPoint];
				Vector3D l_p2 = points[p1->posPoint];

				Form form;
				form.addPointFree(l_p0);
				form.addPointFree(l_p1);
				form.addPointFree(l_p2);
				forms.push_back(form);
				l.pop_front();
			}
			l.push_back(pos);
		}
		else
		{
			if(l.size() > 1)
			{
				Vector3D q = points[edges[l[l.size() - 1]].p0->posPoint];
				Vector3D r = points[edges[l[l.size() - 2]].p0->posPoint];
				Vector3D p = points[p1->posPoint];

				//vec1.crossProductZ(vec2)
				bool bLChain = lChain.find((*p1)) != lChain.end();
				float orientation = Vector3D::orientation(p, q, r);
				while(l.size() > 1 && ((bLChain && orientation > 0) || (!bLChain && orientation < 0)))
				{
					Form form;
					form.addPointFree(q);
					form.addPointFree(r);
					form.addPointFree(p);
					forms.push_back(form);

					l.pop_back();
					if(l.size() > 1)
					{
						q = points[edges[l[l.size() - 1]].p0->posPoint];
						r = points[edges[l[l.size() - 2]].p0->posPoint];

						orientation = Vector3D::orientation(p1, q, r);
					}
				}
			}
			l.push_back(pos);
		}
	}

	if(l.size() > 2)
	{
		//On ajoute les derniers triangles
		cur--;
		l.pop_back();
		for(unsigned i=0; i<l.size()-1; i++)
		{

			Vector3D l_p0 = points[edges[l[i]].p0->posPoint];
			Vector3D l_p1 = points[edges[l[i + 1]].p0->posPoint];
			Vector3D l_p2 = points[edges[v[sizeV - 1]].p0->posPoint];

			Form form;
			form.addPointFree(l_p0);
			form.addPointFree(l_p1);
			form.addPointFree(l_p2);
			forms.push_back(form);
		}
	}
	return forms;
}

void Form::createChains(int *v, int sizeV, std::vector<Edge> edges,
		std::set<PointType> lChain)
{
	Edge start = edges[v[0]];
	PointType* last = edges[v[sizeV - 1]].p0;

	Vector3D collisionVec(start.p0, start.next->p0);
	Vector3D vec(1.0f, 0.0f);

	Vector3D collision;
	bool result = collision.computeIntersection2D(collisionVec, vec, start.p0, (*start.prev->p0));
	bool left = false;
	if(result)
	{
		left = (collision.x() < start.prev->p0->x());
	}
	else
	{
		assert(start.next->p0->y() == start.p0->y());
		left = (start.next->p0->x() < start.p0->x());
	}

	if(left)
	{
		Edge* current = start.next;
		while(current->p0 != last)
		{
			lChain.insert((*current->p0));
			current = current->next;
		}
	}
	else
	{
		Edge* current = start.prev;
		while(current->p0 != last)
		{
			lChain.insert((*current->p0));
			current = current->prev;
		}
	}
}

std::vector<Form> Form::getTriangulation()
{
	std::vector<Form> forms;
	if(isConvex())
	{
		forms.push_back((*this));
		return forms;
	}
	std::deque<Vector3D> pointsV(points.size());
	for(unsigned i=0; i<points.size(); i++)
		pointsV.push_back(points[i]);
	//ArrayList<Point2D[]> edgesL = new ArrayList<Point2D[]>();

	std::deque<int> pointsVPos(points.size());
	std::deque<int> pointsPreviousVPos(points.size());
	std::deque<int> edgesLPos;
	for(unsigned i=0; i<pointsV.size(); i++)
		pointsVPos.push_back(i);

	//1) on range par ordre croissant suivant X les points
	for(unsigned t=1; t<pointsV.size(); t++)
	{
		for(unsigned i=0; i<pointsV.size() - 1; i++)
		{
			if(pointsV[i].x() > pointsV[i+1].x())
			{
				std::iter_swap(pointsV.begin() + i, pointsV.begin() + i + 1);
			}
		}
	}

	Vector3D p[3];
	int pos[3];
	//2) Pour chaque point, on cherche les points d'interesections avec le polygon
	while(pointsV.size() != 0)
	{
		//a) insertion des segments
		p[1] = pointsV[0];
		pos[1] = pointsVPos[0];
		pointsV.pop_front();
		pointsVPos.pop_front();

		//On récupère les deux autres points reliés à ce point
		//point précédent
		pos[0] = pos[1] - 1;
		if(pos[0] < 0)
			pos[0] = points.size() - 1;
		p[0] = points[pos[0]];

		//point suivant
		pos[2] = (pos[1] + 1)%points.size();
		p[2] = points[pos[2]];

		//On insère un segment si le point est à droite, sinon on l'enleve
		//+= 2 signifie, on regarde le point précédent puis le point suivant
		for(int i=0; i<3; i += 2)
		{
			//Dans le cas ou le point a le même x, on prend seulement le point s'il est est au dessus (y inférieur)
			if(p[1].x() < p[i].x())
			{
				bool added = false;
				for(unsigned j=0; j<edgesLPos.size(); j++)
				{
					if(p[1].y() < points[edgesLPos[j]].y())
					{
						edgesLPos.insert(edgesLPos.begin() + j, pos[0] + i/2);
						added = true;
					}
				}
				if(!added)
					edgesLPos.push_back(pos[0] + i/2);
			}
			else if(p[1].x() == p[i].x() && p[1].y() <= p[i].y())
			{
				assert(p[i].y() != p[1].y());

				bool added = false;
				for(unsigned j=0; j<edgesLPos.size(); j++)
				{
					if(p[1].y() < points[edgesLPos[j]].y())
					{
						edgesLPos.insert(edgesLPos.begin() + j, pos[0] + i/2);
						added = true;
					}
				}
				if(!added)
					edgesLPos.push_back(pos[0] + i/2);
			}
			else
			{
				//On enleve le segment
				bool b = false;
				for(unsigned j=0; j<edgesLPos.size(); j++)
				{
					if(pos[0] + i/2 == edgesLPos[j])
					{
						edgesLPos.erase(edgesLPos.begin() + j);
						b = true;
						break;
					}
				}
				assert(b);
			}
		}

		//Si la ligne L touche plus de 2 segments,
		//On crée de nouvelles formes
	}
	return forms;
}

void Form::setConvex(const std::vector<Form>& forms)
{
	convexForms.clear();
	convexForms.insert(convexForms.end(), forms.begin(), forms.end());
}

const std::vector<Form>& Form::getConvexForms() const
{
	return convexForms;
}



void Form::updateConvexForms()
{
	convexForms.clear();
	if(isConvex())
	{
		convexForms.push_back((*this));
	}
	else
	{
		triangulate();
	}
}
