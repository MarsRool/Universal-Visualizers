#include "stdafx.h"
#include "MR_Sector2D.h"

MR::Geometry::Sector2D::Sector2D(const Angle2D &angle1, const Angle2D &angle2, const Angle2D &angleMiddle)
{
	this->angle1 = (angle1 < angle2) ? angle1 : angle2;
	this->angle2 = (angle1 > angle2) ? angle1 : angle2;
	correct(angleMiddle);
}

bool MR::Geometry::Sector2D::isZero()
{
	//справа нулевой угол с таким же типом точности, как у любого угла, например 1
	return (angle1 == angle2) && (angle1 < angle2);
}

bool MR::Geometry::Sector2D::isFullCircle()
{
	return ((angle2 - angle1) == Angle2D(MR::Helpers::DoublePreciseApproximate(360, smallV, angle1.getAccuracyType())) ||
			(angle1 == angle2) && (angle1 >= angle2));
}

bool MR::Geometry::Sector2D::isSectorIntersect(const Sector2D & sec) const
{
	MR::Helpers::DoublePreciseApproximate thisAngle1, thisAngle2, secAngle1, secAngle2;
	AngleToDegreeDiapazon(thisAngle1, thisAngle2);
	AngleToDegreeDiapazon(secAngle1, secAngle2);
	if (thisAngle2 > secAngle1 || secAngle2 > thisAngle1)
		return true;
	return false;
}

bool MR::Geometry::Sector2D::isSectorTangential(const Sector2D & sec) const
{
	if (angle1 == sec.angle1 || sec.angle2 == angle2 || angle2 == sec.angle1 || sec.angle2 == angle1)
		return true;
	return false;
}

MR::Geometry::Sector2D * MR::Geometry::Sector2D::integrateSectors(const Sector2D & sec1, const Sector2D & sec2)
{
	if (sec1.isSectorAdjacent(sec2))
	{
		MR::Helpers::DoublePreciseApproximate sec1Angle1, sec1Angle2, sec2Angle1, sec2Angle2;
		sec1.AngleToDegreeDiapazon(sec1Angle1, sec1Angle2);
		sec2.AngleToDegreeDiapazon(sec2Angle1, sec2Angle2);
		int i = 3;
		while (sec1Angle2 > sec2Angle1 && i > 0)
		{
			sec2Angle1 = sec2Angle1 + 360.0;
			sec2Angle2 = sec2Angle2 + 360.0;
			i--;
		}
		i = 3;
		while (sec2Angle2 > sec1Angle1 && i > 0)
		{
			sec1Angle1 = sec1Angle1 + 360.0;
			sec1Angle2 = sec1Angle2 + 360.0;
			i--;
		}
		if (sec1Angle2 == sec2Angle1 || sec2Angle2 == sec1Angle1)
		{
			MR::Helpers::DoublePreciseApproximate angle1 = (sec1Angle1 < sec2Angle1) ? sec1Angle1 : sec2Angle1;
			MR::Helpers::DoublePreciseApproximate angle2 = (sec1Angle2 > sec2Angle2) ? sec1Angle2 : sec2Angle2;
			MR::Helpers::DoublePreciseApproximate angleMiddle = (angle1 + angle2) / 2.0;
			return new Sector2D(Angle2D(angle1), Angle2D(angle2), Angle2D(angleMiddle));
		}
		else
			return nullptr;
	}
	else
		return nullptr;
}

void MR::Geometry::Sector2D::integrateSectors(std::list<Sector2D*>& sectors)
{
	if (sectors.size() > 0)
	{
		Sector2D *result = *sectors.cbegin(), *temp;
		sectors.pop_front();
		while (sectors.size() > 0)
		{
			bool foundInFor = false;
			for (std::list<Sector2D*>::iterator iter = sectors.begin(); iter != sectors.end(); iter++)
			{
				temp = result->integrateSectors(*result, **iter);
				if (temp != nullptr)
				{
					delete result;
					delete *iter;
					result = temp;
					foundInFor = true;
					iter = sectors.erase(iter);
					if (iter == sectors.end())
						break;
					//при этом произойдет перескакивание через один элемент, но об этом можно не париться,
					//потому что мы в while и мы пройдемся в итоге по всем элементам,
					//пока объединение не закончится либо элементы не будут объединяться
				}
			}
			if (foundInFor == false)
				break;
		}
		sectors.push_back(result);
	}
}

void MR::Geometry::Sector2D::AngleToDegreeDiapazon(MR::Helpers::DoublePreciseApproximate & angle1Out, MR::Helpers::DoublePreciseApproximate & angle2Out) const
{
	angle1Out = MR::Helpers::DoublePreciseApproximate(this->angle1.getAngleDegree());
	angle2Out = MR::Helpers::DoublePreciseApproximate(this->angle2.getAngleDegree());
	if (angle1Out > angle2Out)
		angle1Out = angle1Out - 360.0;
}

void MR::Geometry::Sector2D::DegreeDiapazonToAngle(MR::Helpers::DoublePreciseApproximate angle1In, MR::Helpers::DoublePreciseApproximate angle2In)
{
	angle1.setAngleDegree(angle1In());
	angle2.setAngleDegree(angle2In());
}

void MR::Geometry::Sector2D::correct(const Angle2D &angleMiddle)
{
	if (angle1 > angleMiddle && angle2 > angleMiddle || angle1 < angleMiddle && angle2 < angleMiddle)
	{
		Angle2D temp = angle1;
		angle1 = angle2;
		angle2 = temp;
	}
}
