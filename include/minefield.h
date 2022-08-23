#ifndef MINEFIELD_H
#define MINEFIELD_H
#include <vector>

#include "cell.h"

class Minefield
{

public:
	void GenerateMineField(dimension width, dimension height, dimension count);
	void Print();

protected:
	void SetMine(dimension index);
	void CountMine(dimension index);

private:
	std::vector<Cell> _field;
	dimension _width, _height;
};
// i could have used a shared_ptr for dynamic array on the field which would have been probably a bit more performant.
// but it would have increased the complexity of the code. we wouldn't be able to rely on the std functions.
// and would increase the cognitive cost of the project(tm) (e.g. juniors would have more difficulty with it, and be prone to introduce problems)

#endif // MINEFIELD_H
