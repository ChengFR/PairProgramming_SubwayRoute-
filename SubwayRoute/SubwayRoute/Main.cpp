#include <stdio.h>
#include <tchar.h>
#include "ReadMap.h"
#include "calculateRoute.h"
#include "GUI.h"
#include <iostream>
#include <fstream>
#include <GL/glut.h>
#include <windows.h>
#include <math.h>
#include <string>
#include <iostream>
#include <time.h>
using namespace std;

//��ȡ�����ĳ��·���ϵ�����վ��
void getStations(string name);
//���㲢�������·��
bool getRoute(string str, string begin, string end);
//����������õ�·�߱��浽�ļ���
void saveData(string args);

//��ͼ����
void drawCNString(const char* str);
void selectFont(int size, int charset, const char* face);
void display();
void animation();
void OnTimer(int value);

ReadMap rm;
calculateRoute cr;
vector<string> route1;     //ͨ������õ���·��,����������Ϣ
vector<string> route2;     //ͨ������õ���·��,��������Ϣ
int bt = 0; //-b�Ĵ���
int ct = 0; //-c�Ĵ���


//��ͼ����
const int n = 50;
const GLfloat R = 0.01f;
const GLfloat Pi = 3.1415926536f;
#define MAX_CHAR 128
int step = 0;

int ac;
char **av;
//��ͼ�߳�
DWORD WINAPI draw(LPVOID lpParam) {
	step = 0;
	//��ʼ��
	glutInit(&ac, av);
	//��ɫģʽ������ģʽ
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	//���ó�ʼ���ڵ�λ��(�������Ͻ��������������(x,y))����λ������
	glutInitWindowPosition(0, 0);
	//���ڴ�С
	glutInitWindowSize(1300, 900);

	//�������ڣ������Ǵ�����
	glutCreateWindow("beijing subway");
	glutDisplayFunc(&display);
	glutTimerFunc(1000, OnTimer, 1);
	//����ѭ��
	glutMainLoop();

	return 0;
}


int main(int argc, char *argv[]) {

	DWORD dwThread;
	ac = argc;
	av = argv;
	//��ȡ��ͼ��Ϣ
	cout << "read map ..." << endl;
	if (!rm.readFile()) {
		cout << "map is wrong !" << endl;
	}
	if (!rm.setInf()) {
		cout << "map is wrong !" << endl;
	}
	if (!rm.readPosi()) {
		cout << "map is wrong !" << endl;
	}
	cout << "finished" << endl;
	cr.init(rm);
	
	//��ձ�����ļ�
	remove("saveData.txt");

	//��ȡ����
	string str;
	string beginSta, endSta;
	while (true) {
		cout << "Please input the args��" << endl;
		cin >> str;
		if (str == "-b" || str == "-c") {
			//��¼ƫ��
			if (str == "-b") {
				bt++;
			}
			else {
				ct++;
			}
			cin >> beginSta;
			cin >> endSta;
			getRoute(str,beginSta,endSta);
			str +=" "+ beginSta +" "+ endSta;
			saveData(str);
		}
		else if (str == "-g") {
			cin >> beginSta;
			cin >> endSta;
			//ͨ��ƫ�ü���������ַ�ʽ
			if (bt >= ct) {
				getRoute("-b", beginSta, endSta);
			}
			else {
				getRoute("-c", beginSta, endSta);
			}
			saveData("-g "+ beginSta+" "+ endSta);

			CreateThread(NULL, 0, draw, NULL, 0, &dwThread);
			
		}
		else {
			getStations(str);
			saveData(str);
		}
	}
	
	return 0;
}

bool getRoute(string str, string begin, string end) {
	int i = 0;
	vector<vector<string>> route;
	if (str == "-b") {
		if (!(rm.ifContain_1(rm.stationQueen, begin) >= 0 && rm.ifContain_1(rm.stationQueen, end) >= 0)) {
			cout << "error args" << endl;
			return false;
		}
		route = cr.addTransferInf(cr.getMinStaRoute(begin, end));
		route1 = route[0];
		route2 = route[1];
	}
	else if (str == "-c") {
		if (!(rm.ifContain_1(rm.stationQueen, begin) >= 0 && rm.ifContain_1(rm.stationQueen, end) >= 0)) {
			cout << "error args" << endl;
			return false;
		}
		route = cr.addTransferInf(cr.getMinStaOfMinTraRoute(cr.getAllMinTraRoute(begin, end)));
		route1 = route[0];
		route2 = route[1];
	}
	else {
		cout << "�������" << endl;
		return false;
	}

	return true;

}

void getStations(string name) {
	string str = "����·���������ͼ��";
	if (!rm.printRoute(name)) {
		cout << str << endl;
	}
}

void saveData(string args) {
	ofstream outfile("saveData.txt", ios::app);
	if (!outfile) {
		cout << "error in open saveData.txt" << endl;
	}
	else {
		outfile << args << endl;
		int i = 0,j = 0;
		if (args[0] == '-') {
			for (i = 0; i < route1.size(); i++) {
				outfile << route1[i] + " ";
			}
			outfile << "" << endl;
		}
		else {
			for (i = 0; i<18; i++) {
				if (rm.r[i].routeName == args) {
					//cout<< name<<endl;
					for (j = 0; j<rm.r[i].stationNumber; j++) {
						outfile << rm.r[i].stations.at(j) +" ";
					}
					break;
				}
			}
			outfile << "" << endl;
		}
		outfile.close();
	}
	
}

void display() {

	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	int i = 0,j = 0;

	//����
	station s0, s1;
	float x0, y0, x1, y1;
	glColor3f(0.44f, 0.50f, 0.56f);
	glLineWidth(2.0f);
	for (i = 0; i < 18; i++) {
		for (j = 0; j < rm.r[i].stationNumber - 1; j++) {
			s0 = rm.getStation(rm.r[i].stations[j]);
			s1 = rm.getStation(rm.r[i].stations[j + 1]);
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

	//����
	float x = 0;
	float y = 0;
	for (i = 0; i<rm.stationQueen.size(); i++) {
		x = rm.stationQueen[i].x / 26.0f;
		y = rm.stationQueen[i].y / 26.0f;
		if (rm.stationQueen[i].TraSta) {
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
		//дվ����
		selectFont(10, DEFAULT_CHARSET, "���ķ���");
		glColor3f(0.0f, 0.0f, 0.0f);
		glRasterPos2f(x, y);
		const char *name = rm.stationQueen[i].name.c_str();
		drawCNString(name);
	}
	
	//����
	animation();
}
//��ʾ����
void drawCNString(const char* str) {
	int len, i;
	wchar_t* wstring;
	HDC hDC = wglGetCurrentDC();
	GLuint list = glGenLists(1);

	// �����ַ��ĸ���
	// �����˫�ֽ��ַ��ģ����������ַ����������ֽڲ���һ���ַ�
	// ����һ���ֽ���һ���ַ�
	len = 0;
	for (i = 0; str[i] != '\0'; ++i)
	{
		if (IsDBCSLeadByte(str[i]))
			++i;
		++len;
	}

	// ������ַ�ת��Ϊ���ַ�
	wstring = (wchar_t*)malloc((len + 1) * sizeof(wchar_t));
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, str, -1, wstring, len);
	wstring[len] = L'\0';

	// �������ַ�
	for (i = 0; i<len; ++i)
	{
		wglUseFontBitmapsW(hDC, wstring[i], 1, list);
		glCallList(list);
	}

	// ����������ʱ��Դ
	free(wstring);
	glDeleteLists(list, 1);
}
//��������
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

	//�߹����� 
	glColor3f(1.0f, 0.0f, 0.0f);
	glLineWidth(3.0f);
	for (i = 0; i < step; i++) {
		x0 = rm.getStation(route1[i]).x / 26.0f;
		y0 = rm.getStation(route1[i]).y / 26.0f;
		x1 = rm.getStation(route1[i+1]).x / 26.0f;
		y1 = rm.getStation(route1[i+1]).y / 26.0f;
		glBegin(GL_LINES);
		glVertex2f(x0, y0);
		glVertex2f(x1, y1);
		glEnd();
	}

	//�߹���վ�� ��ɫ
	for (i = 0; i < step; i++) {
		x = rm.getStation(route1[i]).x / 26.0f;
		y = rm.getStation(route1[i]).y / 26.0f;
		glColor3f(1.0f, 1.0f, 0.0f);
		glBegin(GL_POLYGON);
		for (j = 0; j<n; j++)
			glVertex2f(x + R*cos(2 * Pi / n*j), y + R*sin(2 * Pi / n*j));
		glEnd();
	}

	//��ǰվ�� ǳ��ɫ
	x = rm.getStation(route1[step]).x / 26.0f;
	y = rm.getStation(route1[step]).y / 26.0f;
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_POLYGON);
	for (j = 0; j<n; j++)
		glVertex2f(x + R*cos(2 * Pi / n*j), y + R*sin(2 * Pi / n*j));
	glEnd();

	glFlush();
	glutSwapBuffers();
}

//����ˢ��Ƶ��Ƶ��
void OnTimer(int value)
{
	if (step < route1.size() - 1) {
		step++;
		glutPostRedisplay();
		glutTimerFunc(1000, OnTimer, 1);
	}
}
