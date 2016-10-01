#pragma once
#include <iostream>
#include <string>

class FileNotExistException {
public:
	FileNotExistException() {
		std::cerr << "��ȡ�ļ�������" << std::endl;
	}
	FileNotExistException(std::string filename) {
		std::cerr << "��ȡ�ļ�:"+filename+" ������" << std::endl;
	}
};

class MapPatterException {
public:
	MapPatterException() {
		std::cerr << "��ͼ��ʽ����" << std::endl;
	}
};

class LineNotExistException {
public:
	LineNotExistException() {
		std::cerr << "��·������" << std::endl;
	}
	LineNotExistException(std::string line) {
		std::cerr << line + "������" << std::endl;
	}
};

class StationNotExistException {
public:
	StationNotExistException() {
		std::cerr << "վ�㲻����" << std::endl;
	}
	StationNotExistException(std::string station) {
		std::cerr << station + "������" << std::endl;
	}
};

class InputPatternException {
public:
	InputPatternException() {
		std::cerr << "�����ʽ����" << std::endl;
	}
};

class RouteSearchException {
public:
	RouteSearchException(){
		std::cerr << "Ѱ·����" << std::endl;
	}
};