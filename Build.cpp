#include "Build.h"
#include "Build.h"
#include "openJson.h"
using json = nlohmann::json;

//constractor
Build::Build(string typeName) :typeName(typeName), countOfCars(0), countOfTracks(0) {

	this->js = openJson::GetFile();
	resources.resize(js["ResourceTypes"].size());
}

//return the resource
vector<int>& Build::getResource()
{
	return resources;
}

//return the name
string Build::getTypeName()
{
	return typeName;
}
//return the count of the car
int Build::getCountOfCars()
{
	return countOfCars;
}
//edit the count of the car
void Build::setCountOfCars(int cars)
{
	countOfCars = cars;
}
//return the count of the helicopter
int Build::getCountOfHelicopters()
{
	return countOfHelicopters;
	return 0;
}
//edit the count of the track
void Build::setCountOfTracks(int tracks)
{
	countOfTracks = tracks;
}
//return the count of the track
int Build::getCountOfTracks()
{
	return countOfTracks;
}
//reset the vector of the resource
void Build::reset()
{
	for (int i = 0; i < resources.size(); ++i) {
		resources[i] = 0;
	}
}
//add resource
void Build::addResource(int count, int type)
{
		int capasities = resources[type];
		if (js["Capacities"][typeName][type].get<int>() >= (count + capasities)){
			resources[type] += count;
		}
		else{
			resources[type] = js["Capacities"][typeName][type].get<int>();
		}
}
//print resource
void Build::printResources() {
	for (int i = 0; i < resources.size() - 1; i++) {
		cout << resources[i] << " ";
	}
	cout << endl;
}

