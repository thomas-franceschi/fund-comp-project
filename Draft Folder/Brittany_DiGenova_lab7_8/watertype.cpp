#include <iostream>
#include "watertype.h"

using namespace std;

//Default constructor
Watertype::Watertype(string n, int max_hp, int hp, int att, int def, int lev, int ev_lev, int ex, int str, int wk) : Pokemon (n, max_hp, hp, att, def, lev, ev_lev, ex ) {
	strengths = str;
	weaknesses = wk;
}