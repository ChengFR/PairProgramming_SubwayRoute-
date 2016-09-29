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
	calculateRoute _calRoute;
	vector<vector<string>> route;
	int bt = 0; //-b的次数
	int ct = 0; //-c的次数
	
public:
	ReadMap _map;
	vector<string> route1;     //通过计算得到的路线,不带换乘信息
	vector<string> route2;     //通过计算得到的路线,带换乘信息
	subwayNet() {
		_map.init();
		_calRoute.init(_map);
	}
	//存储信息
	void saveData(string &args);
	//输出线路上的站点
	void getStations(string &name);
	//最短距离寻路
	bool getRouteB(string &begin, string &end);
	//最小换乘寻路
	bool getRouteC(string &begin, string &end);
	//画图
	bool getRouteG(string &begin, string &end);
	
	
};