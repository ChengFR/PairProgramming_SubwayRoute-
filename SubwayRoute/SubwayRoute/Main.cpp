#include <stdio.h>
#include <tchar.h>
#include "ReadMap.h"
#include "calculateRoute.h"
#include "GUI.h"
#include <iostream>
#include <fstream>

//��ȡ�����ĳ��·���ϵ�����վ��
void getStations(string name);
//���㲢�������·��
bool getRoute(string str, string begin, string end);
//����������õ�·�߱��浽�ļ���
void saveData(string args);

ReadMap rm;
calculateRoute cr;
GUI g;
vector<string> route;     //ͨ������õ���·��
int btime = 0; //-b�Ĵ���
int ctime = 0; //-c�Ĵ���

int main() {
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
				btime++;
			}
			else {
				ctime++;
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
			if (btime >= ctime) {
				getRoute("-b", beginSta, endSta);
			}
			else {
				getRoute("-c", beginSta, endSta);
			}

			//����gui


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
	int route_size;
	if (str == "-b") {
		if (!(rm.ifContain_1(rm.stationQueen, begin) >= 0 && rm.ifContain_1(rm.stationQueen, end) >= 0)) {
			cout << "error args" << endl;
			return false;
		}
		route = cr.addTransferInf(cr.getMinStaRoute(begin, end));
		cout << route.size() << endl;
		route_size = route.size();
		for (i = 0; i < route_size; i++) {
			cout << route.at(i) << endl;
		}

	}
	else if (str == "-c") {
		if (!(rm.ifContain_1(rm.stationQueen, begin) >= 0 && rm.ifContain_1(rm.stationQueen, end) >= 0)) {
			cout << "error args" << endl;
			return false;
		}
		route = cr.addTransferInf(cr.getMinStaOfMinTraRoute(cr.getAllMinTraRoute(begin, end)));
		cout << route.size() << endl;
		route_size = route.size();
		for (i = 0; i < route_size; i++) {
			cout << route.at(i) << endl;
		}
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
			for (i = 0; i < route.size(); i++) {
				outfile << route[i] + " ";
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
