#pragma once
#pragma once
#include<vector>
#include<iostream>
#include<fstream>
#include <string>
using namespace std;

//վ�����Ϣ
struct station
{
	string name = "";
	int nearbyStationNumber = 0;
	vector<string> nearbyStations;
	vector<int> nearbyStationsId;
	int routeNumber = 0;
	vector<string> routes;
	//����
	int x = 0;
	int y = 0;
	//�Ƿ��ǻ���վ
	bool TraSta = false;
};

//·�ߵ���Ϣ
struct route
{
	string routeName = "";
	int stationNumber = 0;
	vector<string> stations;
};

class ReadMap {
	//�ַ����зֺ���
	vector<string> split(const string& s, const string& delim);

public:
	//��·��վ�����
	route r[18];
	vector<station> stationQueen;
	int id = 0;
	void init();

	//��ȡ��ͼ��Ϣ
	bool readFile();
	//��¼����վ����Ϣ
	bool setInf();

	//���ݴ�������·�������������·�ϵ�վ��
	bool printRoute(string &name);

	//���ߺ���
	//����վ����Ϊdata��վ���ڶ���stationQueen�е��±�
	int ifContain_1(vector<station> &queen, string &data);
	//�ж�һ���ַ����������Ƿ����ĳ���ַ���
	bool ifContain_2(vector<string> &queen, string &data);
	//ͨ��վ������ȡվ��
	station getStation(string &name);
	//ͨ����·����ȡ��·
	route getRoute(string &routeName);

	//������������ȡ����
	bool readPosi() ;
	int getStationIndex(string &name);

};


