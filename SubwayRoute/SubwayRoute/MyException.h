#pragma once
#include <iostream>
#include <string>

class FileNotExistException {
public:
	FileNotExistException() {
		std::cerr << "读取文件不存在" << std::endl;
	}
	FileNotExistException(std::string filename) {
		std::cerr << "读取文件:"+filename+" 不存在" << std::endl;
	}
};

class MapPatterException {
public:
	MapPatterException() {
		std::cerr << "地图格式错误" << std::endl;
	}
};

class LineNotExistException {
public:
	LineNotExistException() {
		std::cerr << "线路不存在" << std::endl;
	}
	LineNotExistException(std::string line) {
		std::cerr << line + "不存在" << std::endl;
	}
};

class StationNotExistException {
public:
	StationNotExistException() {
		std::cerr << "站点不存在" << std::endl;
	}
	StationNotExistException(std::string station) {
		std::cerr << station + "不存在" << std::endl;
	}
};

class InputPatternException {
public:
	InputPatternException() {
		std::cerr << "输入格式错误" << std::endl;
	}
};

class RouteSearchException {
public:
	RouteSearchException(){
		std::cerr << "寻路错误" << std::endl;
	}
};