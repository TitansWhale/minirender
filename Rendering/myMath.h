#pragma once
#include<math.h>

/*************************************************************************
//三维相关函数，可以用作四维
//三维矩阵采用横向量
**************************************************************************/
const float eps = 1e-6;
int sgn(double d) {
	return d<-eps ? -1 : d>eps;
}

//c叉乘
template <class T>
inline void myVCross3(const T *a,const T *b, T *out)
{
	
	out[0] = a[1] * b[2] - a[2] * b[1];
	out[1] = a[2] * b[0] - a[0] * b[2];
	out[2] = a[0] * b[1] - a[1] * b[0];

}
//点乘
template <class T>
inline T myVDot3(T *a, T *b)
{
	return (a[0] * b[0] + a[1] * b[1] + a[2] * b[2]);
}
//求单位向量
template <class T>
inline void myVNormal3(const T *a, T *out)
{
	float y;
	float scale;
	int k;
	float absxk;
	float t;
	y = 0.0F;
	scale = 1.29246971E-26F;
	for (k = 0; k < 3; k++) {
		absxk = (float)fabs(a[k]);
		if (absxk > scale) {
			t = scale / absxk;
			y = 1.0F + y * t * t;
			scale = absxk;
		}
		else {
			t = absxk / scale;
			y += t * t;
		}
	}

	y = scale * (float)sqrt(y);
	for (k = 0; k < 3; k++) {
		out[k] = a[k] / y;
	}
}
//求向量的长度
template <class T>
inline float myVLenth3(const T *a)
{
	float out;
	float scale;
	int k;
	float absxk;
	float t;
	out = 0.0F;
	scale = 1.29246971E-26F;
	for (k = 0; k < 3; k++) {
		absxk = (float)fabs(a[k]);
		if (absxk > scale) {
			t = scale / absxk;
			out = 1.0F + out * t * t;
			scale = absxk;
		}
		else {
			t = absxk / scale;
			out += t * t;
		}
	}

	return scale * (float)sqrt(out);
}
//向量乘以矩阵
template <class T>
inline void myVxM3(const T v[3], const T m[9], T out[3])
{
	int i0;
	int i1;
	float tempOut[3];
	for (i0 = 0; i0 < 3; i0++) {
		tempOut[i0] = 0.0F;
		for (i1 = 0; i1 < 3; i1++) {
			tempOut[i0] += v[i1] * m[i1 + 3 * i0];
		}
	}
	out[0] = tempOut[0];
	out[1] = tempOut[1];
	out[2] = tempOut[2];
}

/*************************************************************************
//四维维相关函数
**************************************************************************/
template <class T>
inline void myVxM4(const T v[4], const T m[16], T out[4])
{
	int i0;
	int i1;
	float tempOut[4];
	for (i0 = 0; i0 < 4; i0++) {
		tempOut[i0] = 0.0F;
		for (i1 = 0; i1 < 4; i1++) {
			tempOut[i0] += v[i1] * m[i1 + (i0 << 2)];
		}
	}
	out[0] = tempOut[0];
	out[1] = tempOut[1];
	out[2] = tempOut[2];
	out[3] = tempOut[3];
}

template <class T>
inline void myMxM4(const T m1[16], const T m2[16], T out[16])
{
	int i0;
	int i1;
	int i2;
	for (i0 = 0; i0 < 4; i0++) {
		for (i1 = 0; i1 < 4; i1++) {
			out[i0 + (i1 << 2)] = 0.0F;
			for (i2 = 0; i2 < 4; i2++) {
				out[i0 + (i1 << 2)] += m1[i0 + (i2 << 2)] * m2[i2 + (i1 << 2)];
			}
		}
	}
}

template <class T>
inline void myMaddM4(const T m1[16], const T m2[16], T out[16])
{
	out[0] = m1[0] + m2[0];
	out[1] = m1[1] + m2[1];
	out[2] = m1[2] + m2[2];
	out[3] = m1[3] + m2[3];
	out[4] = m1[4] + m2[4];
	out[5] = m1[5] + m2[5];
	out[6] = m1[6] + m2[6];
	out[7] = m1[7] + m2[7];
	out[8] = m1[8] + m2[8];
	out[9] = m1[9] + m2[9];
	out[10] = m1[10] + m2[10];
	out[11] = m1[11] + m2[11];
	out[12] = m1[12] + m2[12];
	out[13] = m1[13] + m2[13];
	out[14] = m1[14] + m2[14];
	out[15] = m1[15] + m2[15];
}

template <class T>
inline void myMSubM4(const T m1[16], const T m2[16], T out[16])
{
	out[0] = m1[0] - m2[0];
	out[1] = m1[1] - m2[1];
	out[2] = m1[2] - m2[2];
	out[3] = m1[3] - m2[3];
	out[4] = m1[4] - m2[4];
	out[5] = m1[5] - m2[5];
	out[6] = m1[6] - m2[6];
	out[7] = m1[7] - m2[7];
	out[8] = m1[8] - m2[8];
	out[9] = m1[9] - m2[9];
	out[10] = m1[10] - m2[10];
	out[11] = m1[11] - m2[11];
	out[12] = m1[12] - m2[12];
	out[13] = m1[13] - m2[13];
	out[14] = m1[14] - m2[14];
	out[15] = m1[15] - m2[15];
}

template <class T>
void invM(const T x[16], T out[16])
{
  int i0;
  float b_x[16];
  int j;
  signed char ipiv[4];
  int c;
  int iy;
  int k;
  signed char p[4];
  int ix;
  float smax;
  float s;
  int jy;
  int i;
  for (i0 = 0; i0 < 16; i0++) {
    out[i0] = 0.0F;
    b_x[i0] = x[i0];
  }

  for (i0 = 0; i0 < 4; i0++) {
    ipiv[i0] = (signed char)(1 + i0);
  }

  for (j = 0; j < 3; j++) {
    c = j * 5;
    iy = 0;
    ix = c;
    smax = (float)fabs(b_x[c]);
    for (k = 2; k <= 4 - j; k++) {
      ix++;
      s = (float)fabs(b_x[ix]);
      if (s > smax) {
        iy = k - 1;
        smax = s;
      }
    }

    if (b_x[c + iy] != 0.0F) {
      if (iy != 0) {
        ipiv[j] = (signed char)((j + iy) + 1);
        ix = j;
        iy += j;
        for (k = 0; k < 4; k++) {
          smax = b_x[ix];
          b_x[ix] = b_x[iy];
          b_x[iy] = smax;
          ix += 4;
          iy += 4;
        }
      }

      i0 = (c - j) + 4;
      for (i = c + 1; i + 1 <= i0; i++) {
        b_x[i] /= b_x[c];
      }
    }

    iy = c;
    jy = c + 4;
    for (i = 1; i <= 3 - j; i++) {
      smax = b_x[jy];
      if (b_x[jy] != 0.0F) {
        ix = c + 1;
        i0 = (iy - j) + 8;
        for (k = 5 + iy; k + 1 <= i0; k++) {
          b_x[k] += b_x[ix] * -smax;
          ix++;
        }
      }

      jy += 4;
      iy += 4;
    }
  }

  for (i0 = 0; i0 < 4; i0++) {
    p[i0] = (signed char)(1 + i0);
  }

  for (k = 0; k < 3; k++) {
    if (ipiv[k] > 1 + k) {
      iy = p[ipiv[k] - 1];
      p[ipiv[k] - 1] = p[k];
      p[k] = (signed char)iy;
    }
  }

  for (k = 0; k < 4; k++) {
    c = p[k] - 1;
    out[k + ((p[k] - 1) << 2)] = 1.0F;
    for (j = k; j + 1 < 5; j++) {
      if (out[j + (c << 2)] != 0.0F) {
        for (i = j + 1; i + 1 < 5; i++) {
          out[i + (c << 2)] -= out[j + (c << 2)] * b_x[i + (j << 2)];
        }
      }
    }
  }

  for (j = 0; j < 4; j++) {
    iy = j << 2;
    for (k = 3; k >= 0; k--) {
      jy = k << 2;
      if (out[k + iy] != 0.0F) {
        out[k + iy] /= b_x[k + jy];
        for (i = 0; i + 1 <= k; i++) {
          out[i + iy] -= out[k + iy] * b_x[i + jy];
        }
      }
    }
  }
}

//向量相关
template <class T>
inline void myVAdd4(const T a[4], const T b[4], T out[4])
{
	out[0] = a[0] + b[0];
	out[1] = a[1] + b[1];
	out[2] = a[2] + b[2];
	out[3] = a[3] + b[3];
}

template <class T>
inline void myVSub4(const T a[4], const T b[4], T out[4])
{
	out[0] = a[0] - b[0];
	out[1] = a[1] - b[1];
	out[2] = a[2] - b[2];
	out[3] = a[3] - b[3];
}

template <class T>
void getCameraSpace(T *o, T *vector, T *up, T *out)
{
	//第一行
	myVCross3(up, vector, out);
	out[3] = 0;
	//第二行
	myVCross3(vector, out, out + 4);
	out[7] = 0;
	//第三行
	out[8] = vector[0];
	out[9] = vector[1];
	out[10] = vector[2];
	out[11] = 0;
	//第四行
	out[12] = -o[0];
	out[13] = -o[1];
	out[14] = -o[2];
	out[15] = 1;
}
 
template <class T>
T get0To1(const T &data)
{
	return data < 0 ? 0 : data>1 ? 1 : data;
}


/**************************************************************************
//渲染相关
***************************************************************************/
//获得坐标空间的b变换矩阵
