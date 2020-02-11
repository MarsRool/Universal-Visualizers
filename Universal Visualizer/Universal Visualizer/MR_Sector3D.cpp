#include "stdafx.h"
#include "MR_Sector3D.h"

MR::Geometry::Sector3D::Sector3D(const MR::Model::Face & face, const Point3DCartesian &centerSphere)
{
	std::list<MR::Geometry::Point3DCartesian*> points;
	face.getPointsPath(points);
	setFromPointsPath(points, centerSphere);
	simplify();
	if (!check())
		throw std::exception("Wrong Sector3D");
}

MR::Geometry::Sector3D::Sector3D(const Sector3D &other)
{
	for (Angle3D a : other.angles)
		angles.push_back(Angle3D(a));
}

bool MR::Geometry::Sector3D::isSectorIntersect(const Sector3D & sec) const
{
	return false;
}

bool MR::Geometry::Sector3D::isSectorTangential(const Sector3D & sec) const
{
	return false;
}

MR::Geometry::Sector3D * MR::Geometry::Sector3D::integrateSectors(const Sector3D & sec1, const Sector3D & sec2)
{
	return nullptr;
}

void MR::Geometry::Sector3D::integrateSectors(std::list<Sector3D*>& sectors)
{
}

bool MR::Geometry::Sector3D::check()
{
	for (std::list<Angle3D>::const_iterator i = angles.cbegin(); i != angles.cend(); i++)
		for (std::list<Angle3D>::const_iterator j = angles.cbegin(); j != angles.cend(); j++)
		{
			if (i == j)
				continue;
			else
			{
				if (*i == *j)
					return false;
			}
		}
	return true;
}

void MR::Geometry::Sector3D::setFromPointsPath(const std::list<MR::Geometry::Point3DCartesian*>& points, const Point3DCartesian & centerSphere)
{
	//создается из корректной цепи точек, считая, что первая точка соединена с последней
	angles.clear();
	for (Point3DCartesian *p : points)
		angles.push_back(Angle3D(Vector3D(centerSphere, *p)));
}

void MR::Geometry::Sector3D::simplify()
{
	bool foundInInternalWhile = false;
	do
	{
		foundInInternalWhile = false;
		if (angles.size() <= 2)
		{
			angles.clear();
			return;
		}
		//angles.size() > 2
		//три итератора - прошлый, текущий, будущий. Счет идет по текущему[1]
		std::list<Angle3D>::iterator iterAngle[3] = { angles.end()--, angles.begin(), angles.begin()++ };
		while (iterAngle[1] != angles.end())
		{
			if (*(iterAngle[0]) == *(iterAngle[2]))//если будущая точка равна прошлой
			{//то удаляем текущую и прошлую точку, то есть исключаем лишнее ребро
				angles.erase(iterAngle[0]);
				angles.erase(iterAngle[1]);
				foundInInternalWhile = true;
			}
			for (int i = 0; i < 3; i++)//iterate
			{
				iterAngle[i]++;
				if (i != 1)
					if (iterAngle[i] == angles.end())
						iterAngle[i] = angles.begin();
			}
		}
	}
	while (foundInInternalWhile == true);
}
