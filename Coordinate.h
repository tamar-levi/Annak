#pragma once
#include "Build.h"
#include "openJson.h"
#include "Tile.h"
#include "vehicle.h"

using json = nlohmann::json;
class Coordinate
{
private:
	shared_ptr<vehicle> isPeople;
	shared_ptr<Tile> pointerTile;
	bool isRoad;
	shared_ptr<vehicle> pointerHelicopter;
	shared_ptr<vehicle> pointerVehicleRoad;
	Build* build;
	json js;
	int position_x;
	int position_y;

public:
	Coordinate(shared_ptr<Tile> pointerTile,int position_x,int position_y) :pointerTile(pointerTile), isRoad(0),position_x(position_x),position_y(position_y){
		this->js = openJson::GetFile();
		build = nullptr;
	};
	shared_ptr<Tile> getPointerTile();
	void setPointerHelicopter(shared_ptr<vehicle>);
	shared_ptr<vehicle> getPointerHelicopter();
	void setPointerVehicleRoad(shared_ptr<vehicle>);
	shared_ptr<vehicle> getPointerVehicleRoad();
	shared_ptr<vehicle> getIsPeople();
	Build* getBuild();
	int GetPositionX();
	int GetPositionY();
	void setIsPeople(shared_ptr<vehicle> isPeople);
	bool setBuild(string name);
	bool getIsRoad();
	void setIsRoad(bool isRoad);
};

