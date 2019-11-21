#include "stdafx.h"
#include "MR_CircleTest.h"

MR::Geometry::CircleTest::CircleTest(const Model::Face & face, const Geometry::Point3D & point, double radius) : TestFace(face), TestPoint(point)
{
	this->Radius = radius;
	isOk = check();
	test();
	if (!isOk)
		throw std::exception("Wrong CircleTest");
}

MR::Geometry::CircleTest::~CircleTest()
{
	for (Sector2D *s: Sectors)
		delete s;
}

bool MR::Geometry::CircleTest::check()
{
	int i = 10;
	while (isCircleIntersectFace() == true && i > 0)//корректировка: если окружность пересекает грань,
	{
		Radius /= 2;//то уменьшить радиус в два раза
		i--;
	}
	if (isCircleIntersectFace() == true)
		return false;
	if (!isPointInFacePlane())
		return false;
	return true;
}

bool MR::Geometry::CircleTest::isCircleIntersectFace() const
{
	std::list<Model::Edge*> tempEdges;
	TestFace.getEdges(tempEdges);
	Point3D *point1, *point2;
	for (Model::Edge *e : tempEdges)
	{
		e->getPoints(&point1, &point2);
		if (Line3D(*point1, *point2).distance(TestPoint) < Radius)
			return true;
	}
	return false;
}

bool MR::Geometry::CircleTest::isPointInFacePlane() const
{
	std::list<Point3D*> tempList;
	TestFace.getPoints(tempList);
	Plane3D tempPlane(TestFace.getNormal(), **tempList.cbegin());
	return (tempPlane.isInPlane(TestPoint));
}

void MR::Geometry::CircleTest::test()
{
	bool isOk_t;//корректность текущего полученного угла в базисе
	std::list<Model::Edge*> Edges;//все ребра тестируемой грани
	TestFace.getEdges(Edges);
	Point3D *point1, *point2, pointMiddle;//точки текущего ребра
	(*Edges.cbegin())->getPoints(&point1, &point2);
	Basis2D Basis = Basis2D(Vector3D(TestPoint, *point1), Vector3D(TestPoint, *point2));//устанавливаем базис
	double angle1, angle2, angleMiddle;//углы радиус-векторов точек текущего ребра
	for (Model::Edge *e : Edges)
	{
		//получаем углы для текущего ребра angle1, angle2
		e->getPoints(&point1, &point2);
		angle1 = Basis.getAngleRad_0To2Pi(Vector3D(TestPoint, *point1), isOk_t);
		isOk = isOk && isOk_t;
		if (!isOk)
			return;
		angle2 = Basis.getAngleRad_0To2Pi(Vector3D(TestPoint, *point2), isOk_t);
		isOk = isOk && isOk_t;
		if (!isOk)
			return;
		pointMiddle = point1->getMiddlePoint(*point2);
		angleMiddle = Basis.getAngleRad_0To2Pi(Vector3D(TestPoint, pointMiddle), isOk_t);
		isOk = isOk && isOk_t;
		if (!isOk)
			return;

		Sectors.push_back(new Sector2D(angle1, angle2, angleMiddle));
	}
	Sector2D::sortSectors(Sectors);
	Sector2D::integrateSectors(Sectors);
	for (Sector2D *s : Sectors)
		if (s->isFullCircle() == true)
			IsInside = true;
}
