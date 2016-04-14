#pragma once

#include <TL-Engine.h>
#include "Coords.h"
#include "enumeratedTypes.h"
using namespace tle;

class CTile
{
public:
	IModel* model;		 //tile model for the user interface
	SCoords coords;		 //the coordinates of this tile
	int cost;			 //cost reach this tile
	ETerrain terrain;	 //the type of ground, used for skin in ui
	SCoords parent;	//coordinates of the previous node
};
