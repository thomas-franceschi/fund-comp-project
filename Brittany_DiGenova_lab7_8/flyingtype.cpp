#include <iostream>
#include "flyingtype.h"
#include "pokemon.h"

using namespace std;

//Default constructor
Flyingtype::Flyingtype(string n, int hp, int att, int def, int sp_att, int sp_def, int sp, int lev, int str, int wk) : Pokemon (n, hp, att, def, sp_att, sp_def, sp, lev ) {
	strengths = str;
	weaknesses = wk;
}