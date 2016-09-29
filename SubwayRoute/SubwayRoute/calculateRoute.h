#pragma once
#include<iostream>
#include<vector>
#include<string>
#include "ReadMap.h"
using namespace std;

/*���ڸ���·�ߵļ���*/
class calculateRoute {
	ReadMap rm;
	//·�߼���ʱ���õ���һЩ���ߺ���
	//��ȡ��վ�㹲ͬ���ڵ�·����
	string getSameRoute(vector<string> &route1, vector<string> &route2);
	//��ȡ���˴���
	int getTranfTime(vector<string> &route);
public:
	
	void init(ReadMap r) {
		rm = r;
	}

	//��վ�����ٵ����·��
	vector<string> getMinStaRoute(string &beginSta, string &endSta);
	//Ϊ���·����ӻ�����Ϣ
	vector<vector<string>> addTransferInf(vector<string> &route);

	//���������ٻ��˵�·��
	vector<vector<string>> getAllMinTraRoute(string &beginSta, string &endSta);
	//�����л������ٵ�·�����ҵ�һ����̵�
	vector<string> getMinStaOfMinTraRoute(vector<vector<string>> &routes);
};





