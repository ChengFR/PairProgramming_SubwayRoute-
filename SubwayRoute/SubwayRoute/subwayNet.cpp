#include "subwayNet.h"




void subwayNet::saveData(string &args, Route &route) {
	ofstream outfile("saveData.txt", ios::app);
	if (!outfile) {
		throw FileNotExistException("saveData.txt");
	}
	outfile << args << endl;
	int i = 0, j = 0;
	for (i = 0; i < route.size(); i++) {
		outfile << route[i] + " ";
	}
	outfile << "" << endl;
	outfile.close();
}
Route subwayNet::getStations(string &line) {
	Route route;
	if (!_map.printRoute(line)) {
		throw LineNotExistException(line);
	}
	for (int i = 0; i < 18; i++) {
		if (_map.r[i].routeName == line) {
			//cout<< name<<endl;
			for (int j = 0; j<_map.r[i].stationNumber; j++) {
				route.push_back( _map.r[i].stations.at(j));
			}
			break;
		}
	}
	saveData(line, route);
	return route;
}
Route subwayNet::getRouteB(string &begin, string &end) {
	Route route;
	bt++;
	if (!(_map.ifContain_1(_map.stationQueen, begin) >= 0 && _map.ifContain_1(_map.stationQueen, end) >= 0)) {
		throw StationNotExistException();
	}
	route = _calRoute.getMinStaRoute(end, begin);
	string str ="-b" + begin + " " + end;
	saveData(str, route);
	return route;
}
Route subwayNet::getRouteC(string &begin, string &end) {
	Route route;
	ct++;
	if (!(_map.ifContain_1(_map.stationQueen, begin) >= 0 && _map.ifContain_1(_map.stationQueen, end) >= 0)) {
		throw StationNotExistException();
	}
	route = _calRoute.getMinStaOfMinTraRoute(_calRoute.getAllMinTraRoute(end, begin));

	string str = "-c" + begin + " " + end;
	saveData(str, route);
	return route;
}

Route subwayNet::getRouteG(string &begin, string &end) {
	Route route;
	if (bt >= ct) {
		route = getRouteB(begin, end);
	}
	else {
		route = getRouteC(begin, end);
	}
	string str = "-g" + begin + " " + end;
	saveData(str, route);
	return route;
}

string subwayNet::changeRouteToString(Route & route) {
	string routeString;
	Route newRoute = _calRoute.addTransferInf(route);
	auto begin = newRoute.begin();
	auto end = newRoute.end();
	int size = newRoute.size();
	routeString += to_string(size);
	routeString += "\n";
	for (; begin != end; begin++) {
		routeString += *begin;
		routeString += "\n";
	}
	return routeString;
}
