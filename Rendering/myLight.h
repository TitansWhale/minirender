#pragma once
#include"myRendering.h"

template <class T>
class myLightRay :public myRay<T>
{
public:
	myVec4<T> I;				//光强，rgb
	myLightRay(const myVec4<T> &o_, const myVec4<T> &d_, const myVec4<T> I_) :myRay<T>(o_, d_)
	{
		I = I_;
	}
	myLightRay()
	{

	}
	void setI(const T &i)
	{
		I.x = I.y = I.z = i;
	}
};
template <class T>
class myLight
{
public:
	myVec4<T> color;

	myLight(const myLight &light)
	{
		color = light.color;
	}
	myLight()
	{

	}

	const myLight & operator=(const myLight& light)
	{
		color = light.color;
	}
	virtual const myLightRay<T> getRadaten(const myVec4<T> &pos)const =0;
	
};


template <class T>
class myDotLight :public myLight<T>
{
public:
	myVec4<T> o;//光源坐标
	T a0;		//衰减度           1/a0+a1*d+a2*d^2
	T a1;
	T a2;
	myVec4<T> color;
	myDotLight(const myVec4<T> &color_ , const myVec4<T> &o_ , const T & a0_,const T &a1_,const T &a2_)
	{
		color = color_;
		o = o_;
		a0 = a0_;
		a1 = a1_;
		a2 = a2_;

	}
	myDotLight()
	{
		o.set(0,0,0,1);
		a0 = 1;
		a1 = 0;
		a2 = 0;
	}
	const myLightRay<T> getRadaten(const myVec4<T> &pos)const
	{
		//计算光照强度
		T tempD = pos.getDistance(o);
		T tempI =1 / (a0 + a1 * tempD + a2 * tempD*tempD);
		tempI = get0To1(tempI);
		myVec4<T> VecI(tempI,tempI, tempI,0);

		//计算光照方向
		myVec4<T> tempVec = pos - o;
		tempVec = tempVec.getNormal();
		
		


		return myLightRay<T>(o, tempVec,VecI) ;

	}
	

};

