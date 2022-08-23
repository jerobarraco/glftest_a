#include "../include/coord.h"


dimension Coord::toIndex()
{
	return x + (y*stride);
}

void Coord::fromIndex(dimension index, dimension pStride)
{
	stride = pStride;
	if (stride == 0) {
		y = 0;
		x = 0;
		return;
	}

	y = (index/stride);
	x = (index%stride);
}

