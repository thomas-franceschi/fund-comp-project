//Brittany DiGenova
//pokemon.cpp
//This file contains the basic member functions for the class type potion which are carried by trainers and used to heal pokemon

#include <iostream>
#include "potion.h"

using namespace std;

//Default constructor
Potion::Potion( string n, int hp ){
	if (hp < 0) hp = 0;
	
	healing_power = hp;
	name = n;
}

//Get functions
int Potion::get_healing_power() {
	return (healing_power);	
}

string Potion::get_name() {
	return (name);
}