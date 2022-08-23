#include "../include/coord.h"


dimension Coord::toIndex()
{
	return x + (y*stride);
}

void Coord::fromIndex(dimension index)
{
	y = (index/stride);
	x = (index%stride);
}

