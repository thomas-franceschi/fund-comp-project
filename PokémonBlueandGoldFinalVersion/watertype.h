//Brittany DiGenova
//watertype.h
//This is the base class for watertype pokemon, inheriting pokemon.h

#include <iostream> 
#include "pokemon.h"

using namespace std;

class Watertype : public Pokemon {
	
	public:
	Watertype( string name = "none", int max_hit_points = 75, int hit_points = 45, int attack = 45, int defense = 50, int level = 3, int evolve_level = 12, int exp = 10, int strengths = 0, int weaknesses = 0 );
	
	private:
	int strengths;	//Types of pokemon fights well against
	int weaknesses;	//Types of pokemon week against 
};
