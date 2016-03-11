#ifndef _COORDS
#define _COORDS

class SCoords
{
public:
	int x;
	int z;
	SCoords operator= (SCoords);
};

SCoords SCoords::operator= (SCoords operand)
{
	x = operand.x;
	z = operand.z;
	return *this;
}

#endif