//Brittany DiGenova
//moves.h
//This is the base class for flyingtype pokemon, inheriting pokemon.h

#ifndef MOVES_H
#define MOVES_H

#include <iostream> 
#include <string>

using namespace std;

class Moves {
	
	public:
	Moves( string name = "none", int power = 10, int accuracy = 70); //Constructor with fall backs 
	int get_power();
	int get_accuracy();
	string get_name();
	
	private:
	string name;	//Name of move 
	int power;		//Determines damage done by move 
	int accuracy; 	//Value between 1 and 100 that denotes percentage change of making contact 
};

#endif