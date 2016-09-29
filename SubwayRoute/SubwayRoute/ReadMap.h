#pragma once
#pragma once
#include<vector>
#include<iostream>
#include<fstream>
#include <string>
using namespace std;

//站点的信息
struct station
{
	string name = "";
	int nearbyStationNumber = 0;
	vector<string> nearbyStations;
	vector<int> nearbyStationsId;
	int routeNumber = 0;
	vector<string> routes;
	//坐标
	int x = 0;
	int y = 0;
	//是否是换乘站
	bool TraSta = false;
};

//路线的信息
struct route
{
	string routeName = "";
	int stationNumber = 0;
	vector<string> stations;
};

class ReadMap {
	//字符串切分函数
	vector<string> split(const string& s, const string& delim);

public:
	//线路和站点队列
	route r[18];
	vector<station> stationQueen;
	int id = 0;
	void init();

	//读取地图信息
	bool readFile();
	//记录所有站点信息
	bool setInf();

	//根据传进来的路线名输出整条线路上的站点
	bool printRoute(string &name);

	//工具函数
	//返回站点名为data的站点在队列stationQueen中的下标
	int ifContain_1(vector<station> &queen, string &data);
	//判断一个字符串数组中是否包含某个字符串
	bool ifContain_2(vector<string> &queen, string &data);
	//通过站点名获取站点
	station getStation(string &name);
	//通过线路名获取线路
	route getRoute(string &routeName);

	//新增函数，读取坐标
	bool readPosi() ;
	int getStationIndex(string &name);

};


