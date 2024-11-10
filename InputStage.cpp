#include "InputStage.h"
#include <algorithm>
#include<math.h>

//A function responsible for sending the appropriate variables to the appropriate functions
void InputStage::DoSteps()
{
	for (const auto& cmd : steps) {
		if (cmd->name == Command::SELECT) {
			Select(stoi(cmd->arguments[0]), stoi(cmd->arguments[1]));
		}
		else {
			if (cmd->name == Command::WORK) {
				Work(stoi(cmd->arguments[0]), stoi(cmd->arguments[1]));
			}
			else {
				if (cmd->name == Command::RAIN) {
					Rain();
				}
				else {
					if (cmd->name == Command::DEPOSIT) {
						Deposit(stoi(cmd->arguments[1]), stoi(cmd->arguments[0]));
					}
					else {
						if (cmd->name == Command::PEOPLE) {
							addPeople(stoi(cmd->arguments[0]), stoi(cmd->arguments[2]), stoi(cmd->arguments[1]));
						}
						else {
							if (cmd->name == Command::BUILD) {
								buildType(stoi(cmd->arguments[2]), stoi(cmd->arguments[1]), cmd->arguments[0]);

							}
							else {
								if (cmd->name == Command::TAKE_RESOURCES) {
									TakeResources(stoi(cmd->arguments[1]), stoi(cmd->arguments[0]));
								}
								else {
									if (cmd->name == Command::MANUFACTURE) {
										Manufacture(cmd->arguments[0], stoi(cmd->arguments[2]), stoi(cmd->arguments[1]));
									}
									else {
										if (cmd->name == Command::MOVE) {
											Move(stoi(cmd->arguments[1]), stoi(cmd->arguments[0]));
										}
									}
								}
							}
						}
					}
				}
			}
		}
	

	}

}
//go to this place in the world mat
void InputStage::Select(int col, int row)
{
	WorldMap->setCurrentTile(WorldMap->foundTile(col, row));
	WorldMap->setCurrentCoordinate(WorldMap->foundCoordinate(col, row));
}
//the people work and take resources
void InputStage::Work(int col, int row)
{
	if (!WorldMap->getCurrentCoordinate()->getIsPeople())
		throw "no people in this Coordinate";
	Tile& target = WorldMap->foundTile(col, row);
	auto it = find_if(js["ResourceTypes"].begin(), js["ResourceTypes"].end(), [&target,this](string x) {return x == this->js["ResourcePerTile"][target.getTypeName()]; });
	int index = distance(js["ResourceTypes"].begin(), it);
	WorldMap->getCurrentCoordinate()->getIsPeople()->addResource(1, index);
	target.deleteResource(1.0);
	WorldMap->getWorld()[row - 1][col - 1]->setIsPeople(WorldMap->getCurrentCoordinate()->getIsPeople());

}
void InputStage::Wait(int time)
{
}
//add resource
void InputStage::Rain()
{
	int sizeTileRow=this->js["Sizes"]["Tile"][1];
	int sizeTileCol = this->js["Sizes"]["Tile"][0];

	for (int i = 0; i < WorldMap->getWorld().size(); i += sizeTileRow)
	{
		for (int j = 0; j < WorldMap->getWorld()[0].size(); j += sizeTileCol)
		{
			if (WorldMap->getWorld()[i][j]->getPointerTile()->getType() == js["Tiles"]["Forest"].get<int>())
				WorldMap->getWorld()[i][j]->getPointerTile()->addResource(1, "Wood");
			if (WorldMap->getWorld()[i][j]->getPointerTile()->getType() == js["Tiles"]["Field"])
				WorldMap->getWorld()[i][j]->getPointerTile()->addResource(1, "Wool");
		}
	}
}
//build
void InputStage::buildType(int row, int col, string s)
{
	WorldMap->buildForInput(row, col, s);
}
//deposit the resource
void InputStage::Deposit(int row, int col)
{
	auto coordinateToDeposit = WorldMap->getWorld()[row - 1][col - 1];
	auto currentCoordinate = WorldMap->getCurrentCoordinate();
	if (coordinateToDeposit->getBuild()){
		if (coordinateToDeposit->getBuild()->getTypeName() == "City" || coordinateToDeposit->getBuild()->getTypeName() == "Village"){
			if (currentCoordinate->getPointerHelicopter()) {
				vector<int>& temp = coordinateToDeposit->getBuild()->getResource();
				for (int i = 0; i < temp.size(); i++){
					temp[i] = currentCoordinate->getPointerHelicopter()->getResource()[i];
				}
				currentCoordinate->getPointerHelicopter()->reset();
			}
			else {
				if (currentCoordinate->getPointerVehicleRoad()) {
					vector<int>& temp = coordinateToDeposit->getBuild()->getResource();
					for (int i = 0; i < temp.size(); i++){
						temp[i] = currentCoordinate->getPointerVehicleRoad()->getResource()[i];
					}
					currentCoordinate->getPointerVehicleRoad()->reset();
				}
				else {
					if (currentCoordinate->getBuild() != nullptr) {
						vector<int>& temp = coordinateToDeposit->getBuild()->getResource();
						for (int i = 0; i < temp.size(); i++){
							temp[i] = currentCoordinate->getBuild()->getResource()[i];
						}
						currentCoordinate->getBuild()->reset();
					}
					else {
						int countDepositSource = currentCoordinate->getPointerTile()->getCount();
						coordinateToDeposit->getBuild()->addResource(countDepositSource, currentCoordinate->getPointerTile()->getType());
					}
				}
			}
		}
		else{
			coordinateToDeposit->getBuild()->setCountOfCars(currentCoordinate->getBuild()->getCountOfCars());
			coordinateToDeposit->getBuild()->setCountOfTracks(currentCoordinate->getBuild()->getCountOfTracks());
		}
	}
	else{
		if (coordinateToDeposit->getIsPeople()){
			shared_ptr<vehicle>v = make_shared<vehicle>(vehicle("Poeple"));
			coordinateToDeposit->setIsPeople(v);
			currentCoordinate->setIsPeople(nullptr);
		}
	}
}
//add people
void InputStage::addPeople(int count, int row, int col)
{
	WorldMap->checkIfCanAddPeople(count, row, col);
}
//take resource
void InputStage::TakeResources(int row, int col)
{
	if (WorldMap->getCurrentCoordinate()->getPointerHelicopter()) {

		if (WorldMap->getWorld()[row - 1][col - 1]->getBuild()) {

			for (int i = 0; i < js["Capacities"]["Helicopter"].size(); i++){
				
					int countAvailableToDelete = js["Capacities"]["Helicopter"][i].get<int>() - WorldMap->getCurrentCoordinate()->getPointerHelicopter()->getResource()[i];
					int countToDelete= min(countAvailableToDelete, WorldMap->getWorld()[row-1][col-1]->getBuild()->getResource()[i]);
					WorldMap->getWorld()[row-1][col-1]->getBuild()->getResource()[i] -= countToDelete;
					WorldMap->getCurrentCoordinate()->getPointerHelicopter()->addResource(countToDelete, i);
			}
		}
		else {
			string typeName = WorldMap->getWorld()[row - 1][col - 1]->getPointerTile()->getTypeName();
			string resourceName = js["ResourcePerTile"][typeName];
			int index = 0;
			for (int i = 0; i < js["ResourceTypes"].get<int>(); i++) {
				if (resourceName == js["ResourceTypes"][i])
					index = i;
			}
			int countAvailableToDelete = js["Capacities"]["Helicopter"][index].get<int>() - WorldMap->getCurrentCoordinate()->getPointerHelicopter()->getResource()[index];
			int countToDelete = min(countAvailableToDelete, WorldMap->getWorld()[row-1][col-1]->getPointerTile()->getCount());
			WorldMap->getWorld()[row - 1][col - 1]->getPointerTile()->deleteResource(countToDelete);
			WorldMap->getCurrentCoordinate()->getPointerHelicopter()->addResource(countToDelete, index);
		}
	}
	if (WorldMap->getCurrentCoordinate()->getPointerVehicleRoad()) {
		shared_ptr<vehicle> v = WorldMap->getCurrentCoordinate()->getPointerVehicleRoad();
		if (WorldMap->getWorld()[row - 1][col - 1]->getBuild()) {

			for (int i = 0; i < js["Capacities"][v->getTypeName()].size(); i++) {

				int countAvailableToDelete = js["Capacities"][v->getTypeName()][i].get<int>() - WorldMap->getCurrentCoordinate()->getPointerVehicleRoad()->getResource()[i];
				int countToDelete = min(countAvailableToDelete, WorldMap->getWorld()[row - 1][col - 1]->getBuild()->getResource()[i]);
				WorldMap->getWorld()[row - 1][col - 1]->getBuild()->getResource()[i] -= countToDelete;
				WorldMap->getCurrentCoordinate()->getPointerVehicleRoad()->addResource(countToDelete, i);
			}
		}
		else {
			string typeName = WorldMap->getWorld()[row - 1][col - 1]->getPointerTile()->getTypeName();
			string resourceName = js["ResourcePerTile"][typeName];
			int index = 0;
			for (int i = 0; i < js["ResourceTypes"].get<int>(); i++) {
				if (resourceName == js["ResourceTypes"][i])
					index = i;
			}
			int countAvailableToDelete = js["Capacities"][v->getTypeName()][index].get<int>() - WorldMap->getCurrentCoordinate()->getPointerVehicleRoad()->getResource()[index];
			int countToDelete = min(countAvailableToDelete, WorldMap->getWorld()[row - 1][col - 1]->getPointerTile()->getCount());
			WorldMap->getWorld()[row - 1][col - 1]->getPointerTile()->deleteResource(countToDelete);
			WorldMap->getCurrentCoordinate()->getPointerVehicleRoad()->addResource(countToDelete, index);
		}
	}


}
//manufacture the car
bool InputStage::Manufacture(string name, int row, int col)
{
	auto coorForManu = WorldMap->getWorld()[row - 1][col - 1]->getBuild();
	if (coorForManu){
		for (int i = 0; i < coorForManu->getResource().size(); i++){
			if (coorForManu->getResource()[i] < js["Costs"][name][i].get<int>()) {
				return false;
			}
		}
		for (int i = 0; i < coorForManu->getResource().size(); i++){
			coorForManu->getResource()[i] -= js["Costs"][name][i].get<int>();
		}
		WorldMap->Manufacture(name, row, col);
		return true;
	}
	return false;
}
//move the resource
void InputStage::Move(int row, int col)
{
	auto curentCoordinate = WorldMap->getCurrentCoordinate();
	auto coordinateToMove = WorldMap->getWorld()[row - 1][col - 1];
	string type;
	//להעביר מ-אליקופטר:
	if (curentCoordinate->getPointerHelicopter()) {
		coordinateToMove->getPointerHelicopter() = curentCoordinate->getPointerHelicopter();
		type = "Helicopter";
	}
	else {
		// להעביר מכלי רכב
		if (curentCoordinate->getPointerVehicleRoad()) {
			coordinateToMove->getPointerVehicleRoad() = curentCoordinate->getPointerVehicleRoad();
			type = curentCoordinate->getPointerVehicleRoad()->getTypeName();
		}
		else {
			//להעביר איש ל
			if (curentCoordinate->getIsPeople() && coordinateToMove->getPointerTile()->getTypeName() != "Water") {
				if (coordinateToMove->getBuild()) {
					auto it = find_if(js["ResourceTypes"].begin(), js["ResourceTypes"].end(), [](string x) { return x == "People"; });
					int index = distance(js["ResourceTypes"].begin(), it);
					coordinateToMove->getBuild()->addResource(1, index);
					type = "People";
				}
				else {
					if (!coordinateToMove->getIsPeople()) {
						coordinateToMove->setIsPeople(curentCoordinate->getIsPeople());
						curentCoordinate->setIsPeople(nullptr);
					}
				}
			}
			else
				return;
		}
	}
	//loop to remove the old position of the sources
	for (int x = curentCoordinate->GetPositionX() - js["Sizes"][type][1].get<int>(); x < curentCoordinate->GetPositionX() + js["Sizes"][type][1].get<int>(); x++) {
		for (int y = curentCoordinate->GetPositionY() - js["Sizes"][type][0].get<int>(); y < curentCoordinate->GetPositionY() + js["Sizes"][type][1].get<int>(); y++) {
			if (type == "Helicopter") {
				if (WorldMap->getWorld()[y][x]->getPointerHelicopter()!= nullptr && WorldMap->getWorld()[y][x]->getPointerHelicopter() == curentCoordinate->getPointerHelicopter()) {
					WorldMap->getWorld()[y][x]->setPointerHelicopter(nullptr);
				}
			}
			else {
				if (type =="People") {
					if (WorldMap->getWorld()[y][x]->getIsPeople() != nullptr && WorldMap->getWorld()[y][x]->getIsPeople() == curentCoordinate->getIsPeople()) {
						WorldMap->getWorld()[y][x]->setIsPeople(nullptr);
					}
				}
				else {
						if (WorldMap->getWorld()[y][x]->getPointerVehicleRoad() != nullptr && WorldMap->getWorld()[y][x]->getPointerVehicleRoad() == curentCoordinate->getPointerVehicleRoad()) {
							WorldMap->getWorld()[y][x]->setPointerVehicleRoad(nullptr);
						}
				}
			}
		}
	}

	WorldMap->setMoveColCoordinateMove(col);
	WorldMap->setMoveRowCoordinateMove(row);
			
}

