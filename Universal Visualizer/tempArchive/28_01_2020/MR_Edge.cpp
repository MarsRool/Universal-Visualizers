#include "stdafx.h"
#include "conversions.h"
#include "MR_Edge.h"

MR::Model::Edge::Edge(const Geometry::Point3D *Point1_i, const Geometry::Point3D *Point2_i, short int count)
{
	CopyNotUnique(Point1_i, Point2_i, count);
	if (!check())
		throw exception("Wrong Edge");
}

MR::Model::Edge::Edge(const Edge & edgeToCopy)
{
	CopyNotUnique(edgeToCopy.Point1, edgeToCopy.Point2, edgeToCopy.CountIncludingInFaces);
	if (!check())
		throw exception("Wrong Edge");
}

MR::Model::Edge::~Edge()
{
	Point1->operator--();
	Point2->operator--();
}

bool MR::Model::Edge::existing() const
{
	if (CountIncludingInFaces > 0)
		return true;
	return false;
}

void MR::Model::Edge::getPoints(Geometry::Point3D ** Point1_i, Geometry::Point3D ** Point2_i)
{
	if (Point1_i != nullptr && Point2_i != nullptr)
	{
		*Point1_i = Point1;
		*Point2_i = Point2;
	}
}

MR::Geometry::Vector3D MR::Model::Edge::getVector12() const
{
	return Geometry::Vector3D(*Point1, *Point2);
}

bool MR::Model::equalEdges(const Edge *edge_left, const Edge *edge_right)
{
	return ((((*edge_left->Point1 == *edge_right->Point1) && (*edge_left->Point2 == *edge_right->Point2))) ||
		(((*edge_left->Point1 == *edge_right->Point2) && (*edge_left->Point2 == *edge_right->Point1))));
}

const bool MR::Model::Edge::operator==(const Edge & edge_right) const
{//сравнение по значению
	return equalEdges(this, &edge_right);
}

MR::Model::Edge& MR::Model::Edge::operator++()
{
	this->CountIncludingInFaces++;
	return *this;
}

MR::Model::Edge& MR::Model::Edge::operator--()
{
	if (CountIncludingInFaces > 0)
		this->CountIncludingInFaces--;
	return *this;
}

MR::Model::Edge& MR::Model::Edge::operator+=(short int added)
{
	this->CountIncludingInFaces += added;
	return *this;
}

MR::Model::Edge& MR::Model::Edge::operator=(const Edge & edge_right)
{
	if (&edge_right == this)
		return *this;
	
	CopyNotUnique(edge_right.Point1, edge_right.Point2, edge_right.CountIncludingInFaces);
	if (!check())
		throw exception("Wrong Edge");
	return *this;
}

bool MR::Model::Edge::check() const
{
	if (Point1 == nullptr || Point2 == nullptr)
		return false;
	return true;
}

void MR::Model::Edge::CopyNotUnique(const Geometry::Point3D *Point1_i, const Geometry::Point3D *Point2_i, short int count)
{
	if (Point1 != nullptr)
		Point1->operator--();
	if (Point2 != nullptr)
		Point2->operator--();
	Point1 = const_cast<Geometry::Point3D*>(Point1_i);
	Point2 = const_cast<Geometry::Point3D*>(Point2_i);
	Point1->operator++();
	Point2->operator++();
	CountIncludingInFaces = count;
}

MR::Model::Edge * MR::Model::searchEdge(const std::list<Edge*> &Edges, const Edge *Edge_key)
{
	for (std::list<Edge*>::const_iterator iter = Edges.cbegin(); iter != Edges.cend(); iter++)
		if (*iter != nullptr)
			if (**iter == *Edge_key)
				return *iter;
	return nullptr;
}

MR::Geometry::Point3D * MR::Model::getCommonPointInEdges(const std::list<Edge*> &Edges)
{
	if (Edges.size() < 2)
		return nullptr;
	if (Edges.size() == 2)
	{
		if ((*Edges.begin()) == nullptr || (*(--Edges.end())) == nullptr)
			return nullptr;
		Geometry::Point3D *p1 = nullptr, *p2 = nullptr, *p3 = nullptr, *p4 = nullptr;
		(*Edges.begin())->getPoints(&p1, &p2);
		(*(--Edges.end()))->getPoints(&p3, &p4);
		if ((p1 == p3) || (p1 == p4))
			return p1;
		else if ((p2 == p3) || (p2 == p4))
			return p2;
		else
			return nullptr;
	}
	else
	{
		for (Edge *e : Edges)
			if (e == nullptr)
				return nullptr;
		list<Edge*> edgesTemp;
		std::list<Edge*>::const_iterator iter = Edges.cbegin();
		edgesTemp.push_back(*iter); iter++;
		edgesTemp.push_back(*iter);
		Geometry::Point3D *tempPoint, *commonPoint = getCommonPointInEdges(edgesTemp);
		edgesTemp.pop_back();

		for (; iter != Edges.cend(); iter++)
		{
			edgesTemp.push_back(*iter);
			tempPoint = getCommonPointInEdges(edgesTemp);//всегда имеет размер 2
			if (commonPoint != tempPoint || tempPoint == nullptr)
				return nullptr;
			edgesTemp.pop_back();
		}
		return commonPoint;
	}
}