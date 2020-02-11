#include "stdafx.h"
#include "conversions.h"
#include "MR_Face.h"

MR::Model::Face::Face(const std::list<Edge*> &Edges_i)
{
	for (Edge* e : Edges_i)
		if (e != nullptr)
			Edges.push_back(e);

	Geometry::Point3DCartesian *Point1, *Point2;
	for (Edge *e : Edges)
	{
		e->operator++();
		e->getPoints(&Point1, &Point2);
		Points.push_back(Point1);
		Points.push_back(Point2);
	}
	Points.unique(Geometry::equalPoints);

	calculateNormal();
	calculateCenterOfMass();
	//calculateArea();
	if (!check())
		throw exception("Wrong Face");
}

MR::Model::Face::Face(const Face & faceToCopy)
{
	CopyNotUnique(faceToCopy);
	if (!check())
		throw exception("Wrong Face");
}

MR::Model::Face::~Face()
{
	for (Edge *e: Edges)
		e->operator--();
}

bool MR::Model::Face::istEdgesInPlane(const std::list<Edge*> &Edges_i)
{//true- если ребра находятся в одной плоскости
	if (Edges_i.size() <= 2)
		return true;
	else if (Edges_i.size() == 3)
	{
		Geometry::Vector3D vec[3];
		int i = 0;
		for (std::list<Edge*>::const_iterator iter = Edges_i.cbegin(); iter != Edges_i.cend() && i < 3; iter++, i++)
		{
			if (*iter == nullptr)
				return false;
			vec[i] = (*iter)->getVector12();
			vec[i].normalize();
		}
		double result = Geometry::mixedProduct(vec[0], vec[1], vec[2]);
		if (std::abs(result) < smallV)
			return true;
		else
			return false;
	}
	else
	{
		std::list<Edge*>::const_iterator iter = Edges_i.cbegin();
		std::list<Edge*> Edges3;
		Edges3.push_back(*iter); iter++;
		Edges3.push_back(*iter); iter++;
		for (; iter != Edges_i.cend(); iter++)
		{
			if (*iter == nullptr)
				return false;
			Edges3.push_back(*iter);
			if (istEdgesInPlane(Edges3) == false)
				return false;
			Edges3.pop_back();
		}
		return true;
	}
}

void MR::Model::Face::getPointsPath(std::list<MR::Geometry::Point3DCartesian*>& points) const
{
	//face гарантирует попарную связность ребер, но не гарантируют правильную последовательность точек в ребрах
	points.clear();

	MR::Geometry::Point3DCartesian *commonPointI;
	list<MR::Model::Edge*> edgesTemp;
	std::list<MR::Model::Edge*>::const_iterator iter = Edges.cbegin();
	while (iter != Edges.cend())
	{
		edgesTemp.clear();
		edgesTemp.push_back(*iter);
		iter++;
		if (iter == Edges.cend())
			break;
		edgesTemp.push_back(*iter);
		commonPointI = getCommonPointInEdges(edgesTemp);
		if (commonPointI == nullptr)
			throw std::exception("wrong interpretating from face: commonPointI == nullptr!");
		if (points.empty())
		{
			Edge *first = Edges.front();
			MR::Geometry::Point3DCartesian *p1, *p2;
			first->getPoints(&p1, &p2);
			if (*p1 == *commonPointI)
				points.push_back(p2);
			else if (*p2 == *commonPointI)
				points.push_back(p1);
		}
		points.push_back(commonPointI);
	}
}

bool MR::Model::Face::isBoundary()
{
	for (Edge *e : Edges)
		if (e->getCountIncludingInFaces() <= 1)
			return true;
	return false;
}

bool MR::Model::equalFaces(const Face &face_left, const Face &face_right)
{
	if (face_left.Points.size() != face_right.Points.size() ||
		face_left.Edges.size() != face_right.Edges.size())
		return false;//количество точек и ребер должно быть одинаково

	for (Geometry::Point3DCartesian *p : face_left.Points)//каждая точка должна взаимно содержаться в массиве точек
		if (searchPoint(face_right.Points, p) == nullptr)
			return false;
	for (Geometry::Point3DCartesian *p : face_right.Points)
		if (searchPoint(face_left.Points, p) == nullptr)
			return false;

	if ((compareAproximately(face_left.Normal, face_right.Normal) == false &&//сравнение нормалей и проверка их на неравенство nullptr
		compareAproximately(-(face_left.Normal), face_right.Normal) == false))
		return false;

	//сравнение последовательности ребер. последовательность может быть в обе стороны
	int lastDirectIndex = -1; bool direct = true;
	//обход в одну и ту же сторону, то есть если бы ребра соответствовали друг другу, но шли бы со сдвигом
	//0 1 2 3 4  (0) (1)			face_right.Edges
	//    | | |  (|) (|)
	//    0 1 2   3   4		->		Edges
	int lastReverseIndex = -1; bool reverse = true;
	//обход в разные стороны, то есть если бы ребра соответствовали друг другу, но шли бы в противоположные стороны
	//0 1 2 3 4  (0) (1)			face_right.Edges
	//    | | |  (|) (|)
	//    4 3 2   1   0		<-		Edges
	for (std::list<Edge*>::const_iterator iterLeft = face_left.Edges.cbegin(); iterLeft != face_left.Edges.cend(); iterLeft++)
	{
		if (searchEdge(face_right.Edges, *iterLeft) == nullptr)
			return false;
		unsigned int j = 0;
		if (direct)
			for (std::list<Edge*>::const_iterator iterRight = face_left.Edges.cbegin();
				iterRight != face_left.Edges.cend() && j < face_right.Edges.size(); iterRight++, j++)
				if (**iterLeft == **iterRight)
					if (lastDirectIndex == -1)
						lastDirectIndex = j;
					else
					{
						if (j == ((lastDirectIndex + 1) % face_left.Edges.size()))
						{
							lastDirectIndex = j;
						}
						else
							direct = false;
					}

		j = 0;
		if (reverse)
			for (std::list<Edge*>::const_iterator iterRight = face_left.Edges.cbegin();
				iterRight != face_left.Edges.cend() && j < face_right.Edges.size(); iterRight++, j++)
				if (**iterLeft == **iterRight)
					if (lastReverseIndex == -1)
						lastReverseIndex = j;
					else
					{
						if (j == ((face_left.Edges.size() + lastReverseIndex - 1) % face_left.Edges.size()))
						{
							lastReverseIndex = j;
						}
						else
							reverse = false;
					}
	}
	return (direct || reverse);
}

bool MR::Model::Face::operator==(const Face & face_right)
{
	return equalFaces(*this, face_right);
}

MR::Model::Face& MR::Model::Face::operator=(const Face & faceToCopy)
{
	if (&faceToCopy == this)
		return *this;

	CopyNotUnique(faceToCopy);
	if (!check())
		throw exception("Wrong Face");
	return *this;
}

bool MR::Model::Face::check()
{
	if (Edges.size() < 3)
		return false;

	for (Edge *e : Edges)//проверка на корректность элементов.
		if (e == nullptr)//Точки нет смысла проверять на корректность, потому что они получены из Ребер
			return false;//Значит они прошли Point3d::check() и не равны nullptr

	if (istEdgesInPlane(Edges) == false)//проверка на то, чтобы ребра лежали в одной плоскости
		return false;

	//проверка, чтобы все ребра были последовательно связаны. То есть имели по очереди попарно общую точку
	list<Edge*> edgesTemp;
	std::list<Edge*>::const_iterator iter = Edges.cbegin();
	while (iter != Edges.cend())
	{
		edgesTemp.clear();
		edgesTemp.push_back(*iter);
		iter++;
		if (iter == Edges.cend())
			break;
		edgesTemp.push_back(*iter);
		if (getCommonPointInEdges(edgesTemp) == nullptr)
			return false;
	}
	return true;
}

void MR::Model::Face::CopyNotUnique(const Face & faceToCopy)
{
	Normal = faceToCopy.Normal;
	CenterOfMass = faceToCopy.CenterOfMass;
	Area = faceToCopy.Area;
	Flag = faceToCopy.Flag;//true- если уже участвовал в рекурсивном тесте на 3D модель

	for (Edge *e : Edges)
		e->operator--();
	Points.clear();
	Edges.clear();
	for (Geometry::Point3DCartesian *p: faceToCopy.Points)
		Points.push_back(p);
	for (Edge *e: faceToCopy.Edges)
		Edges.push_back(e);
}

void MR::Model::Face::calculateNormal()
{
	if (Edges.size() >= 2)
	{
		Normal = vectorProduct((*Edges.begin())->getVector12(), (*(--Edges.end()))->getVector12());
		Normal.normalize();
	}
}

void MR::Model::Face::calculateCenterOfMass()
{
	double x = 0, y = 0, z = 0;
	for (Geometry::Point3DCartesian *p: Points)
	{
		x += p->x();
		y += p->y();
		z += p->z();
	}
	x /= Points.size();
	y /= Points.size();
	z /= Points.size();
	CenterOfMass.set(x, y, z);
}