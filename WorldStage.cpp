#include "WorldStage.h"


//Creates a pointer to the data
void WorldStage::BuildWorldMap()/*throw(const char*)*/
{
	if (!world)
		cout << "";
	myWorld = make_shared<World>(world->data);
}

//get function
const shared_ptr<World>  WorldStage::getWorldMap()
{
	return myWorld;
}
