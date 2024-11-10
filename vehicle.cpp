#include "vehicle.h"
#include<iostream>
using namespace std;

//constructor
vehicle::vehicle(string type):typeName(type)
{
	this->js = openJson::GetFile();
	resource.resize(js["ResourceTypes"].size());
}
//return resource
vector<int>& vehicle::getResource()
{
	return resource;
}
//return name
string vehicle::getTypeName()
{
	return typeName;
}
//reset all the resource
void vehicle::reset()
{

	for (int i = 0; i < resource.size(); ++i) {
		resource[i] = 0;
	}
}
//add resource
void vehicle::addResource(int count, int type)
{
		int capacity = resource[type];
		if (js["Capacities"][this->typeName][type] >= (count + capacity)){
			resource[type] += count;
		}
		else{
			resource[type] = js["Capacities"][this->typeName][type];
		}
}
//print resource
void vehicle::printResources()
{
	for (int i = 0; i < resource.size() - 1; i++) {
		cout << resource[i] << " ";
	}
	cout << endl;
}
