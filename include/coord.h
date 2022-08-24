#ifndef COORD_H
#define COORD_H
#include "cell.h"

class Coord
{
public:
	dimension x = 0;
	dimension y = 0;
	dimension toIndex(dimension stride);

	void fromIndex(dimension index, dimension pStride);
	void adjacents(dimension width, dimension height, Coord& min, Coord& max);
};

#endif // COORD_H
