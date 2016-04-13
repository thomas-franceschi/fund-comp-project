//Brittany DIGenova
//main.cpp
//This serves as a simple driver to showcase that my various classes work together properly. These classes and member functions will be combined with
//SDL graphics to build our game interface later on

#include <iostream>
#include "watertype.h"
#include "flyingtype.h"
#include "firetype.h"

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
	Watertype Kyle("Kyle (AKA Whale)", 52, 60, 55, 5, 12, 0, 0); //No strengths or weaknesses yet
	Firetype Thomas("Tbone", 52, 60, 55, 5, 12, 0, 0);
	Flyingtype Brittany("Britters", 52, 60, 55, 5, 12, 0, 0);
	
	//Initialize Potions 
	Potion potion("potion", 20);
	Potion super_potion ("super_potion", 50);
	
	//Initialize moves 
	Moves pound("Pound", 40, 100);
	Moves hydro_pump("Hydro Pump", 110, 80);
	Moves headbutt("Headbutt", 70, 100);
	Moves tackle("Tackle", 50, 100);
	Moves bodyslam("Bodyslam", 85, 100);
	
	//show Pokemon's hit points before simple healing
	cout << "Charmander has " << Charmander.get_hit_points() << " hit points." << endl;
	
	//heal Pokemon
	Charmander.heal(potion);
	Charmander.heal(super_potion);
	
	//show Pokemon's hit points after simple healing
		cout << "Charmander has " << Charmander.get_hit_points() << " hit points." << endl;
	
	
	
	return 0;
}