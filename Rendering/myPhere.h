#pragma once
#include"myGeometry3d.h"
template<class T>
class mySphere :public myGeometry<T>
{
public:
	myVec4<T> o;
	T r;

	mySphere(const myVec4<T> &o_, const T &r_)
	{
		o = o_;
		r = r_;

	}
	mySphere()
	{
		o = 0;
		r = 1;
	}
	//数学相关
	//计算法向量
	const myVec4<T> getN(myVec4<T> p)
	{
		myVec4<T> temp = p-o;
		temp = temp.getNormal();
		return temp;
	}
	StaticAABBBox<T> getAABBBox()
	{
		myVec4<T> temp(r, r, r, 0);
		myVec4<T> min = o - temp;
		myVec4<T> max = o + temp;

		return StaticAABBBox<T>(min, max);


	}
	bool isHit(const myRay<T> ray, T &min, T &max)//球的碰撞公式，（p-p0）^2-r^2=0  变换后解二次方程 计算机图形学p486
	{
		const myVec4<T> &u = -ray.d;
		myVec4<T> dp = ray.o - o;

		T temp = sqrt((u.dot(dp)*u.dot(dp)) - dp.dot(dp) + r * r);

		if (temp < 0) return false;

		min = u.dot(dp) + temp;
		max = u.dot(dp) - temp;

		if (min > max) swap(min, max);

		return true;
	}
};

