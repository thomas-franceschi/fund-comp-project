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
	void heal( Potion );
	int get_hit_points();
	void make_attack( Pokemon );
	void defend( Pokemon );
	
	private:
	string name;
	int hit_points;
	int attack;
	int defense;
	int special_attack;
	int special_defense;
	int speed;
	int level;
};

#endif