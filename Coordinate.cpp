#include "Coordinate.h"
#include "Tile.h"

//return the pointer for the tile
shared_ptr<Tile> Coordinate::getPointerTile()
{
    return pointerTile;
}
//edit the helicopter pointer
void Coordinate::setPointerHelicopter(shared_ptr<vehicle> p)
{
    pointerHelicopter = p;
}
//return the helicopter pointer
shared_ptr<vehicle> Coordinate::getPointerHelicopter()
{
    return pointerHelicopter;
}
//edit the pointer to vehicleRoad
void Coordinate::setPointerVehicleRoad(shared_ptr<vehicle> p)
{
    pointerVehicleRoad=p;
}
//return the pointer to vehicleRoad
shared_ptr<vehicle> Coordinate::getPointerVehicleRoad()
{
    return pointerVehicleRoad;
}
//return the people
shared_ptr<vehicle> Coordinate::getIsPeople()
{
    return isPeople;
}
//return the build
Build* Coordinate::getBuild()
{
    return build;
}
int Coordinate::GetPositionX()
{
    return position_x;
}
int Coordinate::GetPositionY()
{
    return position_y;
}
//edit the people
void Coordinate::setIsPeople(shared_ptr<vehicle> isPeople)
{
    if (isPeople == nullptr)
        isPeople = nullptr;
    else
        this->isPeople = isPeople;
}
//edit the build
bool Coordinate::setBuild(string name)
{
    if (build != nullptr || pointerTile->getType() != js["Tiles"]["Ground"].get<int>())
        return false;
    build = new Build(name);
    return true;
}
//return the road
bool Coordinate::getIsRoad()
{
    return isRoad;
}
//edit the road
void Coordinate::setIsRoad(bool isRoad)
{
    this->isRoad = isRoad;
}


