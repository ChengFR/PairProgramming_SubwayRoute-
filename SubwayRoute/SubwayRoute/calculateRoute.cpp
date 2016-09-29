#include "calculateRoute.h"



/*���룺������յ�
���������·��
���ܣ���һ�����·��
*/
vector<string> calculateRoute::getMinStaRoute(string &beginSta, string &endSta) {
	vector<string> route; //վ��˳���ǵ��ŵ�
	if (beginSta == endSta) {
		route.push_back(beginSta);
		return route;
	}
	vector<string> nowStations;//��ǰվ��
	vector<string> nextStations;//��һȦվ��
	vector<string> usedStations;//�����Ѿ���������վ��
	vector<vector<string>> stepStation; //ÿһ��������վ��
	vector<string> temp; //���ڵ���
	string tempStr;
	int i = 0, j = 0, n = 0;
	int nowStations_size;
	station sta;
	nowStations.push_back(beginSta);
	usedStations.push_back(beginSta);
	stepStation.push_back(nowStations);
	while (!rm.ifContain_2(nowStations, endSta)) {
		nowStations_size = nowStations.size();
		for (i = 0; i<nowStations_size; i++) {
			sta = rm.getStation(nowStations.at(i));
			if (sta.nearbyStationNumber == 0) {
				cout << "error" << endl;
				return route;
			}
			for (j = 0; j<sta.nearbyStationNumber; j++) {
				tempStr = sta.nearbyStations.at(j);
				if (!rm.ifContain_2(usedStations, tempStr)) {
					usedStations.push_back(tempStr);
					nextStations.push_back(tempStr);
				}
			}
		}
		nowStations.swap(nextStations);
		nextStations.clear();
		stepStation.push_back(nowStations);
	}
	route.push_back(endSta);
	int temp_size;
	for (i = stepStation.size() - 2; i >= 0; i--) {
		temp = stepStation[i];
		temp_size = temp.size();
		for (j = 0; j < temp_size; j++) {
			sta = rm.getStation(temp[j]);
			if (rm.ifContain_2(sta.nearbyStations, route[n])) {
				route.push_back(sta.name);
				n++;
				break;
			}
		}
	}

	return route;


}

/*���룺������յ�
������������ٻ���·��
���ܣ������������ٻ���·��
*/
vector<vector<string>> calculateRoute::getAllMinTraRoute(string &beginSta, string &endSta) {
	vector<vector<string>> Routes;//ÿ��·����ֻ����������Ҫվ��
	vector<vector<string>> completeRoutes; //��֮ǰ��õ�·�߽������

										   //���ڱ���
	station nowStation;
	route nowRoute;
	vector<vector<string>> stepStation; //����������ÿ���׶ε�����վ��,���һ�����������յ�վ
	vector<string> step;

	vector<string> usedSta; //��������վ�㲻�ظ�����
	int i = 0, j = 0, si = 0;
	int m = 0;
	bool find = false;
	step.push_back(beginSta);
	stepStation.push_back(step);
	step.clear();
	usedSta.push_back(beginSta);
	int stepStation_size;
	while (!find) {
		//����ǰһ�׶����е�վ��
		stepStation_size = stepStation[m].size();
		for (i = 0; i < stepStation_size; i++) {
			nowStation = rm.getStation(stepStation[m][i]);
			//����վ��������·��·��
			for (j = 0; j < nowStation.routeNumber; j++) {
				nowRoute = rm.getRoute(nowStation.routes[j]);
				//�ҵ��յ�
				if (rm.ifContain_2(nowRoute.stations, endSta)) {
					find = true;
				}
				//��������·�ϵ�վ����stepStation
				for (si = 0; si < nowRoute.stationNumber; si++) {
					//û�б�������
					if (!rm.ifContain_2(usedSta, nowRoute.stations[si])) {
						step.push_back(nowRoute.stations[si]);
						usedSta.push_back(nowRoute.stations[si]);
					}
				}
			}
		}
		stepStation.push_back(step);
		step.clear();
		m++;
	}

	int k = 0, size = 0, ri = 0;
	vector<string> tempRoute;
	vector<string> newRoute;
	vector<string> beforeStas;
	station sta;
	tempRoute.push_back(endSta);
	Routes.push_back(tempRoute);
	tempRoute.clear();
	m = 0;
	int beforeStas_size;
	while (Routes[0][m] != beginSta) {
		size = Routes.size();
		for (ri = 0; ri < size; ri++) {
			tempRoute = Routes[ri];
			nowStation = rm.getStation(tempRoute[m]);
			beforeStas = stepStation[stepStation.size() - 2 - m]; //��ȡǰһվ������վ��
																  //����ǰһվ�㣬��˭�����ٻ���·����
			beforeStas_size = beforeStas.size();
			for (i = 0; i<beforeStas_size; i++) {
				sta = rm.getStation(beforeStas[i]);
				for (j = 0; j < sta.routeNumber; j++) {
					nowRoute = rm.getRoute(sta.routes[j]);
					if (rm.ifContain_2(nowRoute.stations, nowStation.name)) {
						if (k == 0) {
							Routes[ri].push_back(sta.name);
							k++;
						}
						else {
							newRoute.assign(tempRoute.begin(), tempRoute.end());
							newRoute.push_back(sta.name);
							Routes.push_back(newRoute);
							newRoute.clear();
						}
						break;
					}
				}
			}
			k = 0;
		}
		m++;
	}

	tempRoute.clear();
	newRoute.clear();
	station nextStation;
	string routeName;
	int Routes_size = Routes.size();
	int tempRoute_size;
	for (i = 0; i < Routes_size; i++) {
		tempRoute = Routes[i];
		tempRoute_size = tempRoute.size();
		for (j = 0; j < tempRoute_size - 1; j++) {
			nowStation = rm.getStation(tempRoute[j]);
			nextStation = rm.getStation(tempRoute[j + 1]);
			//�����ǰ·����
			if (nowStation.routeNumber == 1) {
				routeName = nowStation.routes[0];
			}
			else {
				if (nextStation.routeNumber == 1) {
					routeName = nextStation.routes[0];
				}
				else {
					routeName = getSameRoute(nowStation.routes, nextStation.routes);
				}
			}
			//��ȫ·��
			nowRoute = rm.getRoute(routeName);
			for (ri = 0; ri < nowRoute.stationNumber; ri++) {
				if (nowRoute.stations[ri] == nowStation.name) {
					while (nowRoute.stations[ri] != nextStation.name) {
						newRoute.push_back(nowRoute.stations[ri]);
						ri++;
					}
					break;
				}
				else if (nowRoute.stations[ri] == nextStation.name) {
					k = ri;
					while (nowRoute.stations[ri] != nowStation.name) {
						ri++;
					}
					while (ri != k) {
						newRoute.push_back(nowRoute.stations[ri]);
						ri--;
					}
					break;
				}
			}
		}
		newRoute.push_back(beginSta);
		completeRoutes.push_back(newRoute);
		newRoute.clear();
	}
	return completeRoutes;
}

/*���룺�������ٻ���·��
��������ٻ�����·����̵�·��
���ܣ������������ٻ���·����·����̵�·��
*/
vector<string> calculateRoute::getMinStaOfMinTraRoute(vector<vector<string>> &routes) {
	int i = 0;
	int min = routes[0].size(), order = 0;
	int routes_size = routes.size();
	int route_size;
	for (i = 1; i < routes_size; i++) {
		route_size = routes[i].size();
		if (route_size < min) {
			min = routes[i].size();
			order = i;
		}
	}
	return routes[order];
}

/*���룺һ��·��
��������˴���
���ܣ�����һ��·���Ļ��˴���
*/
int calculateRoute::getTranfTime(vector<string> &route) {
	int i = 0, j = 0, n = 0;
	vector<string>::iterator it; //���������Ǹ�ָ��
	string nowRouteName = "";
	station nowStation;
	station lastStation;
	station nextStation;
	//�������ǰ·����
	nowStation = rm.getStation(route.at(0));
	if (nowStation.routeNumber == 1) {
		nowRouteName = nowStation.routes.at(0);
	}
	else {
		nextStation = rm.getStation(route.at(1));
		if (nextStation.routeNumber == 1) {
			nowRouteName = nextStation.routes.at(0);
		}
		else {
			nowRouteName = getSameRoute(nowStation.routes, nextStation.routes);
		}
	}
	it = route.begin();
	for (it++, i = 1; it != route.end(); it++, i++) {
		nowStation = rm.getStation(*it);
		//��ǰվ�㲢����֮ǰ����·��
		if (!rm.ifContain_2(nowStation.routes, nowRouteName)) {
			if (nowStation.routeNumber == 1) {
				nowRouteName = nowStation.routes.at(0);
			}
			else {
				lastStation = rm.getStation(route.at(i - 1));
				if (lastStation.routeNumber == 1) {
					nowRouteName = nextStation.routes.at(0);
				}
				else {
					nowRouteName = getSameRoute(nowStation.routes, lastStation.routes);
				}
			}
			n++;
		}
	}
	return n;
}

/*���룺�����·��vector<string>
����������޸ĺ��·��vector<string>
���ܣ���·��ת�����ӻ�����Ϣ
*/
vector<vector<string>> calculateRoute::addTransferInf(vector<string> &route) {
	vector<string> newRoute1;//�޻�����Ϣ
	vector<string> newRoute2;
	vector<vector<string>> Route;
	int i = 0, j = 0;
	vector<string>::iterator it; //���������Ǹ�ָ��
	string temp = "";
	string nowRouteName = "";
	station nowStation;
	station nextStation;
	station lastStation;
	for (i = route.size() - 1; i >= 0; i--) {
		newRoute1.push_back(route.at(i));
		newRoute2.push_back(route.at(i));
	}
	//�������ǰ·����
	nowStation = rm.getStation(newRoute2.at(0));
	if (nowStation.routeNumber == 1) {
		nowRouteName = nowStation.routes.at(0);
	}
	else {
		nextStation = rm.getStation(newRoute2.at(1));
		if (nextStation.routeNumber == 1) {
			nowRouteName = nextStation.routes.at(0);
		}
		else {
			nowRouteName = getSameRoute(nowStation.routes, nextStation.routes);
		}
	}
	it = newRoute2.begin();
	for (it++, i = 1; it != newRoute2.end(); it++, i++) {
		nowStation = rm.getStation(*it);
		//��ǰվ�㲢����֮ǰ����·��
		if (!rm.ifContain_2(nowStation.routes, nowRouteName)) {
			if (nowStation.routeNumber == 1) {
				nowRouteName = nowStation.routes.at(0);
			}
			else {
				lastStation = rm.getStation(newRoute2.at(i - 1));
				if (lastStation.routeNumber == 1) {
					nowRouteName = nextStation.routes.at(0);
				}
				else {
					nowRouteName = getSameRoute(nowStation.routes, lastStation.routes);
				}
			}

			temp = newRoute2.at(i - 1) + "����" + nowRouteName;
			newRoute2.erase(it - 1);
			//��newRoute�����޸ĺ������ʧЧ
			newRoute2.insert(newRoute2.begin() + i - 1, temp);
			it = newRoute2.begin() + i;
		}
	}
	cout << newRoute2.size() << endl;
	int route_size = newRoute2.size();
	for (i = 0; i < route_size; i++) {
		cout << newRoute2.at(i) << endl;
	}
	Route.push_back(newRoute1);
	Route.push_back(newRoute2);
	return Route;
}

/*���룺����station��route����
����������е�һ����ͬ��·����
���ܣ���ȡ����station����ͬ��·����
*/
string calculateRoute::getSameRoute(vector<string> &route1, vector<string> &route2) {
	int i = 0;
	int route_size = route1.size();
	for (i = 0; i < route_size; i++) {
		if (rm.ifContain_2(route2, route1.at(i))) {
			return route1.at(i);
		}
	}
	return NULL;
}