//Brittany DiGenova
//potion.h
//This is the base class for healing potions 

#include <iostream>
#include <string>

using namespace std;

class Potion {
	
	public:
	Potion( string name = "Potion", int healing_power = 20 );
	int get_healing_power();
	
	private:
	string name;
	int healing_power;
};

