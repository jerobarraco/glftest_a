#include <iostream>

#include "../include/minefield.h"

using namespace std;

int main()
{
    cout << "Hello World!" << endl;
	Minefield mf;
	mf.GenerateMineField(10, 10, 70);
	mf.Print();
    return 0;
}
