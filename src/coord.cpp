#include "../include/coord.h"


dimension Coord::toIndex(dimension stride)
{
	return x + (y*stride);
}

void Coord::fromIndex(dimension index, dimension stride)
{
	if (stride == 0) {
		y = 0;
		x = 0;
		return;
	}

	y = (index/stride);
	x = (index%stride);
}

void Coord::adjacents(dimension width, dimension height, Coord &min, Coord &max)
{
	min.x = x > 0 ? x-1: 0;
	min.y = y > 0 ? y-1: 0;
	max.x = x < width-1 ? x+1: x;
	max.y = y < height-1 ? y+1: y;
}

