#include "World.h"
#include <iostream>
#include "Command.h"
#include "Input.h"
#include "json.hpp"
#include "Utility.h"
#include <fstream>
#include <string>
#include "openJson.h"
#include <fstream>
#include "Coordinate.h"

using namespace std;
using json = nlohmann::json;

//constructor
World::World(const vector<vector<string>>& data) :countCity(0), countRoad(0), countVillage(0), countCar(0), countTruck(0), countHelicopter(0){

    this->js = openJson::GetFile();
    int tileWidthConfig = this->js["Sizes"]["Tile"][0];
    int tileHeightConfig = this->js["Sizes"]["Tile"][1];
    this->world = vector<vector<shared_ptr<Coordinate>>>(data.size() * tileWidthConfig);


    for (size_t tileRowIndex = 0; tileRowIndex < data.size() * tileWidthConfig; tileRowIndex += tileWidthConfig) {
        for (size_t tileColumnIndex = 0; tileColumnIndex < tileWidthConfig; tileColumnIndex++) {
            this->world[tileColumnIndex + tileRowIndex] = vector<shared_ptr<Coordinate>>(data[tileRowIndex / tileHeightConfig].size() * tileHeightConfig);
        }
    }

    for (size_t tileRowIndex = 0; tileRowIndex < data.size(); tileRowIndex++) {

        for (size_t tileColumnIndex = 0; tileColumnIndex < data[tileRowIndex].size(); tileColumnIndex++) {
            shared_ptr< Tile>newTile = make_shared<Tile>(stoi(data[tileRowIndex][tileColumnIndex]));
            for (size_t i = 0; i < tileWidthConfig; i++)
            {
                for (size_t j = 0; j < tileHeightConfig; j++)
                {
                    this->world[tileRowIndex * tileWidthConfig + i][tileColumnIndex * tileHeightConfig + j] = make_shared<Coordinate>(Coordinate(newTile, tileRowIndex * tileWidthConfig + i, tileColumnIndex * tileHeightConfig + j));
                }
            }

        }

    }
}
//return count of car
int World::getCountCar()
{
    return countCar;
}
//return count of truck
int World::getCountTruck()
{
    return countTruck;
}
//return count of hlicopter
int World::getCountHelicopter()
{
    return countHelicopter;
}
//return count of city
int World::getCountCity()
{
    return countCity;
}
//return count of road
int World::getCountRoad()
{
    return countRoad;
}
//return count of village
int World::getCountVillage()
{
    return countVillage;
}
//get Type of category
string World::getCategoryNameByType(int type)
{
    auto iter = find_if(js["Tiles"].items().begin(), js["Tiles"].items().end(), [type](auto& x) {return x.value() == type; });
    if (iter != js["Tiles"].items().end())
    return iter.key();
    return "";
}
//return name of category
string World::getTileCategoryName(shared_ptr<Tile> tile)
{
    return getCategoryNameByType(tile->getType());
}
//the correct coordinate
Coordinate& World::foundCoordinate(int col, int row)
{
    return *(world[row-1][col-1]);
}
//return the world
vector<vector<shared_ptr<Coordinate>>>& World::getWorld()
{
    return world;
}
//return the current tile
shared_ptr<Tile>& World::getCurrentTile()
{
    return currentTile;
}
//return the current coordinate
shared_ptr<Coordinate> World::getCurrentCoordinate()const
{
    return currentCoordinate;
}
//return row
int World::getMoveRowCoordinate() const
{
    return moveRowCoordinate;
}
//edit col
void World::setMoveColCoordinateMove(int c)
{
    moveColCoordinate = c;
}
//edit row
void World::setMoveRowCoordinateMove(int r)
{
    moveRowCoordinate = r;
}
//return col
int World::getMoveColCoordinate()const
{
    return moveColCoordinate;
}
//set the tile
void World::setCurrentTile(Tile& currentTile)
{
    this->currentTile = make_shared<Tile>(currentTile);
}
//set the coordinate
void World::setCurrentCoordinate(Coordinate& currentCoordinate)
{
    this->currentCoordinate = make_shared<Coordinate>(currentCoordinate);

}
//found the place of the tile
Tile& World::foundTile(int col, int row) {
    return *(world[row-1][col-1]->getPointerTile());
}
//build
bool World::buildType(int row, int col, string typeName)
{
    int sizeTypeRow = js["Sizes"][typeName][1].get<int>();
    int sizeTypeCol = js["Sizes"][typeName][0].get<int>();
    for (int i = row - 1; i < sizeTypeRow + row - 1; i++) {
        for (int j = col - 1; j < sizeTypeCol + col - 1; j++) {
            if (typeName == "Road" && world[i][j]->getIsRoad()) {
                return false;
            }
            if (world[i][j]->getBuild() != nullptr)
                return false;
        }
    }
    for (int i = row - 1; i < js["Sizes"][typeName][0].get<int>() + row - 1; i++) {
        for (int j = col - 1; j < js["Sizes"][typeName][1].get<int>() + col - 1; j++) {
            if (typeName == "Road") {
                world[i][j]->setIsRoad(true);
            }
            else
              world[i][j]->setBuild(typeName);
        }
    }
    if (typeName == "City")
        countCity++;
    if (typeName == "Road")
        countRoad++;
    if (typeName == "Village")
        countVillage++;
    return true;
}
//build
bool World::buildForInput(int row, int col, string s)
{
    if (checkIfHaveRoade(row, col, s))
        buildType(row, col, s);
    return true;
    return false;
}
//do it empty
void World::makeEmpty(int row, int col)
{
    if (world[row][col]->getBuild() != nullptr)
    {
        world[row][col]->getBuild()->reset();
    }
}
//check if enable to add people and add him
bool World::checkIfCanAddPeople(int count, int row, int col)
{
    auto forCheck = world[row - 1][col - 1]->getBuild();
    if (forCheck)
    {
        string type = forCheck->getTypeName();
        auto it = find(js["ResourceTypes"].begin(), js["ResourceTypes"].end(), "People");
        int index = distance(js["ResourceTypes"].begin(), it);
        int capasities = forCheck->getResource()[index];
        if (js["Capacities"][type][index] >= (count + capasities)){
            forCheck->getResource()[index] += count;
        }
        else{
            forCheck->getResource()[index] = js["Capacities"][type][index];
        }
        return true;
    }
    else {
        shared_ptr<vehicle>v = make_shared<vehicle>(vehicle("People"));
        world[row-1][col-1]->setIsPeople(v);
        return true;
    }
    return false;
}
//calculate the amount of the people
int World::amountOfPeople(Coordinate& cor)
{
    if (cor.getBuild())
    {
        auto it = find(js["ResourceTypes"].begin(), js["ResourceTypes"].end(), "People");
        int index = distance(js["ResourceTypes"].begin(), it);
        return cor.getBuild()->getResource()[index];
    }
    return cor.getIsPeople()!=nullptr;
}
//check if its neighbor
bool World::isValidNeighbor(int row, int col) {
    return row >= 0 && row < world.size() && col >= 0 && col < world[0].size();
}
//manufacture
bool World::Manufacture(string typeName, int row, int col)
{
    int sizeTypeRow = js["Sizes"][typeName][1];
    int sizeTypeCol = js["Sizes"][typeName][0];
    for (int i = row - 1; i < sizeTypeRow + row - 1; i++) {
        for (int j = col - 1; j < sizeTypeCol + col - 1; j++) {
            if (typeName == "Helicopter") {
                if (world[i][j]->getPointerHelicopter()!= nullptr)
                    return false;
            }
            else {
                if (world[i][j]->getPointerVehicleRoad() != nullptr&&world[i][j]->getPointerTile()->getTypeName()=="Water")
                    return false;
            }
        }
    }
    shared_ptr<vehicle> v = make_shared<vehicle>(typeName);
    for (int i = row - 1; i < js["Sizes"][typeName][0].get<int>() + row - 1; i++) {
        for (int j = col - 1; j < js["Sizes"][typeName][1].get<int>() + col - 1; j++) {
            if (typeName == "Helicopter") {
                world[i][j]->setPointerHelicopter(v);
            }
            else {
                world[i][j]->setPointerVehicleRoad(v);
                
            }
        }
    }
    if (typeName == "Car")
        countCar++;
    if (typeName == "Truck")
        countTruck++;
    else
        countHelicopter++;
    return true;
}
//check if have road
bool World::checkIfHaveRoade(int row, int col, string s)
{
    int sizeRoad = js["Sizes"]["Road"][0];
    int countPoint = 0, countPoint1 = 0;
    for (int i = row - 1; i <= row - 1 + js["Sizes"][s][1].get<int>(); i++) {
        if (isValidNeighbor(i, col - 2) && world[i][col - 2]->getIsRoad()) {
            countPoint++;
        }
        else{
            if (countPoint >= sizeRoad)
                return true;
            countPoint = 0;
        }
        if (isValidNeighbor(i, col - 1 + js["Sizes"][s][0].get<int>()) && world[i][col - 1 + js["Sizes"][s][0].get<int>()]->getIsRoad()){
            countPoint1++;
        }
        else{
            if (countPoint1 >= sizeRoad)
                return true;
            countPoint1 = 0;
        }
    }
    if (countPoint == sizeRoad || countPoint1 == sizeRoad)
        return true;
    countPoint = 0, countPoint1 = 0;
    for (int j = col - 1; j < col - 1 + js["Sizes"][s][1].get<int>(); j++) {
        if (isValidNeighbor(row - 1, j) && world[row - 1][j]->getIsRoad()){
            countPoint++;
        }
        else{
            if (countPoint >= sizeRoad)
                return true;
            countPoint = 0;
        }
        if (isValidNeighbor(row - 1 + js["Sizes"][s][1].get<int>(), j) && world[row - 1 + js["Sizes"][s][1].get<int>()][j]->getIsRoad()){
            countPoint1++;
        }
        else{
            if (countPoint1 >= sizeRoad)
                return true;
            countPoint1 = 0;
        }
    }
    if (countPoint == sizeRoad || countPoint1 == sizeRoad)
        return true;
    return false;
}







