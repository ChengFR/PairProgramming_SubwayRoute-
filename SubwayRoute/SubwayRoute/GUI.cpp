#include <GL/glut.h>
#include <windows.h>
#include <math.h>
#include <string>
#include <iostream>
#include "ReadMap.h"
using namespace std;

ReadMap rm;
vector<string> route;
const int n = 50;
const GLfloat R = 0.01f;
const GLfloat Pi = 3.1415926536f;

void init(ReadMap Rm, vector<string> Route) {
	rm = Rm;
	route = Route;
}

void drawPoint() {
	int i = 0;
	for(i=0;i<rm.stationQueen.size();i++){
		
	}
}

void drawLine() {

}

void drawRoute() {

}

void display(int argc, char *argv[]) {
	//初始化
	glutInit(&argc, argv);
	//颜色模式，缓冲模式
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	//设置初始窗口的位置(窗口左上角相对于桌面坐标(x,y))，单位是像素
	glutInitWindowPosition(300, 200);
	//窗口大小
	glutInitWindowSize(600, 600);
	//创建窗口，参数是窗口名
	glutCreateWindow("beijing subway");
	//调用画图方法
	glutDisplayFunc(&drawPoint);
	glutDisplayFunc(&drawLine);
	glutDisplayFunc(&drawRoute);

	//结束
	glutMainLoop();
}


