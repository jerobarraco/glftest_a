#include <iostream>
#include <memory>

#include "../include/minefield.h"
#include "../include/solver.h"

int main()
{
	std::shared_ptr<Minefield> field = std::make_shared<Minefield>();

	int width=5, height=5, count=5;
	/*
	std::cout << "Hello, enter your preferences: " << std::endl;
	std::cout << "\twidth= ";
	std::cin >> width;
	std::cout << "\theight= ";
	std::cin >> height;
	std::cout << "\tcount= ";
	std::cin >> count;
*/
	field->GenerateMineField(width, height, count);
//	field.Print();
	int x, y;

	Solver solver(field);



	return 0;
	while(true) {
		std::cout << std::endl<<"Try it" << std::endl;
		std::cout << "x=";
		std::cin >> x;
		if(std::cin.eof())
			break;

		std::cout << " y=";
		std::cin >> y;
		if(std::cin.eof())
			break;

		Cell cell = field->Open(x, y);
		field->Print();
		if (cell == Cell::MINE) {
			std::cout << "You're dead game over"<< std::endl;
			break;
		}
		if (field->IsSolved()) {
			std::cout << "You've solved the game! but it still game over" << std::endl;
			break;
		}
	}
    return 0;
}
