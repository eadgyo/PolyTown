/*
 * Form.h
 *
 *  Created on: Feb 27, 2016
 *      Author: ronan-h
 */

#ifndef FORM_H_
#define FORM_H_

#include <vector>
#include "Matrix4.h"
#include "Vector3D.h"
#include <set>
#include "Edge.h"
#include "PointType.h"
#include <map>

class Form
{
	class AxesSat
	{
		std::vector<Vector3D> axes;
		std::vector<float> tAxes;
		std::vector<Vector3D> axesT;
		std::vector<float> tAxesT;
	};

public:
	Form(int size);
	Form();
	Form(const Form& form);
	Form(float omega, float scale, bool flipH, bool flipV, float surface, const Vector3D& vec);
	virtual ~Form();

	Form clone() const;
	void resetTransformations();
	void clearTransformations();
	void setInit(Form form);

	// Getter
	const Matrix4& getOrientation() const;
	Matrix4 getOrientationInverse() const;
	inline float getOmega() const { return omega; };
	inline float getScale() const { return scale; };
	inline bool getFlipH() const { return flipH; };
	inline bool getFlipV() const { return flipV; };
	Vector3D getCentroidWorld() const;
	Vector3D getCentroidLocal() const;
	inline int size() const { return points.size(); };

	float getLocalX() const;
	float getLocalY() const;
	const Vector3D& getLocal() const;
	float getLocalX(int n) const;
	float getLocalY(int n) const;
	Vector3D getLocal(int n) const;
	float getX() const;
	float getY() const;
	float getX(int n) const;
	float getY(int n) const;
	Vector3D get() const;
	Vector3D get(int n) const;
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

	Vector3D* getVectorsSatLocal() const;
	Vector3D* getVectorsLocal() const;
	Vector3D* getVectorsWorld() const;
	Vector3D* getPointsLocal() const;
	Vector3D* getPointsWorld() const;
	Vector3D transform(const Vector3D& vertex, const Vector3D& p, const Vector3D& v, const Matrix4& orientation, float& t) const;
	Vector3D handleEdgePoint(const Vector3D& PA, const Vector3D& PB, const Vector3D& PB2) const;

	Vector3D& operator[](int i);
	void updateCenter();
	void updateOrientation();

	// Setter
	void setCenter(const Vector3D& center);
	void setPoint(int n, const Vector3D& p);
	void addPointFree(const Vector3D& p);
	void addPoint(const Vector3D& p);
	void removePoint(int i);
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
	void setPos(const Vector3D& v);
	void setRadians(float omega);
	void setScale(float scale);
	void setFlipH(bool flipH);
	void setFlipV(bool flipV);
	void calculateSurface();

	// Collisions detection
	bool collisionSat(const Form& form) const;
	bool collisionSat(const Form& form, const Vector3D& VA,
			const Vector3D& VB, const Vector3D& push, float& t) const;
	bool collisionSatFree(const Form& B, const Vector3D& VA, const Vector3D& VB);
	bool intervalIntersectionFree(const Vector3D& axis, const Vector3D* pointsA, int sizeA,
			const Vector3D* pointsB, const Vector3D& relPos, const Vector3D& relVel, const Matrix4& orientI);

	bool collisionSatA(const Form& B, const Vector3D& VA, const Vector3D& VB, const Vector3D& push, float& t);
	bool intervalIntersection(const Vector3D& axis, const Vector3D* pointsA, int sizeA,
			const Vector3D* pointsB, const Vector3D& relPos, const Vector3D& relVel, const Matrix4& orientI,
			AxesSat& axes, float& t);

	bool getInterval(const Vector3D& axis, const Vector3D* points, int size);
	void getPushVector(AxesSat& axesSat, Vector3D& push, float& t);


	// Convex
	bool isConvex() const;
	int getClockwise() const;
	Edge* getEdgesLocal() const;

	// Triangulate
	void triangulate();

	// Make Monotone
	std::vector<Form> makeMonotone();
	void sortPointsY(Edge* edges, int sizeE, int* v, int sizeI);
	void determineType(int pos, Edge* edges, int sizeE, std::map<Edge, PointType>& helpers, std::map<float, std::vector<Edge>>& I);
	Edge getLeftEdge(int pos, Edge* edges, int sizeE, std::map<float, std::vector<Edge>>& I);
	Edge getLeftEdge(PointType& p, Edge* lEdges, int sizeE);
	Form* transformEdges(Edge* edges, int sizeE);
	void handleStartVertex(int pos, Edge* edges, int sizeE, std::map<Edge, PointType>& helpers);
	void handleSplitVertex(int pos, Edge* edges, int sizeE, std::map<Edge, PointType>& helpers, std::map<float, std::vector<Edge>>& I);
	void handleMergeVertex(int pos, Edge* edges, int sizeE, std::map<Edge, PointType>& helpers,  std::map<float, std::vector<Edge>>& I);
	void handleRegularVertex(int pos, Edge* edges, int sizeE, std::map<Edge, PointType>& helpers,  std::map<float, std::vector<Edge>>& I);
	int numberLeftEdges(int pos, Edge* edges, int sizeE, std::map<float, std::vector<Edge>>& I);
	int numberLeftEdges(PointType& p, Edge* edges, int sizeE);
	std::vector<Form> triangulateMonotone();
	void createChains(int* v, int size, Edge* edges, int sizeE, std::set<PointType> lChain);
	std::vector<Form> getTriangulation();

	void setConvex(const std::vector<Form>& forms);
	const std::vector<Form>& getConvexForms() const;
	inline const int getConvexFormsSize() const { return convexForms.size(); };
	void updateConvexForms();

private:

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
