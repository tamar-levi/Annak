#pragma once
#ifndef INPUTSTAGE_H
#define INPUTSTAGE_H
// !INPUTSTAGE
#include "Input.h"
#include <map>
#include "WorldStage.h"
#include <fstream>
#include <map>
#include <iostream>
#include "json.hpp"
#include "Tile.h"
using namespace std;
using json = nlohmann::json;
class InputStage
{
private:

	//vector of pointers to the command
	const vector<shared_ptr<Command>>steps;
	//pointer to the world
	const shared_ptr<World> WorldMap;
	//json object
	json js;


public:
	InputStage(const vector<shared_ptr<Command>>steps, const shared_ptr<World>  WorldMap) : steps(steps), WorldMap(WorldMap) {
		this->js=openJson::GetFile();
	}
	void DoSteps();
	void Select(int col, int row);
	void Work(int col, int row);//מומש לא נכון!!!
	void Wait(int time);///לא מומש עדיין!!
	void Rain();
	void buildType(int row, int col, string s);
	void Deposit(int row, int col);
	void addPeople(int count, int, int);
	void TakeResources(int, int);
	bool Manufacture(string, int, int);
	void Move(int, int);

	
};
#endif

