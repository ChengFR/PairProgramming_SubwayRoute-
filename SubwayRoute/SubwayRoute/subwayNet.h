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
	int bt = 0; //-b�Ĵ���
	int ct = 0; //-c�Ĵ���
	
public:
	ReadMap _map;
	vector<string> route1;     //ͨ������õ���·��,����������Ϣ
	vector<string> route2;     //ͨ������õ���·��,��������Ϣ
	subwayNet() {
		_map.init();
		_calRoute.init(_map);
	}
	//�洢��Ϣ
	void saveData(string &args);
	//�����·�ϵ�վ��
	void getStations(string &name);
	//��̾���Ѱ·
	bool getRouteB(string &begin, string &end);
	//��С����Ѱ·
	bool getRouteC(string &begin, string &end);
	//��ͼ
	bool getRouteG(string &begin, string &end);
	
	
};