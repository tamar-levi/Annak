#include "StartStage.h"
#include<vector>

//Constructor
StartStage::StartStage(const shared_ptr<World> Worldmap, const vector<shared_ptr<Command>>& start) :Worldmap(Worldmap), start(start)
{
	this->js = openJson::GetFile();
}

//A function responsible for sending the appropriate variables to the appropriate functions
void StartStage::doStart()
{
	for (const auto& cmd : start)
	{
		if (cmd->name == Command::RESOURCE) {
			addResource(stoi(cmd->arguments[0]), cmd->arguments[1], stoi(cmd->arguments[2]), stoi(cmd->arguments[3]));
		}
		else {
			if (cmd->name == Command::BUILD) {
				buildType(stoi(cmd->arguments[2]), stoi(cmd->arguments[1]), cmd->arguments[0]);
			}
			else {
				if (cmd->name == Command::MANUFACTURE) {
					Manufacture(stoi(cmd->arguments[2]), stoi(cmd->arguments[1]), cmd->arguments[0]);
				}
				else {
					if (cmd->name == Command::RESOURCES) {
						Resources(stoi(cmd->arguments[0]), stoi(cmd->arguments[1]), stoi(cmd->arguments[2]), stoi(cmd->arguments[3]), stoi(cmd->arguments[4]), stoi(cmd->arguments[5]));
					}
					else {
						if (cmd->name == Command::PEOPLE) {
							addPeople(stoi(cmd->arguments[0]), stoi(cmd->arguments[2]), stoi(cmd->arguments[1]));
						}
					}
				}
			}
		}
	
	}
}

//add resource 
void StartStage::addResource(double count, string name, int col, int row)
{
	int index = 0;
	for (int i = 0; i < js["ResourceTypes"].size(); i++){
		if (js["ResourceTypes"][i] == name){
			index = i;
		}
	}
	shared_ptr<Coordinate> c = Worldmap->getWorld()[row-1][col-1];

	if (c->getBuild())
	{
		Worldmap->getWorld()[row-1][col-1]->getBuild()->addResource(count, index);
	}
	else {
		if (c->getPointerHelicopter()) {

			c->getPointerHelicopter()->addResource(count, index);
		}
		else {
			if (c->getPointerVehicleRoad()) {

				c->getPointerVehicleRoad()->addResource(count, index);
			}
			else {
				if (c->getIsPeople()) {

					c->getIsPeople()->addResource(count, index);
				}


				else {
					Worldmap->getWorld()[row - 1][col - 1]->getPointerTile()->addResource(count, name);
				}

			}
		}
	}

}
//add people
void StartStage::addPeople(int count, int row, int col)
{
	Worldmap->checkIfCanAddPeople(count, row, col);
}
//build
void StartStage::buildType(int row, int col, string s)
{
	Worldmap->buildType(row, col, s);
}
//manufacture
void StartStage::Manufacture(int row, int col, string type)
{
	Worldmap->Manufacture(type, row, col);
}
//initialization resources
bool StartStage::Resources(int wood, int wool , int iron , int blocks , int col, int row)
{
	vector<int> params{ wood,wool,iron,blocks };
	auto coorForResource = Worldmap->getWorld()[row - 1][col - 1];
	if (coorForResource->getPointerHelicopter()){
		
		for (int i = 0; i < coorForResource->getPointerHelicopter()->getResource().size() - 1; i++){
			coorForResource->getPointerHelicopter()->addResource(params[i], i);
		}
		return true;
	}
	else {
		if (coorForResource->getPointerVehicleRoad()){

			for (int i = 0; i < coorForResource->getPointerVehicleRoad()->getResource().size() - 1; i++){
				coorForResource->getPointerVehicleRoad()->addResource(params[i], i);
			}
			return true;
		}
		else {
			if (coorForResource->getBuild()){
				for (int i = 0; i < coorForResource->getBuild()->getResource().size() - 1; i++){
					coorForResource->getBuild()->addResource(params[i], i);
				}
				return true;
			}
		}
	}
	return false;
}
