#include "Tile.h"

//constructor
Tile::Tile(int type) :type(type), count(0) {
	this->js = openJson::GetFile();

}
//return type
int Tile::getType()
{
	return type;
}
//return count
int Tile::getCount()
{
	return count;
}
//return name
string Tile::getTypeName()
{
	for (auto a : js["Tiles"].items()) {
		if (a.value().get<int>() == type)
			return a.key();
	}
	return "";
}
//delete the resource
void Tile::deleteResource(double amount)
{
	if (amount >= count)
		count = 0;
	else
		count -= amount;
}

//add resource
void Tile::addResource(double c, string resource)
{
	string tileType = "";
	for (auto item : js["ResourcePerTile"].items()) {
		if (item.value() == resource)
			tileType = item.key();
	}
	if (tileType == "") {
		return;
		throw"cant allocate this resource to that tile";
	}
	if (js["Tiles"][tileType] != type)
	{
		return;
	}
	count += c;
}
