//Brittany DiGenova
//pokemon.h
//This is the base class for the pokemon inheritance structure. It stores the main components necessary for pokemon to battle 
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
	Pokemon(string name="Pokemon", int max_hit_points = 100, int hit_points = 0, int attack = 0, int defense = 0, int level = 2, int evolve_level = 12, int exp = 10 );
	int battle( Pokemon & );
	void heal( Potion );			//Uses potion to heal pokemon 
	int get_hit_points();			//get function
	int get_attack();				//get function 
	int get_defense();				//get function
	int get_level();				//get function
	string get_name ();				//get function 
	int get_max_hit_points();		//get function
	void make_attack( Pokemon & );	//makes attack on specified pokemon 
	void deduct_hit_points(int); 	//subtract from hit_point amount (used to make logical sense in battle functions)
	void defend( Pokemon & );		//Read in pokemon performs attack on player's pokemon
	void check_pokemon ();  		//Checks to see if pokemon should faint, evolve etc. 
	void evolve();					// Sets evolved pokemon attributes 
	void add_move( Moves ); 		//Adds inputted move to moves vector
	void list_moves();				//list moves stored in moves vector 
	void set_hit_points(int);		//Set function 
	
	private:
	string name;				//Stores pokemon name
	int max_hit_points;			//Maximum health that a pokemon can store 
	int hit_points;				//Hit points signify health, zero means pokemon have fainted 
	int attack;					//Causes attacks to inflict more damage 
	int defense;				//Decreases amount of hitpoints taken away when defending an attack
	int level;					//Current level of pokemon
	int evolve_level;			//Level at which pokemon evolves 
	int exp;
	vector < Moves > moves; 	//Stores the moves that the pokemon is capable of performing 
};

#endif