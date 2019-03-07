#pragma once

#include"myCamera.h"
#include"myViewMesh.h"
#include"myScence.h"
#include<vector>
using namespace std;
template <class T>
class myDevice
{
public:
	int screenWidth;
	int screenHight;
	myScence<T> *Scence;										//场景中的灯光物体等
	myCamera<T> *camera;										//照相机
	myViewMesh<T> *viewMesh;									//通过照相机生成的视平面网格
	vector<myVec4<T>> screenMemory;

	void init(int screenWidth_,
		int screenHight_,
		myScence<T> *Scence_,										//场景中的灯光物体等
		myCamera<T> *camera_,										//照相机
		myViewMesh<T> *viewMesh_									//通过照相机生成的视平面网格
		)
	{
		screenWidth = screenWidth_;
		screenHight = screenHight_;
		Scence = Scence_;
		camera = camera_;
		viewMesh = viewMesh_;
		screenMemory.resize(screenWidth*screenHight);
	}
	//渲染，深度，背景颜色

	void rendering(const int deep, const myVec4<T> backGroundColor)
	{
#pragma omp parallel for
			for (int i = 0; i < screenWidth; i++)
			{

				for (int j = 0; j < screenHight; j++)
				{


					myVec4<T> writeColor(0, 0, 0, 0);										//写入内存的颜色
					myRay<T> V = viewMesh->getRandRay(i, j);							//得出一个视线,从眼睛发出
					myGeometry<T> *tempPGoe = NULL;										//临时几何体指针
					myVec4<T> tempColor(0, 0, 0, 0);										//临时颜色

					T min;
					T max;

					if (Scence->hit(V, &tempPGoe, min, max))							//有焦点
					{
						tempPGoe->getspecColorPhong(1, Scence->Light, V, tempColor);

						writeColor = tempColor;
						tempColor.clear();

						for (int k = 1; k < deep; k++)
						{
							if (Scence->hit(V, &tempPGoe, min, max))
							{
								tempPGoe->getspecColorPhong(1.0 / deep, Scence->Light, V, tempColor);				//计算反射光颜色
								writeColor = writeColor + tempColor;
								writeColor.Set10();															//单位化
							}
							else
							{
								screenMemory[i*screenHight + j] = writeColor;								//写入反射颜色
							}
						}
						screenMemory[i*screenHight + j] = writeColor;
					}
					else
					{
						screenMemory[i*screenHight + j] = backGroundColor;
					}
				}
			}
		
	}
};