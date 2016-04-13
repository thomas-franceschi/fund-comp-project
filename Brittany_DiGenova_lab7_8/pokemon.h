//Brittany DiGenova
//pokemon.h
//This is the base class for the pokemon inheritance structure
#ifndef PACKAGE_H
#define PACKAGE_H

#include <iostream> 
#include "potion.h"
#include <string>

using namespace std;

class Pokemon {
	
	public:
	Pokemon(string name="Pokemon", int hit_points = 0, int attack = 0, int defense = 0, int special_attack = 0, int special_defense = 0, int speed = 0, int level = 2);
	int battle( Pokemon );
	void heal( Potion );		//Uses potion to heal pokemon 
	int get_hit_points();
	void make_attack( Pokemon );	//makes attack on specified pokemon 
	void defend( Pokemon );
	void check_pokemon;  //Checks to see if pokemon should faint, evolve etc. 
	void evolve();		// Sets evolved pokemon attributes 
	
	private:
	string name;
	int hit_points;
	int attack;
	int defense;
	int special_attack;
	int special_defense;
	int speed;
	int level;
	int evolve_level;
};

#endif