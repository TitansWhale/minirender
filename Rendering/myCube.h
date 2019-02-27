#pragma once
#include"myGeometry3d.h"
#include<math.h>
template<class T>
class myCube :public myGeometry<T>
{
public:
	myVec4<T> minPoint;
	myVec4<T> maxPoint;

	myCube()
	{
		minPoint.set(0, 0, 0, 1);
		maxPoint.set(1, 1, 1, 1);
	}
	myCube(const myVec4<T> &min, const myVec4<T> &max)
	{
		minPoint = min;
		maxPoint = max;
	}

	StaticAABBBox<T> getAABBBox()
	{
		return StaticAABBBox<T>(minPoint, maxPoint);
	}



	const myVec4<T> getN(myVec4<T> p)
	{
		if (sgn(p.x - minPoint.x) == 0) return myVec4<T>(-1, 0, 0, 0);
		if (sgn(p.x - maxPoint.x) == 0) return myVec4<T>(1, 0, 0, 0);

		if (sgn(p.y - minPoint.y) == 0) return myVec4<T>(0, -1, 0, 0);
		if (sgn(p.y - maxPoint.y) == 0) return myVec4<T>(0, 1, 0, 0);

		if (sgn(p.z - minPoint.z) == 0) return myVec4<T>(0, 0, -1, 0);
		if (sgn(p.z - maxPoint.z) == 0) return myVec4<T>(0, 0, 1, 0);

		return myVec4<T>(0, 0, 0, 0);
	}

	virtual bool isHit(myRay<T> ray, T &min, T &max)
	{
		StaticAABBBox<T> tempBox = getAABBBox();
		return tempBox.isectSegAABB(ray, min, max);
	}


	friend ostream &operator<<(ostream &os, const myCube &cb)
	{
		os << cb.minPoint;
		os << cb.maxPoint;
		return os;
	}

};