#include "stdafx.h"
#include "Tests.h"
#include "3DModel.h"
#include "MR_CircleTest.h"
#include "MR_TestedModel.h"

namespace MR{
	void MR_Test()
	{
		Geometry::Point3D *p1 = new Geometry::Point3D(10, 0, 0), *p2 = new Geometry::Point3D(0, 10, 0), *p3 = p3 = new Geometry::Point3D(0, 0, 10);
		MR::Model::Edge* edge1 = new MR::Model::Edge(p1, p2);
		MR::Model::Edge* edge2 = new MR::Model::Edge(p2, p3);
		MR::Model::Edge* edge3 = new MR::Model::Edge(p3, p1);

		list<MR::Model::Edge*> ei;
		ei.push_back(edge1);
		ei.push_back(edge2);
		ei.push_back(edge3);
		MR::Model::Face* f1 = new MR::Model::Face(ei);
		edge2 = edge1;
		edge3 = edge1;
	}
}
bool Test_MR_Model(t3DModel &Model, MR::Model:: Model **MR_Model)
{
	Model.loadModel("data/obj/sphere.obj");
	(*MR_Model)->addFrom3DModel(Model);
	//MR::Model::Model* MR_Model_Tested = static_cast<MR::Model::TestedModel*>(*MR_Model)->getModelTested3DObjects();
	//*MR_Model = MR_Model_Tested;

	/*std::vector<MR::Geometry::Point3D*> Points;
	Points.push_back(new MR::Geometry::Point3D(10.0, 10.0, 0.0));
	Points.push_back(new MR::Geometry::Point3D(10.0, -10.0, 0.0));
	Points.push_back(new MR::Geometry::Point3D(-20.0, 0.0, 0.0));
	std::list<MR::Model::Edge*> Edges;
	Edges.push_back(new MR::Model::Edge(Points[0], Points[1]));
	Edges.push_back(new MR::Model::Edge(Points[0], Points[2]));
	Edges.push_back(new MR::Model::Edge(Points[2], Points[1]));
	MR::Model::Face ftest = MR::Model::Face(Edges);
	MR::Geometry::Point3D p1(0.0, 0.0, 0.0), p2(11.0, 10.0, 0.0), p3(-19.5, 0.0, 0.0);
	MR::Geometry::CircleTest test1(ftest, p1);
	MR::Geometry::CircleTest test2(ftest, p2);
	MR::Geometry::CircleTest test3(ftest, p3);*/
	std::vector<MR::Geometry::Point3D*> Points;
	Points.push_back(new MR::Geometry::Point3D(-10.0, 0.0, -10.0));
	Points.push_back(new MR::Geometry::Point3D(0.0, -10.0, -10.0));
	Points.push_back(new MR::Geometry::Point3D(5.0, 5.0, 10.0));
	std::list<MR::Model::Edge*> Edges;
	Edges.push_back(new MR::Model::Edge(Points[0], Points[1]));
	Edges.push_back(new MR::Model::Edge(Points[0], Points[2]));
	Edges.push_back(new MR::Model::Edge(Points[2], Points[1]));
	MR::Model::Face ftest = MR::Model::Face(Edges);
	MR::Geometry::Point3D p1(0.0, 0.0, 0.0), p2(4.0, -5.0, -1.0), p3(-4.0, -4.0, -8.0);
	MR::Geometry::CircleTest test1(ftest, p1);
	MR::Geometry::CircleTest test2(ftest, p2);
	MR::Geometry::CircleTest test3(ftest, p3);
	return true;
}