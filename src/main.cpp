#include <iostream>
#include <memory>
#include <ctime>

#include "../include/minefield.h"
#include "../include/solver.h"

int main()
{
	std::srand(std::time(0));
	std::shared_ptr<Minefield> field = std::make_shared<Minefield>();

	int width=5;
	int height=5;
	int count=3;
	field->GenerateMineField(width, height, count);
	field->Print(true);
	int x, y;

	Solver solver(field);

	bool isDead = false;
	while(!field->IsSolved() && !isDead) {
		std::cout << std::endl;
		solver.Step();
		field->Print();
		isDead = field->IsDead();
	}

	std::cout << "Game over: " << (isDead ? "You lost" : "You won") << std::endl;
	return 0;
}
