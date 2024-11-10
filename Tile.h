#pragma once
#include<string>
#include"openJson.h"
#include <vector>
#include "json.hpp"
using json = nlohmann::json;

using namespace std;

class Tile
{

private:
	int type;
	double count;
	json js;
public:

	Tile(int type);
	int getType();
	int getCount();
	string getTypeName();
	 void deleteResource(double amount);
	 void addResource(double, string);
};

