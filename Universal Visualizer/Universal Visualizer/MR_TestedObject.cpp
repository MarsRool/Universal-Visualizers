#include "stdafx.h"
#include "conversions.h"
#include "MR_TestedObject.h"

MR::Model::TestedObject::TestedObject() : Object(), IsTested(false)
{
}

MR::Model::TestedObject::TestedObject(const std::list<Face*>& Faces_i, string name) : Object(Faces_i,name), IsTested(false)
{
}

MR::Model::TestedObject::TestedObject(const std::list<Geometry::Point3D*>& Points_i, const std::list<Edge*>& Edges_i, const std::list<Face*>& Faces_i, string name) : Object(Points_i, Edges_i, Faces_i, name), IsTested(false)
{
}

MR::Model::TestedObject::TestedObject(const TestedObject & objectToCopy) : Object(objectToCopy), IsTested(objectToCopy.IsTested)
{
}

MR::Model::TestedObject::~TestedObject()
{
}

MR::Model::TestedObject & MR::Model::TestedObject::operator=(const TestedObject & objToCopy)
{
	if (&objToCopy == this)
		return *this;

	Object::operator=(objToCopy);
	this->IsTested = objToCopy.IsTested;

	return *this;
}

std::list<MR::Model::TestedObject*>* MR::Model::TestedObject::getTested3dObjects(const TestedObject & object)
{
	TestedObject* result = getObjCleanedBoundaryFaces(object);
	list<TestedObject*>* resultList = get3DObjects(*result);
	delete result;
	for (TestedObject *to : *resultList)
		to->IsTested = true;
	return resultList;
}

std::list<MR::Model::TestedObject*>* MR::Model::TestedObject::getTested3dObjects()
{
	return getTested3dObjects(*this);
}

MR::Model::TestedObject * MR::Model::TestedObject::ToTestedObject(Object *objectToCopy)
{
	TestedObject *result = new TestedObject();
	result->clearData();
	result->Position = objectToCopy->getPos();
	result->Color.setColor((rand() % 256) / 256, (rand() % 256) / 256, (rand() % 256) / 256);
	result->StrName = objectToCopy->getStrName();
	result->ReplaceNotUnique(*objectToCopy);
	delete objectToCopy;
	return result;
}

MR::Model::TestedObject* MR::Model::TestedObject::getObjCleanedBoundaryFaces(const TestedObject &object)
{
	TestedObject* result = new TestedObject(object);

	bool isBoundaries = true;//true- если есть граничные грани на удаление
	while (isBoundaries == true)
	{
		isBoundaries = false;
		for (std::list<Face*>::const_iterator iter = result->Faces.cbegin(); iter != result->Faces.cend(); iter++)
			if ((*iter)->isBoundary() == true)
			{
				delete (*iter);
				result->Faces.erase(iter);
				isBoundaries = true;
				break;
			}
	}
	result->clearNonexistent();
	return result;
}

std::list<MR::Model::TestedObject*>* MR::Model::TestedObject::get3DObjects(TestedObject & object)
{
	list<TestedObject*>* result = new list<TestedObject*>;

	TestedObject* obj;

	list<Face*> faces_i;//грани текущего объекта

	int count = 0;
	bool isOk = false;

	while (object.Faces.size() > 0)
	{
		faces_i.clear();

		object.clearSelection();
		object.selectFaces(*object.Faces.cbegin(), object.Faces);
		if (object.Faces.size() > 1)
			for (std::list<Face*>::const_iterator iter = ++object.Faces.cbegin(); iter != object.Faces.cend(); iter++)
				if ((*iter)->flag() == true)
				{
					faces_i.push_back(*iter);
					iter = object.Faces.erase(iter);
					iter--;
				}
		//дополнительная проверка потому что если будет удаляться первый элемент,
		//iter присвоится новый cbegin, после которого нельзя применить iter--;
		if ((*object.Faces.cbegin())->flag() == true)
		{
			faces_i.push_back(*object.Faces.cbegin());
			object.Faces.erase(object.Faces.cbegin());
		}

		obj = new TestedObject(faces_i, object.StrName + "_tested_" + uchTostr(dtuch(count)));		
		result->push_back(obj);
		count++;
	}
	return result;
}