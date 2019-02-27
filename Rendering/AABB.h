#pragma once
#include"myRendering.h"
template<class T>
class StaticAABBBox
{
public:
	//第一个是box的最小值，第二个是最大值
	myVec4<T> min;
	myVec4<T> max;
	
	//构造函数
	StaticAABBBox(const myVec4<T> &min_, const myVec4<T> &max_)
	{
		min = min_;
		max = max_;
	}
	StaticAABBBox()
	{
	}
	StaticAABBBox(const myVec4<T> *PointList, const int &count)
	{
		

		min = PointList[0];
		max = PointList[0];
		for (int i = 0; i < count - 1; i += 2)
		{
			if (i + 1 == count)
			{
				i--;
			}

			const myVec4<T> &d1 = PointList[i];
			const myVec4<T> &d2 = PointList[i + 1];
			//x
			if (d1.x > d2.x)
			{
				if (d1.data[0] > max.data[0]) max.data[0] = d1.data[0];
				if (d2.data[0] < min.data[0]) min.data[0] = d2.data[0];
			}
			else
			{
				if (d2.data[0] > max.data[0]) max.data[0] = d2.data[0];
				if (d1.data[0] < min.data[0]) min.data[0] = d1.data[0];
			}
			//y
			if (d1.data[1] > d2.data[1])
			{
				if (d1.data[1] > max.data[1]) max.data[1] = d1.data[1];
				if (d2.data[1] < min.data[1]) min.data[1] = d2.data[1];
			}
			else
			{
				if (d2.data[1] > max.data[1]) max.data[1] = d2.data[1];
				if (d1.data[1] < min.data[1]) min.data[1] = d1.data[1];
			}
			//z
			if (d1.data[2] > d2.data[2])
			{
				if (d1.data[2] > max.data[2]) max.data[2] = d1.data[2];
				if (d2.data[2] < min.data[2]) min.data[2] = d2.data[2];
			}
			else
			{
				if (d2.data[2] > max.data[2]) max.data[2] = d2.data[2];
				if (d1.data[2] < min.data[2]) min.data[2] = d1.data[2];
			}
		}
	}
	StaticAABBBox(const StaticAABBBox &box)
	{
		min = box.min;
		max = box.max;
	}
	//运算符重载
	friend ostream &operator<<(ostream &os, const StaticAABBBox &box)
	{
		os << "aabbBox";
		os << box.min;
		os << box.max;
		return os;
	}
	const StaticAABBBox operator =(const StaticAABBBox &box)
	{
		min = box.min;
		max = box.max;
	}

	//数学运算函数
	const myVec4<T> getCentre()const 
	{
		myVec4<T> temp;
		temp = min + max;
		temp /= 2;
		return temp;
	}
	bool isectSegAABB(myRay<T> ray, T& tmin, T& tmax) const
	{
		myVec4<T> ptOnPlane; //射线与包围盒某面的交点
							 //Vec3 min = aabb._min; //aabb包围盒最小点坐标
							 //Vec3 max = aabb._max; //aabb包围盒最大点坐标

		const myVec4<T>& origin = ray.o; //射线起始点
		const myVec4<T>& dir = ray.d; //方向矢量


		//分别判断射线与各面的相交情况

		//判断射线与包围盒x轴方向的面是否有交点
		if ((fabs(dir.x)>eps)) //射线x轴方向分量不为0 若射线方向矢量的x轴分量为0，射线不可能经过包围盒朝x轴方向的两个面
		{
			/*
			使用射线与平面相交的公式求交点
			*/
			if (dir.x > 0)//若射线沿x轴正方向偏移
				tmin = (min.x - origin.x) / dir.x;
			else  //射线沿x轴负方向偏移
				tmin = (max.x - origin.x) / dir.x;

			if (tmin > 0.f) //t>0时则射线与平面相交
			{
				ptOnPlane = origin +  dir*tmin; //计算交点坐标
											  //判断交点是否在当前面内
				if (min.y < ptOnPlane.y && ptOnPlane.y < max.y && min.z < ptOnPlane.z && ptOnPlane.z < max.z)
				{
					return true; //射线与包围盒有交点
				}
			}
		}

		//若射线沿y轴方向有分量 判断是否与包围盒y轴方向有交点
		if (fabs(dir.y)>eps)
		{
			if (dir.y > 0)
				tmin = (min.y - origin.y) / dir.y;
			else
				tmin = (max.y - origin.y) / dir.y;

			if (tmin > 0.f)
			{
				ptOnPlane = origin +  dir * tmin;

				if (min.z < ptOnPlane.z && ptOnPlane.z < max.z && min.x < ptOnPlane.x && ptOnPlane.x < max.x)
				{
					return true;
				}
			}
		}

		//若射线沿z轴方向有分量 判断是否与包围盒y轴方向有交点
		if (fabs(dir.z)>eps)
		{
			if (dir.z > 0)
				tmin = (min.z - origin.z) / dir.z;
			else
				tmin = (max.z - origin.z) / dir.z;

			if (tmin > 0.f)
			{
				ptOnPlane = origin +  dir * tmin ;

				if (min.x < ptOnPlane.x && ptOnPlane.x < max.x && min.y < ptOnPlane.y && ptOnPlane.y < max.y)
				{
					return true;
				}
			}
		}

		return false;
	}

	

};

