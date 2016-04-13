//Brittany DiGenova
//flyingtype.h
//This is the base class for airtype pokemon, inheriting pokemon.h

#include <iostream> 
#include "pokemon.h"

using namespace std;

class Flyingtype : public Pokemon {
	
	public:
	Flyingtype( string name = "none", int hit_points = 45, int attack = 45, int defense = 50, int special_attack = 55, int special_defense = 55, int speed = 50, int level = 3, int strengths = 0, int weaknesses = 0 );
	
	private:
	int strengths;
	int weaknesses;
};

