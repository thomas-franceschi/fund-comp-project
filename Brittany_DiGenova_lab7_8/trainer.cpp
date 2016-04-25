//Brittany DIGenova
//Trainer.cpp
//This file contains the basic member functions for the class type trainer 

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

void Trainer::list_pokemon () {
	
	cout << "You have the following pokemon: " << endl;
	
	for ( int i = 0; i < pokemon.size(); i++ ){
		cout << i + 1 << ". " << pokemon[i].get_name() << ": " << pokemon[i].get_hit_points() << " hp" << endl;
	}
	
	cout << endl;
}

void Trainer::list_potion () {
	
	cout << "You have the following potions: " << endl;
	
	for ( int i = 0; i < potions.size(); i++ ){
		cout << i + 1 << ". " << potions[i].get_name() << endl;
	}
	
	cout << endl;	
}

void Trainer::list_stats() {
	
	list_potion ();
	
	list_pokemon ();
	
}


//Set functions 

void Trainer::catch_pokemon ( Pokemon input_pokemon ) {
	pokemon.push_back( input_pokemon );
	cout << "Congrats! " << input_pokemon.get_name() << " has been added to your Pokemon!" << endl;
}

void Trainer::add_potion ( Potion  input_potion ) {
	potions.push_back( input_potion );
}


void Trainer::encounter_pokemon ( Pokemon & battle_pokemon ) {
	if (pokemon[0].battle(battle_pokemon) == 1 ) catch_pokemon ( battle_pokemon );
	else {
		cout << "Oh no! " << battle_pokemon.get_name() << " got away!!" << endl;
	}
}


//Battle function 
int Trainer::battle_trainer ( Trainer & opponent ){
	srand(time(NULL));
	
	int kill = 0, choice = 0, pokemon_number;
	vector < Pokemon > usable_pokemon;
	vector < Pokemon > usable_opponent_pokemon;
	Pokemon opponent_pokemon;
	
	while (kill == 0) {
		
		usable_pokemon.clear();
		
		for (int i = 0; i < pokemon.size(); i++ ){
			if (pokemon[i].get_hit_points()> 0) usable_pokemon.push_back(pokemon[i]);
		}
		
		if ( usable_pokemon.size() == 0 ) {
			cout << "All your Pokemon have fainted. Go heal them, then you can battle." << endl;
			return 0;
		}
		
		else {
			cout << " Please choose a Pokemon " << endl;
			list_pokemon();
			cin >> choice;
			
			if (choice < 1 || choice > pokemon.size() ) choice = 1;
			
			//Change choice to choice - 1 since access starts at 0
			choice = choice - 1;
			
			if (pokemon[choice].get_hit_points() <= 0) {
				cout << "Sorry that Pokemon is fainted please pick another." << endl;
			}
			
			else {
				cout << "You picked " << pokemon[choice].get_name() << "." << endl;
				usable_opponent_pokemon.clear();
				for (int i = 0; i < opponent.pokemon.size(); i++ ){
					if (opponent.pokemon[i].get_hit_points()!=0) usable_opponent_pokemon.push_back(opponent.pokemon[i]);
				}
		
				if ( usable_opponent_pokemon.size() == 0 ) {
					cout << "All the opponents Pokemon have fainted. You win!" << endl;
					return 1;
				}
				
				else {
					pokemon_number = rand () % opponent.pokemon.size();
					
					while ( opponent.pokemon[pokemon_number].get_hit_points() == 0 ) {
						//choose a different pokemon
						pokemon_number = rand () % opponent.pokemon.size();
					}
					
					pokemon[choice].battle(opponent.pokemon[pokemon_number]);	
				}				
			}	
		}
	}
}


int Trainer::add_pokeball(){
	pokeball++;
}
