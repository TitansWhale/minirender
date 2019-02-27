#pragma once
#include"myRendering.h"
template <class T>
class myCamera
{
public:
	myVec4<T> o1;								//�ӵ�
	myVec4<T> o2;								//��ƽ���е�
	
	myVec4<T> vecUp;							//�Ϸ���
	T Width;									//��ƽ����
	T Hight;									//��ƽ��߶�

												//Ĭ�Ϲ��캯��
	/*myCamera()
	{

	}*/
												//һ�㹹�캯��
	//�ӵ㣬��ƽ���е㣬�Ϸ��򣬿���
	myCamera(const myVec4<T> &o1_,const myVec4<T> &o2_,const  myVec4<T> &vecUp_,const T &width_,const T &Hight_)
	{
		o1 = o1_;
		o2 = o2_;
		vecUp = vecUp_;
		Width = width_;
		Hight = Hight_;
	}
												//ȡ�ñ仯����
	const myMat4<T> getMat()const
	{
		myVec4<T> x;
		myVec4<T> y;
		myVec4<T> z = o2 - o1;
		
		z = z.getNormal();
		y = vecUp;

		x = y.cross(z);							//x��y���
		y = z.cross(x);							//y��z���

		y = y.getNormal();						//��λ��
		x = x.getNormal();						//��λ��

												//����ƽ��
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

