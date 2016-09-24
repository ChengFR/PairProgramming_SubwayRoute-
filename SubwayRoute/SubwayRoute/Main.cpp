#include <stdio.h>
#include <tchar.h>
#include "ReadMap.h"
#include "calculateRoute.h"
#include "GUI.h"
#include <iostream>
#include <fstream>

//获取并输出某条路线上的所有站点
void getStations(string name);
//计算并输出所求路径
bool getRoute(string str, string begin, string end);
//将参数和求得的路线保存到文件中
void saveData(string args);

ReadMap rm;
calculateRoute cr;
GUI g;
vector<string> route;     //通过计算得到的路线
int btime = 0; //-b的次数
int ctime = 0; //-c的次数

int main() {
	//读取地图信息
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
	
	//清空保存的文件
	remove("saveData.txt");

	//读取参数
	string str;
	string beginSta, endSta;
	while (true) {
		cout << "Please input the args：" << endl;
		cin >> str;
		if (str == "-b" || str == "-c") {
			//记录偏好
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
			//通过偏好计算出用哪种方式
			if (btime >= ctime) {
				getRoute("-b", beginSta, endSta);
			}
			else {
				getRoute("-c", beginSta, endSta);
			}

			//调用gui


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
		cout << "错误参数" << endl;
		return false;
	}
	return true;

}

void getStations(string name) {
	string str = "该线路不存在与地图中";
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
