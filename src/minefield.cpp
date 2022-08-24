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
	_fieldState.resize(size);
	for (dimension i=0; i<size; ++i){
		// initialization is not super important the 1st time, but in case the user calls this function again.
		_field[i] = Cell::EMPTY;
		_fieldState[i] = CellState::CLOSED;
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

void Minefield::Print(bool debug)
{
	Coord coord;

	for (dimension x = 0; x<_width; ++x){
		coord.x = x;
		for (dimension y = 0; y<_height; ++y) {
			coord.y = y;
			dimension index = coord.toIndex(_width);
			CellState state = _fieldState[index];
			if (state == CellState::OPEN || debug) {
				Cell cell = _field[index];
				std::cout << CELL_CHARS[static_cast<int>(cell)];
			} else if (state == CellState::CLOSED) {
				std::cout << "_";
			}else if (state == CellState::FLAGGED){
				std::cout << "X";
			}
		}
		std::cout<<std::endl;
	}
}

Cell Minefield::Open(dimension x, dimension y, bool justFlag)
{
//	std::cout << "Opening " << x << "."<< y<< std::endl;
	if (x >= _width || y>= _height) {
		std::cout << "Warning: Attempted to open a cell out of bounds."<< std::endl;
		return Cell::EMPTY;
	}

	Cell cell = GetCellAt(x, y);
	Coord coord;
	coord.x = x;
	coord.y = y;

	dimension index = coord.toIndex(_width);
	CellState state = _fieldState[index];
	if (state == CellState::OPEN) {
		// Cell already opened not doing that again
		return cell;
	}

	if(justFlag) {
		_fieldState[index] = CellState::FLAGGED;
		return cell;
	}

	_fieldState[index] = CellState::OPEN;

	// actually try to open
	if (cell == Cell::MINE) {
		std::cout << "BOOM! You're dead" << std::endl;
		return cell;
	}

	if (cell != Cell::EMPTY) return cell;

	// lets automagically open the adjacents, only happens for empty cells
	Coord min, max, coord_to;
	coord.adjacents(_width, _height, min, max);
	for (dimension mx = min.x; mx <= max.x; ++mx) {
		coord_to.x = mx;
		for (dimension my = min.y; my<= max.y; ++my) {
			coord_to.y = my;
			Open(coord_to.x, coord_to.y, false);
		}
	}

	return cell;
}

bool Minefield::IsSolved() const
{
	for (dimension i=0; i<_field.size(); ++i) {
		bool isMine = _field[i] == Cell::MINE;
		CellState state = _fieldState[i];

		bool unsolved = isMine ? state != CellState::FLAGGED : state != CellState::OPEN;
		if (unsolved) return false;
	}
	return true;
}

CellState Minefield::GetStateAt(dimension x, dimension y) const {
	if (x>=_width || y>=_width) return CellState::CLOSED;
	Coord coord;
	coord.x = x;
	coord.y = y;
	return _fieldState[coord.toIndex(_width)];
}

bool Minefield::PeekCellAt(dimension x, dimension y, Cell &cell) const
{
	if (x>=_width || y>=_width) return false;

	CellState state = GetStateAt(x, y);
	if (state != CellState::OPEN) return false;

	cell = GetCellAt(x, y);
	return true;
}

Cell Minefield::GetCellAt(dimension x, dimension y) const
{
	if (x >= _width || y>= _height) return Cell::EMPTY;
	Coord coord;
	coord.x = x;
	coord.y = y;
	return _field[coord.toIndex(_width)];
}

void Minefield::SetMine(dimension index)
{
	if (index >= _field.size()) {
		std::cout << "Warning: Attempted to set a mine on an invalid index."<< std::endl;
		return;
	}

	Coord coord;
	coord.fromIndex(index, _width);

	Coord coord_to;

	// mark current cell as mined
	_field[index] = Cell::MINE;

	// now mark the surrounding cells
	// go from -1 to +1 in both directions
	// i could have embedded this into the for, i would also need to increase the size of the type to make it signed safely.
	// and would make the logic a bit more complex
	Coord min, max;
	coord.adjacents(_width, _height, min, max);
	for (dimension mx = min.x; mx <= max.x; ++mx) {
		coord_to.x = mx;
		for (dimension my = min.y; my<= max.y; ++my) {
			coord_to.y = my;
			CountMine(coord_to.toIndex(_width));
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
		// Not an error. If the cell has a mine don't count anything.
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
