#pragma once
#include"myCamera.h"
template<class T>
class myViewMesh
{
public:
	myVec4<T> o;											//�ӵ�
	myMat4<T> mat;											//���½�����ϵ�ı任����
	T WidthStep;
	T HightStep;

	//ȡ����������ߣ������Ǹ����ص�
	myRay<T> getRandRay(const int &x,const int &y)const 
	{
		//���ɿռ�����
		
		T tempX = x * WidthStep+(rand()/(float)RAND_MAX)*WidthStep;
		T tempY = y * HightStep+(rand() / (float)RAND_MAX)*HightStep;
		//���ɿռ��
		myVec4<T> retO(tempX, tempY, 0, 1);			//ƽ���ϵĵ�
		retO = retO * (mat);						//ת��Ϊ��������
		


		retO = retO - o;
		retO = retO.getNormal();					//ȡ������

		return myRay<T>(o, retO);						//��������
	}

	myViewMesh(const T &screenWidth, const T &screenHight,
			   const T &Width, const T &Hight,
			   const myCamera<T> &ca)
	{
		WidthStep = Width / screenWidth;
		HightStep = Hight / screenHight;

		o = ca.o1;							//�ӵ�
		mat = ca.getMat();
		mat=mat.tans();
	}
}; 