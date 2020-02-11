#include "stdafx.h"
#include "Tests.h"
#include "3DModel.h"
#include "MR_CircleTest.h"
#include "MR_SphereTest.h"
#include "MR_TestedModel.h"
#include "MR_Point3D_Cartesian.h"

namespace MR{
	void MR_Test()
	{
		Geometry::Point3DCartesian *ps1 = new Geometry::Point3DCartesian(10, 0, 0), *ps2 = new Geometry::Point3DCartesian(10, 0, 0);
		bool equal = (*ps1 == *ps2);
		Geometry::Point3DCartesian ps3 = *ps1 + *ps2;
		Geometry::Point3DCartesian *p1 = new Geometry::Point3DCartesian(10, 0, 0), *p2 = new Geometry::Point3DCartesian(0, 10, 0), *p3 = p3 = new Geometry::Point3DCartesian(0, 0, 10);
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

	MR::Geometry::Vector3D vec1 = MR::Geometry::Vector3D(-0.866, 0.5, 6.9);//150 градусов
	MR::Geometry::Vector3D vec2 = MR::Geometry::Vector3D(0, 3.1849, -0.9);//90 градусов
	MR::Geometry::Vector3D vec3 = MR::Geometry::Vector3D(-176, 0, 5.9);//180 градусов
	MR::Geometry::Vector3D vec4 = MR::Geometry::Vector3D(-0.5, -0.866, 1.9);//240 градусов
	MR::Geometry::Vector3D vec5 = MR::Geometry::Vector3D(0.5, -0.866, -2.9);//300 градусов

	MR::Geometry::Angle2D angle1 = MR::Geometry::Angle2D(vec1);
	MR::Geometry::Angle2D angle2 = MR::Geometry::Angle2D(vec2);
	MR::Geometry::Angle2D angle3 = MR::Geometry::Angle2D(vec3);
	MR::Geometry::Angle2D angle4 = MR::Geometry::Angle2D(vec4);
	MR::Geometry::Angle2D angle5 = MR::Geometry::Angle2D(vec5);

	/*try
	{
		std::vector<MR::Geometry::Point3D*> Points;
		Points.push_back(new MR::Geometry::Point3D(-9.0, 1.0, 0.0));
		Points.push_back(new MR::Geometry::Point3D(1.0, -9.0, 0.0));
		Points.push_back(new MR::Geometry::Point3D(6.0, 6.0, 0.0));
		std::list<MR::Model::Edge*> Edges;
		Edges.push_back(new MR::Model::Edge(Points[0], Points[1]));
		Edges.push_back(new MR::Model::Edge(Points[0], Points[2]));
		Edges.push_back(new MR::Model::Edge(Points[2], Points[1]));
		MR::Model::Face ftest = MR::Model::Face(Edges);
		MR::Geometry::Point3D p(0.0, 0.0, 0.0), dest(6.0, 6.0, 0.0);//always true, at the end throws exception cause of radius->0 fault
		//MR::Geometry::Point3D p(1.0, -10.0, 0.0), dest(6.0, 6.0, 0.0);//always false, at the end throws exception cause of radius->0 fault
		
		//MR::Geometry::Point3D p1(0.0, 0.0, 0.0), p2(11.0, 10.0, 0.0), p3(-19.5, 0.0, 0.0);
		//MR::Geometry::CircleTest test1(ftest, p1);//true
		//MR::Geometry::CircleTest test2(ftest, p2);//false
		//MR::Geometry::CircleTest test3(ftest, p3);//false
		
		int tempCount = 100;
		for (int i = 0; i < tempCount; i++)
		{
			double k = (double)i / (double)(tempCount-1);
			MR::Geometry::Point3D delta = (dest - p);
			delta.setX(delta.x()*k);
			delta.setY(delta.y()*k);
			delta.setZ(delta.z()*k);
			MR::Geometry::Point3D result = p + delta;
			MR::Geometry::CircleTest test1(ftest, result);
			bool isInside = test1.isInside();
			if (isInside == false)
			{
				int a = 0;
				a++;
			}
			if (i == tempCount - 2)
			{
				int v = 5;
				v--;
			}
			//std::cout << i << ") " << (isInside == true ? "true" : "false");
		}
	}
	catch (std::exception &ex)
	{
		std::cout << ex.what();
	}*/
	/*try
	{
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

		MR::Helpers::DoublePreciseApproximate d1 = MR::Helpers::DoublePreciseApproximate(1.564);
		MR::Helpers::DoublePreciseApproximate d2 = MR::Helpers::DoublePreciseApproximate(1.564);
		MR::Helpers::DoublePreciseApproximate d3 = d1 + d2;
		MR::Geometry::Angle2D angle = MR::Geometry::Angle2D(30);
		MR::Helpers::DoublePreciseApproximate::AccuracyType type = angle.getAccuracyType();
		}
	catch (std::exception &ex)
	{
		std::cout << ex.what();
	}*/
	return true;
}