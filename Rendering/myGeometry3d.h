#pragma once

#include"AABB.h"
#include"myLight.h"



template<class T>
class myGeometry
{
public:

	myVec4 <T> color;

	
	T ns = 1;//�⻬��   1�������
	T ka = 0.3;//�������ǿϵ��

	virtual StaticAABBBox<T> getAABBBox() = 0;

	virtual bool isHit(myRay<T> ray, T &min, T &max) = 0;			//�Ƿ���ײ
	virtual const myVec4<T> getN(myVec4<T> p) = 0;			//ȡ�÷����������뽻��
	
	



	//���߷������⣬���շ������ڣ�������ɫ
	virtual bool getspecColorPhong(const T &ks,const myLightRay<T> &lightRay, myRay<T> &V, myVec4<T> &I)
	{
		T min;
		T max;
 		if (isHit(V, min, max))				//����н��㷵����ɫ
		{
			myVec4<T> HitPoint = V.o + V.d*min;		//���㽻��
			myVec4<T> N = getN(HitPoint);				//���㷨����			
			myVec4<T> L = -lightRay.d;					//���շ�����
			myVec4<T> R = ((N*2.0f).cross(L)).cross(N) - L;		//���շ��䷽��
			
			T VR = V.d.dot(R);
			T resultVR = 1;
			for (int i = 0; i < ns; i++)
			{
				resultVR *= VR;
			}
			T kd = 1 - ka;
			T result=get0To1(ks*resultVR);						//���ط�����ɫ
			I = color * (result+ka);

			

			I.Set10();
			
			V.o = HitPoint;
			V.d = ((N*2.0f).cross(V.d)).cross(N) - V.d;
			return true;
		}
		else
		{
			return false;
		}
	}

//	virtual bool getspecColorPhong(const myLightRay<T> &lightRay, const myVec4<T> &V, myVec4<T> &colorf)										//������ɫ
//	{
//		colorf.clear();
//		T min;
//		T max;
//		if (isHit(lightRay, min, max))
//		{
//			myVec4<T> HitPoint = lightRay.o + lightRay.d*min;
//			myVec4<T> N = getN(HitPoint);
//			myVec4<T> L = -lightRay.d;
//			myVec4<T> R = N * (2 * N.cross(L)) - L;
//
//			myVec4<T> VR = V.cross(R);
//			T resultVR = 1;
//			for (int i = 0; i < ns; i++)
//			{
//				resultVR *= VR;
//			}
//
//			myVec4<T> colorf = lightRay.I*(ka*resultVR);
//			colorf.x = colorf.x*color.x;
//			colorf.y = colorf.y*color.y;
//			colorf.z = colorf.x*color.z;
//			return true;
//		}
//		else
//		{
//			return false;
//		}
//	}
//	virtual const myVec4<T> getN(myVec4<T> p) = 0;
//	
};

//minPoint   maxPoint


//template<class T>
//class myEllipsoid :public myGeometry<T>
//{
//public:
//	myVec4<T> o;
//	T a;				//X��
//	T b;				//Y��
//	T c;				//Z��
//
//	//���캯��
//	myEllipsoid(const myVec4<T> &o_,const T &a, const T &b, const T &c)
//	{
//
//	}
//	myEllipsoid()
//	{
//		myVec4 o(0, 0, 0, 1);
//		a = 0; b = 0; c = 0;
//	}
//	
//	//���������
//	friend ostream &operator<<(ostream &os, const myEllipsoid &ell)
//	{
//		os <<"o="<< o;
//		os << "a=" << a << "b=" << b << "c=" << c << endl;
//	}
//	const myEllipsoid &operator=(const myEllipsoid &ell)const
//	{
//		o = ell.o;
//		a = ell.a;
//		b = ell.b;
//		c = ell.c;
//		return *this;
//	}
//	
//	//��ѧ�������
//	StaticAABBBox<T> getAABBBox()
//	{
//		myVec4<T> minPoint(a, b, c, 0);
//		myVec4<T> maxPoint(a, b, c, 0);
//
//		minPoint = o - minPoint;
//		maxPoint = o - maxPoint;
//
//		return StaticAABBBox<T>(minPoint, maxPoint);
//	}
//	
//};
//
//template<class T>
//class cylinder :public myGeometry<T>
//{
//	myVec4<T> o;
//	T height;
//	T radius;
//
//	cylinder(const myVec4<T> &o_,const T & height_,const T & radius_)
//	{
//		o = o_;
//		height = height_;
//		radius = radius_;
//	}
//
//	cylinder()
//	{
//		myVec4 o(0,0,0,1);
//		height=1;
//		radius=1;
//	}
//};


