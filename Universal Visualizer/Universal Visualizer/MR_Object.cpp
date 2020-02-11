#include "stdafx.h"
#include "conversions.h"
#include "MR_Object.h"
#include "OpenGL funcs.h"

MR::Model::Object::Object()
{
	clearData();
	Color.setColor((rand() % 256) / 256, (rand() % 256) / 256, (rand() % 256) / 256);
}

MR::Model::Object::Object(const std::list<Face*>& Faces_i, string name)
{
	clearData();
	Color.setColor((rand() % 256) / 256, (rand() % 256) / 256, (rand() % 256) / 256);

	std::list<Edge*> Edges_i, Edges_temp;
	std::list<Geometry::Point3DCartesian*> Points_i, Points_temp;
	for (Face *f : Faces_i)
	{
		f->getEdges(Edges_temp);
		f->getPoints(Points_temp);
		for (Edge *e: Edges_temp)
			Edges_i.push_back(e);
		for (Geometry::Point3DCartesian *p : Points_temp)
			Points_i.push_back(p);
	}
	StrName = name;
	CopyUnique(Points_i, Edges_i, Faces_i);
	deleteNotUsedElements();
	clearNonexistent();
}

MR::Model::Object::Object(const std::list<Geometry::Point3DCartesian*> &Points_i, const std::list<Edge*> &Edges_i, const std::list<Face*> &Faces_i, string name)
{
	clearData();
	Color.setColor((rand() % 256) / 256, (rand() % 256) / 256, (rand() % 256) / 256);
	StrName = name;
	CopyUnique(Points_i, Edges_i, Faces_i);
	deleteNotUsedElements();
	clearNonexistent();
}

MR::Model::Object::Object(const Object & objectToCopy)
{
	clearData();
	Position = objectToCopy.getPos();
	Color.setColor((rand() % 256) / 256, (rand() % 256) / 256, (rand() % 256) / 256);
	StrName = objectToCopy.StrName;
	CopyUnique(objectToCopy.Points, objectToCopy.Edges, objectToCopy.Faces);
	deleteNotUsedElements();
	clearNonexistent();
}

MR::Model::Object::~Object()
{
	clearData();
}

bool MR::Model::Object::isEmpty()
{
	if (Points.size() < 1 || Edges.size() < 3 || Faces.size() < 1)
		return true;
	return false;
}

MR::Geometry::Point3DCartesian MR::Model::Object::getPos() const
{
	return Position;
}

void MR::Model::Object::setPos(Geometry::Point3DCartesian *pointIn)
{
	Position = *pointIn;
}

string MR::Model::Object::getStrName() const
{
	return StrName;
}

void MR::Model::Object::setStrName(string strIn)
{
	StrName = strIn;
}

void MR::Model::Object::drawObject()
{
	glPushMatrix();
	//glEnable(GL_TEXTURE_2D);
	glTranslated(Position.x(), Position.y(), Position.z());
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

	list<Geometry::Point3DCartesian*> drawnPoints_i;
	Geometry::Point3DCartesian *p1, *p2;
	list<Edge*> edges_i;
	double coef = 80.0;
	for (Face* f : Faces)
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

		f->getEdges(edges_i);
		drawnPoints_i.clear();
		const Geometry::Point3DCartesian tmpCenter = f->getCenterOfMass();

		glBegin(GL_POLYGON);
		glColor3d(
			counticolor(tmpCenter.x()*coef, tmpCenter.y()*coef, tmpCenter.z()*coef, 0),
			counticolor(tmpCenter.x()*coef, tmpCenter.y()*coef, tmpCenter.z()*coef, 1),
			counticolor(tmpCenter.x()*coef, tmpCenter.y()*coef, tmpCenter.z()*coef, 2));

		for (Edge *e: edges_i)
		{
			e->getPoints(&p1, &p2);
			if (searchPoint(drawnPoints_i, p1) == nullptr)
			{
				//glNormal3f(normal[0].x, normal[0].y, normal[0].z);
				glVertex3d(p1->x(), p1->y(), p1->z());
				drawnPoints_i.push_back(p1);
			}
			if (searchPoint(drawnPoints_i, p2) == nullptr)
			{
				//glNormal3f(normal[0].x, normal[0].y, normal[0].z);
				glVertex3d(p2->x(), p2->y(), p2->z());
				drawnPoints_i.push_back(p2);
			}
		}

		glEnd();
	}
	//glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

MR::Model::Object & MR::Model::Object::operator=(const Object & objToCopy)
{
	if (&objToCopy == this)
		return *this;

	clearData();
	Position = objToCopy.Position;
	Color.setColor((rand() % 256) / 256, (rand() % 256) / 256, (rand() % 256) / 256);
	StrName = objToCopy.StrName;
	CopyUnique(objToCopy.Points, objToCopy.Edges, objToCopy.Faces);

	return *this;
}

bool MR::Model::Object::check() const
{
	//минимальная фигура - треугольная пирамида, у которой 4 грани, 6 ребер и 4 точки
	if (Faces.size() < 4 || Edges.size() < 6 || Points.size() < 4)
		return false;
	return (!isAllFacesInOnePlane());
}

bool MR::Model::Object::isAllFacesInOnePlane() const
{
	bool allTheSame = true;
	Geometry::Vector3D normal = (*Faces.cbegin())->getNormal(), normal_t;
	std::list<Geometry::Point3DCartesian*> pointsTemp, pointsTemp_t;
	(*Faces.cbegin())->getPoints(pointsTemp);
	Geometry::Plane3D *planeTemp = new Geometry::Plane3D(normal, **pointsTemp.cbegin()), *planeTemp_i;
	for (Face *f : Faces)
	{
		normal_t = f->getNormal();
		f->getPoints(pointsTemp_t);
		planeTemp_i = new Geometry::Plane3D(normal_t, **pointsTemp_t.cbegin());
		if (planeTemp != planeTemp_i)
		{
			allTheSame = false;
			break;
		}
	}
	return allTheSame;
}

void MR::Model::Object::clearData()
{
	Position.set(0.0, 0.0, 0.0);
	for (Face *f: Faces)
		delete f;
	for (Edge *e: Edges)
		if (!e->existing())
			delete e;
	for (Geometry::Point3DCartesian *p: Points)
		if (!p->existing())
			delete p;
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

void MR::Model::Object::clearNonexistent()
{
	if (Edges.size() > 1)
		for (std::list<Edge*>::const_iterator iter = ++Edges.cbegin(); iter != Edges.cend(); iter++)
			if (!(*iter)->existing())
			{
				delete (*iter);
				iter = Edges.erase(iter);
				iter--;
			}
	if (!(*Edges.cbegin())->existing())
	{
		delete (*Edges.cbegin());
		Edges.erase(Edges.cbegin());
	}

	if (Points.size() > 1)
		for (std::list<Geometry::Point3DCartesian*>::const_iterator iter = ++Points.cbegin(); iter != Points.cend(); iter++)
			if (!(*iter)->existing())
			{
				delete (*iter);
				iter = Points.erase(iter);
				iter--;
			}
	if (!(*Points.cbegin())->existing())
	{
		delete (*Points.cbegin());
		Points.erase(Points.cbegin());
	}
}

void MR::Model::Object::CopyUnique(const std::list<Geometry::Point3DCartesian*> &Points_i, const std::list<Edge*> &Edges_i, const std::list<Face*> &Faces_i)
{
	Points.clear();
	Edges.clear();
	Faces.clear();
	for (Geometry::Point3DCartesian* p : Points_i)
	{
		if (p!= nullptr)
			Points.push_back(new Geometry::Point3DCartesian(*p));
	}
	uniquePoints(Points);

	Geometry::Point3DCartesian *p1, *p2;
	Edge *edge_i;
	for (Edge* e : Edges_i)
	{
		if (e == nullptr)
			continue;
		e->getPoints(&p1, &p2);
		p1 = searchPoint(Points, p1);
		p2 = searchPoint(Points, p2);
		if (p1 == nullptr || p2 == nullptr)
			continue;
		edge_i = new Edge(p1, p2);
		Edges.push_back(edge_i);
	}
	uniqueEdges(Edges);

	Face* face_i;
	list<Edge*> edges_temp, edges_i;
	for (Face *f : Faces_i)
	{
		if (f == nullptr)
			continue;
		edges_i.clear();
		f->getEdges(edges_temp);
		for (Edge* e_temp : edges_temp)
			for (Edge* e : Edges)
				if (e_temp != nullptr/* && e != nullptr*/)//e не может быть nullptr.
					if (*e == *e_temp)
						edges_i.push_back(e);
		face_i = new Face(edges_i);
		Faces.push_back(face_i);
	}
}

void MR::Model::Object::ReplaceNotUnique(Object &objectToCopy)
{
	Points.clear();
	Edges.clear();
	Faces.clear();
	for (Geometry::Point3DCartesian* p : objectToCopy.Points)
		Points.push_back(p);
	for (Edge* e : objectToCopy.Edges)
		Edges.push_back(e);
	for (Face* f : objectToCopy.Faces)
		Faces.push_back(f);
	objectToCopy.Points.clear();
	objectToCopy.Edges.clear();
	objectToCopy.Faces.clear();
}

void MR::Model::Object::deleteNotUsedElements()
{
	//удалить неиспользующиеся элементы
	//по определению все ребра используются, поэтому могут не использоваться только точки.
	//проверка на вхождение всех точек в полигоны. Обратное вхождение проверяется в check
	list<Geometry::Point3DCartesian*> PointsInFaces;
	list<Geometry::Point3DCartesian*> PointsTemp;
	for (Face *f : Faces)
	{
		f->getPoints(PointsTemp);
		for (Geometry::Point3DCartesian* p : PointsTemp)
			PointsInFaces.push_back(p);
	}

	if (Points.size() > 1)
		for (std::list<Geometry::Point3DCartesian*>::const_iterator iter = ++Points.cbegin(); iter != Points.cend(); iter++)
			if (searchPoint(PointsInFaces, *iter) == nullptr)
			{
				delete *iter;
				iter = Points.erase(iter);
				iter--;
			}
	//дополнительная проверка потому что если будет удаляться первый элемент,
	//iter присвоится новый cbegin, после которого нельзя применить iter--;
	if (searchPoint(PointsInFaces, *Points.cbegin()) == nullptr)
	{
		delete *Points.cbegin();
		Points.erase(Points.cbegin());
	}

	if (Points.size() == 0)
		System::Windows::Forms::MessageBox::Show(L"Ошибка на этапе унификации элементов.\nЕсли вы видите это сообщение, то программа работает некорректно.", L"Ошибка", System::Windows::Forms::MessageBoxButtons::OK, System::Windows::Forms::MessageBoxIcon::Warning);
}

void MR::Model::Object::clearSelection()
{
	for (Face *f : Faces)
		f->setFlag(false);
}

void MR::Model::Object::selectFaces(Face * face)
{
	if (face->flag() == true)
		return;
	else
	{
		face->setFlag(true);
		std::list<Edge*> edges_i;
		face->getEdges(edges_i);
		for (Edge *e_i : edges_i)//для каждого ребра текущей грани
			if (e_i->getCountIncludingInFaces() > 1)//у которой количество включающих граней больше 1
				for (Face *f : Faces)//ищем в каждом ребре всех граней
					if (f != face)//и если грань не текущая, то
					{
						std::list<Edge*> edges_j;
						f->getEdges(edges_j);
						for (Edge *e_j : edges_j)//ищем на совпадение каждое ребро в каждой грани
							if (e_j == e_i)//ребра совпали. f - найденная грань и ее нужно выделить
								selectFaces(f);
					}
	}
}

void MR::Model::Object::selectFaces(Face *face, const std::list<Face*> &Faces)
{
	if (face->flag() == true)
		return;
	else
	{
		face->setFlag(true);
		std::list<Edge*> edges_i;
		face->getEdges(edges_i);
		for (Edge *e_i : edges_i)//для каждого ребра текущей грани
			if (e_i->getCountIncludingInFaces() > 1)//у которой количество включающих граней больше 1
				for (Face *f : Faces)//ищем в каждом ребре всех граней
					if (f != face)//и если грань не текущая, то
					{
						std::list<Edge*> edges_j;
						f->getEdges(edges_j);
						for (Edge *e_j : edges_j)//ищем на совпадение каждое ребро в каждой грани
							if (e_j == e_i)//ребра совпали. f - найденная грань и ее нужно выделить
								selectFaces(f, Faces);
					}
	}
}

double MR::Model::Object::counticolor(double a, double b, double c, int k)
{//координаты текущей точки, i - номер цвета (0,1,2) в RGB_MR
	double res = 0.0;
	switch (TypeColor)
	{
	case 1:
	{
		return Color.getColor(k);
	}break;
	case 2:
	case 3://раскраска 4 цветами от dl,dr,ul,ur.
	{
		//расчет цвета текущего полигона
		double n = 1;//(вид сверху)
		double rastofdl = partofS(a, b, -razm / 2, razm / 2) / razm * n;//dl расстояние от текущей точки до нижнего левого угла(точка 1)
		double rastoful = partofS(a, b, -razm / 2, -razm / 2) / razm * n;//ul расстояние от текущей точки до верхнего левого угла(точка 2)
		double rastofur = partofS(a, b, razm / 2, -razm / 2) / razm * n;//ur расстояние от текущей точки до верхнего правого угла(точка 3)
		double rastofdr = partofS(a, b, razm / 2, razm / 2) / razm * n;//dr расстояние от текущей точки до нижнего правого угла(точка 4)
		double idl, iul, iur, idr;
		if (rastofdl > 1)
			idl = 0;
		else
			idl = ColorGrad[0].getColor(k)*(1 - rastofdl);//цвет от нижнего левого угла(1)

		if (rastoful > 1)
			iul = 0;
		else
			iul = ColorGrad[1].getColor(k)*(1 - rastoful);//цвет от верхнего левого угла(2)

		if (rastofur > 1)
			iur = 0;
		else
			iur = ColorGrad[2].getColor(k)*(1 - rastofur);//цвет от верхнего правого угла(3)

		if (rastofdr > 1)
			idr = 0;
		else
			idr = ColorGrad[3].getColor(k)*(1 - rastofdr);//цвет от нижнего правого угла(4)

		res = idl + iul + iur + idr;
		if (res > 1)
			return 1.0;
		else if (res < 0)
			return 0.0;
		else
			return res;
	}break;
	case 4:
	{//ландшафт. радуга от красного до фиолетового сверху вниз.
		double partofc = 1 - (c + double(razm) / 2.0) / double(razm);//расстояние до верха в кубе(от 0 до 1)
		int hi = partofc != 1 ? (int)floor(partofc * 6) : 5;//7 цветов. 6 отрезков. hi-номер отрезка сверху вниз. от 0 до 5. соответственно с верхним цветом отрезка.
		double mix = (partofc - double(hi)*0.1666667) * 6;
		res = ColorMix(ColorGradLand[hi].getColor(k), ColorGradLand[hi + 1].getColor(k), mix);
		return res;
	}break;
	default: return 0;
	}

}

void MR::Model::Object::uniquePoints(std::list<Geometry::Point3DCartesian*> &list)
{
	for (std::list<Geometry::Point3DCartesian*>::const_iterator p_i = list.cbegin(); p_i != list.cend(); p_i++)
	{
		for (std::list<Geometry::Point3DCartesian*>::const_iterator p_j = list.cbegin(); p_j != list.cend(); p_j++)
			if (p_i != p_j && **p_i == **p_j)
			{
				delete *p_j;
				p_j = list.erase(p_j);
				p_j--;
				(*p_i)->operator+=((*p_j)->getCountIncludingInEdges());
			}
	}
}

void MR::Model::Object::uniqueEdges(std::list<Edge*>& list)
{
	for (std::list<Edge*>::const_iterator e_i = list.cbegin(); e_i != list.cend(); e_i++)
	{
		for (std::list<Edge*>::const_iterator e_j = list.cbegin(); e_j != list.cend(); e_j++)
			if (e_i != e_j && **e_i == **e_j)
			{
				delete *e_j;
				e_j = list.erase(e_j);
				e_j--;
				(*e_i)->operator+=((*e_j)->getCountIncludingInFaces());
			}
	}
}