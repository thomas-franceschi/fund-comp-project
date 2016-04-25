//Brittany DiGenova
//moves.h
//This is the base class for flyingtype pokemon, inheriting pokemon.h

#ifndef TRAINER_H
#define TRAINER_H

#include <iostream> 
#include <string>
#include <vector>
#include "potion.h"
#include "watertype.h"
#include "flyingtype.h"
#include "firetype.h"

using namespace std;

class Trainer {
	
	public:
	Trainer(string name = "none", int pokeball = 1);
	string get_name();
	void catch_pokemon ( Pokemon );
	void add_potion ( Potion );
	void list_pokemon ();
	void list_potion ();
	void list_stats ();
	void encounter_pokemon ( Pokemon &);
	void battle_trainer ( Trainer & );
	int get_pokeball();
	int add_pokeball();
	
	private:
	string name;
	int pokeball;
	vector < Pokemon > pokemon;
	vector < Potion > potions;
};

#endif