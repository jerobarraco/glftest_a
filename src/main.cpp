#include <iostream>

#include "../include/minefield.h"

using namespace std;

int main()
{
	Minefield mf;
	mf.GenerateMineField(10, 10, 10);
	mf.Print();
    return 0;
}
