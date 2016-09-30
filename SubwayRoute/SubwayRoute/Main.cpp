#include <stdio.h>
#include <tchar.h>
#include "ReadMap.h"
#include "calculateRoute.h"
#include "subwayNet.h"
#include <iostream>
#include <fstream>
#include <GL/glut.h>
#include <windows.h>
#include <math.h>
#include <string>
#include <iostream>
#include <time.h>
#include "MyException.h"
using namespace std;


//画图函数
void drawCNString(const char* str);
void selectFont(int size, int charset, const char* face);
void display();
void animation();
void OnTimer(int value);
//画图参数
const int n = 50;
const GLfloat R = 0.01f;
const GLfloat Pi = 3.1415926536f;
#define MAX_CHAR 128
//画图线程
int ac;
char **av;
int step = 0;
DWORD WINAPI draw(LPVOID lpParam) {
	step = 0;
	//初始化
	glutInit(&ac, av);
	//颜色模式，缓冲模式
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	//设置初始窗口的位置(窗口左上角相对于桌面坐标(x,y))，单位是像素
	glutInitWindowPosition(0, 0);
	//窗口大小
	glutInitWindowSize(1300, 900);

	//创建窗口，参数是窗口名
	glutCreateWindow("beijing subway");
	glutDisplayFunc(&display);
	glutTimerFunc(1000, OnTimer, 1);
	//无限循环
	glutMainLoop();

	return 0;
}

subwayNet sn;
int main(int argc, char *argv[]) {

	DWORD dwThread;
	ac = argc;
	av = argv;
	

	//清空保存的文件
	remove("saveData.txt");
	//读取参数
	string str;
	string beginSta, endSta;
	while (true) {
		cout << "Please input the args：" << endl;
		cin >> str;
		if (str == "-b") {
			cin >> beginSta;
			cin >> endSta;
			sn.getRouteB(beginSta, endSta);
		}
		else if (str == "-c") {
			cin >> beginSta;
			cin >> endSta;
			sn.getRouteC(beginSta, endSta);
		}
		else if (str == "-g") {
			cin >> beginSta;
			cin >> endSta;
			//通过偏好计算出用哪种方式
			sn.getRouteG(beginSta, endSta);		
			CreateThread(NULL, 0, draw, NULL, 0, &dwThread);
		}
		else {
			sn.getStations(str);
		}
	}
	
	return 0;
}




void display() {

	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	int i = 0,j = 0;
	//画线
	station s0, s1;
	float x0, y0, x1, y1;
	glColor3f(0.44f, 0.50f, 0.56f);
	glLineWidth(2.0f);
	for (i = 0; i < 18; i++) {
		for (j = 0; j < sn._map.r[i].stationNumber - 1; j++) {
			s0 = sn._map.getStation(sn._map.r[i].stations[j]);
			s1 = sn._map.getStation(sn._map.r[i].stations[j + 1]);
			x0 = s0.x / 26.0f;
			y0 = s0.y / 26.0f;
			x1 = s1.x / 26.0f;
			y1 = s1.y / 26.0f;
			glBegin(GL_LINES);
			glVertex2f(x0, y0);
			glVertex2f(x1, y1);
			glEnd();
		}
	}

	//画点
	float x = 0;
	float y = 0;
	for (i = 0; i<sn._map.stationQueen.size(); i++) {
		x = sn._map.stationQueen[i].x / 26.0f;
		y = sn._map.stationQueen[i].y / 26.0f;
		if (sn._map.stationQueen[i].TraSta) {
			glColor3f(0.11f, 0.56f, 1.0f);
			glBegin(GL_POLYGON);
			for (j = 0; j<n; j++)
				glVertex2f(x + R*cos(2 * Pi / n*j), y + R*sin(2 * Pi / n*j));
			glEnd();
		}
		else {
			glColor3f(0.0f, 1.0f, 1.0f);
			glBegin(GL_POLYGON);
			for (j = 0; j<n; j++)
				glVertex2f(x + R*cos(2 * Pi / n*j), y + R*sin(2 * Pi / n*j));
			glEnd();
		}
		//写站点名
		selectFont(10, DEFAULT_CHARSET, "华文仿宋");
		glColor3f(0.0f, 0.0f, 0.0f);
		glRasterPos2f(x, y);
		const char *name = sn._map.stationQueen[i].name.c_str();
		drawCNString(name);
	}
	
	//动画
	animation();
}
//显示文字
void drawCNString(const char* str) {
	int len, i;
	wchar_t* wstring;
	HDC hDC = wglGetCurrentDC();
	GLuint list = glGenLists(1);

	// 计算字符的个数
	// 如果是双字节字符的（比如中文字符），两个字节才算一个字符
	// 否则一个字节算一个字符
	len = 0;
	for (i = 0; str[i] != '\0'; ++i)
	{
		if (IsDBCSLeadByte(str[i]))
			++i;
		++len;
	}

	// 将混合字符转化为宽字符
	wstring = (wchar_t*)malloc((len + 1) * sizeof(wchar_t));
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, str, -1, wstring, len);
	wstring[len] = L'\0';

	// 逐个输出字符
	for (i = 0; i<len; ++i)
	{
		wglUseFontBitmapsW(hDC, wstring[i], 1, list);
		glCallList(list);
	}

	// 回收所有临时资源
	free(wstring);
	glDeleteLists(list, 1);
}
//字体设置
void selectFont(int size, int charset, const char* face) {
	HFONT hFont = CreateFontA(size, 0, 0, 0, FW_MEDIUM, 0, 0, 0,
		charset, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, face);
	HFONT hOldFont = (HFONT)SelectObject(wglGetCurrentDC(), hFont);
	DeleteObject(hOldFont);
}

void animation() {
	float x, y;
	float x0, y0, x1, y1;
	int i = 0,j = 0;

	//走过的线 
	glColor3f(1.0f, 0.0f, 0.0f);
	glLineWidth(3.0f);
	for (i = 0; i < step; i++) {
		x0 = sn._map.getStation(sn.route1[i]).x / 26.0f;
		y0 = sn._map.getStation(sn.route1[i]).y / 26.0f;
		x1 = sn._map.getStation(sn.route1[i+1]).x / 26.0f;
		y1 = sn._map.getStation(sn.route1[i+1]).y / 26.0f;
		glBegin(GL_LINES);
		glVertex2f(x0, y0);
		glVertex2f(x1, y1);
		glEnd();
	}

	//走过的站点 黄色
	for (i = 0; i < step; i++) {
		x = sn._map.getStation(sn.route1[i]).x / 26.0f;
		y = sn._map.getStation(sn.route1[i]).y / 26.0f;
		glColor3f(1.0f, 1.0f, 0.0f);
		glBegin(GL_POLYGON);
		for (j = 0; j<n; j++)
			glVertex2f(x + R*cos(2 * Pi / n*j), y + R*sin(2 * Pi / n*j));
		glEnd();
	}

	//当前站点 浅绿色
	x = sn._map.getStation(sn.route1[step]).x / 26.0f;
	y = sn._map.getStation(sn.route1[step]).y / 26.0f;
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_POLYGON);
	for (j = 0; j<n; j++)
		glVertex2f(x + R*cos(2 * Pi / n*j), y + R*sin(2 * Pi / n*j));
	glEnd();

	glFlush();
	glutSwapBuffers();
}

//设置刷新频率频率
void OnTimer(int value)
{
	if (step < sn.route1.size() - 1) {
		step++;
		glutPostRedisplay();
		glutTimerFunc(1000, OnTimer, 1);
	}
}
