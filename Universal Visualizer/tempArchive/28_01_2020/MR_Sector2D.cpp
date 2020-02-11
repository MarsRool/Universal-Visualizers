#include "stdafx.h"
#include "MR_Sector2D.h"

MR::Geometry::Sector2D::Sector2D(double angle1, double angle2, double angleMiddle)
{
	this->angle1 = (angle1 < angle2) ? angle1 : angle2;
	this->angle2 = (angle1 > angle2) ? angle1 : angle2;
	correct(angleMiddle);
	if (!check())
		throw std::exception("Wrong Sector2D");
}

bool MR::Geometry::Sector2D::isZero()
{
	return (std::abs(angle1 - angle2) < smallV);
}

bool MR::Geometry::Sector2D::isFullCircle()
{
	return (std::abs(angle2 - angle1 - 2 * PI) < smallV);
}

bool MR::Geometry::Sector2D::isSectorIntersect(const Sector2D & sec) const
{
	if (angle2 > sec.angle1 || sec.angle2 > angle1)
		return true;
	return false;
}

bool MR::Geometry::Sector2D::compareSectors(const Sector2D * a, const Sector2D * b)
{
	if (a != nullptr && b != nullptr)
		return (a->angle1 < b->angle2);
	return false;
}

MR::Geometry::Sector2D * MR::Geometry::Sector2D::integrateSectors(const Sector2D & sec1, const Sector2D & sec2)
{
	if (sec1.isSectorIntersect(sec2))
	{
		double angle1 = (sec1.angle1 < sec2.angle1) ? sec1.angle1 : sec2.angle1;
		double angle2 = (sec1.angle2 > sec2.angle2) ? sec1.angle2 : sec2.angle2;
		double angleMiddle = (angle1 + angle2) / 2.0;
		return new Sector2D(angle1, angle2, angleMiddle);
	}
	else
		return nullptr;
}

void MR::Geometry::Sector2D::integrateSectors(std::list<Sector2D*>& sectors)
{
	Sector2D* last = *sectors.cbegin(), *dthis, *integrated_t;
	std::list<Sector2D*>::iterator iter = ++sectors.begin(), lastIter = sectors.begin();
	while (iter!=sectors.end())
	{
		dthis = *iter;
		if ((integrated_t = integrateSectors(*last, *dthis)) != nullptr)
		{
			delete dthis;
			delete last;
			sectors.erase(lastIter);
			lastIter = iter = sectors.erase(iter);
			sectors.insert(iter, integrated_t);
			lastIter--;
			last = *lastIter;
			continue;
		}
		last = *iter;
		iter++; lastIter++;
	}
}

void MR::Geometry::Sector2D::sortSectors(std::list<Sector2D*>& sectors)
{
	Sector2D* temp;
	for (std::list<Sector2D*>::iterator s_i = sectors.begin(); s_i != sectors.end(); s_i++)
	{
		for (std::list<Sector2D*>::iterator s_j = sectors.begin(); s_j != sectors.end(); s_j++)
			if (s_i != s_j && compareSectors(*s_i, *s_j))
			{
				temp = *s_j;
				s_j = sectors.erase(s_j);
				s_j = sectors.insert(s_i, temp);
			}
	}
}

void MR::Geometry::Sector2D::correct(double angleMiddle)
{
	if (angle1 > angleMiddle && angle2 > angleMiddle || angle1 < angleMiddle && angle2 < angleMiddle)
	{
		angle2 -= 2 * PI;
		double temp = angle1;
		angle1 = angle2;
		angle2 = temp;
	}
	if (std::abs(angle1) < smallV)
		angle1 = 0;
	if (std::abs(angle2) < smallV)
		angle2 = 0;
}

bool MR::Geometry::Sector2D::check()
{
	if ((angle1 < angle2) && (angle2 >= 0) && (angle2 < 2 * PI + smallV) && ((angle2 - angle1) < 2 * PI + smallV))
		return true;
	return false;
}
