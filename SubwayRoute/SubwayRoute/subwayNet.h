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
	//输出线路上的站点
	string getStations(string name);
	//最短距离寻路
	string getRouteB(string begin, string end);
	//最小换乘寻路
	string getRouteC(string begin, string end);
	//存储信息
	void saveData(string data);
};