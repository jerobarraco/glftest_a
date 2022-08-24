#include <iostream>

#include "../include/minefield.h"

using namespace std;


int main()
{
	Minefield mf;
	mf.GenerateMineField(10, 10, 10);
//	mf.Print();
	int x, y;
	while(true) {
		cout << std::endl<<"Try it: x=";
		cin >> x;
		if(cin.eof())
			break;

		cout << " y=";
		cin >> y;
		if(cin.eof())
			break;
		mf.Open(x, y);
		mf.Print();
	}
    return 0;
}
