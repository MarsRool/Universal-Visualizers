#include "stdafx.h"
#include "conversions.h"
#include "MR_TestedModel.h"

MR::Model::TestedModel::TestedModel() : Model()
{
}

MR::Model::TestedModel::TestedModel(const TestedModel & modelToCopy, bool fullCopy)
{
	for (Object *o : modelToCopy.Objects)
		Objects.push_back((fullCopy ? 
			(dynamic_cast<TestedObject*>(o) != nullptr
				? new TestedObject(*dynamic_cast<TestedObject*>(o))
				: new Object(*o) )
		: o));
}

MR::Model::TestedModel* MR::Model::TestedModel::getModelTested3DObjects()
{
	TestedModel* result = new TestedModel();//результирующая модель
	TestedModel* thisCopy = new TestedModel(*this);
	std::list<MR::Model::TestedObject*>* Objects_t;

	for (Object *o : thisCopy->Objects)
	{
		TestedObject *to = dynamic_cast<TestedObject*>(o);
		if (to == nullptr)
		{
			to = TestedObject::ToTestedObject(o);
			o = nullptr;
		}
		Objects_t = to->getTested3dObjects();
		for (TestedObject *to_t : *Objects_t)
			result->Objects.push_back(dynamic_cast<Object*>(to_t));
		if (o != nullptr)
			delete o;
		else
			delete to;
		delete Objects_t;
	}
	delete thisCopy;
	return result;
}