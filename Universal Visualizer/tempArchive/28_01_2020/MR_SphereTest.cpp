#include "stdafx.h"
#include "MR_SphereTest.h"

MR::Geometry::SphereTest::SphereTest(const MR::Model::Model &model, const Geometry::Point3D &point, double radius) : TestModel(model, false), TestPoint(point)
{
	this->Radius = radius;
	isOk = check();
	test();
	if (!isOk)
		throw std::exception("Wrong SphereTest");
}

bool MR::Geometry::SphereTest::check()
{
	int i = 10;
	while (isSphereIntersectModel() == true && i > 0)//�������������: ���� ���������� ���������� �����,
	{
		Radius /= 2;//�� ��������� ������ � ��� ����
		i--;
	}
	if (isSphereIntersectModel() == true)
		return false;
	return true;
}

bool MR::Geometry::SphereTest::isSphereIntersectModel()
{
	std::list<Model::Object*> tempObjects;
	std::list<Model::Face*> tempFaces;
	TestModel.getObjects(tempObjects);
	for (Model::Object *o : tempObjects)
	{
		o->getFaces(tempFaces);
		for (Model::Face *f : tempFaces)
			if (Plane3D(*f).distance(TestPoint) < Radius)
				return true;
	}
	return false;
}

void MR::Geometry::SphereTest::test()
{
	bool isOk_t;//������������ �������� ����������� ���� � ������
	std::list<Model::Object*> tempObjects;//������� ����������� ������
	std::list<Model::Face*> tempFaces;//����� ������� ����������� ������
	TestModel.getObjects(tempObjects);
	for (Model::Object *o : tempObjects)
	{
		o->getFaces(tempFaces);
		for (Model::Face *f : tempFaces)
		{
			....
		}
	}
	////////////////////////////////////////
	bool isOk_t;//������������ �������� ����������� ���� � ������
	std::list<Model::Edge*> Edges;//��� ����� ����������� �����
	TestFace.getEdges(Edges);
	Point3D *point1, *point2, pointMiddle;//����� �������� �����
	(*Edges.cbegin())->getPoints(&point1, &point2);
	Basis2D Basis = Basis2D(Vector3D(TestPoint, *point1), Vector3D(TestPoint, *point2));//������������� �����
	double angle1, angle2, angleMiddle;//���� ������-�������� ����� �������� �����
	for (Model::Edge *e : Edges)
	{
		//�������� ���� ��� �������� ����� angle1, angle2
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
