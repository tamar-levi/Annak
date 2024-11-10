#pragma once
#include<string>
#include<iostream>
#include <vector>
#include "json.hpp"
#include "openJson.h"
using namespace std;
class Build
{
	using json = nlohmann::json;
private:
	string typeName;
	vector<int> resources;
	json js;
	int countOfCars;
	int countOfTracks;
	int countOfHelicopters;
	//משאבים
public:
	Build(string typeName);
	string getTypeName();
	int getCountOfCars();
	int getCountOfHelicopters();
	void setCountOfCars(int);
	void setCountOfTracks(int);
	int getCountOfTracks();
	vector<int>& getResource();
	void reset();
	void addResource(int, int);
	void printResources();
};

