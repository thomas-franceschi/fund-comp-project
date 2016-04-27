#include <iostream>
#include "flyingtype.h"
#include "pokemon.h"

using namespace std;

//Default constructor
Flyingtype::Flyingtype(string n, int max_hp, int hp, int att, int def, int lev, int ev_lev, int ex, int str, int wk) : Pokemon (n, max_hp, hp, att, def, lev, ev_lev, ex ) {
	strengths = str;
	weaknesses = wk;
}