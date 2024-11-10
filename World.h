#pragma once
using namespace std;
#include<iostream>
#include<vector>
#include<string>
#include "Input.h"
#include "Tile.h"
#include "openJson.h"
#include "Coordinate.h"
class World
{
private:
	//basis mat..
	vector<vector<shared_ptr<Coordinate>>> world;
	//json object
	json js;
	//tile obect
	shared_ptr<Tile> currentTile;
	//coordinate object
	shared_ptr<Coordinate> currentCoordinate;
	int moveRowCoordinate;
	int moveColCoordinate;
	int countCity;
	int countRoad;
	int countVillage;
	int countCar;
	int countTruck;
	int countHelicopter;


public:
	World(const vector<vector<string> >&);
	int getCountCar();
	int getCountTruck();
	int getCountHelicopter();

	int getCountCity();
	int getCountRoad();
	int getCountVillage();
	string getCategoryNameByType(int type) /*throw(const char*)=*/;
	Tile& foundTile(int col, int row);
	string getTileCategoryName(shared_ptr<Tile> tile);
	Coordinate& foundCoordinate(int col, int row);
	vector<vector<shared_ptr<Coordinate>>>& getWorld();
	shared_ptr<Tile>& getCurrentTile();
	shared_ptr<Coordinate> getCurrentCoordinate()const;
	int getMoveColCoordinate()const;
	int getMoveRowCoordinate()const;
	void setMoveColCoordinateMove(int);
	void setMoveRowCoordinateMove(int);

	void setCurrentTile(Tile& currentTile);
	void setCurrentCoordinate(Coordinate& currentCoordinate);
	bool buildType(int row, int col, string);
	bool checkIfHaveRoade(int row, int col, string s);
	bool buildForInput(int row, int col, string s);
	void makeEmpty(int row, int col);
	bool checkIfCanAddPeople(int count, int row, int col);
	int amountOfPeople(Coordinate&);
	bool isValidNeighbor(int row, int col);
	bool Manufacture(string,int,int);


};

