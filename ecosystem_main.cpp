#include <iostream>
#include <cstring>
#include <ctime>
#include <cstdlib>
#include "ecosystem.h"

using namespace std;

int main()
{
	int dimension, lake, hills, days;						//dimension: Terrain's size, lake: lake's size, hills: number of hills, days: days for the simulation
	cout << "Give ecosystem's dimension: (>=10)\n";
	cin >> dimension;
	if(dimension < 10)
	{
		cout << "Input error!\n";
		return -1;
	}

	srand(time(NULL));
	Ecosystem ecosystem(dimension);							//creating ecosystem with size "dimension"

	lake = rand() %dimension +1;							//from 1 up to "dimension"
	cout << "Give number of hills:\n";
	cin >> hills;
	cout << endl;

	ecosystem.MapGenerator(lake,hills);						//creating river, lake, hills, meadows and placing plants and animals
	
	cout << "Give number of days for the simulation:\n";
	cin >> days;

	ecosystem.RunEcosystem(days);							//running ecosystem's simulation
	return 0;
}
