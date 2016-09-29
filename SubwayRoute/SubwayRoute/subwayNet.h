#pragma once
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

class subwayNet {
private:
	ReadMap _map;
	calculateRoute _calRoute;
public:
	subwayNet();
	~subwayNet();
	//�����·�ϵ�վ��
	string getStations(string name);
	//��̾���Ѱ·
	string getRouteB(string begin, string end);
	//��С����Ѱ·
	string getRouteC(string begin, string end);
	//�洢��Ϣ
	void saveData(string data);
};