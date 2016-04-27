//Brittany DIGenova
//Trainer.cpp
//This file contains the basic member functions for the class type trainer. It include funcitons to encounter a wild pokemon, battle another trainer,
//get and set various trainer attributes and add pokemon to the trainer's list.

#include <iostream>
#include <string>
#include <cstdlib>
#include "trainer.h"

using namespace std;

//Default Constructor 
Trainer::Trainer( string n, int pb ) {
	if (pb < 0 ) pb = 1;
	pokeball = pb;
	name = n;
}

//Get functions
string Trainer::get_name(){
	return (name);
}

int Trainer::get_pokeball(){
	return (pokeball);
}


//The following functions output various statistics to the user 
//List the pokemon that the user has available as well as their individual hit points 
void Trainer::list_pokemon () {
	cout << "You have the following pokemon: " << endl;
	
	//Loop through all the pokemon in the trainer's pokemon vector 
	for ( int i = 0; i < pokemon.size(); i++ ){
		cout << i + 1 << ". " << pokemon[i].get_name() << ": " << pokemon[i].get_hit_points() << " hp" << endl;
	}
	cout << endl;
}


//List the potions that the user has available as well as their individual healing powers 
void Trainer::list_potion () {
	cout << "You have the following potions: " << endl;
	
	//Loop through all the potions in the trainer's potions vector 
	for ( int i = 0; i < potions.size(); i++ ){
		cout << i + 1 << ". " << potions[i].get_name() << " + " << potions[i].get_healing_power() << " health" << endl;
	}
	cout << endl;	
}

//List stats calls previous two functions to output the trainer's information
void Trainer::list_stats() {
	cout << "You have " << pokeball << " pokeballs." << endl;
	list_potion ();
	cout << endl;
	list_pokemon ();	
}


//Set functions 
//Adds pokemon to your available pokemon using push_back
void Trainer::catch_pokemon ( Pokemon input_pokemon ) {
	pokemon.push_back( input_pokemon );
	cout << "Congrats! " << input_pokemon.get_name() << " has been added to your Pokemon!" << endl;
}

//Adds potion to your available potions using push_back
void Trainer::add_potion ( Potion  input_potion ) {
	potions.push_back( input_potion );
}

//Function when run into wild pokemon and try to capture it 
void Trainer::encounter_pokemon ( Pokemon & battle_pokemon ) {
	if (pokemon[0].battle(battle_pokemon) == 1 ) catch_pokemon ( battle_pokemon );
	else {
		cout << "Oh no! " << battle_pokemon.get_name() << " got away!!" << endl;
	}
}


//Battle function creates a battle between two trainer's pokemon by looping through and calling the pokemon battle function until 
//All of a trainer's pokemon have fainted 
int Trainer::battle_trainer ( Trainer & opponent ){
	srand(time(NULL));
	
	//Declare initial variables 
	int kill = 0, choice = 0, pokemon_number;
	vector < Pokemon > usable_pokemon;	//Vector filled with pokemon that have not fainted
	vector < Pokemon > usable_opponent_pokemon; //Vector filled with opponent's pokemon that have not fainted
	Pokemon opponent_pokemon; //Used as a temp pokemon
	
	//Clear temporary vector that signifies unfainted pokemon 
	usable_pokemon.clear();
	
	//Add usable pokemon to the usable_pokemon vector using push_back
	for (int i = 0; i < pokemon.size(); i++ ){
		if (pokemon[i].get_hit_points()> 0) usable_pokemon.push_back(pokemon[i]);
	}
	
	//If there are no usable pokemon return 0 for the battle, you have lost 
	if ( usable_pokemon.size() == 0 ) {
		cout << "All your Pokemon have fainted. Go heal them, then you can battle." << endl;
		return 0;
	}
	
	//Continuous battle until all pokemon have fainted 
	while (kill == 0) {
		
		//Clear temporary vector that signifies unfainted pokemon 
		usable_pokemon.clear();
		
		//Add usable pokemon to the usable_pokemon vector using push_back
		for (int i = 0; i < pokemon.size(); i++ ){
			if (pokemon[i].get_hit_points()> 0) usable_pokemon.push_back(pokemon[i]);
		}
		
		//If there are no usable pokemon return 0 for the battle, you have lost 
		if ( usable_pokemon.size() == 0 ) {
			cout << "All your Pokemon have fainted. You lose." << endl;
			opponent.heal_all();  //Restore opponent's pokemon for a future fight 
			return 0;
		}
		
		//If the user's trainer does have healthy pokemon continue
		else {
			
			//Prompt user to choose pokemon from list 
			cout << " Please choose a Pokemon " << endl;
			list_pokemon();
			cin >> choice;
			
			//Ensure choice is valid 
			if (choice < 1 || choice > pokemon.size() ) choice = 1;
			
			//Change choice to choice - 1 since access starts at 0
			choice = choice - 1;
			
			//Safegaurd against trying to use fainted pokemon 
			if (pokemon[choice].get_hit_points() <= 0) {
				cout << "Sorry that Pokemon is fainted please pick another." << endl;
			}
			
			//If pokemon is alive and able to use proceed 
			else {
				cout << "You picked " << pokemon[choice].get_name() << "." << endl;
				
				//Clear vector representing the opponents usable pokemon 
				usable_opponent_pokemon.clear();
				
				//Retest opponents pokemon to see which ones have not fainted 
				for (int i = 0; i < opponent.pokemon.size(); i++ ){
					if (opponent.pokemon[i].get_hit_points()!=0) usable_opponent_pokemon.push_back(opponent.pokemon[i]);
				}
				
				//If the opponent has no usable pokemon then return 1 for a user victory 
				if ( usable_opponent_pokemon.size() == 0 ) {
					cout << "All the opponents Pokemon have fainted. You win!" << endl;
					opponent.heal_all(); //Restore the opponents pokemon for a future fight 
					return 1;
				}
				
				//If the user does have useable pokemon randomly pick a pokemon to use in the battle 
				else {
					pokemon_number = rand () % opponent.pokemon.size();
					
					//Pick until it is a valid pokemon that has not fainted 
					while ( opponent.pokemon[pokemon_number].get_hit_points() == 0 ) {
						pokemon_number = rand () % opponent.pokemon.size(); //randomly chooses new pokemon 
					}
					//Once two healthy pokemon are picked begin a pokemon battle 
					pokemon[choice].battle(opponent.pokemon[pokemon_number]);	
				}				
			}	
		}
	}
}

//Adds pokeball to trainer's class 
int Trainer::add_pokeball(){
	pokeball++;
}


//Heals all your pokemon 
void Trainer::heal_all(){
	for(int i = 0; i < pokemon.size(); i++ ) {
		pokemon[i].set_hit_points(pokemon[i].get_max_hit_points());
	}
}


//Checks to see if the trainer has won 
int Trainer::is_winner() {
	int count = 0;
	
	//Cycle through pokemon and check for four that are level 18 or more 
	for(int i = 0; i < pokemon.size(); i++ ) {
		if (pokemon[i].get_level() == 18 ) count++;
	}
	
	//If atleast 4 pokemon have levels over 100 then return 1 for winner 
	if (count >= 4 ) {
		cout << "Congrats you have won the game!!" << endl;
		return 1;
	}
	
	//Otherwise you have not won
	else {
		cout << "Keep training! You haven't won yet." << endl;
		return 0;
	}	
}