#include "AssertsStage.h"

//print the category
void AssertsStage::selectedCategory() const
{

	const shared_ptr<Coordinate> cat = WorldMap->getCurrentCoordinate();
	if (cat->getBuild() != nullptr) {
		cout << "SelectedCategory " << cat->getBuild()->getTypeName() << endl;
	}
	else{
		if (cat->getIsPeople()) {
			cout << "SelectedCategory " << "People" << endl;
		}
		else{
			if (cat->getIsRoad()) {
				cout << "SelectedCategory " << "Road" << endl;
			}
			else{
				cout << "SelectedCategory " << WorldMap->getTileCategoryName(cat->getPointerTile()) << endl;
			}
		}
	}
}

//print the count of the resource
void AssertsStage::SelectedResource()const
{
	cout << "SelectedResource ";
	shared_ptr<Coordinate> coordinateToPrint = WorldMap->getCurrentCoordinate();
	if (coordinateToPrint->getPointerHelicopter()){
		coordinateToPrint->getPointerHelicopter()->printResources();
	}
	else {
		if (coordinateToPrint->getPointerVehicleRoad()){
			coordinateToPrint->getPointerVehicleRoad()->printResources();
		}
		else{
			if (coordinateToPrint->getIsPeople()) {
				coordinateToPrint->getIsPeople()->printResources();
			}
			else {
				shared_ptr<Tile> tileToPrint = WorldMap->getCurrentTile();
				if (coordinateToPrint->getBuild() == nullptr) {
					int type = tileToPrint->getType();
					auto iter1 = find_if(js["Tiles"].items().begin(), js["Tiles"].items().end(), [type](const auto& x) {return x.value() == type; });
					if (iter1.key() == "Forest") {
						cout << tileToPrint->getCount() << " 0 0 0 ";
					}
					else {
						if (iter1.key() == "Field") {
							cout << "0 " << tileToPrint->getCount() << " 0 0 ";
						}
						else {
							if (iter1.key() == "IronMine") {
								cout << "0 0 " << tileToPrint->getCount() << " 0 ";
							}
							else {
								if (iter1.key() == "BlocksMine") {
									cout << "0 0 0 " << tileToPrint->getCount();
								}
							}
						}
					}
				}
				else {
					WorldMap->getCurrentCoordinate()->getBuild()->printResources();
				}
			}
		}
	}
}



//A function responsible for sending the appropriate variables to the appropriate functions
void AssertsStage::DoAsserts() const
{
	for (const auto& assert : asserts) {
		if (assert == "SelectedCategory") {
			selectedCategory();
		}
		else {
			if (assert == "SelectedResource") {
				SelectedResource();
			}
			else {
				if (assert == "CityCount") {
					countType("CityCount");
				}
				else {
					if (assert == "VillageCount") {
						countType("VillageCount");
					}
					else {
						if (assert == "RoadCount") {
							countType("RoadCount");
						}
						else {
							if (assert == "SelectedPeople") {
								selectPeople();
							}
							else {
								if (assert == "SelectedComplete") {
									SelectedComplete();
								}
								else {
									if (assert == "SelectedCar") {
										selectedCar();
									}
									else {
										if (assert == "SelectedTruck") {
											selectedTrack();
										}
										else {
											if (assert == "CarCount") {
												carCount();
											}
											else {
												if (assert == "TruckCount") {
													truckCount();
												}
												else {
													if (assert == "HelicopterCount") {
														helicopterCount();
													}
													else {
														if (assert == "SelectedCoordinates") {
															SelectedCoordinates();
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
			}
		}
	}
}



//check the count of the build.
void AssertsStage::countType(string countType)const
{
	if (countType == "RoadCount") {
		cout << "RoadCount " << WorldMap->getCountRoad() << endl;
	}
	else {
		if (countType == "VillageCount") {
			cout << "VillageCount " << WorldMap->getCountVillage() << endl;
		}
		else {
			if (countType == "CityCount") {
				cout << "CityCount " << WorldMap->getCountCity() << endl;
			}
		}
	}

}
//check if the city completed
string AssertsStage::checkIsCompleted()const
{
	string type;
	vector<int>resources;
	shared_ptr<Coordinate> isCompleted = WorldMap->getCurrentCoordinate();
	if (isCompleted->getBuild()) {
		type = isCompleted->getBuild()->getTypeName();
		resources = isCompleted->getBuild()->getResource();
	}
	else {
		if (isCompleted->getPointerHelicopter()) {
			type = "Helicopter";
			resources = isCompleted->getPointerHelicopter()->getResource();
		}
		else {
			if (isCompleted->getPointerVehicleRoad()) {
				type = isCompleted->getPointerVehicleRoad()->getTypeName();
				resources = isCompleted->getPointerVehicleRoad()->getResource();
			}
			else {
				if (isCompleted->getIsPeople()) {
					type = "People";
					resources = isCompleted->getIsPeople()->getResource();
				}
				else
					return "False";//עבור כביש
			}
		}
	}
	for (int i = 0; i < js["Costs"][type].size();i++) {
		if (resources[i] < js["Costs"][type][i].get<int>()) {
			return "False";
		}
	}
	return "True";
}
//make empty the coordinate
void AssertsStage::EmptyAllResource(int row, int col)
{
	WorldMap->makeEmpty(row, col);
}
//check count of people
void AssertsStage::selectPeople()const
{
	int countOfPeople = WorldMap->amountOfPeople(*(WorldMap->getCurrentCoordinate()));
	cout << "SelectedPeople " << countOfPeople << endl;
}
//check count of car
void AssertsStage::selectedCar()const
{
	cout << "SelectedCar " << WorldMap->getCurrentCoordinate()->getBuild()->getCountOfCars() << endl;
}
//check count of truck
void AssertsStage::selectedTrack()const
{
	cout << "selectedTruck " << WorldMap->getCurrentCoordinate()->getBuild()->getCountOfTracks() << endl;
}
//print if the current select is completed
void AssertsStage::SelectedComplete()const {
	cout << "SelectedComplete "<<checkIsCompleted()<< endl;
}
//print the count of the car
void AssertsStage::carCount()const
{
	cout << "CarCount " << WorldMap->getCountCar() << endl;
}
//print the count of the truck
void AssertsStage::truckCount()const
{
	cout << "TruckCount " << WorldMap->getCountTruck() << endl;
}
//print the count of the helicopter
void AssertsStage::helicopterCount()const
{
	cout << "HelicopterCount " << WorldMap->getCountHelicopter() << endl;
}
//print the coordinate
void AssertsStage::SelectedCoordinates() const
{
	cout << "SelectedCoordinates " << (WorldMap->getMoveColCoordinate() - 1) / (js["Sizes"]["Tile"][0].get<int>()) << " " << (WorldMap->getMoveRowCoordinate() - 1) / (js["Sizes"]["Tile"][1].get<int>());

}


