#pragma once
#include"myMath.h"
#include<iostream>
#include<graphics.h>
using namespace std;

template <class T>
class myVec4
{
public:

	T x;
	T y;
	T z;
	T r;
	//构造函数
	myVec4()
	{
		x = 0;
		y = 0;
		z = 0;
		r = 0;
	}
	myVec4(const T *da)
	{
		x = da[0];
		y = da[1];
		z = da[2];
		r = da[3];
	}
	myVec4(const myVec4 &vec)
	{
		x = vec.x;
		y = vec.y;
		z = vec.z;
		r = vec.r;
	}
	myVec4(const T x_, const T y_, const T z_, const T r_)
	{
		
		x = x_;
		y = y_;
		z = z_;
		r = r_;
	}

	//运算符重载
	inline const myVec4 &operator =(const myVec4 &vec)
	{
		x = vec.x;
		y = vec.y;
		z = vec.z;
		r = vec.r;
		return *this;
	}
	inline const myVec4 &operator =(const T *da)
	{
		x = da[0];
		y = da[1];
		z = da[2];
		r = da[3];
		return *this;
	}
	inline const myVec4 operator -(const myVec4 &vec)const
	{
		myVec4 temp;
		temp.x = x - vec.x;
		temp.y = y - vec.y;
		temp.z = z - vec.z;
		temp.r = r - vec.r;
		return temp;
	}
	inline const myVec4 operator -()const
	{
		return myVec4(-x, -y, -z, r);
	}
	inline const myVec4 operator +(const myVec4 &vec)const
	{
		myVec4 temp;
		temp.x = x + vec.x;
		temp.y = y + vec.y;
		temp.z = z + vec.z;
		temp.r = r + vec.r;
		return temp;
	}
	
	inline const myVec4 operator*(const T &t)const
	{
		myVec4 temp;
		temp.x = t * x;
		temp.y = t * y;
		temp.z = t * z;
		temp.r = t * r;
		return temp;
	}
	inline const myVec4 cross(const myVec4 &vec)const
	{
		myVec4 temp;
		temp.r = r;

		myVCross3<T>(&x, &vec.x, &temp.x);
		return temp;
	}

	inline const T dot(const myVec4 &vec)const
	{
		return myVDot3(&x, &vec.x);
	}

	inline const bool operator==(const myVec4 &vec)const
	{
		if (sgn(x - vec.x) != 0) return false;
		else if (sgn(y - vec.y) != 0) return false;
		else if (sgn(z - vec.z) != 0) return false;
		else if (sgn(r - vec.r) != 0) return false;
		return true;
	}
	/*//点乘
	inline const T *operator *(const myVec4 &vec)
	{
		T temp[4];
		temp[3] = data[3];
		myVCross3(data, vec.data, temp);
		return temp;
	}*/
	//输入输出
	void set(const T &x_, const T &y_, const T &z_, const T &r_)
	{
		x = x_;
		y = y_;
		z = z_;
		r = r_;
	}

	

	friend ostream &operator<<(ostream &os, const myVec4 &vec)
	{
		const T * data = &vec.x;
		for (int i = 0; i < 4; i++)
		{
			os << data[i]<<"\t";
		}
		os << endl;
		return os;
	}
	
	//数学运算
	inline const myVec4 getNormal()const
	{
		T temp[4];
		temp[3] = r;
		myVNormal3(&x, temp);
		return temp;
	}
	inline const float getLenth()const
	{
		return myVLenth3(&x);
	}
	inline const T getDistance(const myVec4 &vec)const
	{
		myVec4 temp;
		temp = vec - *this;
		return temp.getLenth();
	}
	void clear()
	{
		x = y = z = r = 0;
	}

	inline void Set10()
	{
		x = get0To1(x);
		y = get0To1(y);
		z = get0To1(z);
		r = get0To1(r);
	}
	inline int toColorInt()
	{
		int temp = 0;
		int r;
		int g;
		int b;
		r = get0To1(x) * 255;
		g = get0To1(y) * 255;
		b = get0To1(z) * 255;
		temp=RGB(r, g, b);
		return temp;
	}
};

template <class T>
class myMat4
{
public:
	T data[16];
	//构造函数
	myMat4(const myMat4 &Mat)
	{
		data[0] = Mat.data[0];
		data[1] = Mat.data[1];
		data[2] = Mat.data[2];
		data[3] = Mat.data[3];
		data[4] = Mat.data[4];
		data[5] = Mat.data[5];
		data[6] = Mat.data[6];
		data[7] = Mat.data[7];
		data[8] = Mat.data[8];
		data[9] = Mat.data[9];
		data[10] = Mat.data[10];
		data[11] = Mat.data[11];
		data[12] = Mat.data[12];
		data[13] = Mat.data[13];
		data[14] = Mat.data[14];
		data[15] = Mat.data[15];
	}
	myMat4()
	{
		data[0] = 0;
		data[1] = 0;
		data[2] = 0;
		data[3] = 0;
		data[4] = 0;
		data[5] = 0;
		data[6] = 0;
		data[7] = 0;
		data[8] = 0;
		data[9] = 0;
		data[10] = 0;
		data[11] = 0;
		data[12] = 0;
		data[13] = 0;
		data[14] = 0;
		data[15] = 1;
	}
	myMat4(const T *da)
	{
		data[0] = da[0];
		data[1] = da[1];
		data[2] = da[2];
		data[3] = da[3];
		data[4] = da[4];
		data[5] = da[5];
		data[6] = da[6];
		data[7] = da[7];
		data[8] = da[8];
		data[9] = da[9];
		data[10] = da[10];
		data[11] = da[11];
		data[12] = da[12];
		data[13] = da[13];
		data[14] = da[14];
		data[15] = da[15];
	}
	//运算符重载
	const myMat4 operator+(const myMat4 &mat)const
	{
		myMat4 temp;
		temp.data[0] = data[0] + mat.data[0];
		temp.data[1] = data[1] + mat.data[1];
		temp.data[2] = data[2] + mat.data[2];
		temp.data[3] = data[3] + mat.data[3];
		temp.data[4] = data[4] + mat.data[4];
		temp.data[5] = data[5] + mat.data[5];
		temp.data[6] = data[6] + mat.data[6];
		temp.data[7] = data[7] + mat.data[7];
		temp.data[8] = data[8] + mat.data[8];
		temp.data[9] = data[9] + mat.data[9];
		temp.data[10] = data[10] + mat.data[10];
		temp.data[11] = data[11] + mat.data[11];
		temp.data[12] = data[12] + mat.data[12];
		temp.data[13] = data[13] + mat.data[13];
		temp.data[14] = data[14] + mat.data[14];
		temp.data[15] = data[15] + mat.data[15];
		return 0;
	}
	const myMat4 operator-(const myMat4 &mat)const
	{
		myMat4 temp;
		temp.data[0] = data[0] - mat.data[0];
		temp.data[1] = data[1] - mat.data[1];
		temp.data[2] = data[2] - mat.data[2];
		temp.data[3] = data[3] - mat.data[3];
		temp.data[4] = data[4] - mat.data[4];
		temp.data[5] = data[5] - mat.data[5];
		temp.data[6] = data[6] - mat.data[6];
		temp.data[7] = data[7] - mat.data[7];
		temp.data[8] = data[8] - mat.data[8];
		temp.data[9] = data[9] - mat.data[9];
		temp.data[10] = data[10] - mat.data[10];
		temp.data[11] = data[11] - mat.data[11];
		temp.data[12] = data[12] - mat.data[12];
		temp.data[13] = data[13] - mat.data[13];
		temp.data[14] = data[14] - mat.data[14];
		temp.data[15] = data[15] - mat.data[15];
		return 0;
	}
	const myMat4 operator=(const myMat4 &mat)
	{
		data[0] = mat.data[0];
		data[1] = mat.data[1];
		data[2] = mat.data[2];
		data[3] = mat.data[3];
		data[4] = mat.data[4];
		data[5] = mat.data[5];
		data[6] = mat.data[6];
		data[7] = mat.data[7];
		data[8] = mat.data[8];
		data[9] = mat.data[9];
		data[10] = mat.data[10];
		data[11] = mat.data[11];
		data[12] = mat.data[12];
		data[13] = mat.data[13];
		data[14] = mat.data[14];
		data[15] = mat.data[15];
		return *this;
	}
	myMat4 operator=(const T &da)const
	{
		data[0] = da[0];
		data[1] = da[1];
		data[2] = da[2];
		data[3] = da[3];
		data[4] = da[4];
		data[5] = da[5];
		data[6] = da[6];
		data[7] = da[7];
		data[8] = da[8];
		data[9] = da[9];
		data[10] = da[10];
		data[11] = da[11];
		data[12] = da[12];
		data[13] = da[13];
		data[14] = da[14];
		data[15] = da[15];
	}
	inline const bool operator==(const myMat4 &mat)const
	{
		if (sgn(data[0] - vec.data[0]) != 0) return false;
		else if (sgn(data[1] - vec.data[1]) != 0) return false;
		else if (sgn(data[2] - vec.data[2]) != 0) return false;
		else if (sgn(data[3] - vec.data[3]) != 0) return false;
		else if (sgn(data[4] - vec.data[4]) != 0) return false;
		else if (sgn(data[5] - vec.data[5]) != 0) return false;
		else if (sgn(data[6] - vec.data[6]) != 0) return false;
		else if (sgn(data[7] - vec.data[7]) != 0) return false;
		else if (sgn(data[8] - vec.data[8]) != 0) return false;
		else if (sgn(data[9] - vec.data[9]) != 0) return false;
		else if (sgn(data[10] - vec.data[10]) != 0) return false;
		else if (sgn(data[11] - vec.data[11]) != 0) return false;
		else if (sgn(data[12] - vec.data[12]) != 0) return false;
		else if (sgn(data[13] - vec.data[13]) != 0) return false;
		else if (sgn(data[14] - vec.data[14]) != 0) return false;
		else if (sgn(data[15] - vec.data[15]) != 0) return false;
		return true;
	}

	//赋值函数
	void SetX(const myVec4<T> &x)
	{
		data[0] = x.x;
		data[1] = x.y;
		data[2] = x.z;

	}
	void SetY(const myVec4<T> &y)
	{
		data[4] = y.x;
		data[5] = y.y;
		data[6] = y.z;

	}
	void SetZ(const myVec4<T> &z)
	{
		data[8] = z.x;
		data[9] = z.y;
		data[10] = z.z;
	}
	void SetR(const myVec4<T> &r)
	{
		data[12] = r.x;
		data[13] = r.y;
		data[14] = r.z;
	}
	friend const myVec4<T> operator*(const myVec4<T> &vec, const myMat4<T> mat)
	{
		myVec4<T> temp;
		const T *Vdata=&vec.x;
		myVxM4(Vdata, mat.data, &temp.x);
		return temp;
	}

	friend ostream &operator<<(ostream &os,const myMat4 &mat)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				os << mat.data[i * 4 + j] << "\t";
			}
			os << endl;
		}
		return os;
	}
	//数学运算
	const myMat4 inv()const
	{
		myMat4 temp;
		invM(data, temp.data);
		return temp;
	}
	const myMat4 tans()const
	{
		myMat4 retMat=*this;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < i; j++)
			{
				swap(retMat.data[i * 4 + j], retMat.data[j * 4 + i]);
			}
		}
		return retMat;
	}
};



template <class T>
class myFace3
{
public:
	myVec4<T> p1;		//点
	myVec4<T> p2;
	myVec4<T> p3;
	myVec4<T> n;		//法向量（标记正方向）

	myFace3(const T *p1_, const T *p2_, const T *p3_, const T *n_)
	{
		p1 = p1_;
		p2 = p2_;
		p3 = p3_;
		n = n_;
	}
	myFace3(const myVec4<T> &p1_, const myVec4<T> &p2_,const myVec4<T> &p3_,const myVec4<T> &n_)
	{
		p1 = p1_;
		p2 = p2_;
		p3 = p3_;
		p4 = n_;
	}
	myFace3()
	{

	}

	void set(const T *p1_, const T *p2_, const T *p3_, const T *n_)
	{
		p1 = p1_;
		p2 = p2_;
		p3 = p3_;
		n = n_;
	}

	friend ostream &operator<<(ostream &os, const myFace3 &face)
	{
		const myVec4<T>* data = face.p1;
		for (int i = 0; i < 4; i++)
		{
			
			os << face.data[i];
		}
	
		return os;
	}
};

#define RAY_HIT  0
#define RAY_NOHIT -1

//第一个是原点第二个是向量
template <class T>
class myRay
{
public:
	myVec4<T> o; //第一个是原点
	myVec4<T> d;// 第二个是向量
	myRay()
	{

	}
	myRay(const myVec4<T> &o_, const myVec4<T> &d_)
	{
		o = o_;
		d = d_;
	}

	void set(const myVec4<T> &o_, const myVec4<T> d_)
	{
		o = o_;
		d = d_;
	}

	//表面求交运算，之判定是否在三角表面内部有焦点，没做平行检测
	int hit(const myFace3<T> &face, myVec4<T> &hitPoint)
	{ 
		hitPoint.clear();

		const myVec4<T> v1 = (face.data[1] - face.data[0]);
		const myVec4<T> v2 = (face.data[2] - face.data[0]);

		const myVec4<T> &o = data[0];
		const myVec4<T> &v = data[1];
		const myVec4<T> &p = face.data[0];

		T t2 = (v.cross(v1)).dot(o - p)/(v.cross(v1)).dot(v2);
		T t1 = (v.cross(v2)).dot(o - p) / (v.cross(v2)).dot(v1);
		
		
		if (t1 < 0 || t2 < 0)return RAY_NOHIT;
		else if (t1 + t2 > 1) return RAY_NOHIT;

		hitPoint = v1 * t1 + face.data[0] + v2 * t2;
		return RAY_HIT;
	}

};



//#include"myRendering.h"
//#include<iostream>
//#include<math.h>
//using namespace std;
//
//int main()
//{
//	/*float x[4] = { 1,2,3,4 };
//	
//	myVec4<float> vec1(x);
//	myVec4<float> vec;
//	vec= vec1;
//	myMat4<float> mat;
//
//	cout << vec << endl;
//	cout << mat;
//	
//	*/
//	myFace3<float> fa;
//	myVec4<float> fv1(0, 0, 0, 1);
//	myVec4<float> fv2(3,0 , 0, 1);
//	myVec4<float> fv3(0, 3, 0, 1);
//	myVec4<float> fn;
//
//	fn = (fv2 - fv1).cross(fv3 - fv1);
//	fn = fn.getNormal();
//
//	fa.data[0] = fv1;
//	fa.data[1] = fv2;
//	fa.data[2] = fv3;
//	fa.data[3] = fn;
//
//	fv1 = myVec4<float>(3, 3, -1, 1);
//	fv2 = myVec4<float>(0, 0, 1, 0);
//	myRay<float> ray(fv1,fv2);
//
//	ray.hit(fa, fv3);
//
//	cout << fa<<endl;
//	cout << fv3 << endl;
//
//	system("pause");
//	return 0;
//}
//j几何测试：
//       /*************** 2018 8 24 16：57
//myVec4<float> a(0, 0, 0, 1);
//myVec4<float> b(1, 1, 1, 1);
//myCube<float> cube(a, b);
//
//a = myVec4<float>(2, 2, 2, 1);
//b = myVec4<float>(3, 3, 3, 0);
//
//StaticAABBBox<float> box = cube.getAABBBox();
//myRay<float> ray(a, b);
//
//float aa;
//float bb;
//cout << box.isectSegAABB(ray, aa, bb);


