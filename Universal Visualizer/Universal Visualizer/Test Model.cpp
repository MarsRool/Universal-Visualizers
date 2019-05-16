#include "stdafx.h"
#include "Tests.h"
#include "3DModel.h"
#include "MR_3D_Model.h"

namespace MR{
	void MR_Test()
	{
		Point3D **p1 = new Point3D*, **p2 = new Point3D*, **p3 = new Point3D*;
		*p1 = new Point3D(10, 0, 0); *p2 = new Point3D(0, 10, 0); *p3 = new Point3D(0, 0, 10);
		Edge** edge1= new Edge*;
		*edge1 = new Edge(p1, p2);
		Edge** edge2 = new Edge*;
		*edge2 = new Edge(p2, p3);
		Edge** edge3 = new Edge*;
		*edge3 = new Edge(p3, p1);

		vector<Edge**> ei;
		ei.push_back(edge1);
		ei.push_back(edge2);
		ei.push_back(edge3);
		Face* f1 = new Face(ei);
		*edge2 = *edge1;
		*edge3 = *edge1;
	}
}
bool Test_MR_Model(t3DModel &Model, MR::Model &MR_Model)
{
	/*MR::MR_Test();
	int *el1 = new int(20), *el2 = new int(30);
	int **a = new int*;
	*a = el1;
	int **b = a;
	*a = el2;*/
	bool result;
	Model.loadModel("data/obj/sphere.obj");
	MR::Model *MR_Model_new;
	MR_Model.addFrom3DModel(Model);
	result = MR_Model.check();
	MR_Model.uniqueObjects();

	/*MR_Model_new = MR_Model.getModelTested3DObjects();
	result = MR_Model_new->check();
	MR_Model_new->uniqueObjects();
	if (result)
		MR_Model = *MR_Model_new;*/
	return result;
}