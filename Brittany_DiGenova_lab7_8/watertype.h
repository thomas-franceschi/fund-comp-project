//Brittany DiGenova
//watertype.h
//This is the base class for watertype pokemon, inheriting pokemon.h

#include <iostream> 
#include "pokemon.h"

using namespace std;

class Watertype : public Pokemon {
	
	public:
	Watertype(string name = "none", int hit_points = 0, int attack = 0, int defense = 0, int special_attack = 0, int special_defense = 0, int speed = 0, int level = 2, int strengths = 0, int weaknesses = 0);
	
	private:
	int strengths;
	int weaknesses;	
};
