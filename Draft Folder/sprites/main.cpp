//Brittany DIGenova
//main.cpp
//This serves as a simple driver to showcase that my various classes work together properly. These classes and member functions will be combined with
//SDL graphics to build our game interface later on

#include <iostream>
#include "trainer.h"

using namespace std;


int main() {
	
	//Initialize firetype pokemon
	Firetype Charmander; //No strengths or weaknesses yet 
	Firetype Ponyta;
	Firetype Magby;
	Firetype Flareon;
	Firetype Torchic("Torchic", 45,60, 40, 7, 12, 0, 0);
	
	//Initialize watertype pokemon 
	Watertype Squirtle("Squirtle", 44, 48, 65, 4, 12, 0, 0 );
	Watertype Horsea("Horsea", 30, 40, 70, 7, 12, 0, 0);
	Watertype Palpitoad("Tympole", 50, 50, 40, 9, 12, 0, 0);
	Watertype Mantyke("Mantyke", 45, 20, 50, 7, 12, 0, 0 );
	Watertype Spheal ("Spheal", 70, 40, 50, 4, 12, 0, 0 );
	
	//Initialize Flyingtype Pokemon
	Flyingtype Caterpie("Caterpie", 45, 30, 35, 2, 12, 0, 0);
	Flyingtype Zapdos;
	Flyingtype Pidgey;
	Flyingtype Zubat;
	Flyingtype Spearow;
	Flyingtype Dragonite;
	
	//Make kyle, thomas and brittany Pokemon
	Watertype Kyle("Kyle (AKA Whale)", 150, 60, 55, 5, 12); //No strengths or weaknesses yet
	Firetype Thomas("Tbone", 150, 60, 55, 5, 12, 0, 0);
	Flyingtype Brittany("Britters", 150, 60, 55, 5, 12, 0, 0);
	
	//Initialize Potions 
	Potion potion("potion", 20);
	Potion super_potion ("super_potion", 50);
	
	//Initialize moves 
	Moves pound("Pound", 40, 90);
	Moves hydro_pump("Hydro Pump", 110, 80);
	Moves headbutt("Headbutt", 70, 100);
	Moves tackle("Tackle", 50, 90);
	Moves bodyslam("Bodyslam", 85, 75);
	
	//Add moves to Brittany pokemon
	Brittany.add_move(bodyslam);
	Brittany.add_move(headbutt);
	
	Kyle.add_move(bodyslam);
	Kyle.add_move(headbutt);
	
	//Initialize trainer
	Trainer Kyle_Williams("Kyle Williams", 2);
	cout << "The trainer's name is " << Kyle_Williams.get_name() << " and he has " << Kyle_Williams.get_pokeball() << " pokeballs." << endl;
	
	//Print Kyle's stats
	cout << " Prior to the battle Kyle has " << Kyle.get_hit_points() << " hit points." << endl;
	
	//Attack Kyle 
	if (Brittany.battle(Kyle) == 1) cout << "You Win!" << endl;
	
	else {
		cout << "You lose!" << endl;
	}
	
	//Print Kyle's stats
	cout << " After the battle Kyle has " << Kyle.get_hit_points() << " hit points." << endl;
	cout << " After the battle Brittany has " << Brittany.get_hit_points() << " hit points." << endl;
	
	/*//show Pokemon's hit points before simple healing
	cout << "Charmander has " << Charmander.get_hit_points() << " hit points." << endl;
	lpo0pooooooooooooooo-
	//heal Pokemon
	Charmander.heal(potion);
	Charmander.heal(super_potion);
	
	//show Pokemon's hit points after simple healing
		cout << "Charmander has " << Charmander.get_hit_points() << " hit points." << endl;*/
	
	
	
	return 0;
}