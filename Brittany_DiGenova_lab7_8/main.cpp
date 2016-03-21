//Brittany DIGenova
//main.cpp
//This serves as a simple driver to showcase that my various classes work together properly. These classes and member functions will be combined with
//SDL graphics to build our game interface later on

#include <iostream>
#include "watertype.h"
#include "flyingtype.h"
#include "firetype.h"

using namespace std;


int main() {
	
	//Initialize variable
	Firetype Charizard;
	Watertype Blastoise;
	Potion potion("potion", 20);
	Potion super_potion ("super_potion", 50);
	
	//show Pokemon's hit points before simple healing
	cout << "Charizard has " << Charizard.get_hit_points() << " hit points." << endl;
	
	//heal Pokemon
	Charizard.heal(potion);
	Charizard.heal(super_potion);
	
	//show Pokemon's hit points after simple healing
		cout << "Charizard has " << Charizard.get_hit_points() << " hit points." << endl;
	
	
	
	return 0;
}