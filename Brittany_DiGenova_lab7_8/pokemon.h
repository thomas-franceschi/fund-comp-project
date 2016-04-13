//Brittany DiGenova
//pokemon.h
//This is the base class for the pokemon inheritance structure
#ifndef POKEMON_H
#define POKEMON_H

#include <iostream> 
#include "potion.h"
#include "moves.h"
#include <string>
#include <vector>

using namespace std;

class Pokemon {
	
	public:
	Pokemon(string name="Pokemon", int hit_points = 0, int attack = 0, int defense = 0, int level = 2, int evolve_level = 12 );
	int battle( Pokemon );
	void heal( Potion );		//Uses potion to heal pokemon 
	int get_hit_points();
	void make_attack( Pokemon );	//makes attack on specified pokemon 
	void defend( Pokemon );
	void check_pokemon ();  //Checks to see if pokemon should faint, evolve etc. 
	void evolve();		// Sets evolved pokemon attributes 
	
	private:
	string name;
	int hit_points;
	int attack;
	int defense;
	int level;					//Current level of pokemon
	int evolve_level;			//Level at which pokemon evolves 
	vector < Moves > moves; 	//Stores the moves that the pokemon is capable of performing 
};

#endif