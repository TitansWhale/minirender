#pragma once
#include"myRendering.h"
template<class T>
class StaticAABBBox
{
public:
	//��һ����box����Сֵ���ڶ��������ֵ
	myVec4<T> min;
	myVec4<T> max;
	
	//���캯��
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
	//���������
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

	//��ѧ���㺯��
	const myVec4<T> getCentre()const 
	{
		myVec4<T> temp;
		temp = min + max;
		temp /= 2;
		return temp;
	}
	bool isectSegAABB(myRay<T> ray, T& tmin, T& tmax) const
	{
		myVec4<T> ptOnPlane; //�������Χ��ĳ��Ľ���
							 //Vec3 min = aabb._min; //aabb��Χ����С������
							 //Vec3 max = aabb._max; //aabb��Χ����������

		const myVec4<T>& origin = ray.o; //������ʼ��
		const myVec4<T>& dir = ray.d; //����ʸ��


		//�ֱ��ж������������ཻ���

		//�ж��������Χ��x�᷽������Ƿ��н���
		if ((fabs(dir.x)>eps)) //����x�᷽�������Ϊ0 �����߷���ʸ����x�����Ϊ0�����߲����ܾ�����Χ�г�x�᷽���������
		{
			/*
			ʹ��������ƽ���ཻ�Ĺ�ʽ�󽻵�
			*/
			if (dir.x > 0)//��������x��������ƫ��
				tmin = (min.x - origin.x) / dir.x;
			else  //������x�Ḻ����ƫ��
				tmin = (max.x - origin.x) / dir.x;

			if (tmin > 0.f) //t>0ʱ��������ƽ���ཻ
			{
				ptOnPlane = origin +  dir*tmin; //���㽻������
											  //�жϽ����Ƿ��ڵ�ǰ����
				if (min.y < ptOnPlane.y && ptOnPlane.y < max.y && min.z < ptOnPlane.z && ptOnPlane.z < max.z)
				{
					return true; //�������Χ���н���
				}
			}
		}

		//��������y�᷽���з��� �ж��Ƿ����Χ��y�᷽���н���
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

		//��������z�᷽���з��� �ж��Ƿ����Χ��y�᷽���н���
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

