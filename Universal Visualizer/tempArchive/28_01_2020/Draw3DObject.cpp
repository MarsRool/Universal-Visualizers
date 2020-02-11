#include "stdafx.h"
#include "3DModel.h"

void t3DModel::DrawObj(int posx, int posy, int posz)
{
	glEnable(GL_TEXTURE_2D);
	glTranslatef(posx,posy,posz);

	//glColor3f(obj.TextureInf.color[0],obj.TextureInf.color[1],obj.TextureInf.color[2]);
	glColor3f(1.0f,1.0f,1.0f);

	CV3 vertex[3];
	CV2 texvert[3];
	CV3 normal[3];
	float rgb[3];
	int IDi=0;
	bool isttexture;
	const TextureImage *texturei;

	float black[]={0.0, 0.0, 0.0, 1.0};
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

	for (int l=1;l<=numOfObjects;l++)
		for (int i=1;i<=Objects[l].numFaces;i++)
		{
			isttexture=false;
			IDi=Objects[l].pFaces[i].Id_tex;
			for (int j=1;j<=numTex;j++)
				if (IDi==Textures[j].texureId) 
				{
					//цвета, освещение
					if (Textures[j].Ka.ist==true)
					{
						//ambient
						rgb[0]=Textures[j].Ka.rgb[0];
						rgb[1]=Textures[j].Ka.rgb[1];
						rgb[2]=Textures[j].Ka.rgb[2];
						float ambient[]={rgb[0],rgb[1],rgb[2],1.0};
						glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
					}
					else 
						glLightModelfv(GL_LIGHT_MODEL_AMBIENT, black);

					if  (Textures[j].Ka.texture.loaded==true)
					{
						texturei=&Textures[j].Ka.texture.image;//текстура
						glBindTexture(GL_TEXTURE_2D, texturei->texID);
						isttexture=true;
					}
				}

			for (int j=0;j<3;j++)
			{//координаты, нормали
				vertex[j].x=pVerts[Objects[l].pFaces[i].vi[j]].x;
				vertex[j].y=pVerts[Objects[l].pFaces[i].vi[j]].y;
				vertex[j].z=pVerts[Objects[l].pFaces[i].vi[j]].z;

				texvert[j].x=pTexVerts[Objects[l].pFaces[i].ti[j]].x;
				texvert[j].y=pTexVerts[Objects[l].pFaces[i].ti[j]].y;

				normal[j].x=pVerts[Objects[l].pFaces[i].ni[j]].x;
				normal[j].y=pVerts[Objects[l].pFaces[i].ni[j]].y;
				normal[j].z=pVerts[Objects[l].pFaces[i].ni[j]].z;
			}
			if (isttexture==false)//без текстуры с нормалью
			{
				glBegin(GL_TRIANGLES);
					glNormal3f(normal[0].x,normal[0].y,normal[0].z);
					glVertex3f(vertex[0].x,vertex[0].y,vertex[0].z);

					glNormal3f(normal[1].x,normal[1].y,normal[1].z);
					glVertex3f(vertex[1].x,vertex[1].y,vertex[1].z);

					glNormal3f(normal[2].x,normal[2].y,normal[2].z);
					glVertex3f(vertex[2].x,vertex[2].y,vertex[2].z);
				glEnd();
			}
			else//с текстурой и нормалью
			{
				glBegin(GL_TRIANGLES);
					glTexCoord2f(texvert[0].x,texvert[0].y);
					glNormal3f(normal[0].x,normal[0].y,normal[0].z);
					glVertex3f(vertex[0].x,vertex[0].y,vertex[0].z);

					glTexCoord2f(texvert[1].x,texvert[1].y);
					glNormal3f(normal[1].x,normal[1].y,normal[1].z);
					glVertex3f(vertex[1].x,vertex[1].y,vertex[1].z);

					glTexCoord2f(texvert[2].x,texvert[2].y);
					glNormal3f(normal[2].x,normal[2].y,normal[2].z);
					glVertex3f(vertex[2].x,vertex[2].y,vertex[2].z);
				glEnd();
			}
		}
	glDisable(GL_TEXTURE_2D);
}