#pragma once
#include"myCamera.h"
template<class T>
class myViewMesh
{
public:
	myVec4<T> o;											//视点
	myMat4<T> mat;											//左下角坐标系的变换矩阵
	T WidthStep;
	T HightStep;

	//取得随机的视线，输入那个像素点
	myRay<T> getRandRay(const int &x,const int &y)const 
	{
		//生成空间坐标
		
		T tempX = x * WidthStep+(rand()/(float)RAND_MAX)*WidthStep;
		T tempY = y * HightStep+(rand() / (float)RAND_MAX)*HightStep;
		//生成空间点
		myVec4<T> retO(tempX, tempY, 0, 1);			//平面上的点
		retO = retO * (mat);						//转化为世界坐标
		


		retO = retO - o;
		retO = retO.getNormal();					//取得向量

		return myRay<T>(o, retO);						//生成射线
	}

	myViewMesh(const T &screenWidth, const T &screenHight,
			   const T &Width, const T &Hight,
			   const myCamera<T> &ca)
	{
		WidthStep = Width / screenWidth;
		HightStep = Hight / screenHight;

		o = ca.o1;							//视点
		mat = ca.getMat();
		mat=mat.tans();
	}
}; 