#include "stdafx.h"
#include "conversions.h"
#include "MR_math.h"
#include "MR_3D_Model.h"

MR::Edge::Edge()
{
	Point1 = new Point3D*;
	Point2 = new Point3D*;
	*Point1 = NULL;
	*Point2 = NULL;
	CountIncludingInFaces = 0;
}

MR::Edge::Edge(Point3D **point1_i, Point3D **point2_i, short int count)
{
	Point1 = point1_i;
	Point2 = point2_i;
	CountIncludingInFaces = count;
}

MR::Edge::Edge(const Edge & edgeToCopy)
{
	Point1 = new Point3D*;
	Point2 = new Point3D*;
	*Point1 = *edgeToCopy.Point1;
	*Point2 = *edgeToCopy.Point2;
	if (edgeToCopy.CountIncludingInFaces > 0)
		CountIncludingInFaces = edgeToCopy.CountIncludingInFaces;
	else
		CountIncludingInFaces = 0;
}

MR::Edge::~Edge()
{
	/**Point1 = NULL;
	*Point2 = NULL;
	delete Point1;
	delete Point2;*/
}

bool MR::Edge::check()
{
	if ((*Point1)->check() && (*Point2)->check() && Point1 != NULL && Point2 != NULL && (*Point1) != NULL && (*Point2) != NULL)
		return true;
	return false;
}

void MR::Edge::getPoints(Point3D ** Point1_i, Point3D ** Point2_i)
{
	*Point1_i = *Point1;
	*Point2_i = *Point2;
}

MR::Vector3D MR::Edge::getVector12()
{
	return Vector3D(*Point1, *Point2);
}

const bool MR::Edge::operator==(const Edge & edge_right)
{//сравнение по значению
	return ((**Point1 == **edge_right.Point1 && **Point2 == **edge_right.Point2) ||
			(**Point1 == **edge_right.Point2 && **Point2 == **edge_right.Point1));
}

MR::Edge& MR::Edge::operator++(int)
{
	this->CountIncludingInFaces++;
	return *this;
}

MR::Edge& MR::Edge::operator--(int)
{
	if(CountIncludingInFaces > 0)
		this->CountIncludingInFaces--;
	return *this;
}

MR::Edge& MR::Edge::operator+=(int added)
{
	this->CountIncludingInFaces += added;
	return *this;
}

MR::Edge& MR::Edge::operator=(const Edge & edge_right)
{
	if (&edge_right == this)
		return *this;
	return Edge(this->Point1 = edge_right.Point1, this->Point2 = edge_right.Point2, CountIncludingInFaces);
}

MR::Edge ** MR::searchEdge(std::vector<Edge**> Edges, Edge * Edge_key)
{
	for (unsigned int i = 0; i < Edges.size(); i++)
		if (Edges[i] != NULL)
			if ((*Edges[i]) != NULL)
				if (**Edges[i] == *Edge_key)
					return Edges[i];
	return NULL;
}

MR::Point3D * MR::getCommonPointInEdges(std::vector<Edge**> Edges)
{
	if (Edges.size() < 2)
		return NULL;
	if (Edges.size() == 2)
	{
		if (*Edges[0] == NULL || *Edges[1] == NULL)
			return NULL;
		Point3D *p1 = NULL, *p2 = NULL, *p3 = NULL, *p4 = NULL;
		(*Edges[0])->getPoints(&p1, &p2);
		(*Edges[1])->getPoints(&p3, &p4);
		if ((p1 == p3) || (p1 == p4))
			return p1;
		else if ((p2 == p3) || (p2 == p4))
			return p2;
		else
			return NULL;
	}
	else
	{
		for (int i = 0; i < Edges.size(); i++)
			if (*Edges[i] == NULL)
				return NULL;
		Point3D *commonPoint, *tempPoint;
		vector<Edge**> edgesTemp;
		edgesTemp.push_back(Edges[0]);
		edgesTemp.push_back(Edges[1]);
		commonPoint = getCommonPointInEdges(edgesTemp);
		if (commonPoint == NULL)
			return NULL;
		for (unsigned int i = 2; i < Edges.size(); i++)
		{
			edgesTemp.pop_back();
			edgesTemp.push_back(Edges[i]);
			tempPoint = getCommonPointInEdges(edgesTemp);
			if (commonPoint != tempPoint || tempPoint == NULL)
				return NULL;
		}
		return commonPoint;
	}
}

void MR::Face::calculateNormal()
{
	if (Edges.size() >= 2)
	{
		*Normal = vectorProduct((*Edges[0])->getVector12(), (*Edges[1])->getVector12());
		Normal->normalize();
	}
}

void MR::Face::calculateCenterOfMass()
{
	double x = 0, y = 0, z = 0;
	for (Point3D **p : Points)
	{
		x += (*p)->x();
		y += (*p)->y();
		z += (*p)->z();
	}
	x /= Points.size();
	y /= Points.size();
	z /= Points.size();
	CenterOfMass->set(x, y, z);
}

MR::Face::Face()
{
	Normal = new Vector3D();
	CenterOfMass = new Point3D();
	Area = 0;
	Flag = false;
	CenterOfMass = 0;
}

MR::Face::Face(std::vector<Edge**> Edges_i)
{
	Normal = new Vector3D();
	CenterOfMass = new Point3D();
	Area = 0;
	Flag = false;
	if (!istEdgesInPlane(Edges_i) || Edges_i.size() <= 2)
		*this = *new Face();
	else
	{
		Edges = Edges_i;
		Point3D **Point1, **Point2;
		bool uniq1, uniq2;
		for (unsigned int i = 0; i < (int)Edges.size(); i++)
		{
			Point1 = new Point3D*;
			Point2 = new Point3D*;
			(**Edges[i])++;//увеличение количества смежных граней у каждого ребра
			(*Edges[i])->getPoints(Point1, Point2);
			uniq1 = true; uniq2 = true;
			for (unsigned int j = 0; j < Points.size(); j++)
			{
				if (**Points[j] == **Point1)
					uniq1 = false;
				if (**Points[j] == **Point2)
					uniq2 = false;
			}
			if (uniq1)
				Points.push_back(Point1);
			if (uniq2)
				Points.push_back(Point2);
		}
		calculateNormal();
		calculateCenterOfMass();
	}
}

MR::Face::Face(const Face & faceToCopy)
{
	Point3D **point_i;
	Edge **edge_i;
	Normal = new Vector3D(*faceToCopy.Normal);//нормаль
	CenterOfMass = new Point3D(*faceToCopy.CenterOfMass);
	Area = faceToCopy.Area;
	Flag = faceToCopy.Flag;//true- если уже участвовал в рекурсивном тесте на 3D модель

	for (Point3D **p : faceToCopy.Points)
	{
		point_i = new Point3D*;
		*point_i = *p;
		Points.push_back(point_i);
	}
	for (Edge **e : faceToCopy.Edges)
	{
		edge_i = new Edge*;
		*edge_i = *e;
		Edges.push_back(edge_i);
	}
}

MR::Face::~Face()
{
	for (int i = 0; i < Edges.size(); i++)
	{
		(**Edges[i])--;
		if ((*Edges[i])->getCountIncludingInFaces() == 0)
		{
			delete *Edges[i];
			*Edges[i] = NULL;
		}
	}
	delete Normal;
	delete CenterOfMass;
}

bool MR::Face::istEdgesInPlane(std::vector<Edge**> Edges_i)
{//true- если ребра находятся в одной плоскости
	if (Edges_i.size() <= 2)
		return false;
	else if (Edges_i.size() == 3)
	{
		for (int i = 0; i < Edges.size(); i++)
			if (*Edges[i] == NULL)
				return false;
		Vector3D vec0, vec1, vec2;
		double result;
		vec0 = (*Edges_i[0])->getVector12();
		vec0.normalize();
		vec1 = (*Edges_i[1])->getVector12();
		vec1.normalize();
		vec2 = (*Edges_i[2])->getVector12();
		vec2.normalize();
		result = mixedProduct(vec0, vec1, vec2);
		if (std::abs(result) < smallV)
			return true;
		else
			return false;
	}
	else
	{
		for (int i = 0; i < Edges.size(); i++)
			if (*Edges[i] == NULL)
				return false;
		std::vector<Edge**> Edges3;
		Edges3.push_back(Edges_i[0]);
		Edges3.push_back(Edges_i[1]);
		for (int i = 2; i < Edges_i.size(); i++)
		{
			Edges3.push_back(Edges_i[i]);
			if (istEdgesInPlane(Edges3) == false)
				return false;
			Edges3.pop_back();
		}
		return true;
	}
	/*else
	{
		Vector3D vec0, veci, normal1, normali;
		vec0 = Edges_i[0]->getVector12();
		vec0.normalize();
		veci = Edges_i[1]->getVector12();
		veci.normalize();
		normal1 = vectorProduct(vec0, veci);
		normal1.normalize();
		for (unsigned int i = 2; i < Edges_i.size(); i++)
		{
			veci = Edges_i[i]->getVector12();
			veci.normalize();
			normali = vectorProduct(vec0, veci);
			normali.normalize();
			if (!(compareAproximately(normal1, normali) || compareAproximately(normal1, -normali)))
				return false;
		}
		return true;
	}*/
}

bool MR::Face::check()
{
	if (Edges.size() < 3)
		return false;

	for (unsigned int i = 0; i < Edges.size(); i++)//проверка на корректность элементов
		if (*Edges[i] != NULL)
			if ((*Edges[i])->check() == false)
				return false;

	if (istEdgesInPlane(Edges) == false)//проверка на то, чтобы ребра лежали в одной плоскости
		return false;

	//проверка, чтобы все ребра были последовательно связаны. То есть имели по очереди попарно общую точку
	vector<Edge**> edgesTemp;
	edgesTemp.push_back(Edges[0]);
	edgesTemp.push_back(Edges[Edges.size() - 1]);
	if (getCommonPointInEdges(edgesTemp) == NULL)
		return false;
	for (unsigned int i = 0; i < Edges.size() - 1; i++)
	{
		edgesTemp.clear();
		edgesTemp.push_back(Edges[i]);
		edgesTemp.push_back(Edges[i + 1]);
		if (getCommonPointInEdges(edgesTemp) == NULL)
			return false;
	}
	return true;
}

bool MR::Face::isBoundary()
{
	for (Edge **e : Edges)
		if (*e != NULL)
			if ((*e)->getCountIncludingInFaces() <= 1)
				return true;
	return false;
}

const bool MR::Face::operator==(const Face & face_right)
{
	if (Points.size() != face_right.Points.size() ||
		Edges.size() != face_right.Edges.size())
		return false;//количество точек и ребер должно быть одинаково

	for (Point3D **p : Points)//каждая точка должна взаимно содержаться в массиве точек
		if (*p != NULL)
			if (searchPoint(face_right.Points, *p) == NULL)
				return false;
	for (Point3D **p : face_right.Points)
		if (*p != NULL)
			if (searchPoint(Points, *p) == NULL)
				return false;

	if ((compareAproximately(*Normal, *face_right.Normal) == false &&//сравнение нормалей и проверка их на неравенство NULL
		compareAproximately(-(*Normal), *face_right.Normal) == false) ||
		Normal == NULL || face_right.Normal == NULL)
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
	for (unsigned int i = 0; i < Edges.size(); i++)
	{
		if (searchEdge(face_right.Edges, *Edges[i]) == NULL)
			return false;

		if(direct)
			for (unsigned int j = 0; j < face_right.Edges.size(); j++)
				if (**Edges[i] == **Edges[j])
					if (lastDirectIndex == -1)
						lastDirectIndex = j;
					else
					{
						if (j == ((lastDirectIndex + 1) % Edges.size()))
						{
							lastDirectIndex = j;
						}
						else
							direct = false;
					}

		if (reverse)
			for (unsigned int j = 0; j < face_right.Edges.size(); j++)
				if (**Edges[i] == **Edges[j])
					if (lastReverseIndex == -1)
						lastReverseIndex = j;
					else
					{
						if (j == ((Edges.size() + lastReverseIndex - 1) % Edges.size()))
						{
							lastReverseIndex = j;
						}
						else
							reverse = false;
					}
	}
	return (direct || reverse);
}

MR::Face& MR::Face::operator=(const Face & faceToCopy)
{
	if (&faceToCopy == this)
		return *this;

	Point3D **point_i;
	Edge **edge_i;
	*Normal = *faceToCopy.Normal;//нормаль
	*CenterOfMass = *faceToCopy.CenterOfMass;
	Area = faceToCopy.Area;
	Flag = faceToCopy.Flag;//true- если уже участвовал в рекурсивном тесте на 3D модель

	for (Point3D **p : faceToCopy.Points)
	{
		point_i = new Point3D*;
		*point_i = *p;
		Points.push_back(point_i);
	}
	for (Edge **e : faceToCopy.Edges)
	{
		edge_i = new Edge*;
		*edge_i = *e;
		Edges.push_back(edge_i);
	}

	return *this;
}

MR::Object::Object()
{
	Position = new Point3D();
	clearData();
	Color.setColor((rand() % 256) / 256, (rand() % 256) / 256, (rand() % 256) / 256);
}

MR::Object::Object(std::vector<Point3D**> *Points_i, std::vector<Edge**> *Edges_i, std::vector<Face**> *Faces_i, string name)
{
	Position = new Point3D();
	clearData();
	Color.setColor((rand() % 256) / 256, (rand() % 256) / 256, (rand() % 256) / 256);
	Points = *Points_i;
	Edges = *Edges_i;
	Faces = *Faces_i;
	Position = new Point3D();
	StrName = name;
}

MR::Object::Object(const Object & objectToCopy)
{
	Position = new Point3D(*objectToCopy.Position);
	clearData();
	Color.setColor((rand() % 256) / 256, (rand() % 256) / 256, (rand() % 256) / 256);
	StrName = objectToCopy.StrName;

	Point3D **point_i;
	Edge **edge_i;
	Point3D **p1, **p2;
	for (Point3D **p : objectToCopy.Points)
	{
		point_i = new Point3D*;
		*point_i = new Point3D();
		**point_i = **p;
		Points.push_back(point_i);
	}
	for (Edge **e : objectToCopy.Edges)
	{
		p1 = new Point3D*;
		p2 = new Point3D*;
		(*e)->getPoints(p1, p2);
		*p1 = *searchPoint(Points, *p1);
		*p2 = *searchPoint(Points, *p2);
		edge_i = new Edge*;
		*edge_i = new Edge(p1, p2);
		(**edge_i) += (**e).getCountIncludingInFaces();
		Edges.push_back(edge_i);
	}

	Face **face_i;
	vector<Edge**> edges_temp, edges_i;
	for (unsigned int i = 0; i < objectToCopy.Faces.size(); i++)
		if (*objectToCopy.Faces[i] != NULL)
		{
			edges_i.clear();
			(*objectToCopy.Faces[i])->getEdges(&edges_temp);
			face_i = new Face*;
			//*face_i = new Face();
			*face_i = new Face(**objectToCopy.Faces[i]);
			//**face_i = **objectToCopy.Faces[i];
			for (int j = 0; j < edges_temp.size(); j++)
				for (int l = 0; l < Edges.size(); l++)
					if (Edges[l] != NULL && edges_temp[j] != NULL)
						if (**Edges[l] == **edges_temp[j])
							edges_i.push_back(Edges[l]);
			(*face_i)->setEdges(&edges_i);
			Faces.push_back(face_i);
		}
}

MR::Object::~Object()
{
	for (int i = 0; i < Faces.size(); i++)
	{
		delete *Faces[i];
		*Faces[i] = NULL;
	}
	for (int i = 0; i < Points.size(); i++)
	{
		delete *Points[i];
		*Points[i] = NULL;
	}
	delete Position;
}

void MR::Object::clearData()
{
	Position->set(0, 0, 0);
	Points.clear();
	Edges.clear();
	Faces.clear();
	StrName = "";

	TypeColor = 3;//цвета
	Color = RGB_MR(0.0, 0.0, 0.0);

	ColorGrad[0] = RGB_MR(1.0, 0.0, 0.0);
	ColorGrad[1] = RGB_MR(0.0, 1.0, 0.0);
	ColorGrad[2] = RGB_MR(0.0, 0.0, 1.0);
	ColorGrad[3] = RGB_MR(0.0, 0.0, 0.0);

	ColorGradLand[0] = RGB_MR(1.0, 0.06, 0.06);
	ColorGradLand[1] = RGB_MR(1.0, 0.5, 0.06);
	ColorGradLand[2] = RGB_MR(1.0, 0.95, 0.06);
	ColorGradLand[3] = RGB_MR(0.06, 0.85, 0.06);
	ColorGradLand[4] = RGB_MR(0.06, 0.95, 1.0);
	ColorGradLand[5] = RGB_MR(0.06, 0.4, 1.0);
	ColorGradLand[6] = RGB_MR(0.5, 0.06, 0.5);
}

bool MR::Object::isEmpty()
{
	if (Points.size() < 1 || Edges.size() < 3 || Faces.size() < 1)
		return true;
	return false;
}

bool MR::Object::check()
{
	//элементы 3х множеств могут быть нулевыми. они должны быть удалены в uniqueElements()
	//метод поиска ошибки

	for (int i = 0; i < Points.size(); i++)
		if (*Points[i] != NULL)
			if ((*Points[i])->check() == false)
				return false;

	//правильным также является то, что ребро построено на одной и той же точке. это должно быть отсеяно на этапе теста
	for (int i = 0; i < Edges.size(); i++)
	{
		//все ребра должны быть построены на Points.
		Point3D *p1 = NULL, *p2 = NULL;
		if (*Edges[i] != NULL)
		{
			(*Edges[i])->getPoints(&p1, &p2);//Points уже ненулевые, поэтому можно не проверять p1 и p2 на равенство NULL
			if (p1 == NULL || p2 == NULL || searchPoint(Points, p1) == NULL || searchPoint(Points, p2) == NULL || (*Edges[i])->check() == false)
				return false;
		}
	}

	vector<Edge**> Edges_i;
	for (int i = 0; i < Faces.size(); i++)
		if (*Faces[i] != NULL)
		{
			if ((*Faces[i])->check() == false)
				return false;

			//все грани должны быть построены только на Edges.
			(*Faces[i])->getEdges(&Edges_i);
			for (unsigned int i = 0; i < Edges_i.size(); i++)
				if (searchEdge(Edges, *Edges_i[i]) == NULL || Edges_i[i] == NULL)
					return false;
		}
	return true;
}

void MR::Object::uniqueElements()
{
	for (unsigned int i = 0; i < Points.size(); i++)
		if (*Points[i] == NULL)//удаление пустых точек
		{
			*Points[i] = *Points[Points.size() - 1];
			Points.pop_back();
			i--;
			continue;
		}
	for (unsigned int i = 0; i < Points.size(); i++)
	{
		if(Points.size()>1)
			for (unsigned int j = 0; j < Points.size(); j++)
				if (j != i)
				{
					if (**Points[i] == **Points[j])//всегда j > i
					{
						/*if (*Points[i] != *Points[j])
							delete *Points[j];*/
						*Points[j] = *Points[i];
						Points[j] = Points[Points.size() - 1];
						Points.pop_back();
						j--;
					}
				}
	}
	for (unsigned int i = 0; i < Edges.size(); i++)
		if (*Edges[i] == NULL)//удаление пустых ребер
		{
			*Edges[i] = *Edges[Edges.size() - 1];
			Edges.pop_back();
			i--;
			continue;
		}
	for (unsigned int i = 0; i < Edges.size(); i++)
	{
		if (Edges.size() > 1)
		for (unsigned int j = 0; j < Edges.size(); j++)
				if (j != i)
				{
					if (**Edges[i] == **Edges[j])//всегда j > i
					{
						(**Edges[i]) += (*Edges[j])->getCountIncludingInFaces();//добавить число смежных граней из такого же ребра
						/*if (*Edges[i] != *Edges[j])
							delete *Edges[j];*/
						*Edges[j] = *Edges[i];
						Edges[j] = Edges[Edges.size() - 1];
						Edges.pop_back();
						j--;
					}
				}
	}
	for (unsigned int i = 0; i < Faces.size(); i++)
		if (*Faces[i] == NULL)//удаление пустых граней
		{
			*Faces[i] = *Faces[Faces.size() - 1];
			Faces.pop_back();
			i--;
			continue;
		}
	for (unsigned int i = 0; i < Faces.size(); i++)
	{
		if (Faces.size() > 1)
			for (unsigned int j = 0; j < Faces.size(); j++)
				if (j != i)
				{
					if (**Faces[i] == **Faces[j])//всегда j > i
					{
						/*if (*Faces[i] != *Faces[j])
							delete *Faces[j];*/
						*Faces[j] = *Faces[i];
						Faces[j] = Faces[Faces.size() - 1];
						Faces.pop_back();
						j--;
					}
				}
	}
	//удалить неиспользующиеся элементы
	//по определению все ребра используются, поэтому могут не использоваться только точки.
	//проверка на вхождение всех точек в полигоны. Обратное вхождение проверяется в check
	vector<Point3D**> Points_excess;//неиспользуемые точки
	vector<Point3D**> Points_temp;//точки каждой грани
	vector<Edge**> Edges_temp;
	Point3D **Point1, **Point2;
	for (unsigned int i = 0; i < Points.size(); i++)
		Points_excess.push_back(Points[i]);//заполнение возможно неиспользуемые точки всеми точками
	for (unsigned int i = 0; i < Faces.size(); i++)//заполнение точек всех граней
	{
		(*Faces[i])->getEdges(&Edges_temp);
		for (unsigned int j = 0; j < Edges_temp.size(); j++)
		{
			Point1 = new Point3D*;
			Point2 = new Point3D*;
			(*Edges_temp[j])->getPoints(Point1, Point2);
			Points_temp.push_back(Point1);
			Points_temp.push_back(Point2);
		}
	}
	//проверка на вхождение каждого из Points_excess в Points_temp
	for (unsigned int i = 0; i < Points_excess.size(); i++)
	{
		if (searchPoint(Points_temp, *Points_excess[i]) != NULL)//если текущая точка найдена в полигонах, то удаляем ее из Points_excess
		{
			Points_excess[i] = Points_excess[Points_excess.size() - 1];
			Points_excess.pop_back();
			i--;
		}
	}
	//Points_temp содержит неиспользуемые точки и их надо удалить в Points
	for (unsigned int i = 0; i < Points_excess.size(); i++)
		for (unsigned int j = 0; j < Points.size(); j++)
			if (Points[j] == Points_excess[i])
			{
				delete *Points[j];
				*Points[j] = NULL;
				Points[j] = Points[Points.size() - 1];
				Points.pop_back();

				Points_excess[i] = Points_excess[Points_excess.size() - 1];
				Points_excess.pop_back();
				i--;
				break;
			}
	if (Points_excess.size() != NULL)
	{
		System::Windows::Forms::MessageBox::Show(L"Ошибка на этапе унификации элементов.\nЕсли вы видите это сообщение, то программа работает некорректно.", L"Ошибка", System::Windows::Forms::MessageBoxButtons::OK, System::Windows::Forms::MessageBoxIcon::Warning);
	}
}

MR::Object* MR::Object::getObjCleanedBoundaryFaces()
{
	Object* result = new Object(*this);

	bool isBoundaries = true;//true- если есть граничные грани на удаление
	while (isBoundaries == true)
	{
		isBoundaries = false;
		for (int i = 0; i < result->Faces.size(); i++)
			if ((*result->Faces[i])->isBoundary() == true)
			{
				delete *result->Faces[i];
				result->Faces[i] = result->Faces[result->Faces.size() - 1];
				result->Faces.pop_back();
				isBoundaries = true;
				break;
			}
	}
	return result;
}

void MR::Object::selectFaces(Face * face)
{
	if (face->flag() == true)
		return;
	else
	{
		face->setFlag(true);
		std::vector<Edge**> edges_i;
		face->getEdges(&edges_i);
		for (Edge **e_i : edges_i)//для каждого ребра текущей грани
			if ((*e_i)->getCountIncludingInFaces() > 1)//у которой количество включающих граней больше 1
				for (Face **f : Faces)//ищем в каждом ребре всех граней
					if ((*f) != face)//и если грань не текущая, то
					{
						std::vector<Edge**> edges_j;
						(*f)->getEdges(&edges_j);
						for (Edge **e_j : edges_j)//ищем на совпадение каждое ребро в каждой грани
							if (**e_j == **e_i)//ребра совпали. f - найденная грань и ее нужно выделить
								selectFaces(*f);
					}
	}
}

void MR::Object::selectFaces(Face * face, std::vector<Face**>* Faces)
{
	if (face->flag() == true)
		return;
	else
	{
		face->setFlag(true);
		std::vector<Edge**> edges_i;
		face->getEdges(&edges_i);
		for (Edge **e_i : edges_i)//для каждого ребра текущей грани
			if ((*e_i)->getCountIncludingInFaces() > 1)//у которой количество включающих граней больше 1
				for (Face **f : *Faces)//ищем в каждом ребре всех граней
					if ((*f) != face)//и если грань не текущая, то
					{
						std::vector<Edge**> edges_j;
						(*f)->getEdges(&edges_j);
						for (Edge **e_j : edges_j)//ищем на совпадение каждое ребро в каждой грани
							if (**e_j == **e_i)//ребра совпали. f - найденная грань и ее нужно выделить
								selectFaces(*f, Faces);
					}
	}
}

std::vector<MR::Object*>* MR::Object::get3DObjects()
{
	vector<Object*>* result = new vector<Object*>;

	Object *thisCopy = new Object(*this);
	Object* obj;

	Point3D **point_j;
	Edge **edge_j;
	Face **face_j;

	vector<Face**>* faces_i = new vector<Face**>;//грани текущего объекта
	vector<Edge**>* edges_i = new vector<Edge**>;//ребра текущего объекта
	vector<Point3D**>* points_i = new vector<Point3D**>;//точки текущего объекта

	int count = 0;
	bool isOk = false;

	vector<Face**> faces_test;//оставшиеся грани. Их можно создать один раз, потому что они будут использоваться только один раз без повтора(не могут быть одновременно в нескольких выходных обхектах)
	for (Face **f : thisCopy->Faces)
	{
		face_j = new Face*;
		*face_j = *f;
		faces_test.push_back(face_j);
	}

	//разбиение на тела. нужно сделать так, чтобы выходные объекты не были зависимы друг от друга. то есть нужно создать копии их элементов
	while (faces_test.size() > 0)
	{
		points_i->clear();
		edges_i->clear();
		faces_i->clear();
		for (Point3D **p : thisCopy->Points)//!!!неправильно
		{
			point_j = new Point3D*;
			*point_j = *p;
			points_i->push_back(point_j);
		}
		for (Edge **e : thisCopy->Edges)//!!!неправильно из-за того, что ребра должны быть созданы из выделенных граней!
		{
			edge_j = new Edge*;
			*edge_j = *e;
			edges_i->push_back(edge_j);
		}
		
		for (Face **f : faces_test)//снять выделение
			(*f)->setFlag(false);

		selectFaces(*(faces_test[0]), &faces_test);//выделить текущую нулевую грань и все смежные с ней.
		for (int i = 0; i < faces_test.size(); i++)
			if ((*faces_test[i])->flag() == true)
			{
				face_j = new Face*;
				*face_j = *faces_test[i];
				(*face_j)->setFlag(false);
				faces_i->push_back(face_j);//заполнение текущих выходных граней
				faces_test[i] = faces_test[faces_test.size() - 1];
				faces_test.pop_back();//удаление использованных оставшихся граней
				i--;
			}//!!!не работает selectFaces. Это может быть связано с созданием копии текущего объекта
		obj = new Object(points_i, edges_i, faces_i, StrName + "_tested_" + uchTostr(dtuch(count)));
		isOk = obj->check();
		obj->uniqueElements();
		if (isOk)
		{
			result->push_back(obj);
			count++;
		}
		else
		{
			System::Windows::Forms::MessageBox::Show(L"Ошибка на этапе разделения объектов.\nЕсли вы видите это сообщение, то программа работает некорректно.", L"Ошибка", System::Windows::Forms::MessageBoxButtons::OK, System::Windows::Forms::MessageBoxIcon::Warning);
			return NULL;
		}
	}
	if (isEmpty())
	{
		obj = thisCopy;
		obj->StrName+="_tested";
		result->push_back(obj);
	}
	return result;
}

MR::Point3D * MR::Object::getPos()
{
	Point3D *result = new Point3D(*Position);
	return result;
}

void MR::Object::setPos(Point3D *point_in)
{
	*Position = *point_in;
}

void MR::Object::drawObject()
{
	glPushMatrix();
	//glEnable(GL_TEXTURE_2D);
	glTranslated(Position->x(), Position->y(), Position->z());
	glScaled(30, 30, 30);

	//glColor3f(obj.TextureInf.color[0],obj.TextureInf.color[1],obj.TextureInf.color[2]);
	glColor3f(1.0f, 1.0f, 1.0f);

	/*CV3 vertex[3];
	CV2 texvert[3];
	CV3 normal[3];
	float rgb[3];
	int IDi = 0;
	bool isttexture;
	const TextureImage *texturei;

	float black[] = { 0.0, 0.0, 0.0, 1.0 };
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);*/

	Point3D *lastPoint;
	Point3D **p1 = new Point3D*, **p2 = new Point3D*;
	vector<Edge**> edges_i;
	int coef = 80;
	for (Face** f : Faces)
	{
		/*isttexture = false;
		IDi = Objects[l].pFaces[i].Id_tex;
		for (int j = 1; j <= numTex; j++)
			if (IDi == Textures[j].texureId)
			{
				//цвета, освещение
				if (Textures[j].Ka.ist == true)
				{
					//ambient
					rgb[0] = Textures[j].Ka.rgb[0];
					rgb[1] = Textures[j].Ka.rgb[1];
					rgb[2] = Textures[j].Ka.rgb[2];
					float ambient[] = { rgb[0],rgb[1],rgb[2],1.0 };
					glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
				}
				else
					glLightModelfv(GL_LIGHT_MODEL_AMBIENT, black);

				if (Textures[j].Ka.texture.loaded == true)
				{
					texturei = &Textures[j].Ka.texture.image;//текстура
					glBindTexture(GL_TEXTURE_2D, texturei->texID);
					isttexture = true;
				}
			}*/

		(*f)->getEdges(&edges_i);
		lastPoint = NULL;
		Point3D *tmpCenter = (*f)->getCenterOfMass();

		glBegin(GL_POLYGON);
			glColor3d(
				counticolor(tmpCenter->x()*coef, tmpCenter->y()*coef, tmpCenter->x()*coef, 0),
				counticolor(tmpCenter->x()*coef, tmpCenter->y()*coef, tmpCenter->z()*coef, 1),
				counticolor(tmpCenter->x()*coef, tmpCenter->y()*coef, tmpCenter->z()*coef, 2));
			for (int j = 0; j < edges_i.size(); j++)
			{
				(*edges_i[j])->getPoints(p1, p2);
				if (*p1 != lastPoint)
				{
					//glNormal3f(normal[0].x, normal[0].y, normal[0].z);
					glVertex3f((*p1)->x(), (*p1)->y(), (*p1)->z());
					//lastPoint = *p1;
				}
				if((*p2) != lastPoint)
				{
					//glNormal3f(normal[0].x, normal[0].y, normal[0].z);
					glVertex3f((*p2)->x(), (*p2)->y(), (*p2)->z());
					//lastPoint = *p2;
				}
			}
		glEnd();
	}
	//glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

MR::Object & MR::Object::operator=(const Object & objToCopy)
{
	if (&objToCopy == this)
		return *this;

	Object *thisCopy = new Object(objToCopy);
	this->Points = thisCopy->Points;
	this->Edges = thisCopy->Edges;
	this->Faces = thisCopy->Faces;
	this->StrName = thisCopy->StrName;
	this->Position = thisCopy->Position;

	return *this;
}

MR::Model::Model()
{
}

MR::Model::Model(const Model *modelToCopy)
{
	Object *obj_i;
	for (Object *o : modelToCopy->Objects)
	{
		obj_i = new Object(*o);
		Objects.push_back(obj_i);
	}
}

void MR::Model::addFrom3DModel(const t3DModel & Model)
{
	//сначала создаем три массива: точек, ребер и граней
	std::vector<Point3D**> Points;
	std::vector<Edge**> Edges;
	std::vector<Face**> Faces;

	bool isto;					//загружена ли модель

	int  numVerts;              // Число вершин в модели
	//int  numTexVertex;          // Число текстурных координат

	//int  numTex;				// Число текстур
	//vector<tMaterialInfo> Textures;  //Описание каждой текстуры
	//bool bHasTexture;           // TRUE если есть текстурная карта для этого обьекта

	vector<CV3>   pVerts;		// Массив вершин обьекта
	//vector<CV2>   pTexVerts;    // Текстурные координаты

	int numOfObjects;           // Число обьектов в модели
	vector<t3DObject> Objects;  // Полигоны обьекта
	Model.Return_Data(isto, numVerts, pVerts, numOfObjects, Objects);

	if (isto)
	{
		Object *object_l;
		Face **face_i;
		vector<Edge**> edges_i;
		Edge** edge_j;
		Point3D** points_j[3];
		Point3D** point_i;
		for (unsigned int l = 1; l < Objects.size(); l++)
		{
			Edges.clear();
			Faces.clear();
			Points.clear();
			for (unsigned int i = 1; i < pVerts.size(); i++)//заполнение точек
			{
				point_i = new Point3D*;
				*point_i = new Point3D(pVerts[i].x, pVerts[i].y, pVerts[i].z);
				Points.push_back(point_i);
			}
			for (unsigned int i = 1; i < Objects[l].pFaces.size(); i++)
			{
				for (int j = 0; j < 3; j++)
				{
					if (Objects[l].pFaces[i].vi[j] - 1 < (int)Points.size())
						points_j[j] = Points.at(Objects[l].pFaces[i].vi[j] - 1);
					else
						points_j[j] = NULL;
				}

				edges_i.clear();
				for (int j = 0; j < 3; j++)
				{
					edge_j = new Edge*;
					*edge_j = new Edge(points_j[j], points_j[(j + 1)<3?(j + 1):0]);
					edges_i.push_back(edge_j);
					Edges.push_back(edge_j);
				}
				face_i = new Face*;
				*face_i = new Face(edges_i);
				Faces.push_back(face_i);
			}
			/*delete *Faces[Faces.size() - 1]; of test
			delete Faces[Faces.size() - 1];
			Faces.pop_back();*/
			object_l = new Object(&Points, &Edges, &Faces, Objects[l].strName);
			this->Objects.push_back(object_l);
		}
	}
}

void MR::Model::addFromGraph(const graph &Graph)
{
	Object *object();
}

void MR::Model::drawModel()
{
	for (Object* o : Objects)
		o->drawObject();
}

bool MR::Model::check()
{
	if (Objects.size() == 0)
		return false;
	for (Object *o : Objects)
		if (o->check() == false)
			return false;
	return true;
}

void MR::Model::uniqueObjects()
{
	for (Object *o : Objects)
		o->uniqueElements();
}

MR::Model* MR::Model::getModelTested3DObjects()
{
	Model* result = new Model();
	std::vector<MR::Object*>* Objects_t;
	MR::Object* obj_t;

	for (Object *o : Objects)
	{
		obj_t = o->getObjCleanedBoundaryFaces();//obj_t - копия, геометрическое тело или пустое тело
		if (obj_t->check() == true)
		{
			obj_t->uniqueElements();
			Objects_t = obj_t->get3DObjects();
			delete obj_t;
			if (Objects_t != NULL)
				if(Objects_t->size() > 0)
					for (Object *o_t : *Objects_t)
						result->Objects.push_back(o_t);
		}
	}
	return result;
}
