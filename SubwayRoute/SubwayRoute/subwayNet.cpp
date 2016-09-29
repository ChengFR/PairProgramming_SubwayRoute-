#include "subwayNet.h"




void subwayNet::saveData(string &args) {
	ofstream outfile("saveData.txt", ios::app);
	if (!outfile) {
		cout << "error in open saveData.txt" << endl;
	}
	else {
		outfile << args << endl;
		int i = 0, j = 0;
		if (args[0] == '-') {
			for (i = 0; i < route1.size(); i++) {
				outfile << route1[i] + " ";
			}
			outfile << "" << endl;
		}
		else {
			for (i = 0; i<18; i++) {
				if (_map.r[i].routeName == args) {
					//cout<< name<<endl;
					for (j = 0; j<_map.r[i].stationNumber; j++) {
						outfile << _map.r[i].stations.at(j) + " ";
					}
					break;
				}
			}
			outfile << "" << endl;
		}
		outfile.close();
	}

}
void subwayNet::getStations(string &line) {
	string str = "该线路不存在与地图中";
	if (!_map.printRoute(line)) {
		cout << str << endl;
	}
	saveData(line);
}
bool subwayNet::getRouteB(string &begin, string &end) {
	bt++;
	if (!(_map.ifContain_1(_map.stationQueen, begin) >= 0 && _map.ifContain_1(_map.stationQueen, end) >= 0)) {
		cout << "error args" << endl;
		return false;
	}
	route = _calRoute.addTransferInf(_calRoute.getMinStaRoute(begin, end));
	route1 = route[0];
	route2 = route[1];
	string str ="-b" + begin + " " + end;
	saveData(str);
	return true;
}
bool subwayNet::getRouteC(string &begin, string &end) {
	ct++;
	if (!(_map.ifContain_1(_map.stationQueen, begin) >= 0 && _map.ifContain_1(_map.stationQueen, end) >= 0)) {
		cout << "error args" << endl;
		return false;
	}
	route = _calRoute.addTransferInf(_calRoute.getMinStaOfMinTraRoute(_calRoute.getAllMinTraRoute(begin, end)));
	route1 = route[0];
	route2 = route[1];

	string str = "-c" + begin + " " + end;
	saveData(str);
	return true;
}

bool subwayNet::getRouteG(string &begin, string &end) {
	if (bt >= ct) {
		if (!getRouteB(begin, end)) {
			return false;
		}
	}
	else {
		if (!getRouteC(begin, end)) {
			return false;
		}
	}
	string str = "-g" + begin + " " + end;
	saveData(str);
	return true;
}
