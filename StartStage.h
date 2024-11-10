#pragma once
#ifndef STARTSTAGE_H
#define STARTSTAGE_H
// !STARTSTAGE_H
#include "Input.h"
#include "WorldStage.h"
#include <fstream>
#include <map>
#include <iostream>
#include "json.hpp"
using namespace std;
using json = nlohmann::json;
class StartStage
{
private:
	//pointer to the world
	const shared_ptr<World> Worldmap;
	json js;
	//pointer to the command
	vector <shared_ptr<Command>>start;
public:
	StartStage(const shared_ptr<World> Worldmap, const vector<shared_ptr<Command>>& start) ;
	void doStart();
	void addResource(double count, string name, int col, int row);
	void addPeople(int count, int row, int col);
	void buildType(int row, int col, string);
	void Manufacture(int, int, string);
	bool Resources(int, int, int, int, int, int);

};
#endif
