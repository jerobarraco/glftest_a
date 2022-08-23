#include "../include/minefield.h"

#include <iostream> // for messages
#include <algorithm> // for randomization
#include <random> // for shuffling

#include "../include/coord.h"

void Minefield::GenerateMineField(dimension width, dimension height, dimension count)
{
	_width = width;
	_height = height;
	dimension size = width * height;

	// count has not been defined on the specification, i will assume is the mine count
	if (count >= size ) {
		std::cout << "Warning, the number of mines is bigger than the number of cells in the field" << std::endl;
	}

	// stores the indexes for the mines. to help with randomization
	std::vector<dimension> mine_indexes;
	mine_indexes.resize(size);

	// reset and clear the field
	_field.resize(size);
	for (dimension i=0; i<size; ++i){
		// initialization is not super important the 1st time, but in case the user calls this function again.
		_field[i] = Cell::EMPTY;
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
		SetMine(mine_indexes[i]);
	}
}

void Minefield::Print()
{
	Coord coord;
	coord.stride = _width;

	for (dimension x = 0; x<_width; ++x){
		coord.x = x;
		for (dimension y = 0; y<_height; ++y) {
			coord.y = y;
			Cell cell = _field[coord.toIndex()];
			std::cout << CELL_CHARS[static_cast<int>(cell)];
		}
		std::cout<<std::endl;
	}
}

void Minefield::SetMine(dimension index)
{
	if (index >= _field.size()) {
		std::cout << "Warning: Attempted to set a mine on an invalid index;"<< std::endl;
		return;
	}

	Coord coord;
	coord.fromIndex(index, _width);

	Coord coord_to;
	coord_to.stride = _width;

	// mark current cell as mined
	_field[index] = Cell::MINE;

	// now mark the surrounding cells
	// go from -1 to +1 in both directions
	// i could have embedded this into the for, i would also need to increase the size of the type to make it signed safely.
	// and would make the logic a bit more complex
	dimension min_x = coord.x > 0 ? coord.x-1: 0;
	dimension min_y = coord.y > 0 ? coord.y-1: 0;
	dimension max_x = coord.x < _width-1 ? coord.x+1: coord.x;
	dimension max_y = coord.y < _height-1 ? coord.y+1: coord.y;

	for (dimension mx = min_x; mx <= max_x; ++mx) {
		coord_to.x = mx;
		for (dimension my = min_y; my<= max_y; ++my) {
			coord_to.y = my;
			CountMine(coord_to.toIndex());
		}
	}
}

void Minefield::CountMine(dimension index) {
	if (index >=_field.size()) {
		std::cout << "Warning: Attempted to count a mine on an invalid index;"<< std::endl;
		return;
	}

	Cell cell = _field[index];
	if (cell == Cell::MINE){
		std::cout << "Attempted to count a mine on a mine."<< std::endl;
		return;
	}

	// safe to do >= since Mine above returns.
	if (cell >= Cell::M8) {
		std::cout <<  "Warning: Attempted to count a mine on a cell with too many mines around."<< std::endl;
		return;
	}

	// if all is fine do increment.
	_field[index] = static_cast<Cell>(static_cast<int>(cell+1));
}
