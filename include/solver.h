#ifndef SOLVER_H
#define SOLVER_H
#include "minefield.h"

#include <memory>

class Solver
{

public:
	Solver(std::shared_ptr<Minefield> field);
	void Step();
private:
	bool TryAddFlag(dimension x, dimension y) const;
	bool TryPickRandom() const;
	std::shared_ptr<Minefield> _field;
};

#endif // SOLVER_H
