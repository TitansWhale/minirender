#pragma once
#include"myRendering.h"
template <class T>
class myCamera
{
public:
	myVec4<T> o1;								//视点
	myVec4<T> o2;								//视平面中点
	
	myVec4<T> vecUp;							//上方向
	T Width;									//视平面宽度
	T Hight;									//视平面高度

												//默认构造函数
	/*myCamera()
	{

	}*/
												//一般构造函数
	//视点，视平面中点，上方向，宽，高
	myCamera(const myVec4<T> &o1_,const myVec4<T> &o2_,const  myVec4<T> &vecUp_,const T &width_,const T &Hight_)
	{
		o1 = o1_;
		o2 = o2_;
		vecUp = vecUp_;
		Width = width_;
		Hight = Hight_;
	}
												//取得变化矩阵
	const myMat4<T> getMat()const
	{
		myVec4<T> x;
		myVec4<T> y;
		myVec4<T> z = o2 - o1;
		
		z = z.getNormal();
		y = vecUp;

		x = y.cross(z);							//x与y叉乘
		y = z.cross(x);							//y与z叉乘

		y = y.getNormal();						//单位化
		x = x.getNormal();						//单位化

												//设置平移
		myVec4<T> r = o2;
		r.x = r.x-(Width / 2);
		r.y = r.y-(Hight / 2);

		myMat4<T> retMat;
		
		retMat.SetX(x);
		retMat.SetY(y);
		retMat.SetZ(z);
		retMat.SetR(r);
		
		return retMat;
	}
};

