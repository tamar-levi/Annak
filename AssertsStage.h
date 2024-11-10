#pragma once
#ifndef ASSERTSSTAGE_H

#define ASSERTSSTAGE_H
#include "Input.h"
#include <map>
#include "WorldStage.h"
#include <fstream>
#include <map>
#include <iostream>
#include "json.hpp"
#include "InputStage.h"
using namespace std;
using json = nlohmann::json;
class AssertsStage
{
private:
	//vector of asserts
	const vector<std::string>asserts;
	//pointer to the world
	const shared_ptr<World> WorldMap;
	//json object
	json js;
public:
	AssertsStage(const vector<string>asserts, const shared_ptr<World> world) :asserts(asserts), WorldMap(world) {
		this->js = openJson::GetFile();
	}
	void DoAsserts()const;
	void selectedCategory()const;
	void SelectedResource()const;
	void countType(string)const;
	string checkIsCompleted()const;
	void EmptyAllResource(int row, int col);
	void selectPeople()const;
	void selectedCar()const;
	void selectedTrack()const;
	void SelectedComplete()const;
	void carCount()const;
	void truckCount()const;
	void helicopterCount()const;
	void SelectedCoordinates()const;

	//selectCoordinates


};
#endif

