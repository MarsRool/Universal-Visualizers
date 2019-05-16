#include "stdafx.h"
#include "conversions.h"
#include "3DModel.h"

void t3DModel::InitMaterial(tMaterialInfo &mat)
{
	mat.strName="";
	mat.texureId=0;
	mat.Ka.ist=false;
	mat.Ka.fileist=false;
	mat.Kd.ist=false;
	mat.Kd.fileist=false;
	mat.Ks.ist=false;
	mat.Ks.fileist=false;
	mat.Ke.ist=false;
	mat.Ke.fileist=false;
	mat.Ni=-1;
	mat.Ns=-1;
	mat.d=-1;
	mat.illum=-1;
}

void t3DModel::LoadMaterial(const char * path)
{
	FILE * file;
	fopen_s(&file, path, "r");
	if( file != NULL )
	{
		int IDi=0;//текущий ID текстуры
		char lineHeader[128];
		int res;
		char x[255];
		tMaterialInfo *Material_i = new tMaterialInfo();
		InitMaterial(*Material_i);
		Textures.push_back(*Material_i);
		while( 1 )
		{
			lineHeader[0]=0;
			res = fscanf_s(file, "%s", lineHeader, sizeof(lineHeader));
			if (res == EOF)
				break; // EOF =  онец файла. «аканчиваем цикл чтени€

			//новый материал
			if ( strcmp( lineHeader, "newmtl" ) == 0 )
			{
				res = fscanf_s(file, "%s\n", x, sizeof(x));
				string mati=x;
				if (res == 1 && mati!="")
				{
					bool Double=false;//true, если дубль
					int Double_i=0;//i дубл€
					for (int i=1;i<=numTex;i++)//проверка на дубли
						if (Textures[i].strName == mati)
						{
							Double = true;//дубль
							Double_i=i;//i дубл€
						}

					if ( Double == false )
					{
						//если уже считали материал, то добавить его в obj
						if (IDi>0)
						{
							tMaterialInfo *ti= new tMaterialInfo;
							*ti=*Material_i;
							if (Material_i->Ka.texture.loaded==true)
							{
								int count=0;
								while(Material_i->Ka.texture.image.imageData[count]!=0)
								{
									count++;
								}
								GLubyte* Ka = new GLubyte[count-1];
								for (int i=0;i<count-1;i++)
									Ka[i]=Material_i->Ka.texture.image.imageData[i];
								/*//memcpy(Ka,Material_i->Ka.texture.image.imageData,count-1);
									for (int i=0;i<count-1;i++)
										ti->Ka.texture.image.imageData[i]=Ka[i];
									//memcpy(ti->Ka.texture.image.imageData,Ka,count-1);*/
								ti->Ka.texture.image.imageData=Ka;
							}
							if (Material_i->Kd.texture.loaded==true)
							{
								int count=0;
								while(Material_i->Kd.texture.image.imageData[count]!=0)
								{
									count++;
								}
								GLubyte* Ka = new GLubyte[count-1];
								for (int i=0;i<count-1;i++)
									Ka[i]=Material_i->Kd.texture.image.imageData[i];
								ti->Kd.texture.image.imageData=Ka;
							}
							/*if (Material_i->Ks.texture.loaded==true)
								{
									int count=0;
									while(Material_i->Ks.texture.image.imageData[count]!=0)
									{
										count++;
									}
									GLubyte* Ka = new GLubyte[count-1];
									for (int i=0;i<count-1;i++)
										Ka[i]=Material_i->Ks.texture.image.imageData[i];
									ti->Ks.texture.image.imageData=Ka;
								}
								if (Material_i->Ke.texture.loaded==true)
								{
									int count=0;
									while(Material_i->Ke.texture.image.imageData[count]!=0)
									{
										count++;
									}
									GLubyte* Ka = new GLubyte[count-1];
									for (int i=0;i<count-1;i++)
										Ka[i]=Material_i->Ke.texture.image.imageData[i];
									ti->Ke.texture.image.imageData=Ka;
								}*/

							Textures.push_back(*ti);
							numTex++;
						}
						//идентификаци€ нового материала
						InitMaterial(*Material_i);
						Material_i->strName=mati;
						Material_i->texureId=numTex+1;
						IDi=numTex+1;
					}
				}
			}
			else if (IDi>0)
			{
				if ( strcmp( lineHeader, "Ka" ) == 0 )
				{
					TK &col=Material_i->Ka;
					res = fscanf_s(file, "%f %f %f\n", &col.rgb[0], &col.rgb[1], &col.rgb[2] );
					col.ist=true;
				}
				else if ( strcmp( lineHeader, "Kd" ) == 0 )
				{
					TK &col=Material_i->Kd;
					res = fscanf_s(file, "%f %f %f\n", &col.rgb[0], &col.rgb[1], &col.rgb[2] );
					col.ist=true;
				}
				/*else if ( strcmp( lineHeader, "Ks" ) == 0 )
				{
					TK &col=Material_i->Ks;
					res = fscanf_s(file, "%f %f %f\n", &col.rgb[0], &col.rgb[1], &col.rgb[2] );
					col.ist=true;
				}
				else if ( strcmp( lineHeader, "Ke" ) == 0 )
				{
					TK &col=Material_i->Ke;
					res = fscanf_s(file, "%f %f %f\n", &col.rgb[0], &col.rgb[1], &col.rgb[2] );
					col.ist=true;
				}*/
				else if ( strcmp( lineHeader, "Ni" ) == 0 )
				{
					res = fscanf_s(file, "%f\n", &Material_i->Ni);
				}
				else if ( strcmp( lineHeader, "Ns" ) == 0 )
				{
					res = fscanf_s(file, "%f\n", &Material_i->Ns);
				}
				else if ( strcmp( lineHeader, "d" ) == 0 )
				{
					res = fscanf_s(file, "%f\n", &Material_i->d);
				}
				else if ( strcmp( lineHeader, "illum" ) == 0 )
				{
					res = fscanf_s(file, "%i\n", &Material_i->illum);
				}
				else if ( strcmp( lineHeader, "map_Ka" ) == 0 )
				{
					res = fscanf_s(file, "%s\n", x, sizeof(x));
					if (res == 1 && x!="")
					{
						Material_i->Ka.fileist=true;
						//Material_i.Ka.strFile=x;
						Material_i->Ka.texture.LoadTexture(x,Material_i->Ka.texture.image, Material_i->Ka.texture.loaded);
					}
				}
				else if ( strcmp( lineHeader, "map_Kd" ) == 0 )
				{
					res = fscanf_s(file, "%s\n", x, sizeof(x));
					if (res == 1 && x!="")
					{
						Material_i->Kd.fileist=true;
						//Material_i.Kd.strFile=x;
						Material_i->Kd.texture.LoadTexture(x,Material_i->Kd.texture.image, Material_i->Kd.texture.loaded);
					}
				}
				/*else if ( strcmp( lineHeader, "map_Ks" ) == 0 )
				{
					res = fscanf_s(file, "%s\n", &x);
					if (res == 1 && x!="")
					{
						Material_i->Ks.fileist=true;
						//Material_i.Ks.strFile=x;
						Material_i->Ks.texture.LoadTexture(x,Material_i->Ks.texture.image, Material_i->Ks.texture.loaded);
					}
				}
				else if ( strcmp( lineHeader, "map_Ke" ) == 0 )
				{
					res = fscanf_s(file, "%s\n", &x);
					if (res == 1 && x!="")
					{
						Material_i->Ke.fileist=true;
						//Material_i.Ke.strFile=x;
						Material_i->Ke.texture.LoadTexture(x,Material_i->Ke.texture.image, Material_i->Ke.texture.loaded);
					}
				}*/
			}
		}
		tMaterialInfo *ti= new tMaterialInfo;
		*ti=*Material_i;
		if (Material_i->Ka.texture.loaded==true)
		{
			int count=0;
			while(Material_i->Ka.texture.image.imageData[count]!=0)
			{
				count++;
			}
			if (count>0)
			{
				GLubyte* Ka = new GLubyte[count-1];
				for (int i=0;i<count-1;i++)
					Ka[i]=Material_i->Ka.texture.image.imageData[i];
				ti->Ka.texture.image.imageData=Ka;
			}
		}
		if (Material_i->Kd.texture.loaded==true)
		{
			int count=0;
			while(Material_i->Kd.texture.image.imageData[count]!=0)
			{
				count++;
			}
			if (count>0)
			{
				GLubyte* Ka = new GLubyte[count-1];
				for (int i=0;i<count-1;i++)
					Ka[i]=Material_i->Kd.texture.image.imageData[i];
				ti->Kd.texture.image.imageData=Ka;
			}
		}
		/*if (Material_i->Ks.texture.loaded==true)
		{
			int count=0;
			while(Material_i->Ks.texture.image.imageData[count]!=0)
			{
				count++;
			}
			if (count>0)
			{
				GLubyte* Ka = new GLubyte[count-1];
				for (int i=0;i<count-1;i++)
					Ka[i]=Material_i->Ks.texture.image.imageData[i];
				ti->Ks.texture.image.imageData=Ka;
				}
		}
		if (Material_i->Ke.texture.loaded==true)
		{
			int count=0;
			while(Material_i->Ke.texture.image.imageData[count]!=0)
			{
				count++;
			}
			if (count>0)
			{
				GLubyte* Ka = new GLubyte[count-1];
				for (int i=0;i<count-1;i++)
					Ka[i]=Material_i->Ke.texture.image.imageData[i];
				ti->Ke.texture.image.imageData=Ka;
			}
		}*/
		Textures.push_back(*ti);
		numTex++;
	}
}