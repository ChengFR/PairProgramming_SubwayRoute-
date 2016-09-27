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
	//��ʼ��
	glutInit(&argc, argv);
	//��ɫģʽ������ģʽ
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	//���ó�ʼ���ڵ�λ��(�������Ͻ��������������(x,y))����λ������
	glutInitWindowPosition(300, 200);
	//���ڴ�С
	glutInitWindowSize(600, 600);
	//�������ڣ������Ǵ�����
	glutCreateWindow("beijing subway");
	//���û�ͼ����
	glutDisplayFunc(&drawPoint);
	glutDisplayFunc(&drawLine);
	glutDisplayFunc(&drawRoute);

	//����
	glutMainLoop();
}


