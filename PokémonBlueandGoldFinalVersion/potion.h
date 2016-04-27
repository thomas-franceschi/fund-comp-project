//Brittany DiGenova
//potion.h
//This is the base class for healing potions which are carried by trainers and used to increase health of pokemon
#ifndef POTION_H
#define POTION_H

#include <iostream>
#include <string>

using namespace std;

class Potion {
	
	public:
	Potion( string name = "Potion", int healing_power = 20 );	//Constructor with fall back values
	int get_healing_power();		//Amount that potion is able to increase health of pokemon
	string get_name();				//Get function
	
	private:
	string name;
	int healing_power;
};

#endif