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
	Firetype Charmander("Charmander", 39, 52, 43, 60, 50, 65, 2, 0, 0); //No strengths or weaknesses yet 
	Firetype Ponyta("Ponyta", 50, 85, 55, 65, 65, 90, 11, 0 , 0);
	Firetype Magby("Magby", 45, 75, 37, 70, 55, 83, 6, 0, 0);
	Firetype Flareon("Flareon", 65, 130, 60, 95, 110, 65, 35, 0, 0);
	Firetype Torchic("Torchic", 45,60, 40, 70, 50, 45, 7, 0, 0);
	
	//Initialize watertype pokemon 
	Watertype Squirtle("Squirtle", 44, 48, 65, 50, 64, 43, 4, 0, 0 );
	Watertype Horsea("Horsea", 30, 40, 70, 70, 25, 60, 7, 0, 0);
	Watertype Palpitoad("Tympole", 50, 50, 40, 50, 40, 64, 9, 0, 0);
	Watertype Mantyke("Mantyke", 45, 20, 50, 60, 120, 50, 7, 0, 0 );
	Watertype Spheal ("Spheal", 70, 40, 50, 55, 50, 25, 4, 0, 0 );
	
	//Initialize Flyingtype Pokemon
	Flyingtype Caterpie("Caterpie", 45, 30, 35, 20, 20, 45, 2, 0, 0);
	Flyingtype Zapdos;
	Flyingtype Pidgey;
	Flyingtype Zubat;
	Flyingtype Spearow;
	Flyingtype Dragonite;
	
	//Make kyle, thomas and brittany Pokemon
	Watertype Kyle("Kyle (AKA Whale)", 52, 60, 55, 61, 64, 80, 5, 0, 0); //No strengths or weaknesses yet
	Firetype Thomas("Tbone", 55, 58, 64, 61, 70, 74, 5, 0, 0);
	Flyingtype Brittany("Britters", 60, 54, 61, 63, 62, 40, 5, 0, 0);
	
	Potion potion("potion", 20);
	Potion super_potion ("super_potion", 50);
	
	//show Pokemon's hit points before simple healing
	cout << "Charmander has " << Charmander.get_hit_points() << " hit points." << endl;
	
	//heal Pokemon
	Charmander.heal(potion);
	Charmander.heal(super_potion);
	
	//show Pokemon's hit points after simple healing
		cout << "Charmander has " << Charmander.get_hit_points() << " hit points." << endl;
	
	
	
	return 0;
}