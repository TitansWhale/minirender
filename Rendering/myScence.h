#pragma once
#include"myGeometry3d.h"
#include<vector>

using namespace std;



template<class T>
class myScence
{
public:
	vector<myGeometry<T > * > GeoList;
	myLightRay<T> Light;

	myScence()
	{

	}
	myScence(vector<myGeometry<T> > &GeoList_, myLight<T> & Light_)
	{
		GeoList = GeoList_l;
		Light = Light_;
	}

	void set(vector<myGeometry<T> > &GeoList_, myLight<T> & Light_)
	{
		GeoList = GeoList_l;
		Light = Light_;
	}
	//求出碰撞的物体,视线，几何体，min，max
	bool hit(const myRay<T> &ray, myGeometry<T> **geo, T &t1, T &t2)
	{
		t1 = 9999999999;
		t2 = 9999999999;

		bool retFlag = false;
		T tempT1;
		T tempT2;
		for (int i = 0; i < GeoList.size(); i++)//遍历所有找交点
		{
			if (GeoList[i]->isHit(ray,tempT1, tempT2))
			{	//找出最近的且大于0的
							
				
				if (tempT1 < t1&&tempT1>0)
				{
					*geo = GeoList[i];
					t1 = tempT1;
					t2 = tempT2;
					retFlag = true;
				}
			}
		}
		return retFlag;
	}
};


