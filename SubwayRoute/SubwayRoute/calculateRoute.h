#pragma once
#include<iostream>
#include<vector>
#include<string>
#include "ReadMap.h"
using namespace std;

/*用于各种路线的计算*/
class calculateRoute {
	ReadMap rm;
	//路线计算时会用到的一些工具函数
	//获取两站点共同属于的路线名
	string getSameRoute(vector<string> &route1, vector<string> &route2);
	//获取换乘次数
	int getTranfTime(vector<string> &route);
public:
	
	void init(ReadMap r) {
		rm = r;
	}

	//求站点最少的最短路径
	vector<string> getMinStaRoute(string &beginSta, string &endSta);
	//为最短路径添加换乘信息
	vector<vector<string>> addTransferInf(vector<string> &route);

	//求所有最少换乘的路径
	vector<vector<string>> getAllMinTraRoute(string &beginSta, string &endSta);
	//从所有换乘最少的路径中找到一个最短的
	vector<string> getMinStaOfMinTraRoute(vector<vector<string>> &routes);
};





