#ifndef COORD_H
#define COORD_H
#include "cell.h"

class Coord
{
public:
	dimension x = 0;
	dimension y = 0;
	dimension stride = 0;
	dimension toIndex();

	void fromIndex(dimension index);
};

#endif // COORD_H
