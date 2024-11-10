#pragma once
#ifndef WORLDSTAGE_H
#define WORLDSTAGE_H
#include <vector>
// !1
#include <fstream>
#include <map>
#include <iostream>
#include "Input.h"
#include "Input.h"
#include "World.h"
#include "json.hpp"
using namespace std;

class WorldStage
{
private:
	//pointer to the world
	shared_ptr<World>myWorld;
	//pointer to all the command
	shared_ptr<Command>world;
	
public:
	WorldStage(const shared_ptr<Command>world) :world(world) {};
	void BuildWorldMap();
	const shared_ptr<World> getWorldMap();
};
#endif

