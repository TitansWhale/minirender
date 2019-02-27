#include"myScence.h"
#include"myCube.h"
#include"myPhere.h"
#include"myDevice.h"
#include<graphics.h>
#include<fstream>

#define T double
int main()
{
	myDevice<T> dev;
	//设置场景球体红色
	mySphere<T> phere(myVec4<T>(0,200, 0, 1),200);
	//box是绿色
	myCube<T> cubeDown(myVec4<T>(-400, -20, -400, 1), myVec4<T>(400, 0, 400, 1));
	
	//设置颜色
	phere.color = myVec4<T>(1, 1, 1, 0);
	cubeDown.color  = myVec4<T>(0, 1, 0, 0);
	//设置幻境光照系数
	phere.ka = 0.2;

	//添加到场景
	myScence<T> scence;
	scence.GeoList.push_back(&phere);
	scence.GeoList.push_back(&cubeDown);

	//添加光照
	myVec4<T> tempDir(0, -1, 0, 0);
	tempDir = tempDir.getNormal();
	scence.Light = myLightRay<T>(myVec4<T>(0, 600, 0, 1), tempDir, myVec4<T>());

	//设置照相机
	myCamera<T> ca(myVec4<T>(0,300,-800,1), myVec4<T>(0,300,-400,1), myVec4<T>(0, 1, 0, 0),800,600);
	//视平面网格
	myViewMesh<T> viewMesh(800, 600, 800, 600, ca);

	//dev初始化
	dev.init(800,600,&scence,&ca,&viewMesh);
	dev.rendering(2, myVec4<T>(0, 0, 0, 0));

	

	initgraph(800, 600);

	for (int i = 0; i < dev.screenWidth; i++)
	{
		for (int j = 0; j < dev.screenHight; j++)
		{
			int temp = -j + 599;
			int x=dev.screenMemory[i*dev.screenHight + temp].toColorInt();
			
			putpixel(i, j, x);
		}
	}
	
	system("pause");
	closegraph();
}