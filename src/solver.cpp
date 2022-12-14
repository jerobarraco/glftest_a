#include "../include/solver.h"

#include <algorithm> // for randomization
#include <random> // for shuffling
#include <iostream> // for messages

#include "../include/coord.h"

Solver::Solver(std::shared_ptr<Minefield> field)
{
	_field = field;
}

void Solver::Step()
{
	// Attempt to find a cell
	dimension width = _field->GetWidth();
	dimension height = _field->GetHeight();

	// identify bombs
	Coord coord;
	for (coord.x = 0; coord.x<width; ++coord.x){
		for (coord.y= 0; coord.y<height; ++coord.y) {
			if (TryAddFlag(coord)) return;
		}
	}

	// finally pick a random one
	TryPickRandom();
}

bool Solver::TryAddFlag(Coord pos) const {
	// If a tile has the same amount of hidden squares around it as unflagged bombs remaining around it, then all the hidden squares are bombs.
	CellState state = _field->GetStateAt(pos.x, pos.y);
	// we need it to be open (not flagged nor closed)
	if (state != CellState::OPEN) return false;
	Cell cell;
	bool peekOk = _field->PeekCellAt(pos.x, pos.y, cell);
	if (!peekOk) return false;
	// actually dead
	if (cell == Cell::MINE) return true;

	// nothing to do
	if (cell == Cell::EMPTY) return false;

	// now count the amount of non open around
	int mineCount = 0;

	CellState adjState;
	Coord min, max, coord;
	coord = pos; // should copy it
	coord.adjacents(_field->GetWidth(), _field->GetHeight(), min, max);
	// count the amount of possible mines adjacent to this cell
	for (coord.x = min.x; coord.x <= max.x; ++coord.x) {
		for (coord.y = min.y; coord.y<= max.y; ++coord.y) {
			adjState = _field->GetStateAt(coord.x, coord.y);
			if (adjState != CellState::OPEN) {
				++mineCount;
			}
		}
	}

	dimension targetCount = static_cast<int>(cell);

//	std::cout << "Minecount "<< x << ","<< y <<  " "<<  targetCount << ":" << mineCount << std::endl;
	// if it has more or less covered. then were not sure
	if (mineCount != targetCount) return false;

	// otherwise all should be flagged
	for (dimension mx = min.x; mx <= max.x; ++mx) {
		for (dimension my = min.y; my<= max.y; ++my) {
			adjState = _field->GetStateAt(mx, my);
			if (adjState == CellState::CLOSED) {
				std::cout << "Flagging " << mx << ","<< my<< std::endl;
				_field->Open(mx, my, true);
				return true;
			}
		}
	}

	// if all are flagged, just keep on
	return false;
}

bool Solver::TryPickRandom() const
{
	dimension width = _field->GetWidth();
	dimension size = width * _field->GetHeight();
	// get a random list of indexes, this is the most direct way
	std::vector<int> indexes;
	indexes.resize(size);
	for (dimension i =0; i<size; ++i) {
		indexes[i] = i;
	}
	std::random_device random_dev;
	std::mt19937 generator(random_dev());
	std::shuffle(indexes.begin(), indexes.end(), generator);

	// open the 1st closed cell we find
	Coord coord;
	CellState state;
	for (dimension i = 0; i<size; ++i) {
		dimension index = indexes[i];
		coord.fromIndex(index, width);
		state = _field->GetStateAt(coord.x, coord.y);
		if (state == CellState::CLOSED) {
			std::cout << "Opening " << coord.x << ","<< coord.y<< std::endl;
			_field->Open(coord.x, coord.y);
			return true;
		}
	}

	// nothing to do
	return false;
}
