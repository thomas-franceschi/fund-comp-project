//Brittany DiGenova
//moves.h
//This is the base class for the trainer who is the main component of the game and primarily interacts with the  graphics
//The trainer carries pokemon, potions and pokeballs and is able to encounter pokemon or fight other trainers 

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
	Trainer(string name = "none", int pokeball = 1);	//Constructor with fall back values 
	string get_name();									//get function
	void catch_pokemon ( Pokemon );						//Adds the given pokemon to the trainer's vector of pokemon 
	void add_potion ( Potion );							//Adds the potion to the trainer's list of available potions 
	void list_pokemon ();								//Output available pokemon and their hit_points
	void list_potion ();								//Output available potions and their healing value 
	void list_stats ();									//List all stats (potion and pokemon information)
	void encounter_pokemon ( Pokemon &);				//Sends trainer into a battle with a wild pokemon if trainer wins he catches it
	int battle_trainer ( Trainer & );					//Battles another trainer until someone has all fainted pokemon
	int get_pokeball();									// Get Function
	int add_pokeball();									// Get Function
	void heal_all();									//Heals all of the pokemon that a trainer has to full health 
	int is_winner();									//Checks to see if win requirements are met
	int dead_pokemon();
	//void check_press();									//Checks to see which keys have been pressed 
	
	private:
	string name;
	int pokeball;
	vector < Pokemon > pokemon;		//vector storing all the trainer's available pokemon
	vector < Potion > potions;		//vector storing all the trainer's available potions
};

#endif