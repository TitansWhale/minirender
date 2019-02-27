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
	//���ó��������ɫ
	mySphere<T> phere(myVec4<T>(0,200, 0, 1),200);
	//box����ɫ
	myCube<T> cubeDown(myVec4<T>(-400, -20, -400, 1), myVec4<T>(400, 0, 400, 1));
	
	//������ɫ
	phere.color = myVec4<T>(1, 1, 1, 0);
	cubeDown.color  = myVec4<T>(0, 1, 0, 0);
	//���ûþ�����ϵ��
	phere.ka = 0.2;

	//��ӵ�����
	myScence<T> scence;
	scence.GeoList.push_back(&phere);
	scence.GeoList.push_back(&cubeDown);

	//��ӹ���
	myVec4<T> tempDir(0, -1, 0, 0);
	tempDir = tempDir.getNormal();
	scence.Light = myLightRay<T>(myVec4<T>(0, 600, 0, 1), tempDir, myVec4<T>());

	//���������
	myCamera<T> ca(myVec4<T>(0,300,-800,1), myVec4<T>(0,300,-400,1), myVec4<T>(0, 1, 0, 0),800,600);
	//��ƽ������
	myViewMesh<T> viewMesh(800, 600, 800, 600, ca);

	//dev��ʼ��
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