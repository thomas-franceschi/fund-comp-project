#include <iostream>
#include "pokemon.h"

using namespace std;

Pokemon::Pokemon(string n, int hp, int att, int def, int sp_att, int sp_def, int sp, int lev ) {
	if ( hp < 0 ) hp = 0;
	if (att < 0 ) att = 0;
	if ( def < 0 ) def = 0;
	if ( sp_att < 0 ) sp_att = 0;
	if ( sp_def < 0 ) sp_def = 0;
	if ( sp < 0 ) sp = 0;
	if (lev < 2 ) lev = 2;
	
	name = n; 
	hit_points = hp;
	attack = att;
	defense = def;
	special_attack = sp_att;
	special_defense = sp_def;
	speed = sp;
	level = lev;
	
}

//Battle function returns 1 for a win and 0 for a loss
int Pokemon::battle ( Pokemon opponent ) {
	int move = 1;
	
	while (hit_points > 0 && opponent.get_hit_points() > 0 ) {
		//switch between attacking and defending 
		move = move * -1;
		if(move = 1) {
			make_attack(opponent);
		}
		
		else {
			defend(opponent);
		}
	}
	
	//Check to see if your pokemon won, return 1 for winning 0 for loss
	if (hit_points > 0) return 1;
	
	return 0;
	
}

void Pokemon::make_attack( Pokemon opponent ) {
	
}

void Pokemon::defend( Pokemon opponent ) {
	
}

//This function takes the inputted type of Potion (which is an object) 
//and increases Pokemon health by that amount of healing
void Pokemon::heal(Potion healing_type) {
	
	hit_points = hit_points + healing_type.get_healing_power();  
	
	//Make sure hit_points does not go over max amount
	if ( hit_points > 200 ) hit_points = 200;
	
}


//retrieves number of hit_points
int Pokemon::get_hit_points () {
	return (hit_points);
}


//Checks pokemon to see if it should faint, evolve etc. 
void Pokemon::check_pokemon(){
	//check level and compare to evolve level
	if (level != 100 && level >= evolve_level) {
		evolve();
	}
}

//Sends pokemon to the next level 
void Pokemon::evolve(){
	
}