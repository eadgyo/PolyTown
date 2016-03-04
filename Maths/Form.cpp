
#include "Form.h"

Form::Form():
	Form(0, 1.0f, false, false, 0, Vector3D(true))
{

}

Form::~Form()
{
}

Form::Form(int size):
		Form(0, 1.0f, false, false, 0, Vector3D(true))
{
	points.resize(size);
}

Form::Form(float omega, float scale, bool flipH, bool flipV, float surface, const Vector3D& vec):
		omega(omega), scale(scale), flipH(flipH), flipV(flipV), surface(surface)
{
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
	for(int i=0; i<form.size(); i++)
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
		return new Vector3D();
	else if(points.size() == 1)
		return getLocal();
	else if(points.size() == 2)
	{
		std::vector<Vector3D> points = getPointsLocal();
		return new Vector3D((points.at(0).x + points.at(1).x)/2,
							(points.at(0).y + points.at(1).y)/2);
	}
	Vector3D center(true);
	float x0 = 0, y0 = 0, x1 = 0, y1 = 0, signedArea = 0, a = 0;
	std::vector<Vector3D> points = getPointsLocal();
	for(int j=points.size()-1, i=0; i<points.size(); j=i, i++)
	{
		x0 = points.at(i).x;
		y0 = points.at(i).y;
		x1 = points.at(j).x;
		y1 = points.at(j).y;
		a = x0*y1 - x1*y0;
		signedArea += a;
		center.x += (x0 + x1)*a;
		center.y += (y0 + y1)*a;
	}

	signedArea *= 0.5;
	center.x /= (6.0f*signedArea);
	center.y /= (6.0f*signedArea);

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
	if(size() > 0)
		return points.at(0);
	return Vector3D(true);
}

float Form::getLocalX(int n) const
{
	assert(n < size());
	return points.at(n).getX();
}

float Form::getLocalY(int n) const
{
	assert(n < size());
	return points.at(n).getY();
}

Vector3D Form::getLocal(int n) const
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

float Form::getX(int n) const
{
	assert(n < size());
	return orientation.multiplyX(points.at(n));
}

float Form::getY(int n) const
{
	assert(n < size());
	return orientation.multiplyY(points.at(n));
}

Vector3D Form::get() const
{
	return get(0);
}

Vector3D Form::get(int n) const
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
	int* l_X = (int*) malloc(size()*sizeof(int));
	for(int i=0; i<points.size(); i++)
	{
		l_X[i] = (int) getX(i);
	}
	return l_X;
}

int* Form::getYIntArray() const
{
	int* l_Y = (int*) malloc(size()*sizeof(int));
	for(int i=0; i<points.size(); i++)
	{
		l_Y[i] = (int) getY(i);
	}
	return l_Y;
}

float Form::getMinX() const
{
	float xMin = getX(0);
	for(int i=1; i<points.size(); i++)
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
	for(int i=1; i<points.size(); i++)
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
	for(int i=1; i<points.size(); i++)
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
	for(int i=1; i<points.size(); i++)
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
	for(int j=points.size()-1, i=0; i<points.size(); j=i, i++)
	{
		Vector3D v(points.at(j), points.at(i));
		l_vectors.push_back(v.getPerpendicular2D());
	}

	//On enleve les vectors colinéaires
	for(int i=0; i<l_vectors.size()-1; i++)
	{
		//Si on est en dessous de 2 vecteurs ca sert à rien de continuer,
		//On sait que ces 2 vecteurs (ou moins) ne sont pas colinéaires
		if(l_vectors.size() < 3)
			break;

		for(int j=i+1; j<l_vectors.size(); j++)
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
	Vector3D* l_vectors = (Vector3D*) malloc(size()*sizeof(Vector3D));
	for(int j=size()-1, i=0; i<size(); j=i, i++)
	{
		new (l_vectors[i]) Vector3D(i, Vector3D(points.at(j), points.at(i)));
	}
	return l_vectors;
}

Vector3D* Form::getVectorsWorld() const
{
	Vector3D* l_vectors = getVectorsLocal();
	for(int i=0; i<size(); i++)
	{
		l_vectors[i].set(orientation*l_vectors[i]);
	}
	return l_vectors;
}

Vector3D* Form::getPointsLocal() const
{
	return points.data();
}

Vector3D* Form::getPointsWorld() const
{
	if(orientation.getX() == 0 && orientation.getY() == 0 && omega == 0 && scale == 1.0f && !flipV && !flipH)
		return getPointsLocal();
	Vector3D* l_vectors = (Vector3D*) malloc(size()*sizeof(Vector3D));
	for(int i=0; i<size(); i++)
	{
		new (l_vectors[i]) Vector3D(get(i));
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

Vector3D& Form::operator [](int i)
{
	return points[i];
}

void Form::updateCenter()
{
	Vector3D newCenter = getCentroidWorld();
	// Cas NaN, lorsque un flaot est NaN la comparaison avec elle même est toujours fausse
	if(newCenter.x != newCenter.x || newCenter.y != newCenter.y)
	{
		calculateSurface();
		return;
	}

	Matrix4 lastCoor = orientation; //this.center
	Matrix4 newCoor = orientation.copy();
	newCoor.setPos(newCenter);
	Matrix4 inverse = newCoor.getInverse();
	Matrix4 result = inverse*(lastCoor);


	for(int i=0; i<points.size(); i++)
	{
		/*
		result équivaut à ces opérations

		Vector2D p = points.get(i);
		Vector2D pW = orientation.multiply(p);
		Vector2D pN = inverse.multiply(pW);

		*/
		Vector3D vec = result*points.at(i);
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

void Form::setPoint(int n, const Vector3D& p)
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

void Form::removePoint(int i)
{
	assert(i < size() && i > 0);
	Vector3D p = points.erase(points.begin() + i);
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
	orientation.flipH(center);
}

void Form::flipVF(const Vector3D& center)
{
	flipV = !flipV;
	orientation.flipV(center);
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
	for(int i=points.size()-2, i1=points.size()-1, i2=0; i2<points.size(); i=i1, i1=i2, i2++)
	{
		surface += points.at(i1).x()*(points.at(i2).y()-points.at(i).y()) + points.at(i1).y()*(points.at(i).x()-points.at(i2).x());
	}
	surface /= 2;
}

bool Form::collisionSat(const Form& form) const
{
}

bool Form::collisionSat(const Form& form, const Vector3D& VA,
		const Vector3D& VB, const Vector3D& push, float& t) const
{
}

bool Form::collisionSatFree(const Form& B, const Vector3D& VA,
		const Vector3D& VB)
{
}

bool Form::intervalIntersectionFree(const Vector3D& axis,
		const Vector3D* pointsA, int sizeA, const Vector3D* pointsB,
		const Vector3D& relPos, const Vector3D& relVel, const Matrix4& orientI)
{
}

bool Form::collisionSatA(const Form& B, const Vector3D& VA, const Vector3D& VB,
		const Vector3D& push, float& t)
{
}

bool Form::intervalIntersection(const Vector3D& axis, const Vector3D* pointsA,
		int sizeA, const Vector3D* pointsB, const Vector3D& relPos,
		const Vector3D& relVel, const Matrix4& orientI, AxesSat& axes, float& t)
{
}

bool Form::getInterval(const Vector3D& axis, const Vector3D* points, int size)
{
}

void Form::getPushVector(AxesSat& axesSat, Vector3D& push, float& t)
{
}

bool Form::isConvex() const
{
}

int Form::getClockwise() const
{
}

Edge* Form::getEdgesLocal() const
{
}

void Form::triangulate()
{
}

std::vector<Form> Form::makeMonotone()
{
}

void Form::sortPointsY(Edge* edges, int sizeE, int* v, int sizeI)
{
}

void Form::determineType(int pos, Edge* edges, int sizeE,
		std::map<Edge, PointType>& helpers,
		std::map<float, std::vector<Edge> >& I)
{
}

Edge Form::getLeftEdge(int pos, Edge* edges, int sizeE,
		std::map<float, std::vector<Edge> >& I)
{
}

Edge Form::getLeftEdge(PointType& p, Edge* lEdges, int sizeE)
{
}

Form* Form::transformEdges(Edge* edges, int sizeE)
{
}

void Form::handleStartVertex(int pos, Edge* edges, int sizeE,
		std::map<Edge, PointType>& helpers)
{
}

void Form::handleSplitVertex(int pos, Edge* edges, int sizeE,
		std::map<Edge, PointType>& helpers,
		std::map<float, std::vector<Edge> >& I)
{
}

void Form::handleMergeVertex(int pos, Edge* edges, int sizeE,
		std::map<Edge, PointType>& helpers,
		std::map<float, std::vector<Edge> >& I)
{
}

void Form::handleRegularVertex(int pos, Edge* edges, int sizeE,
		std::map<Edge, PointType>& helpers,
		std::map<float, std::vector<Edge> >& I)
{
}

int Form::numberLeftEdges(int pos, Edge* edges, int sizeE,
		std::map<float, std::vector<Edge> >& I)
{
}

int Form::numberLeftEdges(PointType& p, Edge* edges, int sizeE)
{
}

std::vector<Form> Form::triangulateMonotone()
{
}

void Form::createChains(int* v, int size, Edge* edges, int sizeE,
		std::set<PointType> lChain)
{
}

std::vector<Form> Form::getTriangulation()
{
}

void Form::setConvex(const std::vector<Form>& forms)
{
}

const std::vector<Form>& Form::getConvexForms() const
{
}

void Form::updateConvexForms()
{
}
