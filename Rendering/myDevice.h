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
	myScence<T> *Scence;										//�����еĵƹ������
	myCamera<T> *camera;										//�����
	myViewMesh<T> *viewMesh;									//ͨ����������ɵ���ƽ������
	vector<myVec4<T>> screenMemory;

	void init(int screenWidth_,
		int screenHight_,
		myScence<T> *Scence_,										//�����еĵƹ������
		myCamera<T> *camera_,										//�����
		myViewMesh<T> *viewMesh_									//ͨ����������ɵ���ƽ������
		)
	{
		screenWidth = screenWidth_;
		screenHight = screenHight_;
		Scence = Scence_;
		camera = camera_;
		viewMesh = viewMesh_;
		screenMemory.resize(screenWidth*screenHight);
	}
	//��Ⱦ����ȣ�������ɫ

	void rendering(const int deep, const myVec4<T> backGroundColor)
	{
#pragma omp parallel for
			for (int i = 0; i < screenWidth; i++)
			{

				for (int j = 0; j < screenHight; j++)
				{


					myVec4<T> writeColor(0, 0, 0, 0);										//д���ڴ����ɫ
					myRay<T> V = viewMesh->getRandRay(i, j);							//�ó�һ������,���۾�����
					myGeometry<T> *tempPGoe = NULL;										//��ʱ������ָ��
					myVec4<T> tempColor(0, 0, 0, 0);										//��ʱ��ɫ

					T min;
					T max;

					if (Scence->hit(V, &tempPGoe, min, max))							//�н���
					{
						tempPGoe->getspecColorPhong(1, Scence->Light, V, tempColor);

						writeColor = tempColor;
						tempColor.clear();

						for (int k = 1; k < deep; k++)
						{
							if (Scence->hit(V, &tempPGoe, min, max))
							{
								tempPGoe->getspecColorPhong(1.0 / deep, Scence->Light, V, tempColor);				//���㷴�����ɫ
								writeColor = writeColor + tempColor;
								writeColor.Set10();															//��λ��
							}
							else
							{
								screenMemory[i*screenHight + j] = writeColor;								//д�뷴����ɫ
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