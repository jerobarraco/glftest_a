#ifndef SOLVER_H
#define SOLVER_H
#include <memory>

#include "minefield.h"
#include "coord.h"

class Solver
{

public:
	Solver(std::shared_ptr<Minefield> field);
	void Step();

private:
	bool TryAddFlag(Coord pos) const;
	bool TryPickRandom() const;

	std::shared_ptr<Minefield> _field;
};

#endif // SOLVER_H
