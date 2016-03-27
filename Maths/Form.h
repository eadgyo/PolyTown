/*
 * Form.h
 *
 *  Created on: Feb 27, 2016
 *      Author: ronan-h
 */

#ifndef FORM_H_
#define FORM_H_

class sRectangle;

#include <iterator>
#include <vector>
#include <deque>
#include "Matrix4.h"
#include "Vector3D.h"
#include <set>
#include "Edge.h"
#include "PointType.h"
#include <map>
#include "AxesSat.h"


class Form
{
public:
	Form(int size);
	Form();
	Form(const Form& form);
	Form(float omega, float scale, bool flipH, bool flipV, float surface, const Vector3D& vec);
	~Form();

	Form clone() const;
	void resetTransformations();
	void clearTransformations();
	void setInit(Form form);

	// Getter
	inline virtual unsigned getType() { return 0; };
	const Matrix4& getOrientation() const;
	Matrix4 getOrientationInverse() const;
	inline float getOmega() const { return omega; };
	inline float getScale() const { return scale; };
	inline bool getFlipH() const { return flipH; };
	inline bool getFlipV() const { return flipV; };
	Vector3D getCentroidWorld() const;
	Vector3D getCentroidLocal() const;
	inline unsigned size() const { return points.size(); };

	float getLocalX() const;
	float getLocalY() const;
	const Vector3D& getLocal() const;
	float getLocalX(unsigned n) const;
	float getLocalY(unsigned n) const;
	Vector3D getLocal(unsigned n) const;
	float getX() const;
	float getY() const;
	float getX(unsigned n) const;
	float getY(unsigned n) const;
	Vector3D get() const;
	Vector3D get(unsigned n) const;
	float getCenterX() const;
	float getCenterY() const;
	Vector3D getCenter() const;
	int* getXIntArray() const;
	int* getYIntArray() const;
	float getMinX() const;
	float getMinY() const;
	float getMaxX() const;
	float getMaxY() const;
	inline float getSurface() const { return surface; };

	std::vector<Vector3D> getVectorsSatLocal() const;
	Vector3D* getVectorsLocal() const;
	Vector3D* getVectorsWorld() const;
	Vector3D* getPointsLocal() const;
	Vector3D* getPointsLocalAsVec() const;
	Vector3D* getPointsWorld() const;
	Vector3D transform(const Vector3D& vertex, const Vector3D& p, const Vector3D& v, const Matrix4& orientation, float& t) const;
	Vector3D handleEdgePoint(const Vector3D& PA, const Vector3D& PB, const Vector3D& PB2) const;
	sRectangle getBound() const;
	sRectangle getBoundMax() const;
	Vector3D& operator[](int i);
	void updateCenter();
	void updateOrientation();

	// Setter
	void setCenter(const Vector3D& center);
	void setPoint(unsigned n, const Vector3D& p);
	void addPointFree(const Vector3D& p);
	void addPoint(const Vector3D& p);
	void removePoint(unsigned i);
	void removeLast();

	// Transformations
	Vector3D transformLocalToWorld(const Vector3D& point) const;
	Vector3D transformWorldToLocal(const Vector3D& point) const;
	void translate(const Vector3D& v);
	void translateX(float x);
	void translateY(float y);
	void rotateDegrees(float omega, const Vector3D& center);
	void rotateRadians(float omega, const Vector3D& center);
	void scaleF(float factor, const Vector3D& center);
	void flipHF(const Vector3D& center);
	void flipVF(const Vector3D& center);
	void flipHFree(const Vector3D& center);
	void flipVFree(const Vector3D& center);
	void setPos(const Vector3D& v);
	void setRadians(float omega);
	void setScale(float scale);
	void setFlipH(bool flipH);
	void setFlipV(bool flipV);
	void calculateSurface();

	// Collisions detection
	virtual bool isColliding(const Vector3D& pos);
	virtual bool isColliding(Form& form);
	virtual bool isColliding(Form& form, Vector3D& push, float& t);

	// Pas à utiliser directement
	bool collisionSat(Form& form);
	bool collisionSat(Form& form, const Vector3D& VA,
			const Vector3D& VB, Vector3D& push, float& t);
	bool collisionSatFree(const Form& B, const Vector3D& VA, const Vector3D& VB);
	bool intervalIntersectionFree(const Vector3D& axis, const Vector3D* pointsA, unsigned sizeA,
			const Vector3D* pointsB, unsigned sizeB, const Vector3D& relPos, const Vector3D& relVel, const Matrix4& orientI) const;

	bool collisionSatA(const Form& B, const Vector3D& VA, const Vector3D& VB, Vector3D& push, float& t) const;

	bool intervalIntersection(const Vector3D& axis, const Vector3D* pointsA, unsigned sizeA,
			const Vector3D* pointsB, unsigned sizeB, const Vector3D& relPos, const Vector3D& relVel, const Matrix4& orientI,
			AxesSat& axes, float& t) const;

	Vector3D getInterval(const Vector3D& axis, const Vector3D* points, unsigned size) const;
	void getPushVector(AxesSat& axesSat, Vector3D& push, float& t) const;

	std::vector<Form> splitUnsecured(int p0, int p1, std::vector< std::set<int> >& bst, std::vector<std::vector<int> >& vectPos, int actual);
	
	// Convex
	bool isConvex() const;
	int getClockwise() const;
	std::vector<Edge*> getEdgesLocal() const;

	// Triangulate
	void triangulate();

	// Make Monotone
	std::vector<Form> makeMonotone();
	void sortPointsY(std::vector<Edge*>& edges, int* v, unsigned sizeI);
	void sortPointsY(std::vector<Edge*>& edges, std::vector<int>& v);
	void determineType(int pos, std::vector<Edge*>& edges, std::map<Edge*, PointType*>& helpers, std::map<float, std::vector<Edge*> >& I);
	Edge* getLeftEdge(int pos, std::vector<Edge*>& edges, std::map<float, std::vector<Edge*> >& I);
	Edge* getLeftEdge(PointType& p, std::vector<Edge*>& lEdges);
	std::vector<Form> transformEdges(std::vector<Edge*>& edges);
	void handleStartVertex(int pos, std::vector<Edge*>& edges, std::map<Edge*, PointType*>& helpers);
	void handleSplitVertex(int pos, std::vector<Edge*>& edges, std::map<Edge*, PointType*>& helpers, std::map<float, std::vector<Edge*> >& I);
	void handleMergeVertex(int pos, std::vector<Edge*>& edges, std::map<Edge*, PointType*>& helpers,  std::map<float, std::vector<Edge*> >& I);
	void handleEndVertex(int pos, std::vector<Edge*>& edges, std::map<Edge*, PointType*>& helpers);
	void handleRegularVertex(int pos, std::vector<Edge*>& edges, std::map<Edge*, PointType*>& helpers,  std::map<float, std::vector<Edge*> >& I);
	int numberLeftEdges(int pos, std::vector<Edge*>& edges, std::map<float, std::vector<Edge*> >& I);
	int numberLeftEdges(PointType& p, std::vector<Edge*>& edges);
	std::vector<Form> triangulateMonotone();
	void createChains(int* v, int sizeV, std::vector<Edge*>& edges, std::set<PointType*>& lChain);
	std::vector<Form> getTriangulation();

	void setConvex(const std::vector<Form>& forms);
	const std::vector<Form>& getConvexForms() const;
	inline const int getConvexFormsSize() const { return convexForms.size(); };
	void updateConvexForms();

protected:
	Matrix4 orientation;
	float scale;
	float omega;
	bool flipH;
	bool flipV;

	float surface;
	std::vector<Vector3D> points;
	std::vector<Form> convexForms;
};

#endif /* FORM_H_ */
