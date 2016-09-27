#include "ReadMap.h"

bool ReadMap::readFile() {
	ifstream mapFile("beijing_subway.txt");
	int routeOrder = 0;
	int stationNumber = 0;
	string str;
	for (; getline(mapFile, str);) {
		if (str == "") {
			if (routeOrder >17) {
				cout << "地铁线路文件错误" << endl;
				return false;
			}
			r[routeOrder].stationNumber = stationNumber;
			routeOrder++;
		}
		else if (str.substr(str.size() - 2, 2) == "线" || str.substr(str.size() - 2, 2) == "段") {
			r[routeOrder].routeName = str;
			stationNumber = 0;
		}
		else {
			r[routeOrder].stations.push_back(str);
			stationNumber++;
		}
	}
	r[routeOrder].stationNumber = stationNumber;
	return true;
}

bool ReadMap::setInf() {
	int ri = 0;
	int si = 0;
	int n = -1;
	for (ri = 0; ri <18; ri++) {
		for (si = 0; si<r[ri].stationNumber; si++) {
			//判断该站点是否已被记录
			n = ifContain_1(stationQueen, r[ri].stations.at(si));
			//该站点已被记录
			if (n >= 0) {
				//如果这条路线没有记录在该站点的信息内就记录它
				if (!ifContain_2(stationQueen.at(n).routes, r[ri].routeName)) {
					stationQueen.at(n).routeNumber++;
					stationQueen.at(n).routes.push_back(r[ri].routeName);
					stationQueen.at(n).TraSta = true;
				}
			}
			//该站点未被记录
			else {
				station newsta;
				newsta.name = r[ri].stations.at(si);
				newsta.routeNumber++;
				newsta.routes.push_back(r[ri].routeName);
				stationQueen.push_back(newsta);
				n = stationQueen.size() - 1;
			}
			//该站点不是这条路线上最后一个
			if (si < r[ri].stationNumber - 1) {
				//后面的相邻站点未被记录
				if (!ifContain_2(stationQueen.at(n).nearbyStations, r[ri].stations.at(si + 1))) {
					stationQueen.at(n).nearbyStationNumber++;
					stationQueen.at(n).nearbyStations.push_back(r[ri].stations.at(si + 1));
				}
			}
			if (si > 0) {
				if (!ifContain_2(stationQueen.at(n).nearbyStations, r[ri].stations.at(si - 1))) {
					stationQueen.at(n).nearbyStationNumber++;
					stationQueen.at(n).nearbyStations.push_back(r[ri].stations.at(si - 1));
				}
			}
			n = -1;
		}
	}
	return true;
}

bool ReadMap::printRoute(string name) {
	int i = 0, j = 0;
	for (i = 0; i<18; i++) {
		if (r[i].routeName == name) {
			//cout<< name<<endl;
			for (j = 0; j<r[i].stationNumber; j++) {
				cout << r[i].stations.at(j) << endl;
			}
			return true;
		}
	}
	return false;
}

int ReadMap::ifContain_1(vector<station> queen, string data) {
	int i = 0;
	int queen_size;
	queen_size = queen.size();
	if (queen_size == 0) {
		return -1;
	}
	for (i = 0; i<queen_size; i++) {
		if (queen.at(i).name == data) {
			return i;
		}
	}
	return -1;
}

bool ReadMap::ifContain_2(vector<string> queen, string data) {
	int i = 0;
	int queen_size;
	queen_size = queen.size();
	if (queen_size == 0) {
		return false;
	}
	for (i = 0; i<queen_size; i++) {
		if (queen.at(i) == data) {
			return true;
		}
	}
	return false;
}

station ReadMap::getStation(string name) {
	int i = 0;
	int stationQueen_size = stationQueen.size();
	for (i = 0; i < stationQueen_size; i++) {
		if (stationQueen.at(i).name == name) {
			break;
		}
	}
	//该站点不存在
	if (i == stationQueen_size) {
		return stationQueen.at(i-1);
	}
	return stationQueen.at(i);
}

route ReadMap::getRoute(string routeName) {
	int i = 0;
	for (i = 0; i < 18; i++) {
		if (r[i].routeName == routeName) {
			break;
		}
	}
	return r[i];
}

int ReadMap::getStationIndex(string name) {
	int i = 0;
	int stationQueen_size = stationQueen.size();
	for (i = 0; i < stationQueen_size; i++) {
		if (stationQueen.at(i).name == name) {
			break;
		}
	}
	//该站点不存在
	if (i == stationQueen_size) {
		return -1;
	}
	return i;
}

bool ReadMap::readPosi() {
	ifstream posiFile("StationsPosi.txt");
	string str;
	vector<string> data;
	int staIndex;
	int i = 0;
	for (; getline(posiFile, str);i++) {
		data = split(str," ");
		staIndex = getStationIndex(data[0]);
		if (staIndex == -1) {
			cout << data[0] + " is not in map" << endl;
		}
		else {
			stationQueen[staIndex].x = atoi(data[1].c_str());
			stationQueen[staIndex].y = atoi(data[2].c_str());
		}
	}
	//cout << i << endl;
	/*for (i = 0; i < stationQueen.size(); i++) {
		if (stationQueen[i].x == 0 && stationQueen[i].y == 0) {
			cout << stationQueen[i].name << endl;
		}
	}*/

	return true;
}

vector<string> ReadMap::split(const string& s, const string& delim){
	std::vector<std::string> elems;
	size_t pos = 0;
	size_t len = s.length();
	size_t delim_len = delim.length();
	if (delim_len == 0) return elems;
	while (pos < len)
	{
		int find_pos = s.find(delim, pos);
		if (find_pos < 0)
		{
			elems.push_back(s.substr(pos, len - pos));
			break;
		}
		elems.push_back(s.substr(pos, find_pos - pos));
		pos = find_pos + delim_len;
	}
	return elems;
}