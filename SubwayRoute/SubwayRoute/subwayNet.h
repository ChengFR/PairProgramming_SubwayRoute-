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
#include "MyException.h"

typedef vector<string> Route;

class subwayNet {
private:
	calculateRoute _calRoute;
	//Route route;
	int bt = 0; //-b�Ĵ���
	int ct = 0; //-c�Ĵ���
	
	
public:
	ReadMap _map;
	//vector<string> route1;     //ͨ������õ���·��,����������Ϣ
	//vector<string> route2;     //ͨ������õ���·��,��������Ϣ
	subwayNet() {
		_map.init();
		_calRoute.init(_map);
	}
	//�洢��Ϣ
	void saveData(string &args, Route &route);
	//�����·�ϵ�վ��
	Route getStations(string &name);
	//��̾���Ѱ·
	Route getRouteB(string &begin, string &end);
	//��С����Ѱ·
	Route getRouteC(string &begin, string &end);
	//��ͼ
	Route getRouteG(string &begin, string &end);

	string changeRouteToString(Route & route);
	
};