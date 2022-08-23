#include "../include/minefield.h"

#include <iostream> // for messages
#include <algorithm> // for randomization
#include <random> // for shuffling

void Minefield::GenerateMineField(dimension width, dimension height, dimension count)
{
	dimension size = width * height;

	// count has not been defined on the specification, i will assume is the mine count
	if (count >= size ) {
		std::cout << "Warning, the number of mines is bigger than the number of cells in the field" << std::endl;
	}

	// stores the indexes for the mines. to help with randomization
	std::vector<dimension> mine_indexes;
	mine_indexes.resize(size);

	// reset and clear the field
	field.resize(size);
	for (dimension i=0; i<size; ++i){
		field[i] = Cell::EMPTY;
		mine_indexes[i] = i;
	}

	// set the mines
	// 1st randomize the indexes
	std::random_device random_dev;
	std::mt19937 generator(random_dev());
	// could have also used std::rand instead of the generator but this seems to be a bit better in terms of randomization
	std::shuffle(mine_indexes.begin(), mine_indexes.end(), generator);

	// actually mine the field
	for (dimension i = 0; i< count; ++i) {


	}

}

void Minefield::SetMine(dimension index)
{

}
