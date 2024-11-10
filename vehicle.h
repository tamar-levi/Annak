#pragma once
#include<vector>
#include<string>
#include "json.hpp"
#include "openJson.h"
using namespace std;
using json = nlohmann::json;
class vehicle
{
private:
	json js;
	string typeName;
	vector<int> resource;
public:
	vehicle(string); 
	vector<int>& getResource();
	string getTypeName();
	void reset();
	void addResource(int, int);
	void printResources();
};

