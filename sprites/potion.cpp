//Brittany DiGenova
//pokemon.cpp
//This file contains the basic member functions for the class type potion

#include <iostream>
#include "potion.h"

using namespace std;

Potion::Potion( string n, int hp ){
	if (hp < 0) hp = 0;
	
	healing_power = hp;
	name = n;
}


int Potion::get_healing_power() {
	
	return (healing_power);
	
}

string Potion::get_name() {
	return (name);
}