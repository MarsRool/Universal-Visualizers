#include "stdafx.h"
#include "MR_SphereTest.h"

MR::Geometry::SphereTest::SphereTest(const MR::Model::Model &model, const Geometry::Point3D &point, double radius) : TestModel(model, false), TestPoint(point)
{
	this->Radius = radius;
	if (!check())
		throw std::exception("Wrong SphereTest");
}

bool MR::Geometry::SphereTest::check()
{
	return (!isSphereIntersectModel());
}

bool MR::Geometry::SphereTest::isSphereIntersectModel()
{
	return false;
}
