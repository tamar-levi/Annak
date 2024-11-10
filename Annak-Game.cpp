// Annak.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <fstream>
#include <map>
#include <iostream>
#include "json.hpp"
#include "Input.h"
#include "WorldStage.h"
#include "InputStage.h"
#include "AssertsStage.h"
#include "StartStage.h"
using namespace std;

int main()
{
	Input input;
	// קריאת הקלט ועיבוד

	input.parse_and_store();
	//שלב ראשון במשחק
	WorldStage worldStage(input.world);
	worldStage.BuildWorldMap();
	const shared_ptr<World>worldMap = worldStage.getWorldMap();
	//שלב שני במשחק
	StartStage startStage(worldMap, input.start);
	startStage.doStart();
	//שלב שלישי במשחק
	InputStage inputStage(input.steps, worldMap);
	inputStage.DoSteps();
	//שלב רביעי במשחק
	AssertsStage assertsStage(input.asserts, worldMap);
	assertsStage.DoAsserts();

}
