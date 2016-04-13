#include <iostream>
#include "firetype.h"

using namespace std;

//Default constructor
Firetype::Firetype(string n, int hp, int att, int def, int lev, int ev_lev, int str, int wk) : Pokemon (n, hp, att, def, lev, ev_lev ) {
	strengths = str;
	weaknesses = wk;
}